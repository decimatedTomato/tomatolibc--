Nice start to an implementation of smart pointers

- The factory methods do not take universal references
	- this leads to unnecessary copies in this case
- No special templatization for array types
- No deleter optional template parameter
	- c++20 no_unique_address optimization
	- pre-c++20 Emtpy Base Optimization
- The shared_ptr reference count is not thread safe
- Type erased deleter for shared_ptr
- The weak_ptr is unimplemented

