## Overview

This tools suite implements very specific image processing methods that are often missing from image processing libraries and softwares. The goal is to offer simple tools that allows to access to these methods and use them on images mainly in the research domain.

These methods originates from different research field problems and aim to provide possible solutions through easy to use softwares (that remain in command line).

## Image-Suite

Each implemented tool come with its own documentation that explains the implemented solution and gives example of usage and results :

_Histogram and exposure correction_

[Local histogram computation and correction](src/image-adaptative-histogram/README.md)

_Morphological Operators_

[Conway-based region filling of scattered pixels](src/image-morphological-conway/README.md)

_Images completion_

[Missing pixels extrapolation](src/image-missing-pixel/README.md)

In addition, codes come with _doxygen_ documentation that goes in the detail of each aspects of the implemented methods.

## Copyright and License

**image-suite** - Nils Hamel <br >
Copyright (c) 2020 DHLAB, EPFL

This program is licensed under the terms of the GNU GPLv3. Documentation and illustrations are licensed under the terms of the CC BY 4.0.

## Dependencies

The image-suite comes with the following package dependencies ([Instructions](DEPEND.md)) :

* build-essential

and the following external dependencies ([Instructions](DEPEND.md)) :

 * opencv 4.0.1

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
