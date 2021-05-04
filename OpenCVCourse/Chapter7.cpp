#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


////////////////////     Shapes     ////////////////////

Mat imgGray, imgBlur, imgCanny, imgDil;

void getContours(Mat imgDil, Mat img) {	// 도형의 윤곽선 그리기

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {

		string objectType;
		int area = contourArea(contours[i]);	// 도형의 넓이
		cout << area << endl;

		if (area > 1000) {	// 노이즈는 무시
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);	// 꼭지점으로 연결
			//drawContours(img, contours, i, Scalar(255, 0, 255), 2);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << endl;	//꼭지점 갯수

			boundRect[i] = boundingRect(conPoly[i]);	// 각 도형에 사각형 그리기
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

			int objCor = (int)conPoly[i].size();

			if (objCor == 3) { objectType = "Tri"; }
			else if (objCor == 4) { 
				float aspRatio = (float)boundRect[i].width / boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05)
					objectType = "Square";
				else
					objectType = "Rect"; 
			}
			else if (objCor > 4) { objectType = "Circle"; }

			putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 70, 255), 1.5);
		}
	}
}


int main() {
	
	string path = "Resources/shapes.png";
	Mat img = imread(path);

	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);	//흑백
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);	// 흐릿하게
	Canny(imgBlur, imgCanny, 50, 50);	// 검정배경 흰색 윤곽
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);	//윤곽선 찐하게

	getContours(imgDil, img);

	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dil", imgDil);
	waitKey(0);	// wait infinite

}