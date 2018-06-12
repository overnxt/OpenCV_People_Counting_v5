#include "analysis_algorithms/ObjectCouting.h"
#include "backgroundsub_algorithms/PBAS/PixelBasedAdaptiveSegmenter.h"
#include "tracking_algorithms/BlobTracking.h"
#include <iostream>
#include <memory>
#include <opencv2/bgsegm.hpp>
#include <opencv2/opencv.hpp>
using cv::BackgroundSubtractor;
using cv::VideoCapture;
using cv::Ptr;
using cv::bgsegm::BackgroundSubtractorMOG;
using cv::bgsegm::createBackgroundSubtractorMOG;
using std::make_unique;
using std::unique_ptr;
int main(int argc, char* argv[])
{
    for (int i{}; i < argc; i++)
        std::cout << argv[i] << std::endl;
    std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;

    /* Open video file */
    VideoCapture systemCapture;
    systemCapture.open(argv[1]);
    /*capture = cvCaptureFromAVI(argv[1]);
    if (!capture) {
        std::cerr << "Cannot open video!" << std::endl;
        return 1;
    }*/

    /* Background Subtraction Algorithm */
    //unique_ptr<IBGS> bgs{ make_unique<PixelBasedAdaptiveSegmenter>() };
    /* Blob Tracking Algorithm */
    cv::Mat img_blob;
    unique_ptr<BlobTracking> blobTracking{ make_unique<BlobTracking>() };

    /* Vehicle Counting Algorithm */
    unique_ptr<ObjectCouting> vehicleCouting{ make_unique<ObjectCouting>() };

    std::cout << "Press 'q' to quit..." << std::endl;

    Ptr<BackgroundSubtractorMOG> backgroundSuctractor{createBackgroundSubtractorMOG(200, 5, 0.7, 15)};
    Mat img_input{};
    while (1)
    {
        //frame = cvQueryFrame(capture);
        //if (!frame)
        //    break;
        systemCapture >> img_input;
        if (img_input.empty())
            break;
        //cv::Mat img_input = cv::cvarrToMat(frame);
        //cv::imshow("Input", img_input);

        // bgs->process(...) internally process and show the foreground mask image
        cv::Mat img_output;
        //bgs->process(img_input, img_mask);
        backgroundSuctractor->apply(img_input, img_output);
        cv::imshow("BGS", img_output);
        if (!img_output.empty())
        {
            // Perform blob tracking
            blobTracking->process(img_input, img_output, img_blob);

            // Perform vehicle counting
            vehicleCouting->setInput(img_blob);
            vehicleCouting->setTracks(blobTracking->getTracks());
            vehicleCouting->process();
        }
        // Press q to quit the program
        if (cv::waitKey(24) == 'q')
            break;
    }

    cvDestroyAllWindows();
    //cvReleaseCapture(&capture);

    return 0;
}
