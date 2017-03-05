// Main.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

    // open the original image
    cv::Mat imgOriginal;    
    imgOriginal = cv::imread("image.png");

    // verify the image opened successfully, if not, bail
    if (imgOriginal.empty()) {
        std::cout << "error: image not read from file\n\n";
        _getch();                               // may have to modify this line if not using Windows
        return(0);
    }
    cv::imshow("imgOriginal", imgOriginal);

    // convert to grayscale
    cv::Mat imgGrayscale;
    cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);
    cv::imshow("imgGrayscale", imgGrayscale);

    // choose either threshold or adaptiveThreshold() depending on the image and situation

    // threshold() way with OTSU thresholding
    cv::Mat imgThresh;
    cv::threshold(imgGrayscale, imgThresh, 0, 255.0, CV_THRESH_BINARY | CV_THRESH_OTSU);
    cv::imshow("imgThresh", imgThresh);

    // adaptiveThreshold() way
    cv::adaptiveThreshold(imgGrayscale, imgThresh, 255.0, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 19, 9);
    cv::imshow("imgThresh", imgThresh);

    // find contours
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(imgThresh.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    // draw contours
    cv::Mat imgContours(imgOriginal.size(), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));
    cv::drawContours(imgContours, contours, -1, cv::Scalar(255.0, 255.0, 255.0));
    cv::imshow("imgContours", imgContours);
    
    cv::waitKey(0);                 // hold windows open until user presses a key
    return(0);
}

