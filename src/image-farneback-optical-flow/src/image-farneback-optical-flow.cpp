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

    # include "image-farneback-optical-flow.hpp"

/*
    source - image remapping
 */

    void im_farneback_optical_flow_map( cv::Mat & im_flow ) {

        /* parsing flow */
        for ( int im_x(0); im_x < im_flow.cols; im_x ++ ) {

            /* parsing flow */
            for ( int im_y(0); im_y < im_flow.rows; im_y ++ ) {

                /* compute flow to map conversion */
                im_flow.at<cv::Vec2f>(im_y, im_x)[0] += im_x;
                im_flow.at<cv::Vec2f>(im_y, im_x)[1] += im_y;           

            }

        }

    }

/*
    source - main function
 */

    int main( int argc, char ** argv ) {

        /* source image path */
        char * im_img_a_path( lc_read_string( argc, argv, "--image-a", "-a" ) );
        char * im_img_b_path( lc_read_string( argc, argv, "--image-b", "-b" ) );

        /* flow/map exportation path */
        char * im_flow_path( lc_read_string( argc, argv, "--export", "-e" ) );

        /* source image */
        cv::Mat im_img_a;
        cv::Mat im_img_b;

        /* greyscale image */
        cv::Mat im_img_a_g;
        cv::Mat im_img_b_g;

        /* optical flow */
        cv::Mat im_flow;

        /* remapping image */
        cv::Mat im_remap;

        /* flow component */
        cv::Mat im_fcomp[2];

        /* remapping exportation path */
        char * im_remap_path( lc_read_string( argc, argv, "--remap", "-r" ) );

        /* pyramidal reduction factor */
        double im_factor( lc_read_double( argc, argv, "--pyramid", "-p", 0.5 ) );

        /* number of pyramidal level */
        int im_pyramid(1);

        /* window size */
        unsigned int im_window( lc_read_unsigned( argc, argv, "--window", "-w", 8 ) );

    try
    {

        /* read source image */
        im_img_a = cv::imread( im_img_a_path, cv::IMREAD_COLOR );
        im_img_b = cv::imread( im_img_b_path, cv::IMREAD_COLOR );

        /* check source image */
        if ( im_img_a.empty() ) {

            /* send message */
            throw std::runtime_error( "Unable to import source image a" );

        }

        /* check source image */
        if ( im_img_b.empty() ) {

            /* send message */
            throw std::runtime_error( "Unable to import source image b" );

        }

        /* convert source image */
        cv::cvtColor( im_img_a, im_img_a_g, cv::COLOR_BGR2GRAY );
        cv::cvtColor( im_img_b, im_img_b_g, cv::COLOR_BGR2GRAY );

        /* allocate flow matrix */
        im_flow = cv::Mat::zeros( im_img_a.size(), CV_32FC2 );

        /* compute pyramidal level count */
        im_pyramid = std::round( std::log( double(8) / std::max(im_img_a.cols,im_img_a.rows) ) / log( im_factor ) );

        /* compute optical flow */
        cv::calcOpticalFlowFarneback( im_img_a_g, im_img_b_g, im_flow, im_factor, im_pyramid, im_window, 3, 5, 1.2, 0 );

        /* check exportation mode */
        if ( lc_read_flag( argc, argv, "--export-map", "-m" ) == true ) {

            /* compute map */
            im_farneback_optical_flow_map( im_flow );

            /* create exportation file */
            cv::FileStorage im_stream( im_flow_path, cv::FileStorage::WRITE );

            /* export flow */
            im_stream << "optical-flow-yx-remap" << im_flow;

            /* delete stream */
            im_stream.release();

        } else {

            /* create exportation file */
            cv::FileStorage im_stream( im_flow_path, cv::FileStorage::WRITE );

            /* export flow */
            im_stream << "optical-flow-yx" << im_flow;

            /* delete stream */
            im_stream.release();

            /* check map computation requirement */
            if ( im_remap_path != NULL ) {

                /* compute map */
                im_farneback_optical_flow_map( im_flow );

            }

        }

        /* check remapping exportation */
        if ( im_remap_path != NULL ) {

            /* allocate remap image */
            im_remap = cv::Mat::zeros( im_img_a.size(), CV_8UC3 );

            /* decompose map */
            cv::split( im_flow, im_fcomp );

            /* compute remapping */
            cv::remap( im_img_b, im_remap, im_fcomp[0], im_fcomp[1], cv::INTER_CUBIC, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0) );

            /* export remap */
            if ( cv::imwrite( im_remap_path, im_remap ) == false ) {

                /* send message */
                throw std::runtime_error( "Image exportation failed" );

            }

        }

    }
    catch( std::runtime_error & im_error )
    {

        /* display runtime error message */
        std::cerr << "Error : " << im_error.what() << std::endl;

        /* system code */
        return 1;

    }

        /* system code */
        return 0;

    }

