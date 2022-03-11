# col-opt

**Column-Width Optimization**

Finding the optimal column widths to format a spreadsheet or table
within a given width is an [NP-hard problem](https://quintenkent.com/content/column-problem.html).

This project tackles the column problem from a couple different angles,
providing:

- A **generator-based** approach that examines the entire
  problem space for an **optimal** solution *(slow)*

- A **linear programming** approach that reduces the problem space
  to a linear model that can **approximate** the optimal solution *(fast)*


## Project structure

- build/

  Run `make` from this directory to build the main project.
This produces the 'colopt' binary.
(Note that you will need the Clp and CoinUtils dependencies installed,
see Dependencies section).

  You can also run `make gentest` to build a program
to compare the performance of different combination generators,
or `make clpdriver` and `make clpmod` to build
example COIN-OR Clp programs.

- include/

  This directory contains C++ header files

- public\_html/

  This sub-project includes a makefile to build this project for the browser
with WebAssembly (Wasm).
See the separate [README](./public_html) for more details.

- src/

  This directory contains C++ source files

- test/

  This directory contains sample csv files that can be
passed to the colopt program as input.
See the separate [README](./test) in test for more details.


## Dependencies

Building the main program requires you to have the Clp system headers
and shared libraries available on your machine.

On debian, these can be installed with
`apt install coinor-libclp-dev coinor-libcoinutils-dev`.

