## Overview

This tool allows to compute an _adaptative_ histogram correction on a given image. The _adaptative_ term is understood as a local correction. In other words, a local histogram is computed on each area of the image to allow to correct it according to its local specificity.

This tool was designed in the context of city digitization using a spherical camera. As a spherical camera capture full panoramic images, it is able to see everything surrounding it. With good weather, traveling in a street with such camera produces images seeing half buildings exposed to the sun while the other half are seen in their own shade. This tool was designed to correct this effect by normalizing the exposure helping subsequent process that use these images such as _structure from motion_ or _optical flow_.

## Usage

Considering the case of the spherical camera images, the following picture gives an example of a capture in the streets of a city. As the camera see part of itself and the car on which it is attached, a mask is also considered for this example.

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/spherical-camera.jpg?raw=true" width="384">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/spherical-camera-mask.png?raw=true" width="384">
<br />
<i>Example of a spherical camera image and its corresponding mask</i>
</p>
<br />

Using the following command :

    ./image-adaptative-histogram -s spherical-camera.jpg 
                                 -m spherical-camera-mask.png 
                                 -e spherical-camera-1.jpg 
                                 -r 0.1 -k 0.065 -l -n 127.5 -d 64.0

one obtain the following result :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/spherical-camera-1.jpg?raw=true" width="384">
<br />
<i>Result of the local histogram correction with color components linked</i>
</p>
<br />

One can see how the local histogram correction allows to adapt itself to the image local exposure. The building in the shade are more exposed while the sunny ones are a bit less.

If the color components are not linked (missing --linked/-l), the correction is applied component wise which destroy the colorimetry of the image but allows to maximize the correction as shown on this result :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/spherical-camera-2.jpg?raw=true" width="384">
<br />
<i>Result of the previous command without the color linkage flag (--linked/-l)</i>
</p>
<br />

As one can see, not linking the color components during correction can lead to more dangerous corrections as the low exposed components can be scaled up increasing their noise. But this allows to reveal a bit more the shaded parts of the image. This can be interesting for subsequent process such as _optical flow_ and _structure from motion_.

In order to get the desired correction, one as to play with the reduction factor _r_ and the kernel factor _k_. The smaller _r_ is, the greater _k_ has to be in order not to end up with long processing time. One has also to keep in mind that too large value of _r_ associated with a small value of _k_ can lead to a correction of the features of the image instead of the exposure as the correction becomes _too local_.

This tool can also be used to process other type of images such as old photography that show exposure problems such as this aerial image of Paris in the 1920 years. As it comes with undesired features on the edges, a mask is also used for the correction of the image :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/ign-photo-1920.jpg?raw=true" width="320">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/ign-photo-1920-mask.png?raw=true" width="320">
<br />
<i>Aerial image of Paris in the 1920 years (Image : IGN, France) and its mask</i>
</p>
<br />

Using the following command :

    ./image-adaptative-histogram -s ign-photo-1920.jpg 
                                 -m ign-photo-1920-mask.png 
                                 -e ign-photo-1920-1.jpg 
                                 -r 0.1 -k 0.065 -n 127.5 -d 64.0

one can obtain the following correction :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/ign-photo-1920-1.jpg?raw=true" width="320">
<br />
<i>Result of the exposure correction</i>
</p>
<br />

One can see how the local exposure problem can be solved using this image processing methodology. In case of gray-scale images, one need to convert it into a _RGB_ image (gray channel repetition) before to submit it to the tool that only accept three-channel images.

As a last example, this tool can also be used to correct exposure artifacts due to the aging of photographic negative. Using the following command :

    ./image-adaptative-histogram -s old-photo.jpg -e old-photo-1.jpg -r 0.1 -k 0.1 -l -n 170 -d 40

without usage of a mask to consider the whole image, one can obtain the following correction :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/old-photo.jpg?raw=true" width="320">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/old-photo-1.jpg?raw=true" width="320">
<br />
<i>Result of the correction of aging effect on a digitized photographic negative</i>
</p>
<br />

In any case, one has to play with both reduction _r_ and kernel _k_ factors to obtained the appropriate correction depending on the _size_ of the exposure variation to diminish.
