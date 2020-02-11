#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

std::vector<cv::Point2f> getGoodFeatures(const cv::Mat& img)
{
    cv::Mat image_gray;
    cv::cvtColor(img, image_gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Point2f> corners;
    int max_corners = 200;
    double quality_level = 0.01;
    double min_distance = 3.0;
    int block_size = 3;
    bool use_harris = false;
    double k = 0.04;

    cv::goodFeaturesToTrack(image_gray,
                            corners,
                            max_corners,
                            quality_level,
                            min_distance,
                            cv::Mat(),
                            block_size,
                            use_harris,
                            k);
    return corners;
}

std::vector<cv::Point2f> getCornerSubpix(const cv::Mat& img)
{
    cv::Mat image_gray;
    cv::cvtColor(img, image_gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Point2f> corners;
    int max_corners = 200;
    double quality_level = 0.01;
    double min_distance = 3.0;
    int block_size = 3;
    bool use_harris = false;
    double k = 0.04;

    cv::goodFeaturesToTrack(image_gray,
                            corners,
                            max_corners,
                            quality_level,
                            min_distance,
                            cv::Mat(),
                            block_size,
                            use_harris,
                            k);

    cv::TermCriteria criteria = cv::TermCriteria(
            cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
            40,
            0.01);

    cv::cornerSubPix(image_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
    return corners;
}

int main()
{
    cv::Mat image_color = cv::imread("../image/1.jpg", cv::IMREAD_COLOR);
    std::vector<cv::Point2f> corners;
    std::vector<cv::Point2f> corners_subpix;
    corners = getGoodFeatures(image_color);
    corners_subpix = getCornerSubpix(image_color);

    for (int i = 0; i < corners.size(); i++)
    {
        cv::circle(image_color, corners[i], 1, cv::Scalar(0, 0, 255), 2, 8, 0);
    }

    cv::Mat image_color2 = image_color.clone();
    for (int i = 0; i < corners.size(); i++)
    {
        cv::circle(image_color2, corners_subpix[i], 1, cv::Scalar(0, 0, 255), 2, 8, 0);
    }
    cv::imshow("corner", image_color);
    cv::imshow("corner_subpix", image_color2);
    cv::waitKey(0);
    return 0;
}

//int main()
//{
//    cv::Mat image_color = cv::imread("../image/1.jpg", cv::IMREAD_COLOR);
//    cv::Mat image_gray;
//    cv::cvtColor(image_color, image_gray, cv::COLOR_BGR2GRAY);
//
//    //设置角点检测参数
//    std::vector<cv::Point2f> corners;
//    int max_corners = 200;
//    double quality_level = 0.01;
//    double min_distance = 3.0;
//    int block_size = 3;
//    bool use_harris = false;
//    double k = 0.04;
//
//    cv::goodFeaturesToTrack(image_gray,
//                           corners,
//                           max_corners,
//                           quality_level,
//                           min_distance,
//                           cv::Mat(),
//                           block_size,
//                           use_harris,
//                           k);
//    //将检测到的角点绘制到原图上
//    for (int i = 0; i < corners.size(); i++)
//    {
//        cv::circle(image_color, corners[i], 1, cv::Scalar(0, 0, 255), 2, 8, 0);
//    }
//
//    cv::imshow("house corner", image_color);
//    cv::waitKey(0);
//    return 0;
//}


