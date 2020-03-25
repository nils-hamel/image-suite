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
<i>Process result with a reduction factor of 0.5 and 3 iterations on the left and 4 on the right</i>
</p>
<br />

One can see how the increase of the number of scale allows to fill a greater area. This number of scale has to be adapted to the scattering of the pixel as the more scattered they are, the greater the number of scale has to be.

One can also see how the strong reduction factor of _0.5_ creates sharp and squared area edges. A balance has then to be found between the _quality_ of the edges and the _filling power_. In order to keep filling capacity while obtaining smoother edges, one can also play with the factor value.

Increasing the factor value from _0.5_ to _0.75_ allows to obtain smoother edges but requires more number of scale to obtain the _same_ filling capacity. One can use the following approximation of compute the new number of scale in case of a factor modification :

    scale' = log( factor ^ scale ) / log( factor' )

For example, obtaining the same filling capacity of _(r=3, f=0.5)_ with _f'=0.75_, one can use :

    scale' = log( 0.5 ^ 3 ) / log( 0.75 ) = 7.2283 ~ 7

scales. The following images gives the results obtained with _f=0.75_ and a number of iteration computed with the previous relation :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/result_0.75_2.png?raw=true" width="384">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/result_0.75_5.png?raw=true" width="384">
<br />
<i>Process result with a reduction factor of 0.75 and 2 iterations on the left and 5 on the right</i>
</p>
<br />

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/result_0.75_7.png?raw=true" width="384">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/result_0.75_10.png?raw=true" width="384">
<br />
<i>Process result with a reduction factor of 0.75 and 7 iterations on the left and 10 on the right</i>
</p>
<br />