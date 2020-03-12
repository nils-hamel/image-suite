
    # include "image-adaptative-histogram.hpp"

    void image_adaptative_histogram_kernel( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels, int const im_kernel, int const im_px, int const im_py ) {

        /* bounding box */
        int im_x_l( im_px - im_kernel );
        int im_x_h( im_px + im_kernel + 1 );
        int im_y_l( im_py - im_kernel );
        int im_y_h( im_py + im_kernel + 1 );

        /* component variable */
        double im_component( 0. );

        /* count value */
        int im_count( 0 );

        /* clamp bounding box */
        im_x_l = ( im_x_l < 0 ) ? 0 : im_x_l;
        im_y_l = ( im_y_l < 0 ) ? 0 : im_y_l;

        /* clamp bounding box */
        im_x_h = ( im_x_h > im_src.cols ) ? im_src.cols : im_x_h;
        im_y_h = ( im_y_h > im_src.rows ) ? im_src.rows : im_y_h;

        /* parsing kernel region */
        for ( int im_x(im_x_l); im_x < im_x_h; im_x ++ ) {

            /* parsing kernel region */
            for ( int im_y(im_y_l); im_y < im_y_h; im_y ++ ) {

                /* check mask condition */
                if ( im_msk.at<uchar>(im_y, im_x) > 127.5 ) {

                    /* parsing channels */
                    for ( unsigned int im_c(0); im_c < im_channels.size(); im_c ++ ) {

                        /* value accumulation */
                        im_mean.at<float>(im_py, im_px) += im_src.at<cv::Vec3b>(im_y, im_x)[im_channels[im_c]];

                        /* update count */
                        im_count ++;

                    }

                }

            }

        }

        /* compute mean value */
        im_mean.at<float>(im_py, im_px) /= float( im_count );

        /* parsing kernel region */
        for ( int im_x(im_x_l); im_x < im_x_h; im_x ++ ) {

            /* parsing kernel region */
            for ( int im_y(im_y_l); im_y < im_y_h; im_y ++ ) {

                /* check mask condition */
                if ( im_msk.at<uchar>(im_y, im_x) > 127.5 ) {

                    /* parsing channel */
                    for( unsigned int im_c(0); im_c < im_channels.size(); im_c ++ ) {

                        /* compute component */
                        im_component = im_src.at<cv::Vec3b>(im_y, im_x)[im_channels[im_c]] - im_mean.at<float>(im_py, im_px);

                        /* value accumulation */
                        im_std.at<float>(im_py, im_px) += ( im_component * im_component );

                    }

                }

            }

        }

        /* compute standard deviation */
        im_std.at<float>(im_py, im_px) = std::sqrt( im_std.at<float>(im_py, im_px) / float( im_count - 1. ) );

    }

    void image_adaptative_histogram( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels, int const im_kernel ) {

        /* allocate mean image */
        im_mean = cv::Mat::zeros( cv::Size( im_src.cols, im_src.rows ), CV_32FC1 );

        /* allocate standard deviation image */
        im_std  = cv::Mat::zeros( cv::Size( im_src.cols, im_src.rows ), CV_32FC1 );
       
        /* parsing source image pixels */
        for ( int im_x(0); im_x < im_src.cols; im_x ++ ) {

            /* parsing source image pixels */
            for ( int im_y(0); im_y < im_src.rows; im_y ++ ) {

                /* check mask condition */
                if ( im_msk.at<uchar>(im_y, im_x) > 127.5 ) {

                    /* compute mean and standard deviation for current pixel */
                    image_adaptative_histogram_kernel( im_src, im_msk, im_mean, im_std, im_channels, im_kernel, im_x, im_y );

                }

            }

        }

    }

    void image_adaptative_histogram_apply( cv::Mat & im_src, cv::Mat & im_msk, cv::Mat & im_mean, cv::Mat & im_std, std::vector<int> & im_channels ) {

        /* computation variable */
        float im_component( 0. );

        /* parsing channels */
        for ( unsigned int im_c(0); im_c < im_channels.size(); im_c ++ ) {

            /* parsing source image */
            for ( int im_x(0); im_x < im_src.cols; im_x ++ ) {

                /* parsing source image */
                for ( int im_y(0); im_y < im_src.rows; im_y ++ ) {

                    /* check mask condition */
                    if ( im_msk.at<uchar>(im_y, im_x) > 127.5 ) {

                        /* compute corrected component */
                        im_component = ( im_src.at<cv::Vec3b>(im_y, im_x)[im_channels[im_c]] - im_mean.at<float>(im_y, im_x) ) / im_std.at<float>(im_y, im_x) * 64.0 + 127.5;

                        /* clamp value */
                        im_component = ( im_component <   0. ) ?   0. : im_component;
                        im_component = ( im_component > 255. ) ? 255. : im_component;

                        /* assign corrected value */
                        im_src.at<cv::Vec3b>(im_y, im_x)[im_channels[im_c]] = im_component;

                    } else {

                        /* assign null value */
                        im_src.at<cv::Vec3b>(im_y, im_x)[im_channels[im_c]] = 0;

                    }

                }

            }

        }

    }

    int main( int argc, char ** argv ) {

        /* reduction factor */
        double im_reduce( 1. / 8. );

        /* kernel size */
        double im_kernel( 0.065 );

        bool im_linked( true );

        /* importation image */
        cv::Mat im_src, im_rsrc;

        /* mask image */
        cv::Mat im_msk, im_rmsk;

        /* mean value image */
        cv::Mat im_mean, im_rmean;

        /* std value image */
        cv::Mat im_std, im_rstd;

    try
    {

        /* import source image */
        im_src = cv::imread( argv[1], CV_LOAD_IMAGE_UNCHANGED );

        /* check image importation */
        if ( im_src.empty() ) {

            /* send message */
            throw std::runtime_error( "Source image not found" );

        }

        /* check image format */
        if ( im_src.channels() != 3 ) {

            /* send message */
            throw std::runtime_error( "Source image format : RGB only accpeted" );

        }

        /* import mask image */
        im_msk = cv::imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );

        /* check image importation */
        if ( im_msk.empty() ) {

            /* send message */
            throw std::runtime_error( "Mask image not found" );

        }

        /* check consistency of mask image */
        if ( ( im_src.cols != im_msk.cols ) || ( im_src.rows != im_msk.rows ) ) {

            /* send message */
            throw std::runtime_error( "Inconsistent mask size according to source image" );

        }

        /* create source image reduction */
        cv::resize( im_src, im_rsrc, cv::Size(), im_reduce, im_reduce, cv::INTER_CUBIC );

        /* create mask image reduction */
        cv::resize( im_msk, im_rmsk, cv::Size(), im_reduce, im_reduce, cv::INTER_CUBIC );

        /* check image format */
        if ( im_src.channels() == 3 ) {

            /* check channel mode */
            if ( im_linked == true ) {

                /* channel vector */
                std::vector<int> im_channels;

                /* create channel vector */
                im_channels.push_back(0);
                im_channels.push_back(1);
                im_channels.push_back(2);

                /* compute histogram correction maps */
                image_adaptative_histogram( im_rsrc, im_rmsk, im_rmean, im_rstd, im_channels, std::round( im_rsrc.cols * im_kernel ) );

                /* resize mean map to source image size */
                cv::resize( im_rmean, im_mean, cv::Size( im_src.cols, im_src.rows ), 0, 0, cv::INTER_CUBIC );

                /* resize standard deviation map to source image size */
                cv::resize( im_rstd, im_std, cv::Size( im_src.cols, im_src.rows ), 0, 0, cv::INTER_CUBIC );

                /* apply historgam correction */
                image_adaptative_histogram_apply( im_src, im_msk, im_mean, im_std, im_channels );

            } else {

                /* parsing channels */
                for ( int im_channel(0); im_channel < 3; im_channel ++ ) {

                    /* channel vector */
                    std::vector<int> im_channels;

                    /* create channel vector */
                    im_channels.push_back(im_channel);

                    /* compute histogram correction maps */
                    image_adaptative_histogram( im_rsrc, im_rmsk, im_rmean, im_rstd, im_channels, std::round( im_rsrc.cols * im_kernel ) );

                    /* resize mean map to source image size */
                    cv::resize( im_rmean, im_mean, cv::Size( im_src.cols, im_src.rows ), 0, 0, cv::INTER_CUBIC );

                    /* resize standard deviation map to source image size */
                    cv::resize( im_rstd, im_std, cv::Size( im_src.cols, im_src.rows ), 0, 0, cv::INTER_CUBIC );

                    /* apply historgam correction */
                    image_adaptative_histogram_apply( im_src, im_msk, im_mean, im_std, im_channels );

                }

            }

        }

        /* export image */
        cv::imwrite( argv[3], im_src );
        
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

