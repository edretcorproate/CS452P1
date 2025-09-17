Project 1 - Testing a Circular Linked list with a Sentinel Node

    Name: Emanuel Dretcanu
    Email: emidretcanu@u.boisestate.edu
    Class: 452-001

Known Bugs or Issues

From what I can tell there are no issues. I've tested this with a main.c fil as well. So, everything looks like its working and the tests that are ran covers 100% of the code. And well you can just look at the report and see that for yourself.

Experience

If you need a much more in depth description of how these functions operate you can always contact me and I will discuss this even further. But the documentation is not really meant to explain the codes 100%, there are basic assumptions that when you read it you have to take mental notes on how it was designed rather than these function descriptions being explicit. Other than that, it is pretty straight forward for those who are familiar with Singular Linked Lists

I did find it interesting on both the fact that this is circular and the fact that it contains a Sentinel node. The sentinel node doesn't really add to the complexity and neither does the circle implementation (as it is just pointing to the head rather than a null). Same with the Sentinel, as this became the head esentially.

So over all the experience wasn't a horrible one or nightmarish, which most of my coding experience here at BSU can be described as. But it is all worth it for the degree that I plan on getting this semester.

Fixed the coverage using gcov/lcov to ignore specific memory failure lines that cannot be easily tested.

Project 2 - Multithreading without locking

    Name: Emi Dretcanu
    Email: emidretcanu@u.boisestate.edu
    Class: 452-001

Known Bugs or Issues

No known issues. All tests pass and code coverage is 100% for the core list implementation. Memory allocation failure paths are excluded from coverage as they cannot be reliably tested. If any issues are discovered, they will be documented here.

Experience

This project provided valuable experience with both data structures and multithreading in C. For the circular linked list, the main challenge was ensuring correct handling of the sentinel node and edge cases for insertion, removal, and traversal. Writing comprehensive tests and achieving 100% code coverage helped uncover subtle bugs and improved confidence in the implementation.

For the multithreading portion, orchestrating threads without explicit locking required careful design to avoid race conditions, especially when merging and sorting data. Debugging memory management and ensuring no leaks or double-frees was also a key focus. Using code coverage tools (gcov/lcov) was instrumental in identifying untested paths, particularly for error handling.

Overall, the project reinforced the importance of thorough testing, clear code structure, and defensive programming in C. The process was challenging but rewarding, and the final result is robust and well-tested code.