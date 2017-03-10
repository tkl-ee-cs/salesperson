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
~~~~~~~~

Run `salesperson` with `--input-file=<filename>` or as a positional argument.

~~~~~~~~(shell)
$ ./salesperson problem_set.txt
~~~~~~~~

See all of the program options using `--help`.

~~~~~~~~(shell)
./salesperson --help
Usage: salepesrson [options] [input-file]:
  -h [ --help ]           produce help message
  -i [ --input-file ] arg supply problem input file
  -d [ --debug ]          print debug information
~~~~~~~~
