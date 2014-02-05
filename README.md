Btree-source-code
=================

A working project for High-concurrency B-tree source code in C

There are four major code sets in the standard btree source code:

btree2s.c       Single Threaded/MultiProcess with latching supplied by advisory file locking.  Works with network file systems.  Only deletes leaf level pages.

btree2t.c       Single Threaded/MultiProcess version that removes keys all the way back to an original empty btree.

threads2h.c     Multi-Threaded/Multi-Process with latching implemented by a latch manager with pthreads/SRW latches in the first few btree pages.

threads2i.c     Multi-Threaded/Multi-Process with latching implemented by a latch manager with test & set latches  in the first few btree pages with thread yield system calls during contention.

threads2j.c     Multi-Threaded/Multi-Process with latching implemented by a latch manager with test & set locks in the first few btree pages with Linux futex system calls during contention.

The Foster code set includes the same three types of latching:

Fosterbtreee.c  Multi-Threaded/Single Process with latching implemented by a latch manager with pthreads/SRW latches in the first few btree pages.

Fosterbtreef.c  Multi-Threaded/Multi-Process with latching implemented by a latch manager with test & set latches  in the first few btree pages with thread yield  system calls during contention.

Fosterbtreeg.c  Multi-Threaded/Multi-Process with latching implemented by a latch manager with test & set locks in the first few btree pages with Linux futex system calls during contention.

Compilation is achieved on linux or Windows by:

gcc -D STANDALONE threads2h.c -lpthread

or

cl /Ox /D STANDALONE threads2h.c

Please see the project wiki page for documentation
