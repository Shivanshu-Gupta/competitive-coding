1. [Modern C++ Features Compilation - C\++11, C\++14, C\++17, C\++20](https://github.com/AnthonyCalandra/modern-cpp-features)
2. Function pointers, Function Objects or Functors and Lambda Closures
    1. www.cprogramming.com
        1. [C/C\++ Function Pointers](https://www.cprogramming.com/tutorial/function-pointers.html) 
            - allow passing around instructions
            - allow more flexible functions and libraries
            - may use virtual functions (polymorphism) instead. But comes at the cost of having to define classes.
        2. [C++ Function Objects or Functors](https://www.cprogramming.com/tutorial/functors-function-objects-in-c++.html) 
            - the functor class may contain state
            - the functor object may be as a regular function
            - possible because c++ allows operator () to be overloaded
                - overloading possible
            - can be inlined by compiler
            - unlike virtual functions, may be used interchangeably with function pointer as arguments to a templated function
        3. **[C++\-11 lambda closures](https://www.cprogramming.com/c++11/c++11-lambda-closures.html)**
            - using a template allows us to ignore the differences between functors, function pointers and lambda closures
            - alternatively use [std::function](http://www.cplusplus.com/reference/functional/function/function/)
            - don't use capture by reference if returning a lamba function from a function as the reference will not be valid after the function returns
            -  [Herb Sutter's video lecture and slides](https://nwcpp.org/may-2011.html) for more detail on Lambdas
    2. [Clockwise Spiral Rule](http://c-faq.com/decl/spiral.anderson.html)
    3. https://www.quantstart.com/articles/Function-Objects-Functors-in-C-Part-1 
    3. http://www.cplusplus.com/reference/functional/function/function/ 
3. STL
    1.  https://www.topcoder.com/community/data-science/data-science-tutorials/power-up-c-with-the-standard-template-library-part-1/
    2.  https://www.topcoder.com/community/data-science/data-science-tutorials/power-up-c-with-the-standard-template-library-part-2/
    3.  [Great chart of member functions in each container.](http://www.cplusplus.com/reference/stl/)
    4. Useful C++ standard library
        1. [tuple](http://www.cplusplus.com/reference/tuple/tuple/)
        2. string
        3. multiset, multimap
        4. deque
4.  [Different types of Iterators](http://www.cplusplus.com/reference/iterator/)
5.  [Auto and Decltype](https://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html)
6.  Hashing
    1. [Types Don't Know #](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3980.html)
    2. [FNV Hash](http://www.isthe.com/chongo/tech/comp/fnv/index.html)
7. [Tuple and tie tricks](http://bajamircea.github.io/coding/cpp/2017/03/10/std-tie.html)

