## Homework 1

### C Exercises

Modify the link below so it points to the `ex01` directory in your
student repository.

[Here is a link to the ex01 directory in my repository](https://github.com/iblancett/ExercisesInC/tree/master/exercises/ex01)

### Think OS Chapter 1 reading questions

For each of the reading questions below, write answers in the form of
a clear, concise, complete sentence or two.

1) Give an example of a feature common in interpreted languages that is rare in compiled languages.
Dynamic types are common in interpreted languages, while compiled languages try to limit types to static.

2) Name two advantages of static typing over dynamic typing.
Static type checks happen before the program starts, so static errors are found quicker than dynamic type errors.
Static types save space because their variables don't have to be accessible during run time.

3) Give an example of a static semantic error.
A function call that does not provide enough arguments

4) What are two reasons you might want to turn off code optimization?
You are currently working on the code and want to catch bugs that may disappear with optimization.
You are debugging the code and want it to run as is to observe behavior and/or errors.


5) When you run `gcc` with `-S`, why might the results look different on different computers?
Assembly code is machine-readable code, so machines with different architecture may not have the same output.

6) If you spell a variable name wrong, or if you spell a function name wrong, the error messages you get might look very different.  Why?
If the function is from one of the standard libraries, an error may be part of the linking process.
A misspelled variable name would show up as a syntax error.

7) What is a segmentation fault?
If you try to read or write an incorrect location in memory.
