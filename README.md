salesperson
===========

Use the included `Makefile` to build the `salesperson` program.
~~~~~~~~(shell)
$ make
~~~~~~~~

Provide a text file of nodes and values such that each line is node, and each
node holds a unique identification number, an `x` and a `y` coordinate.

~~~~~~~~(shell)
1 2 4
3 20 40
~~~~~~~~(shell)

Run `salesperson` with `--input-file=<filename>` or as a positional argument.

~~~~~~~~(shell)
$ ./salesperson problem_set.txt
~~~~~~~~

~~~~~~~~(shell)
$ ./salesperson --help
Usage: saleperson [options] [input-file]:
  --help                produce help message
  --input-file arg      supply problem input file
~~~~~~~~
