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
    sh "conan install .. --build=missing"
    Dir.chdir ".."
end

desc "run cmake to produce platform-specific build files"
task :cmake => :conan do
    Dir.chdir "build"
    sh "cmake .."
    Dir.chdir ".."
end

desc "build binaries"
task :bin => :cmake do    
    Dir.chdir "build"

    sh "cmake --build . --config Release"

    Dir.chdir ".."
end

desc "run test suite"
task :test => :bin do
    sh "build/bin/test-#{$project_name}"
end

directory "build/docs"

desc "build doxygen docs"
task :docs => "build/docs" do
    sh "doxygen"
end

desc "build tests, run tests and build docs"
task :all => [:bin, :test, :docs]

task :default => :all

# Retrieve the location a conan dependency
def get_location(dep)

    cmd_str = "conan info #{dep} " +
        "--paths --only package_folder " +
        ""

    resp_str = `#{cmd_str}`

    resp_str.lines.each do |line|
        return line.split(": ")[1].strip if line.include?("package_folder")
    end

end

namespace :loc do

    desc "retrieve location of Boost library (from conan)"
    task :boost do
        puts get_location("boost/1.69.0@conan/stable")
    end

    desc "retrieve location of fmr library (from conan)"
    task :fmt do
        puts get_location("fmt/5.3.0@bincrafters/stable")
    end

    desc "retrieve location of Catch2 library (from conan)"
    task :catch2 do
        puts get_location("Catch2/2.7.0@catchorg/stable")
    end

end
