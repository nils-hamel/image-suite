/*
 *  image-suite - morphological conway
 *
 *      Nils Hamel - nils.hamel@bluewin.ch
 *      Copyright (c) 2016-2020 DHLAB, EPFL
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

    /*! \file   image-morphological-conway.hpp
     *  \author Nils Hamel <nils.hamel@bluewin.ch>
     *
     *  image-suite - morphological conway
     */

    /*! \mainpage image-suite
     *
     *  \section overview Overview
     *
     *  \section copyright Copyright and License
     *
     *  **image-suite** - Nils Hamel <br >
     *  Copyright (c) 2016-2020 DHLAB, EPFL
     *
     *  This program is licensed under the terms of the GNU GPLv3.
     */

/*
    header - inclusion guard
 */

    # ifndef __IM_MORPHOLOGICAL_CONWAY__
    # define __IM_MORPHOLOGICAL_CONWAY__

/*
    header - internal includes
 */

/*
    header - external includes
 */

    # include <iostream>
    # include <cmath>
    # include <opencv2/opencv.hpp>
    # include <opencv2/highgui/highgui.hpp>
    # include <common-include.hpp>

/*
    header - preprocessor definitions
 */

/*
    header - preprocessor macros
 */

/*
    header - type definition
 */

/*
    header - structures
 */

/*
    header - function prototypes
 */

    /*! \brief image transformation
     *
     *  This function applies a variation of the Conway game on the source
     *  image. The process is iterative and stops as no pixel can be activated
     *  anymore according to the implemented rule.
     *
     *  The rule is a simplification of the Conway game of life rules. A pixel
     *  is set from zero to 255 (activated) if at least five of its neighbours
     *  are already set to 255 (alive), including itself.
     *
     *  The returned result, made through the \b im_image parameter, is not the
     *  result of the iterative process but only contain the cells that have
     *  been modified from zero to 255 (activated). In other terms, the function
     *  returns a map of the activated cells.
     *
     *  \param im_image Processed image used to return the computed map
     */

    void im_morphological_conway( cv::Mat & im_image );

    /*! \brief image transformation
     *
     *  This function computes the max-pool reduction of the provided source
     *  image and returns it through the \b im_reducted parameter.
     *
     *  The reduction is driven by the provided reduction factor that is
     *  expected to be a floating value between zero and one (]0,1[).
     *
     *  The max-pool operation is performed by parsing the source image and
     *  applying a euclidean division to the pixel coordinates to obtain the
     *  corresponding pixel coordinates on the reduced image. If the value of
     *  the source image pixel is 255, the value of the reduced image pixel is
     *  also set to 255. This way, the pixels of the reduced image keep the
     *  highest value of their corresponding area pixels on the source image.
     *
     *  Using an euclidean division lead to what would correspond to a 'nearest'
     *  interpolation.
     * 
     *  \param im_source   Source image
     *  \param im_reducted Returned reduced image
     *  \param im_factor   Reduction factor
     */

    void im_morphological_conway_maxpool( cv::Mat & im_source, cv::Mat & im_reducted, double const im_factor );

    /*! \brief main function
     *
     *  The main function transforms the source raster expected to contained
     *  scattered and isolated white pixels on a black background into a raster
     *  containing a filled area approximating the covered zone by the scattered
     *  pixels :
     *
     *      ./image-morphological-conway --source/-s [source image path]
     *                                   --export/-e [exportation image path]
     *                                   --factor/-f [scales reduction factor]
     *                                   --reduction/-r [scales count]
     *
     *  To do so, a multi-scale application of a variation of the Conway game of
     *  life is performed. The reduction factor is considered to the power of
     *  the scale to compute the successive reduced image sizes on which the
     *  game is applied :
     *
     *      size_n   = original_size * ( ( factor ) ^ ( n ) )
     *      size_n-1 = original_size * ( ( factor ) ^ ( n - 1 ) )
     *      ...
     *      size_0   = original_size * ( ( factor ) ^ ( 0 ) ) = original_size
     *
     *  where 'n' is equal to 'reduction'. Starting from the highest scales, the
     *  variation of the Conway game is applied on the reduction of the source
     *  image. The map of the newly activated cells, for the considered scale,
     *  is scaled-up to the source image original size and a max-value
     *  convolution with the source image is applied The source image is then
     *  corrected at each step in a progressive process.
     *
     *  Choosing a small reduction factor, such as 0.5, allows to minimise the
     *  amount of step to perform (number of scale), but creates more sharpen
     *  filled surface edges while considering highest factor allows to get
     *  smoother edges but with more scale needed.
     *
     *  The number of scale has to be adapted to the scattering of the source
     *  image pixels. The more the pixels are scattered, the larger scale count
     *  is required to fill the desired area. If the number of scale is too low,
     *  the image can be left unchanged or nearly unchanged.
     *
     *  For the sake of simplicity, for each scale, the implemented Conway game
     *  variation discards cells at the edge of the raster. This allows not to
     *  implemented specific rules for the edge and corner cells.
     *
     *  \param argc Standard parameter
     *  \param argv Standard parameter
     *
     *  \return Returns standard exit code
     */

    int main( int argc, char ** argv );

/*
    header - inclusion guard
 */

    # endif

