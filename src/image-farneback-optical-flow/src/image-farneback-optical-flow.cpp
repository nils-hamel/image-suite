/*
 *  image-suite - farneback optical flow
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

    # include "image-farneback-optical-flow.hpp"


/*
    source - main function
 */

    int main( int argc, char ** argv ) {

        std::cout << "OpenCV version: "
			<< CV_MAJOR_VERSION << "." 
			<< CV_MINOR_VERSION << "."
			<< CV_SUBMINOR_VERSION
			<< std::endl;

        cv::Mat img1 = cv::imread(argv[1], cv::IMREAD_COLOR);
        cv::Mat img2 = cv::imread(argv[2], cv::IMREAD_COLOR);
        cv::Mat res(img1.size(), CV_32FC2);

        if (img1.empty()){std::cerr << "error 1" << std::endl; return 1; }
        if (img2.empty()){std::cerr << "error 2" << std::endl; return 1; }

        cv::Mat prev, next;

        cv::cvtColor(img1, prev, cv::COLOR_BGR2GRAY);
        cv::cvtColor(img2, next, cv::COLOR_BGR2GRAY);

        //cv::calcOpticalFlowFarneback(prev,next,res, 0.5, 5, 4, 3, 5, 1.2, 0);
        cv::calcOpticalFlowFarneback(prev,next,res, 0.5, 7, 8, 3, 5, 1.2, 0 );

        // C++: void calcOpticalFlowFarneback
        //(InputArray prev, InputArray next, InputOutputArray flow, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags)

        std::cerr << "debug a" << std::endl;

        for ( int x(0); x < res.cols; x ++ ) {
            for ( int y(0); y < res.rows; y ++ ) {
                res.at<cv::Vec2f>(y,x)[0] += x;
                res.at<cv::Vec2f>(y,x)[1] += y;
            }
        }

        std::cerr << "debug b" << std::endl;

        cv::Mat comp[2];
        cv::split(res,comp);

        cv::Mat img3(img1.size(), CV_8UC3 );

        cv::remap( img2, img3, comp[0], comp[1], cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0) );

        cv::imwrite( argv[3], img3 );

        return 0;

    }

