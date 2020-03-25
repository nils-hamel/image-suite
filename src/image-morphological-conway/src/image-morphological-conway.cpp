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

    # include "image-morphological-conway.hpp"

/*
    source - Conway game variation
 */

    void im_morphological_conway( cv::Mat & im_image ) {

        /* activated cell count */
        unsigned int im_count(1);

        /* neighbour cell count */
        unsigned int im_neighbour(0);

        /* game evolution grids */
        cv::Mat im_next, im_prev( im_image.clone() );

        /* resulting layer */
        cv::Mat im_layer( cv::Size( im_image.cols, im_image.rows ), CV_8UC1, cv::Scalar( 0 ) );

        /* iteration loop */
        while ( im_count > 0 ) {

            /* reset next grid */
            im_next = cv::Mat::zeros( cv::Size( im_image.cols, im_image.rows ), CV_8UC1 );

            /* reset count value */
            im_count = 0;

            /* update grid */
            for ( int im_x(1); im_x < (im_image.cols - 1); im_x ++ ) {

                /* update grid */
                for ( int im_y(1); im_y < (im_image.rows - 1); im_y ++ ) {

                    /* compute neighbour count */
                    im_neighbour  = im_prev.at<uchar>(im_y - 1, im_x - 1);
                    im_neighbour += im_prev.at<uchar>(im_y - 1, im_x    );
                    im_neighbour += im_prev.at<uchar>(im_y - 1, im_x + 1);
                    im_neighbour += im_prev.at<uchar>(im_y    , im_x - 1);
                    im_neighbour += im_prev.at<uchar>(im_y    , im_x    );
                    im_neighbour += im_prev.at<uchar>(im_y    , im_x + 1);
                    im_neighbour += im_prev.at<uchar>(im_y + 1, im_x - 1);
                    im_neighbour += im_prev.at<uchar>(im_y + 1, im_x    );
                    im_neighbour += im_prev.at<uchar>(im_y + 1, im_x + 1);

                    /* check neighbour count */
                    if ( im_neighbour >= 1275 ) {

                        /* update previous state */
                        im_next.at<uchar>(im_y, im_x) = 255;

                        /* check previous state */
                        if ( im_prev.at<uchar>(im_y, im_x) == 0 ) {

                            /* update resulting layer */
                            im_layer.at<uchar>(im_y, im_x) = 255;

                            /* update cell count */
                            im_count ++;

                        }

                    } else {

                        /* broadcast previous state */
                        im_next.at<uchar>(im_y, im_x) = im_prev.at<uchar>(im_y, im_x);

                    }

                }

            } 

            /* swap grid */
            im_prev = im_next.clone();

        }

        /* send resulting layer */
        im_image = im_layer.clone();

    }

/*
    source - image transformation
 */

    void im_morphological_conway_maxpool( cv::Mat & im_source, cv::Mat & im_reducted, double const im_factor ) {

        /* allocate reduced image */
        im_reducted = cv::Mat::zeros( cv::Size( int(im_source.cols * im_factor), int(im_source.rows * im_factor) ), CV_8UC1 );

        /* parsing source image */
        for ( int im_x(0); im_x < im_source.cols; im_x ++ ) {

            /* parsing source image */
            for ( int im_y(0); im_y < im_source.rows; im_y ++ ) {

                /* check source image pixel value */
                if ( im_source.at<uchar>(im_y, im_x) == 255 ) {

                    /* assign pixels on reduced image */
                    im_reducted.at<uchar>(int(im_y * im_factor), int(im_x * im_factor)) = 255;

                }

            }

        }

    }

/*
    source - main function
 */

    int main( int argc, char ** argv ) {

        /* source image path */
        char * im_source_path( lc_read_string( argc, argv, "--source", "-s" ) );

        /* export image path */
        char * im_export_path( lc_read_string( argc, argv, "--export", "-e" ) );

        /* reduction factor */
        double im_factor( lc_read_double( argc, argv, "--factor", "-f", 0.5 ) );

        /* source image */
        cv::Mat im_source;

        /* reduced image */
        cv::Mat im_reducted;

        /* scale reduction depth */
        unsigned int im_reduce( lc_read_unsigned( argc, argv, "--reduction", "-r", 1 ) );

    try
    {

        /* read source image */
        im_source = cv::imread( im_source_path, cv::IMREAD_GRAYSCALE );

        /* check source image */
        if ( im_source.empty() ) {

            /* send message */
            throw std::runtime_error( "Unable to import source image" );

        }

        /* parsing scales */
        for ( int im_scale( im_reduce ); im_scale >= 0; im_scale -- ) {

            /* check scale value */
            if ( im_scale == 0 ) {

                /* copy original image for scale zero - no reduction */
                im_reducted = im_source.clone();

            } else {

                /* compute reduced image */
                im_morphological_conway_maxpool( im_source, im_reducted, std::pow( im_factor, im_scale ) );

            }

            /* apply variation of Conway game */
            im_morphological_conway( im_reducted );

            /* upscale correction grid */
            cv::resize( im_reducted, im_reducted, cv::Size( im_source.cols, im_source.rows ), 0, 0, cv::INTER_NEAREST );

            /* max-convolution with source image and its correction */
            im_source = cv::max( im_source, im_reducted );

        }

        /* export resulting image */
        cv::imwrite( im_export_path, im_source );

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

