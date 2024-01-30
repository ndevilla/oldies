gnuplot interfaces in ANSI C
============================

(c) 2001

gnuplot is a freely available, command-driven graphical display tool
for Unix. It compiles and works quite well on a number of Unix flavours
as well as other operating systems.

The following module enables sending display requests to a gnuplot
session through simple ANSI C calls. This module is placed in the public
domain. I do appreciate a mention in your code, documentation, or web
pages, if you happen to use this module.

Notice that `gnuplot_i` talks to a gnuplot process by means
of POSIX pipes. This implies that the underlying operating system has
the notion of processes and pipes, and advertizes them in a POSIX
fashion. This module will not work on Windows.

# On-line documentation

[Browse the online documentation](gnuplot_i/index.html)
	
# Download

[Download gnuplot_i-2.10.tar.gz](gnuplot_i-2.10.tar.gz)

# FAQ

## What is gnuplot_i?

`gnuplot_i` is a C module that allows an easy interfacing to
the gnuplot plotting program. In short: it allows you to send
plotting requests to gnuplot from a C program.

## What do I need to compile and use it?

You need a C or C++ compiler (C compiler preferred) to compile the
module.

# Is there any trouble compiling it with a C++ compiler?

Some people have reported some warnings about missing casts. It seems
that many C++ compilers are picky about converting pointer types. There
is no generic solution to this problem. Either you are ready to modify
this module by yourself to shut up all potential C++ compiler warnings
(and errors), or you compile it as a C module and link your C++ programs
against it.

Notice that many C++ compilers will happily compile the module without
complaints, though.

# Which platforms are supported?

Since `gnuplot_i` makes use of pipes, the notion of pipes must be
present and supported by your C library for the module to compile. More
specifically, the `popen()` system call must be supported.

Virtually all Unix flavours support this system call, so you should not
have any problem using this module on Linux, Solaris, HPUX, IRIX, AIX,
Tru64, BSD, etc. All POSIX-compliant platforms should also be supported,
although this has not been tested.

On the other hand, Windows-based systems do not have this call, which
means that the module probably does not even compile on Windows. There
are several solutions around this, but they are completely unsupported.
See the question below.

# Does it work on Windows?

No.

# Can I replace the call to popen() by a call to system()?

Yes, but you would loose the capacity of plotting
user-defined list of doubles and lists of points.

