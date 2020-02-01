1. Function pointers, Function Objects or Functors and Lambda Closures
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
2. STL
    1.  https://www.topcoder.com/community/data-science/data-science-tutorials/power-up-c-with-the-standard-template-library-part-1/
    2.  https://www.topcoder.com/community/data-science/data-science-tutorials/power-up-c-with-the-standard-template-library-part-2/
3.  [Auto and Decltype](https://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html)

