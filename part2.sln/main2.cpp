#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./part2 <dir of Images to be analyzed>" << endl;
        return 2;
    }
    char* dir = strdup(argv[1]);
    Mat img = imread("Image-1.jpg", 0);
    Mat img_blur;
    GaussianBlur(img, img_blur, Size(3,3), 0);
    Mat edges;
    Canny(img_blur, edges, 100, 200, 3, false);
    return 0;
}  
