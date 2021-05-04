#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


////////////////////     Images     ////////////////////

//int main() {
//	
//	string path = "Resources/test.png";
//	Mat img = imread(path);
//	imshow("Image", img);
//	waitKey(0);	// wait infinite
//
//}

////////////////////     Video     ////////////////////

//int main() {
//
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true) {
//
//		cap.read(img);
//
//		imshow("Image", img);
//		waitKey(1);
//
//	}
//}

////////////////////     Webcam     ////////////////////

int main() {

	VideoCapture cap(0);
	Mat img;

	while (true) {

		cap.read(img);

		imshow("Image", img);
		waitKey(1);

	}
}