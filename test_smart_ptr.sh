#!/bin/bash

set -xe
g++ test/test_unique_ptr.cpp -o bin/test_unique_ptr -Isrc -Wall -Wextra -pedantic
bin/test_unique_ptr
g++ test/test_shared_ptr.cpp -o bin/test_shared_ptr -Isrc -Wall -Wextra -pedantic
bin/test_shared_ptr
g++ test/test_weak_ptr.cpp -o bin/test_weak_ptr -Isrc -Wall -Wextra -pedantic
bin/test_weak_ptr
echo "Success!"