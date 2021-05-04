#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


////////////////////     Project 1     ////////////////////

Mat img;
vector<vector<int>> newPoints;

//hmin, smin, vmin, hmax, smax, vmax
vector<vector<int>> myColors{ {159, 170, 131, 172, 238, 196},   //red
							{89, 120, 105, 113, 197, 165},	//blue
							{24, 94, 91, 36, 255, 255} };	//yellow

vector<Scalar> myColorValues{ {0,0,255},
							{255,0,1},
							{0,228,255} };

Point getContours(Mat imgDil) {	// 도형의 윤곽선 그리기

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++) {

		string objectType;
		int area = contourArea(contours[i]);	// 도형의 넓이

		if (area > 1000) {	// 노이즈는 무시
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);	// 꼭지점으로 연결

			boundRect[i] = boundingRect(conPoly[i]);	// 각 도형에 사각형 그리기

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			//drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); // 사각형 그린거 표시하기
		}
	}
	return myPoint;
}

void findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);
		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoints.push_back({ myPoint.x, myPoint.y, i });
		}
	}
}

void drawOnCanvas() {
	for (int i = 0; i < newPoints.size(); i++) {
		circle(img, Point(newPoints[i][0],newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}

int main() {

	VideoCapture cap(0);

	while (true) {

		cap.read(img);

		findColor(img);
		drawOnCanvas();
		imshow("Image", img);
		waitKey(1);

	}
}