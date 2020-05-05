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
     *  This function is used to translate the optical flow vectors field into
     *  an absolute displacement map. The optical flow giving a relative
     *  displacement map according to each pixel, this function adds to each
     *  vector the coordinates of the position of their respective pixel.
     *
     *  This allows to use the optical flow result as transformation map using
     *  for example the OpenCV \b remap() function.
     *
     *  The optical flow is passed as reference in order for the function to
     *  modify it directly, without duplication.
     *
     *  \param im_flow Optical flow (Floating point OpenCV matrix)
     */

    void im_farneback_optical_flow_map( cv::Mat & im_flow );

    /*! \brief main function
     *
     *  The main function reads the two input images and computes a displacement
     *  vectors field to bring pixels of the second image on to their respective
     *  pixels of the first image. The images are then assumed to have a large    
     *  overlap or similitudes :
     *
     *      ./image-farneback-optical-flow --image-a/-a [First image path]
     *                                     --image-b/-b [Second image path]
     *                                     --export/-e [Flow exportation path]
     *                                     --remap/-r [Remapping exportation path]
     *                                     --pyramid/-p [Reduction factor]
     *                                     --window/-w [Windows size]
     *                                     --export-map/-m [Exportation option]
     *
     *  The main function starts by reading the arguments and parameters before
     *  to import the two images to link through a vectors field computed using   
     *  OpenCV optical flow algorithm.
     *
     *  The pyramid parameter allows to define the factor used to reduce the
     *  images size through the different scales. The amount of scales is
     *  computed by the main function to keep, at the deepest scale, an image of
     *  at least 8 pixels in size. The window parameter is the radius used
     *  around images pixels to match them - See OpenCV documentation for more
     *  information.
     *
     *  The result of the optical flow, that is the vectors field, is exported
     *  in XML format using the OpenCV standard exportation tool (FileStorage).
     *  If the '--export-map' is specified, the pixel coordinates is added to
     *  the vectors field before to export it. The exportation path is provided
     *  by the '--export' parameter.
     * 
     *  If the '--remap' path is specified, the vector field is used to remap 
     *  the second image before to export it using the specified path. This
     *  allows to see the performances of the optical flow through a simple 
     *  image. In an perfect case, this exported image should be identical to
     *  the first image.
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

