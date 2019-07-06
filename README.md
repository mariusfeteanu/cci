[![Build Status](https://api.travis-ci.org/mariusfeteanu/cci.svg?branch=master)](https://travis-ci.org/mariusfeteanu/cci)

# Cracking the Coding Interview

Solutions for [Cracking the Coding Interview](http://www.amazon.com/Cracking-Coding-Interview-6th-Edition/dp/0984782850) in the C programming language.

## Pre-requisites
1. A POSIX compatible OS.
2. A c compiler.
3. GNU Make

## How to build and test

`make`

## Description

All of these were written by my in order improve my coding and interview skills. No guarantee is made these are correct in any way, see also the [license](LICENSE).

All code is compiled using C11 and no warnings. Tests are included in each fileand executed automatically.

This is tested with gcc and clang on linux and osx.

Library use is kept to a minimum. Even standard library functions are only usedwhen not part of the specified problem, and if they would not modify the time or space complexity of the algo.

The C style was kept as idiomatic as I can. Performance and readability are both equal concerns and I have tried to strike a balance between the two.

## Repo structure

Everything goes in the root. No problem numbers are included as these might change. No problem text was included, consult the book if you need it.

Each file is prefix with the concept or data structure they work on.

Some (like matrix) are just helper code. These are included when needed using the pre-processor, just to keep the makefile simple.
