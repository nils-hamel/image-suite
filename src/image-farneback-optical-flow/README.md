## Overview

This tool allows to compute the optical flow that link two images together. The result of the optical flow is a displacement vectors field exported in XML format. This displacement field gives the amount of motion to apply on pixels of the second image to bring them on their corresponding pixels on the first image. It can be seen as a way of obtaining dense pixels matching.

## Usage

Considering two successive spherical images acquired with a specific spherical camera : 

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-farneback-optical-flow/doc/image-a.jpg?raw=true" width="384">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-farneback-optical-flow/doc/image-b.jpg?raw=true" width="384">
<br />
<i>Two successive spherical images</i>
</p>
<br />

the following command :

    ./image-farneback-optical-flow -a image-a.jpg -b image-b.jpg -r remap.jpg -p 0.5 -e optical-flow.xml

allows to compute the optical flow that links their corresponding pixels. In addition to the optical flow itself, if an image path is provided through the --remap/-r parameter, the tool export a remap of the second image using the computed flow. The following image shows the resulting remap using the previous images :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-farneback-optical-flow/doc/remap.jpg?raw=true" width="384">
<br />
<i>Second image remap using the computed optical flow vectors field</i>
</p>
<br />

In a perfect case, this remap image should be identical to the first image. Of course, on this example, the elements seen on the two images are different as some part become hidden due to the different points of view.

The parameter --pyramid/-p can be used to drive the reduction factor used to produce the successive scales on which the optical flow is refined. The amount of scales is computed by the tool itself to ensure that the smallest scale corresponds to an image that is at least of eight pixels in size.

If the switch --export-map/-m is provided is the command line, the computed optical flow is converted to a proper remap. It simply adds to each vector of the computed vectors field their corresponding pixel coordinates. Such export can then be directly used with remapping tool such as the [_remap()_](https://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html?highlight=remap#remap) function of OpenCV.
