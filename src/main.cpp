#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << cv::getBuildInformation() << std::endl;
    return 0;
}