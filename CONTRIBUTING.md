# How To Contribute
If you want to ask a question or give suggestions, please open an Issue in the Github 
project. If you would like to contribute code, please fork the project, create a new 
branch and then create a Pull Request.

I am working on this on the side from my day job so I may be slow to communicate, please 
be patient.

## Submitting Changes
Please follow our coding conventions (below) and make sure all of your commits are atomic (one feature per commit). 
Send a Github Pull Request with a clear list of what you have done, always write a clear log message for your commits. 

## Coding Conventions
I am following this [C++ Best Practices](https://lefticus.gitbooks.io/cpp-best-practices/content/03-Style.html) 
coding style guide. There is a '.clang-format' file in the project to help with a consistent coding style.  I am also using Clang-Tidy for linting. 

Specific Details:
* Indentation is 4 spaces
* A light amount of code comments, mostly to document functionality that is not obvious by reading
  the code
* We ALWAYS put spaces after list items and method parameters ([1, 2, 3], not [1,2,3]), around
  operators (x += 1, not x+=1), and around hash arrows.
* Please make code readable for other people
