#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void capture() {
    //Video Capture begins
    Mat stream;
    namedWindow("Video Stream");
    VideoCapture win1(0);
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    win1.open(deviceID, apiID);
    if (!win1.isOpened()) {
         cout << "No video stream detected\n";
         system("pause");
         return;
    }
    while (1) {
         win1 >> stream;
         if (stream.empty()) {
              break;
         }
         imshow("Video Stream", stream);
         char c = (char)waitKey(35);
         if (c == 27) { //Esc
              break;
         }
     }
     win1.release();
     return;
}
