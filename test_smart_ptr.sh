#!/bin/bash

set -xe

CXXFLAGS="-std=c++20 -Werror -Wall -Wextra -pedantic"

g++ test/test_unique_ptr.cpp -o bin/test_unique_ptr -Isrc "$CXXFLAGS"
bin/test_unique_ptr
g++ test/test_shared_ptr.cpp -o bin/test_shared_ptr -Isrc "$CXXFLAGS"
bin/test_shared_ptr
g++ test/test_weak_ptr.cpp -o bin/test_weak_ptr -Isrc "$CXXFLAGS"
bin/test_weak_ptr
echo "Success!"