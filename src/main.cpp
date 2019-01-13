#include "configuration.hpp"
#include "birdview.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // std::cout << "Using OpenCV: " << cv::getBuildInformation() << std::endl;
    // std::cout << "Using Boost: " << BOOST_LIB_VERSION << std::endl;

    Configuration config;
    config.debug();

    std::string path_input = config.get(Configuration::INPUT) + "/" + config.get(Configuration::FILENAME);
    std::string path_output = config.get(Configuration::OUTPUT) + "/" + config.get(Configuration::FILENAME);
    std::string path_threshold = boost::replace_all_copy(path_output, ".jpg", "_1_threshold.jpg");
    std::string path_smooth = boost::replace_all_copy(path_output, ".jpg", "_2_smooth.jpg");
    std::string path_canny = boost::replace_all_copy(path_output, ".jpg", "_3_canny.jpg");
    std::string path_contours = boost::replace_all_copy(path_output, ".jpg", "_4_contours.jpg");
    std::string path_transform = boost::replace_all_copy(path_output, ".jpg", "_5_transform.jpg");
    std::string path_character = boost::replace_all_copy(path_output, ".jpg", "_6_character.jpg");
    std::string text;

    std::vector<std::string> path_result;
    path_result.push_back(path_threshold);
    path_result.push_back(path_smooth);
    path_result.push_back(path_canny);
    path_result.push_back(path_contours);
    path_result.push_back(path_transform);
    path_result.push_back(path_character);

    Birdview image;
    image.load(path_input);
    image.preprocess(Birdview::THRESHOLD);
    image.contours();
    image.boundingbox();
    if (!image.getError())
    {
        image.viewpoints();
        image.transform();
        // image.ocr(text);
        // image.save(path_result);
    }
    if (!image.getError())
    {
        image.debug(Birdview::TRANSFORM);
    }

    return 0;
}