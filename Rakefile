# Rakefile for basic Dev tasks in qLib
#
# Note that qLib is a header-only library - these build tasks are just for
# test suite, and for building documentation.
#
# Copyright Igor Siemienowicz 2018
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)

# --- Config ---

$project_name = "qlib"

# --- End Config ---

directory "build"

desc "clean all build artefacts"
task :clean do
    FileUtils.rm_rf "build"
end

desc "run conan to install / generate dependencies"
task :conan => "build" do
    Dir.chdir "build"
    sh "conan install .."
    Dir.chdir ".."
end

desc "run cmake to produce platform-specific build files"
task :cmake => :conan do
    Dir.chdir "build"

    cmake_cmd = "cmake " +
                "-DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake "

    cmake_cmd += "-G \"Visual Studio 15 2017 Win64\" " \
        if Rake::Win32::windows?

    cmake_cmd += ".."

    sh cmake_cmd

    Dir.chdir ".."
end

desc "build binaries"
task :bin => :cmake do    
    Dir.chdir "build"

    make_cmd = "make -j8"

    make_cmd =
            "msbuild /m #{$project_name}.sln " +
            "/p:Configuration=Release " +
            "/p:Platform=\"x64\" " +
            "" if Rake::Win32::windows?

    sh make_cmd

    Dir.chdir ".."
end

desc "run test suite"
task :test => :bin do
    test_cmd = "build"
    test_cmd += "/Release" if Rake::Win32::windows?
    test_cmd += "/test-qlib"

    sh test_cmd
end


directory "build/docs"

desc "build doxygen docs"
task :docs => "build/docs" do
    sh "doxygen"
end
