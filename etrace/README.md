Run-time function call tree with gcc
====================================

(c) 1998

# etrace: A run-time tracing tool

## Description

These source files provide a simple but efficient utility that allows the
display of a function call tree in a C program at run-time. It is also
possible to dump the results of a program execution to an ASCII file for
later examination.

- Link `ptrace.c` against your code to enable run-time tracing.
- `etrace` is a Python script that will perform the run-time tracing by displaying the function names as they are called
- `etrace.pl` is a Perl script that will perform the run-time tracing by displaying the function names as they are called. Moreover, `etrace.pl` can be used to trace dynamic libraries.

## License

Public domain.

## Pre-requisites

- gcc version 2.95 or later
- The presence of the `nm` utility on your machine, with a BSD-compatible output
- Python 1.5 or later for `etrace` and Perl for `etrace.pl`


## Portability

This code is known to run under Linux, FreeBSD, Solaris, and HPUX.


## Example

There is an example in the `example/` sub-dir. To compile it, run `make`.

You should now have an executable called _crumble_. Running it should give
you a recipe for an apple crumble, with 1-second pauses between sentences.
Now let's get to this function call tree:

To get the tree at run-time, open two terminals.
In the first terminal:

	cd etrace/example
	../src/etrace crumble

In the second terminal:

	cd etrace/example
	crumble

Both shells need to run in the same directory. Data are exchanged between
the running process you are trying to monitor and the `etrace` script
through a named pipe in this directory.

You should see this:

    main 
    |   Crumble_make_apple_crumble 
    |   |   Crumble_buy_stuff 
    |   |   |   Crumble_buy 
    |   |   |   Crumble_buy (total: 5 times) 
    |   |   Crumble_prepare_apples 
    |   |   |   Crumble_skin_and_dice 
    |   |   Crumble_mix 
    |   |   Crumble_finalize 
    |   |   |   Crumble_put 
    |   |   |   Crumble_put (total: 2 times) 
    |   |   Crumble_cook 
    |   |   |   Crumble_put 
    |   |   |   Crumble_bake

To get the tree into a file for later use, do the following:

	cd etrace/example
	touch TRACE
	crumble
	../src/etrace crumble &gt; log

The trace has been saved to a file called `log` in the current directory.


## Another example using etrace.pl

There is an example in the example/ sub-dir. Compile it with `make`.

You should now have an executable called _crumble_. Running it should give
you a recipe for an apple crumble, with 1-second pauses between sentences.
Now let's get to this function call tree:

To get the tree at run-time, open two terminals.
In the first terminal:

	cd etrace/example
	../src/etrace.pl crumble

In the second terminal:

	cd etrace/example
	crumble

Both terminals need to be in the same directory. Data are exchanged between
the running process you are trying to monitor and the 'etrace' script
through a named pipe in this directory.

You should see this:

    \-- main
    |   \-- Crumble_make_apple_crumble
    |   |   \-- Crumble_buy_stuff
    |   |   |   \-- Crumble_buy
    |   |   |   \-- Crumble_buy
    |   |   |   \-- Crumble_buy
    |   |   |   \-- Crumble_buy
    |   |   |   \-- Crumble_buy
    |   |   \-- Crumble_prepare_apples
    |   |   |   \-- Crumble_skin_and_dice
    |   |   \-- Crumble_mix
    |   |   \-- Crumble_finalize
    |   |   |   \-- Crumble_put
    |   |   |   \-- Crumble_put
    |   |   \-- Crumble_cook
    |   |   |   \-- Crumble_put
    |   |   |   \-- Crumble_bake

To get the tree into a file for later use, you can do the following:

	cd etrace/example
	touch TRACE
	crumble
	../src/etrace.pl crumble &gt; log

or

	cd etrace/example
	touch TRACE
	crumble
	../src/etrace.pl crumble TRACE &gt; log

Either way, the trace has been saved to a file called `log` in the current directory.

To see how to modify `ptrace.c` to work with a dynamic library, look at
the example2 directory. The sources there also create a stand-alone
executable, but the `PTRACE_REFERENCE_FUNCTION` macro is defined just as
it would be for a dynamic library.

## How does it work?

gcc 2.95 has a nifty feature called _instrument-functions_, that adds a
couple of function calls to all functions in your code. Every time a
function starts, a function called `__cyg_profile_func_enter()` is called,
and every time a function exits, a function called
`__cyg_profile_func_exit()` is called.

The code in ptrace.c simply redirects the information gathered at each call
to a text file.

Now, if you examine closely what you get from this output, you will see
that only the binary addresses of functions are printed out. To make the
link to true function names, you need to interpret the binary and make the
list of associations. There are many ways of doing this, and to be truly
platform-independent you should have a look at the BFD library from the GNU
project.

etrace implements a much simpler (but of course much less portable)
solution by using the 'nm' utility to dump a list of all defined symbols
and associated addresses. The link between them and the pretty printing as
a function call tree is all done in the 'etrace' script.

etrace.pl works in a manner similarly to etrace. Up to output
pretty-printing, it works the same as etrace on stand-alone
programs. If the first line of the TRACE file is marked "REFERENCE",
however, it uses the values provided to calculate where the reference
function actually resides in memory, and compares the difference
between that address and the address in the symbol table; this offset
is then applied to all the function addresses in the trace. This
feature is enabled by defining the PTRACE_REFERENCE_FUNCTION in
ptrace.c and is essential to correctly map the function names when
tracing a dynamic library (this feature is optional for stand-alone
programs).


## ptrace/etrace usage

The ptrace.c module will look for a file called "TRACE" in the current
directory. If no such file can be found, nothing will be logged. You still
get the penalty associated to the two function calls but nothing else
changes.

If a TRACE file can be found, log data will be appended to it.

The idea is to make the TRACE file a fifo so that another process can read
from it and display the informations at run-time. This is exactly what the
'etrace' script does. You do not have to create the fifo yourself, one will
be created upon startup of 'etrace', and will be deleted afterwards.

'etrace' needs to know the name of the executable you are trying to trace,
to retrieve the symbols (with 'nm'). This is the only argument to the
script.

'etrace.pl' takes two arguments. The first argument, which is
mandatory, is either the name of the executable you want to trace, or
the name of the symbol file (produced by nm) of the executable you
want to trace. The second argument, which is optional, is either the
name of the trace file produced by ptrace (if you want to see the
function calls after the program has finished running) or the name to
use for the FIFO (in which case you will need to make sure ptrace.c
writes to a file with that same name).


## How to use it in your code

To trace a stand-alone program, there is no need to #include any
additional file. Just link your code against ptrace.c and use the
-finstrument-functions option as a compile option for gcc. This should
do it.

Now when you want to trace at run-time (handy to see where the code breaks
in case of segfault), open two terminals. Launch first 'etrace myprogram'
in one terminal, and 'myprogram' in the other. Remember both need to be in
the same directory for the magic to work.

If you want to log the trace to a file, create an empty file called TRACE
in the current directory, launch your program, and examine the results
using 'etrace myprogram'.

If you want to trace a library, you need to provide ptrace.c with the
name of a reference function. The name and address of this function,
once loaded, will be the first line output to the trace file, and will
be used by etrace.pl to correctly map the function pointers to the
symbol names. To provide ptrace.c with the reference function, simply
set the macro PTRACE_REFERENCE_FUNCTION to the name of a function in
your library. You may #include any header files needed to make this
function visible in the "User Macros" section of ptrace.c.

## How to modify it

If you want another name of for the trace file (TRACE) you can actually
rename that both in ptrace.c and etrace. You could also use a dynamic file
name but you need then a way of exchanging the file name between both
processes.

If you prefer, you could have ptrace.c redirect its output to a socket and
etrace retrieve it as a client. This would substantially increase the
amount of code but could be interesting for remotely debugging an
application.

The output of your 'nm' command might slightly change from the BSD standard
(identical to Linux, Solaris, and to some extent to the HPUX output). You
will need to modify the simplistic parser implemented in 'etrace' to handle
these changes.

You could also use the tracing feature to have 'ptrace.c' send many more
informations through the line, like memory allocations, file operations,
etc. This might make the output somewhat harder to read and is most
probably better handled by a debugger.

Well anyway, this is just one possible use of the function instrumentation
feature of gcc 2.95. Thanks to the gcc team for this VERY useful tool!


## Support

This code is not supported. This is only 80 lines of Python and 100 lines of C, so if you need additional features I'd say you are better off on your own. :-)

Authors: N. Devillard and V. Chudnovsky.

# Download

[etrace-2.1.tar.gz](etrace-2.1.tar.gz)

