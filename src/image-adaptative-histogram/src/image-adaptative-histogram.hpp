/*
 *  image-suite - adaptative histogram
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

    /*! \file   image-adaptative-histogram.hpp
     *  \author Nils Hamel <nils.hamel@bluewin.ch>
     *
     *  image-suite - adaptative histogram
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

    # ifndef __IM_ADAPTATIVE_HISTOGRAM__
    # define __IM_ADAPTATIVE_HISTOGRAM__

/*
    header - internal includes
 */

/*
    header - external includes
 */

    # include <iostream>
    # include <vector>
    # include <cstdlib>
    # include <cmath>
    # include <opencv2/opencv.hpp>
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

    /*! \brief main function
     *
     *  This function is responsible for the computation of the local histogram
     *  of the provided pixel of the source image. It uses the provided kernel
     *  value to determine the size of the area around the pixel that is
     *  considered for the computation of the mean and standard deviation of the
     *  pixel.
     *
     *  The mask image is used to ignore pixels of the source image with value  
     *  below 127.5 in the corresponding mask image position. These pixels do
     *  not contribute to the statistical quantities.
     *
     *  The \b im_channel is a vector that contain the index of the color
     *  component to consider for the computation of the mean and standard
     *  deviation of the pixel. If \b 0 is provided as a single element of the
     *  vector, only the first channel of the image is considered for the
     *  computation of the mean and standard deviation. If the vector contains
     *  two element \b 0 and \b 2, the red and blue channels are used to compute
     *  the statistical quantities. 
     * 
     *  The function assumes that the provided images \b im_mean and \b im_std
     *  are already allocated in terms of their memory and have a size equal to
     *  the size of the source image (assumed to be reduced).
     *
     *  \param im_src         Source image, assumed to be reduced
     *  \param im_msk         Mask image, identical size as source image
     *  \param im_mean        Mean value map, computed by the function
     *  \param im_std         Standard deviation map, computed by the function
     *  \param im_channels    Vector of channel index to consider
     *  \param im_kernel      Kernel size, in pixels
     *  \param im_px          Pixel x position
     *  \param im_py          Pixel y position
     */

    void image_adaptative_histogram_kernel( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels, int const im_kernel, int const im_px, int const im_py );

    /*! \brief main function
     *
     *  This function is a front-end for the computation of each pixel of the
     *  source image local histogram. The source image is assumed to be reduced
     *  in size. The mask is expected to have the same size of the provided
     *  source image. The mask is broadcasted to the subsequent process that
     *  performs the statistical quantities computation.
     *
     *  This function simply parses the source image pixels and invokes the
     *  computation of the local histogram.
     *
     *  The \b im_channel and \b im_kernel are only broadcast to the local
     *  histogram computation function \b image_adaptative_histogram_kernel().
     *
     *  This function is also responsible of allocating the memory of the two
     *  maps for mean and standard deviation computed for each pixels.
     *
     *  \param im_src         Source image, assumed to be reduced
     *  \param im_msk         Mask image, identical size as source image
     *  \param im_mean        Mean value map, computed by the function
     *  \param im_std         Standard deviation map, computed by the function
     *  \param im_channels    Vector of channel index to consider
     *  \param im_kernel      Kernel size, in pixels
     */

    void image_adaptative_histogram( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels, int const im_kernel );

    /*! \brief main function
     *
     *  Based on the provided mean and standard deviation map, giving each pixel
     *  of the source image local histogram, this function perform the local
     *  histogram correction.
     *
     *  It uses the provided maps to cancel the source image local statistical
     *  quantities and to replace them by the provided target quantities. The
     *  correction for one pixel component can be summarised as follows :
     *
     *      c = ( ( c - local_mean ) / local_std ) * target_std + target_mean
     *
     *  Each pixel of the source image is processed as so.
     *
     *  The \b im_channels vector gives the list of the component on which the
     *  correction allowed by the provided has to take place. If the vector
     *  contain only the \b 0 value, the correction is only applied on the
     *  first color component. If the vector contains \b 0 and \b 1, the same
     *  correction is made for the two first components.
     *
     *  The mask image is used to ignore pixels during correction of the local
     *  histogram. If the value of a pixel in the mask image is below 127.5, it
     *  is ignored.
     *
     *  \param im_src         Source image, assumed to be at its original size
     *  \param im_msk         Mask image, identical size as source image
     *  \param im_mean        Mean value map, identical size as source image
     *  \param im_std         Standard deviation map, identical size as source image
     *  \param im_channels    Vector of channel index to consider
     *  \param im_target_mean Target mean value
     *  \param im_target_std  Target standard deviation
     */

    void image_adaptative_histogram_apply( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels, double const im_target_mean, double const im_target_std );

    /*! \brief main function
     *
     *  The main function reads the input image and performs an adaptative
     *  histogram correction procedure before to export it :
     *
     *      ./image-adaptative-histogram --source/-s [source image path]
     *                                   --mask/-m [mask image path]
     *                                   --export/-e [image exportation path]
     *                                   --reduce/-r [image reduction factor]
     *                                   --kernel/-k [kernel factor]
     *                                   --linked/-l [color component linkage]
     *                                   --mean/-n [target mean value]
     *                                   --std/-d [target standard deviation]
     *
     *  In order to apply the adaptative histogram correction on the source
     *  image, the main function starts by reducing it. The reduced version of
     *  the source image is used to compute the local statistical quantities,
     *  that are the pixel mean value and standard deviation, creating two
     *  statistical maps for both quantities. These computed quantities are then
     *  used to correct the local histogram and to make it match to the provided
     *  target mean and standard deviation. As the computed statistical maps are
     *  also of a reduced size, they are scale back to the source image original
     *  size using a bicubic interpolation.
     *
     *  A mask image can be provided to the main function. If the pixel value of
     *  the mask is above 127.5, the pixel is considered during the processing
     *  and ignore otherwise.
     *
     *  The reduction of the source image is based on the provided reduction
     *  factor. The size of the reduce image is given be the original size of
     *  the source image times this reduction factor.
     *
     *  The size of each pixel surrounding area used to compute the statistical
     *  quantities, i.e. the local histogram, is given by the size of the
     *  reduced source image time the provided kernel factor. The higher the
     *  value is, the larger is the region used to compute pixels local
     *  histogram (and the time needed to compute the correction maps).
     *
     *  The local histogram are computed based on a reduced version of the
     *  source image in order not to end up with very heavy process. It also
     *  allows to play with the reduction factor to adapt the correction to
     *  specific feature scale.
     *
     *  If the \b linked flag is provided, the correction is performed while
     *  keeping the color component group together. Otherwise, the correction
     *  is made component-wise, computing correction maps for each component.
     *
     *  Note : if the provided reduction factor is too large, the process can
     *  explode in term of computation time. A size of around 512 pixels is
     *  usually a good starting point for a reduced version of the source image.
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

