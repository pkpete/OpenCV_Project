#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


////////////////////     Resize and Crop     ////////////////////

int main() {

	string path = "Resources/test.png"; //768 X 559
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	//cout << img.size() << endl;
	//resize(img, imgResize, Size(640,480));
	resize(img, imgResize, Size(), 0.5, 0.5);

	//roi = region of interest 관심영역
	Rect roi(100, 100, 300, 250);	// 100,100 좌표에서 옆으로 300, 아래로 250 
	imgCrop = img(roi);

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);
	
	waitKey(0);	// wait infinite

}
