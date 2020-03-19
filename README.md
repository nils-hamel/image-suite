## Overview

This tools suite implements specific image processing methods that are often missing from image libraries and softwares.

## Copyright and License

**image-suite** - Nils Hamel <br >
Copyright (c) 2020 DHLAB, EPFL

This program is licensed under the terms of the GNU GPLv3. Documentation and illustrations are licensed under the terms of the CC BY 4.0.

## Dependencies

The image-suite comes with the following package dependencies (Ubuntu 16.04 LTS) :

* build-essential
* libopencv-dev

The code documentation is built using Doxygen.

## Compilation

To build the project, including the sub-modules, use make with the following targets :

    $ make clean-all && make all

To rebuild the binaries without rebuilding sub-modules, use the make targets :

    $ make clean && make build

To only rebuild sub-modules, use the make command with the targets :

    $ make clean-module && make module

To generate the documentation of the project, use the targets :

    $ make clean-doc && make doc

and the targets :

    $ make clean-all-doc && make all-doc

to generate the documentation of the project and its sub-modules.
