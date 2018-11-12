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
    cv::cvtColor(m_imgInput, m_imgGrey, cv::COLOR_BGR2GRAY);
    cv::bilateralFilter(m_imgGrey, m_imgSmooth, 11, 17, 17);
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

void Birdview::boundingbox()
{
    double temp, area, arclen = 0;
    int indexAreaMax = 0;

    for (int i = 0; i < static_cast<int>(m_contours.size()); i++)
    {
        temp = cv::contourArea(m_contours[i]);
        if (temp > area)
        {
            arclen = cv::arcLength(m_contours[i], true);
            cv::approxPolyDP(m_contours[i], m_contourApprox, 0.02 * arclen, true);
            if (m_contourApprox.size() == 4)
            {
                area = temp;
                indexAreaMax = i;
            }
            else
            {
                continue;
            }
        }
    }
    cv::drawContours(m_imgInput, m_contours, indexAreaMax, cv::Scalar(0, 255, 0), 2, 8, m_hierarchy, 0, cv::Point());
    std::cout << "Contour Index:\t" << indexAreaMax << std::endl;
    std::cout << "Contour Edges:\t" << m_contourApprox.size() << std::endl;
}

void Birdview::debug()
{
    // TODO: Conditional check needs to be expanded
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