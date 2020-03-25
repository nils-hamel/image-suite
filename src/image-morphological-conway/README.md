## Overview

This tool transforms a raster containing scattered white pixels into a raster on which the area roughly defined by the scattered points is filled with white pixels. This is a filling algorithm in case the region is fill is not formally defined by specific properties of the raster. It implements a multi-scale variation of the Conway game of life.

This tools originated from the _structure-from-motion_ field where sparse keypoints of an 3D objects appears as a set of scattered points when reprojected on images that see the objects. The objective of this tool was to have a way of extrapolating the area covered by an object on an image based on the few reporjected points coming from it.

## Usage example

To illustrate the tools result, the following example image is considered :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-morphological-conway/doc/example.png?raw=true" width="384">
<i>Original source raster contained scattered white pixels</i>
</p>
<br />