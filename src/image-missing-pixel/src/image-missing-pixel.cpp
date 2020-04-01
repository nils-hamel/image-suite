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

    # include "image-missing-pixel.hpp"

/*
    source - main function
 */

    int main( int argc, char ** argv ) {

        /* kernel sampling width */
        int im_kernel( lc_read_signed( argc, argv, "--kernel", "-k", 8 ) );

        /* Source image */
        cv::Mat im_source;

        /* Mask image */
        cv::Mat im_mask;

        /* export image */
        cv::Mat im_export;

    try
    {

        /* import source image */
        im_source = cv::imread( lc_read_string( argc, argv, "--source", "-s" ), cv::IMREAD_UNCHANGED );

        /* check source image */
        if ( im_source.empty() ) {

            /* send message */
            throw std::runtime_error( "Source image not found" );

        }

        /* import source image */
        im_mask = cv::imread( lc_read_string( argc, argv, "--mask", "-m" ), cv::IMREAD_GRAYSCALE );

        /* check source image */
        if ( im_mask.empty() ) {

            /* send message */
            throw std::runtime_error( "Mask image not found" );

        }

        /* check consistency */
        if ( ( im_source.cols != im_mask.cols ) || ( im_source.rows != im_mask.rows ) ) {

            /* send message */
            throw std::runtime_error( "Source and mask image have different sizes" );

        }

        /* invert mask */
        im_mask = cv::Scalar::all(255) - im_mask;

        /* apply opencv inpaint on image with mask */
        cv::inpaint( im_source, im_mask, im_export, im_kernel, cv::INPAINT_TELEA );

        /* export completed image */
        if ( cv::imwrite( lc_read_string( argc, argv, "--export", "-e" ), im_export ) == false ) {

            /* send message */
            throw std::runtime_error( "Image exportation failed" );

        }

    }
    catch( std::runtime_error & im_error)
    {

        /* display runtime error message */
        std::cerr << "Error : " << im_error.what() << std::endl;

        /* system code */
        return 1;

    }

        /* system code */
        return 0;

    }

