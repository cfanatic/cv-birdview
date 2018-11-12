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

void Birdview::viewpoints()
{
    std::vector<cv::Point> contourFinal;
    std::vector<int> pointOfView;
    int idxPoint;

    std::cout << "Contour Edge 0:\t" << m_contourApprox[0].x << " " << m_contourApprox[0].y << std::endl;
    std::cout << "Contour Edge 1:\t" << m_contourApprox[1].x << " " << m_contourApprox[1].y << std::endl;
    std::cout << "Contour Edge 2:\t" << m_contourApprox[2].x << " " << m_contourApprox[2].y << std::endl;
    std::cout << "Contour Edge 3:\t" << m_contourApprox[3].x << " " << m_contourApprox[3].y << std::endl;

    contourFinal.resize(4);
    for (int i = 0; i < static_cast<int>(m_contourApprox.size()); i++)
    {
        pointOfView.push_back(m_contourApprox[i].x + m_contourApprox[i].y);
    }
    idxPoint = std::min_element(std::begin(pointOfView), std::end(pointOfView)) - pointOfView.begin();
    contourFinal[0] = m_contourApprox[idxPoint];
    idxPoint = std::max_element(std::begin(pointOfView), std::end(pointOfView)) - pointOfView.begin();
    contourFinal[2] = m_contourApprox[idxPoint];

    pointOfView.clear();
    for (int i = 0; i < static_cast<int>(m_contourApprox.size()); i++)
    {
        pointOfView.push_back(m_contourApprox[i].x - m_contourApprox[i].y);
    }
    idxPoint = std::max_element(std::begin(pointOfView), std::end(pointOfView)) - pointOfView.begin();
    contourFinal[1] = m_contourApprox[idxPoint];
    idxPoint = std::min_element(std::begin(pointOfView), std::end(pointOfView)) - pointOfView.begin();
    contourFinal[3] = m_contourApprox[idxPoint];

    cv::putText(m_imgInput, "TL", contourFinal[0], 5, 1, cv::Scalar(0, 0, 255), 2);
    cv::putText(m_imgInput, "TR", contourFinal[1], 5, 1, cv::Scalar(0, 0, 255), 2);
    cv::putText(m_imgInput, "BR", contourFinal[2], 5, 1, cv::Scalar(0, 0, 255), 2);
    cv::putText(m_imgInput, "BL", contourFinal[3], 5, 1, cv::Scalar(0, 0, 255), 2);
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