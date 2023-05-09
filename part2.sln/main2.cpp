#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <dirent.h>
using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Usage: ./part2 <dir of Images to be analyzed>" << endl;
		return 2;
	}
        struct dirent* entry;
	char* dir = strdup(argv[1]);
        DIR* dp = opendir(dir);
        //Iterate over image directory
        //assuming all files are images to be analyzed
	while ((entry = readdir(dp))) {
		std::cout << entry->d_name << std::endl;
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
continue;
}
                std::string img_path = dir;
                img_path = img_path + "/" + entry->d_name;
		Mat img = imread(img_path, 0);
		Mat img_blur;
                //preprocessing using Gaussian Blur
		GaussianBlur(img, img_blur, Size(3,3), 0);
		Mat edges;
                //Canny Edge detection
		Canny(img_blur, edges, 100, 200, 3, false);
                //TBD: Deep Learning Blank Image Detection here
	}
	return 0;
}  
