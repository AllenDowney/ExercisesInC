# Exercise 2.5

### C strings

The goal of this exercise is to give you more practice in C, and
practice using C libraries.

C provides a basic string type in the form of character
arrays/pointers, and string.h provides a set of basic string
manipulation functions.  In addition, there are many libraries that
provide strings types with additional features.  You can read about
some of them [here](http://www.and.org/vstr/comparison).

1) In this directory you should find `find_track.c`, which is a
version of the code from Chapter 2.5 of *Head First C*, with a little
cleanup.  Compile and run it.

If you read the code, you'll see a function named `find_track_regex`
that is mostly empty.  Your job is to fill it in.

2) `regex.h` provides functions for performing regular expression
matching on strings.  Read [the
documentation](http://pubs.opengroup.org/onlinepubs/7908799/xsh/regex.h.html)
and search for examples.

Fill in the body of `find_track_regex` and modify `main` to test it.
For example, the regular expression `[A-F]` should match any track
that contains one of the capital letters `A`-`F`.

3) Check your code quality:

*  If you call a library function that might return an error code, check the return value.  In case of an error, print an appropriate message and `exit(1)`.

*  If you call `regcomp`, you should call `regfree` when you are done.

*  As always, every function should have a function-level comment that explains what it does, but not how.  Additional comments inside the function should explain anything non-obvious about how the function works.

4) Push your modified file back to the repo.


### BigInt

In this directory you should find `bigint.c`, which contains an implementation
of a `BigInt` type ([arbitrary size integers](https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic)).  Open the file, read the instructions at
the top, and do what they say.

Then push your modified file back to the repo.

Optional challenge problem: Implement `multiply_bigint`!
