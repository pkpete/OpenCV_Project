#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


////////////////////     Warp Images     ////////////////////

float w = 250, h = 350;
Mat matrix[4], imgWarp[4];

int main() {
	
	string path = "Resources/cards.jpg";
	Mat img = imread(path);

	Point2f src[4][4] = { {{529,142}, {771,190}, {405,395}, {674,457}},
		{{61,312}, {338,276}, {91,633},{405,575}},
		{{739,382},{1024,436},{643,709},{972,784}},
		{{774,105},{1018,80},{839,359},{1119,333}}
	};
	Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h} };

	for (int i = 0; i < 4; i++) {
		matrix[i] = getPerspectiveTransform(src[i], dst);
		warpPerspective(img, imgWarp[i], matrix[i], Point(w, h));
	}
	for (int i = 0; i < 4; i++) {
		for(int j =0; j < 4; j++)
			circle(img, src[i][j], 10, Scalar(0, 0, 255), FILLED);
	}


	imshow("Image", img);
	for (int i = 0; i < 4; i++) {
		imshow("Image Warp" + i, imgWarp[i]);
	}
	waitKey(0);	// wait infinite

}