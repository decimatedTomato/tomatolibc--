Nice start to an implementation of smart pointers

- No special templatization for array types
- No deleter optional template parameter
	- c++20 no_unique_address optimization
	- pre-c++20 Emtpy Base Optimization
- Type erased deleter for shared_ptr
- The weak_ptr is unimplemented
