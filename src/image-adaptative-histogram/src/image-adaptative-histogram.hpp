/*
 *  image-suite - vision
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
     */

    void image_adaptative_histogram_kernel( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels, int const im_kernel, int const im_px, int const im_py );

    /*! \brief main function
     */

    void image_adaptative_histogram( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels, int const im_kernel );

    /*! \brief main function
     */

    void image_adaptative_histogram_apply( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels, double const im_target_mean, double const im_target_std );

    /*! \brief main function
     *
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

