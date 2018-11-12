#include "birdview.hpp"

Birdview::Birdview()
{
    m_rng = cv::RNG(time(NULL));
}

Birdview::~Birdview()
{
}

void Birdview::load(std::string path)
{
    m_imgInput = cv::imread(path);
}

void Birdview::preprocess()
{
    cv::resize(m_imgInput, m_imgInput, cv::Size(m_imgInput.cols / SCALE, m_imgInput.rows / SCALE));
    cv::cvtColor(m_imgInput, m_imgInput, cv::COLOR_BGR2GRAY);
    cv::bilateralFilter(m_imgInput, m_imgSmooth, 11, 17, 17);
    cv::Canny(m_imgSmooth, m_imgCanny, 30, 200);
}

void Birdview::contours()
{
    m_imgContours = cv::Mat::zeros(m_imgCanny.size(), CV_8UC3);
    cv::findContours(m_imgCanny, m_contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    for(int i = 0; i < static_cast<int>(m_contours.size()); i++)
    {
        cv::Scalar color = cv::Scalar(m_rng(255), m_rng(255), m_rng(255));
        cv::drawContours(m_imgContours, m_contours, i, color, 2, 8, m_hierarchy, 0, cv::Point());
    }
}

void Birdview::debug()
{
    if (!m_imgInput.empty())
    {
        cv::imshow("m_imgInput", m_imgInput);
        cv::imshow("m_imgSmooth", m_imgSmooth);
        cv::imshow("m_imgCanny", m_imgCanny);
        cv::imshow("m_imgContours", m_imgContours);
        cv::waitKey(0);
    }
    else
    {
        std::cout << "No image found!" << std::endl;
    }
}