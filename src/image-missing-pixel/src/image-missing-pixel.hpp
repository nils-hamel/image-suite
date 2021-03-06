/*
 *  image-suite - image missing
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

    /*! \file   image-missing-pixel.hpp
     *  \author Nils Hamel <nils.hamel@bluewin.ch>
     *
     *  image-suite - missing pixel
     */

    /*! \mainpage image-suite
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

    # ifndef __IM_MISSING_PIXEL__
    # define __IM_MISSING_PIXEL__

/*
    header - internal includes
 */

/*
    header - external includes
 */

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
     *  The main function implements a simple front-end to the OpenCV inpaint
     *  missing pixel completion :
     *
     *      ./image-missing-pixel --source/-s [source image path]
     *                            --mask/-m [mask image path]
     *                            --export/-e [exported image path]
     *                            --kernel/-k [inpaint radius value]
     *
     *  The main function starts by importing the source image and the mask
     *  image. The mask image is expected to be a grayscale image containing
     *  only black and white pixels. The black pixels corresponds to the pixels
     *  to extrapolate.
     *
     *  The inpaint function is called using the INPAINT_TELEA (A. Telea) method
     *  to compute and assign the missing pixels.
     *
     *  The resulting image is exported by the main function using the provided
     *  exportation path.
     *
     *  See more information on inpaint function in the OpenCV documentation.
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

