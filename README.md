Fibonacci Heap in C
===================
Max Goldstein

This is an implementation of the Fibonacci heap data structure.  Like the more
familiar binary heap, it offers efficient removal of its smallest element. It
is asymptotically superior to binary heaps, allowing insertion, merging, and
decreasing the key in constant time. However the constants are fairly large,
making them often undesirable in practice. Fibonacci heaps were designed in the
1980s to expedite finding the shortest-path for dense graphs.

This project was completed as part of my undergraduate coursework and is placed
here with permission of the instructor. The full academic writeup is available
in LaTeX format, and describes the performance of the Fibonacci heap against a
naive, array-based heap. It can be compiled using `gnuplot plots.p && pdflatex
README.tex`. The file `use.h` determines which heap will be used.

Copyright 2012 Max Goldstein. No license granted.
