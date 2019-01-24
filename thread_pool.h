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

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

#include "default_decs.h"

#ifndef _qlib_thread_pool_h_included
#define _qlib_thread_pool_h_included

namespace qlib {

/**
 * \brief A simple worker thread pool implementation, written using pure
 * standard C++
 *
 * This work is based on Jakob Progsch's excellent example, which may be
 * found at https://github.com/progschj/ThreadPool.
 *
 * \todo Add basic usage example
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
            std::size_t num_threads = std::thread::harware_concurrency()) :
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
                        std::unique_lock<std::mutex> tasks_lck(m_tasks_mtx);
                        m_tasks_cv.wait(
                            tasks_lck
                            , [this](void)
                            {
                                return m_stop || (!this->m_tasks.empty());
                            });

                        if (m_stop && tasks.empty()) return;

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
        std::unique_lock<std::mutex> tasks_lck(m_tasks_mtx);
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
     */
    template <typename F, typename... Args>
    auto enqueue(F&& fn, Args&&... args)
    {

        // Package the task for executing
        using return_t = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_t(void)> >(
            std::bind(std::forward<F>(fn), std::forward<Args>(args)...));

        std::future<return_t> result = task->get_future();

        // Place the task in the queue and notify a sleeping thread
        std::unique_lock<std::mutex> tasks_lck(m_tasks_mtx);

        if (m_stop)
            throw std::runtime_error(
                "attempt to enqueue on stopped thread pool");

        tasks.emplace([task](void){ (*task)(); });

        tasks_lck.unlock();

        m_tasks_cv.notify_one();
        return result;
    }   // end enqueue method

    private:

    /**
     * \brief The collection of thread objects
     */
    std::vector<std::thread> m_workers;

    /**
     * \brief The queue of tasks
     */
    std::queue<std::function<void(void)> > m_tasks;

    /**
     * \brief Mutex for synchronising task queue access
     */
    std::mutex m_tasks_mtx;

    /**
     * \brief Condition variable for monitoring tasks queue status
     */
    std::condition_variable m_tasks_cv;

    /**
     * \brief Flag to signal that thread pool is being shut down
     */
    bool m_stop;

};  // end thread_pool class

}   // end qlib namespace

#endif
