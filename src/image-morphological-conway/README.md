## Overview

This tool transforms a raster containing scattered white pixels into a raster on which the area roughly defined by the scattered points is filled with white pixels. This is a filling algorithm in case the region is fill is not formally defined by specific properties of the raster. It implements a multi-scale variation of the Conway game of life.

This tools originated from the _structure-from-motion_ field where sparse keypoints of an 3D objects appears as a set of scattered points when reprojected on images that see the objects. The objective of this tool was to have a way of extrapolating the area covered by an object on an image based on the few reporjected points coming from it.

## Usage example

To illustrate the tools result, the following example image is considered :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/example.png?raw=true" width="384">
<br />
<i>Original source raster contained scattered white pixels</i>
</p>
<br />

To apply the region filling on the image, one uses the following command :

    ./image-morphological-conway -s example.png -e result_0.5_1.png -r 1 -f 0.5

The reduction factor _r_ gives the amount of scale to consider for the process while the factor _f_ gives the scales reduction value that has to be between _0_ and _1_. See the tool doxygen documentation for more details.

The following image shows the results obtained used _f=0.5_ and with a varying number of iterations :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/result_0.5_1.png?raw=true" width="384">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/result_0.5_2.png?raw=true" width="384">
<br />
<i>Process result with a reduction factor of 0.5 and 1 iteration on the left and 2 on the right</i>
</p>
<br />

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/result_0.5_3.png?raw=true" width="384">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/result_0.5_4.png?raw=true" width="384">
<br />
<i>Process result with a reduction factor of 0.5 and 3 iteration on the left and 4 on the right</i>
</p>
<br />

