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
    std::string path_text = boost::replace_all_copy(path_output, ".jpg", "_text.txt");

    std::vector<std::string> path_images;
    path_images.push_back(path_threshold);
    path_images.push_back(path_smooth);
    path_images.push_back(path_canny);
    path_images.push_back(path_contours);
    path_images.push_back(path_transform);
    path_images.push_back(path_character);

    std::vector<Birdview::modes> pre_level;
    std::vector<Birdview::modes>::iterator it;
    pre_level.push_back(Birdview::THRESHOLD);
    pre_level.push_back(Birdview::SMOOTH);
    it = pre_level.begin();

    Birdview image;
    do
    {
        std::cout << "----------------------------------------" << std::endl;
        image.load(path_input);
        image.preprocess(pre_level[it - pre_level.begin()]);
        image.contours();
        image.boundingbox();
        if (!image.getError())
        {
            image.viewpoints();
            image.transform();
            image.ocr(Birdview::CHECK, path_text);
            image.save(path_images);
        }
        if (!image.getError())
        {
            image.debug(Birdview::TRANSFORM);
            break;
        }
        ++it;
    }
    while (it != pre_level.end());

    return 0;
}