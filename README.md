[![Build Status](https://api.travis-ci.org/mariusfeteanu/cci.svg?branch=master)](https://travis-ci.org/mariusfeteanu/cci)

# Cracking the Coding Interview (in C)

Solutions for [Cracking the Coding Interview](http://www.amazon.com/Cracking-Coding-Interview-6th-Edition/dp/0984782850) in the C programming language.

## Pre-requisites
1. A POSIX compatible OS.
2. A c compiler.
3. GNU Make

## How to build and test

`make`

## Description

All of these were written by my in order improve my coding and interview skills. No guarantee is made these are correct in any way, see also the [license](LICENSE).

All code is compiled using C11 and all warnings are considered errors. Tests are included in each file and executed automatically.

This is tested with gcc on linux.

Library use is kept to a minimum. Even standard library functions are only used when not part of the specified problem, and if they would not modify the time or space complexity of the solution.

The C style was kept as idiomatic as I can. Performance and readability are both equal concerns and I have tried to strike a balance between the two.

## Repo structure

Everything goes in the root. No problem numbers are included as these might change in different version of the book. No problem text was included, consult the book if you need it.

Each file is prefixed with the concept or data structure it applies to.

Helper code goes into the `common` directory. These get compiled separately but they also have tests.
