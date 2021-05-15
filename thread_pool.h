/**
 * \file thread_pool.h
 * Simple Modern C++ thread pool implementation
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <functional>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>

#include "default_decs.h"
#include "thread.h"

#ifndef _qlib_thread_pool_h_included
#define _qlib_thread_pool_h_included

namespace qlib {

/**
 * \brief A simple worker thread pool implementation, written using pure
 * standard C++
 *
 * This class implements a lightweight worker thread pool, using std::thread.
 * Tasks may be any callable object (lambda, or whatever), and are passed to
 * the `enqueue` method, which packages them as tasks, and places them on the
 * internal execution queue, and yields a `std::future` object, which can be
 * used to access the result.
 *
 * Internally, worker threads sleep until a task is enqueued, upon which,
 * one thread awakens to process thet ask. The thread pool destructor awakens
 * all the threads and joins them before exiting.
 *
 * This work is based on Jakob Progsch's excellent example, which may be
 * found at https://github.com/progschj/ThreadPool.
 *
 * \par Example Usage
 *
 * \code
 * qlib::thread_pool tp;    // Number of threads equal to hardware
 *                          // concurrrency
 *
 * // Put some tasks in the queue for the thread pool to execute
 * // The first one sets an external falg
 * bool test_flag = false;
 * auto result1 = tp.enqueue([&test_flag]() { test_flag = true; });
 *     // result1 is type qlib::future<void>
 *
 * // The second task takes no arguments, but returns a result
 * auto result2 = tp.enqueue([]() { return std::string("abc"); });
 *     // result2 is type qlib::future<std::string>
 *
 * // This task uses a predefined lambda that adds two integers. Note that
 * // the call to enqueue the task takes the arguments as well.
 * auto my_fn = [](int a, int b) { return a+b; };
 * auto result3 = tp.enqueue(my_fn, 2, 3);
 *     // result3 is type qlib::future<int>
 *
 * // This task throws an exception!
 * auto result4 = tp.enqueue([]() { throw std::runtime_error("test"); });
 *     // result4 is type qlib::future<void>
 *
 * // Four tasks now being executed...
 *
 * result1.get();
 * // test_flag is now true
 *
 * // Prints "abc - 5" to the console
 * std::cout << result2.get() << " - " << result3.get() << std::endl;
 *
 * // This line re-throws the std::runtime_error that was thrown in the
 * // task.
 * result4.get();
 * \endcode
 *
 * \todo Continuations have not been tested with the new Boost futures
 */
class thread_pool final
{

    DECLARE_NO_COPY_SEMANTICS(thread_pool);
    DECLARE_DEFAULT_MOVE_SEMANTICS(thread_pool);

    public:

    /**
     * \brief Constructor - initialises all attributes and constructs the
     * thread pool
     *
     * \param num_threads The number of threads to create in the pool
     * (defaults to the available hardware concurrency)
     */
    explicit thread_pool(
            std::size_t num_threads = thread::hardware_concurrency()) :
        m_workers()
        , m_tasks()
        , m_tasks_mtx()
        , m_tasks_cv()
        , m_stop(false)
    {

        // Build the pool of threads that each sit in a loop, waiting for a
        // task to be available in the queue, or the stop flag to be raised.
        // When tasks are available, it popped and executed.
        for (std::size_t i = 0; i < num_threads; i++)
            m_workers.emplace_back(
                [this](void)
                {
                    while (true)
                    {
                        std::function<void(void)> task;

                        // Wait until there is a task, or 'stop' has been
                        // raised.
                        lock tasks_lck(m_tasks_mtx);
                        m_tasks_cv.wait(
                            tasks_lck
                            , [this](void)
                            {
                                return m_stop || (!this->m_tasks.empty());
                            });

                        if (m_stop && m_tasks.empty()) return;

                        task = std::move(m_tasks.front());
                        m_tasks.pop();

                        tasks_lck.unlock();

                        task();
                    }   // end infinite loop
                });

    }   // end constructor

    /**
     * \brief Destructor, shutting down the thread pool
     *
     * This method raises the `stop` flag, and then joins all the threads.
     */
    ~thread_pool(void)
    {
        lock tasks_lck(m_tasks_mtx);
        m_stop = true;
        tasks_lck.unlock();

        m_tasks_cv.notify_all();
        for (auto& w : m_workers) w.join();
    }

    /**
     * \brief Enqueue a new task
     *
     * This method packages up the given function and its arguments into a
     * `std::packaged_task` object, from which a future is then derived. This
     * is then placed in a lambda for the execution queue.
     *
     * \tparam F The type of the function to be enqueued
     *
     * \tparam Args The types of the arguments to the function
     *
     * \param fn The callable object to enqueued
     *
     * \param args The arguments to the enqueued function
     *
     * \return A `future` object that can be used to obtain the result of
     * `fn`, or access any exception thrown
     */
    template <typename F, typename... Args>
    auto enqueue(F&& fn, Args&&... args)
    {

        // Package the task for executing
        using return_t = typename std::invoke_result<F, Args...>::type;

        auto task = std::make_shared<packaged_task<return_t> >(
            std::bind(std::forward<F>(fn), std::forward<Args>(args)...));

        future<return_t> result = task->get_future();

        // Place the task in the queue and notify a sleeping thread
        lock tasks_lck(m_tasks_mtx);

        if (m_stop)
            throw std::runtime_error(
                "attempt to enqueue on stopped thread pool");

        m_tasks.emplace([task](void){ (*task)(); });

        tasks_lck.unlock();

        m_tasks_cv.notify_one();
        return result;
    }   // end enqueue method

    private:

    /**
     * \brief The collection of thread objects
     */
    std::vector<thread> m_workers;

    /**
     * \brief The queue of tasks
     */
    std::queue<std::function<void(void)> > m_tasks;

    /**
     * \brief Mutex for synchronising task queue access
     */
    mutex m_tasks_mtx;

    /**
     * \brief Condition variable for monitoring tasks queue status
     */
    condition_variable m_tasks_cv;

    /**
     * \brief Flag to signal that thread pool is being shut down
     */
    bool m_stop;

};  // end thread_pool class

}   // end qlib namespace

#endif
