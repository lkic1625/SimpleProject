cmake_minimum_required(VERSION 3.17)
project(SimpleProject)

set(CMAKE_CXX_STANDARD 17)



add_executable(SimpleProject
        algorithm_pr/BAEK15956.cpp algorithm_pr/LEET-maximum-value-of-k-coins-from-piles.cpp algorithm_pr/minimum-initial-energy-to-finish-tasks.cpp)
