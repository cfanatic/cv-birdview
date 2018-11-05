#include <iostream>
#include <boost/version.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "Using OpenCV: " << cv::getBuildInformation() << std::endl;
    std::cout << "Using Boost: " << BOOST_LIB_VERSION << std::endl;
    return 0;
}