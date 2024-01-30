Big/Little endian determination
===============================

    It is allowed on all Hands, that the primitive Way of
    breaking Eggs before we eat them, was upon the larger End: But
    his present Majesty's Grand-father, while he was a Boy, going
    to eat an Egg, and breaking it according to the ancient
    Practice, happened to cut one of his Fingers. Whereupon the
    Emperor his Father, published an Edict, commanding all his
    Subjects, upon great Penalties, to break the smaller End of
    their Eggs. The People so highly resented this Law, that our
    Histories tell us, there have been six Rebellions raised on
    that Account;... It is computed that eleven Thousand Persons
    have, at several Times, suffered Death, rather than submit to
    break their Eggs at the smaller End. Many hundred large
    Volumes have been published upon this Controversy: But the
    Books of the Big-Endians have been long forbidden...

    -- Jonathan Swift's Gulliver's Travels

# How to determine a machine's endian-ness at run-time?

One simple way is to use the following trick: declare an integer
variable that is at least 16 bits long, and assign 1 to it. On a big
endian machine, only the rightmost bit will be 1, all others 0. On a
little endian machine, the rightmost byte will always be 0 due to
byte-swapping. You can have a peek at this rightmost byte and read:
if you find a zero you are on a little-endian machine. Otherwise you
are on a big-endian machine.

In other words, the expression `(*(char*)&x)`
takes value _one_ on little-endian and _zero_ on big-endian
platforms, for all integer values of x of more than 8 bits. This makes it
easy to integrate into a test like:

    void test_m(void)
    {
        int x = 1;
        printf("this machine has a") ;
        (*(char*)&x) ? printf("n Intel") : printf(" Motorola") ;
        printf(" based processor\n") ;
    }

# How to determine a machine's endian-ness at compile-time?

Run a program like the one above and output the results to an
include file. Include then this header file in all your sources.
In a Makefile, it would look like the following:

    detection: endian.c
        $(CC) $(CFLAGS) -o endian endian.c
        endian &gt; config.h

# Source Download

The following source code should compile anywhere with a decent ANSI
C compiler, with the correct options set to compile ANSI C. It is used
either with a command-line argument, or without. Without argument, it
will print out a report of how variables look like on your machine. With
an argument (anything), it will create a default header file you can
#include in your source code, to know what kind of endian-ness the
machine compiling the code has.

[endian.c](endian.c)

The following source code provides generic functions to perform byte
swapping on 2 bytes, 4 bytes, and any even number of bytes. They should
compile everywhere without having to add specific stuff to your compile
lines.

[byteswap.c](byteswap.c)

(c) 1996

