/*
 *  image-suite - farneback optical flow
 *
 *      Nils Hamel - nils.hamel@bluewin.ch
 *      Copyright (c) 2020 DHLAB, EPFL
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

    /*! \file   image-farneback-optical-flow.hpp
     *  \author Nils Hamel <nils.hamel@bluewin.ch>
     *
     *  image-suite - farneback optical flow
     */

    /*! \mainpage image-suite
     *
     *  \section overview Overview
     *
     *  This tools suite implements very specific image processing methods that
     *  are often missing from image processing libraries and softwares. The
     *  goal is to offer simple tools that allows to access to these methods and
     *  use them on images mainly in the research domain.
     *
     *  These methods originates from different research field problems and aim
     *  to provide possible solutions through easy to use softwares (that remain
     *  in command line).
     *
     *  \section copyright Copyright and License
     *
     *  **image-suite** - Nils Hamel <br >
     *  Copyright (c) 2020 DHLAB, EPFL
     *
     *  This program is licensed under the terms of the GNU GPLv3. Documentation
     *  and illustrations are licensed under the terms of the CC BY 4.0.
     */

/*
    header - inclusion guard
 */

    # ifndef __IM_FARNBACK_OPTICAL_FLOW__
    # define __IM_FARNBACK_OPTICAL_FLOW__

/*
    header - internal includes
 */

/*
    header - external includes
 */

    # include <opencv4/opencv2/opencv.hpp>
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

    /*! \brief image remapping
     *
     */

    void im_farneback_optical_flow_map( cv::Mat & im_flow );

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

