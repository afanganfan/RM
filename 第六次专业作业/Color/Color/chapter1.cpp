////////////////////HSV Thresholding////////////////////


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int h_min1 = 0, s_min1 = 0, v_min1 = 0;
int h_max1 = 179, s_max1 = 255, v_max1 = 255;

int h_min2 = 0, s_min2 = 0, v_min2 = 0;
int h_max2 = 179, s_max2 = 255, v_max2 = 255;

int main()
{
	VideoCapture cap(0);

	namedWindow("Threshold1", WINDOW_AUTOSIZE);
	namedWindow("Threshold2", WINDOW_AUTOSIZE);

	createTrackbar("H Min1", "Threshold1", &h_min1, 179);
	createTrackbar("H Max1", "Threshold1", &h_max1, 179);
	createTrackbar("S Min1", "Threshold1", &s_min1, 255);
	createTrackbar("S Max1", "Threshold1", &s_max1, 255);
	createTrackbar("V Min1", "Threshold1", &v_min1, 255);
	createTrackbar("V Max1", "Threshold1", &v_max1, 255);

	createTrackbar("H Min2", "Threshold2", &h_min2, 179);
	createTrackbar("H Max2", "Threshold2", &h_max2, 179);
	createTrackbar("S Min2", "Threshold2", &s_min2, 255);
	createTrackbar("S Max2", "Threshold2", &s_max2, 255);
	createTrackbar("V Min2", "Threshold2", &v_min2, 255);
	createTrackbar("V Max2", "Threshold2", &v_max2, 255);

	Mat frame, hsv, mask1, mask2;
	vector<vector<Point>> contours;

	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		cvtColor(frame, hsv, COLOR_BGR2HSV);

		inRange(hsv, Scalar(h_min1, s_min1, v_min1),
			Scalar(h_max1, s_max1, v_max1), mask1);
		inRange(hsv, Scalar(h_min2, s_min2, v_min2),
			Scalar(h_max2, s_max2, v_max2), mask2);

		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(mask1, mask1, MORPH_OPEN, kernel);
		morphologyEx(mask2, mask2, MORPH_OPEN, kernel);

		auto draw_contours = [&](Mat mask, Scalar color) {
			findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			for (const auto& contour : contours) {
				if (contourArea(contour) > 500) {
					Rect rect = boundingRect(contour);
					rectangle(frame, rect, color, 2);
				}
			}
			};

		draw_contours(mask1, Scalar(0, 255, 0));
		draw_contours(mask2, Scalar(0, 0, 255));

		imshow("Camera", frame);
		imshow("Threshold1", mask1);
		imshow("Threshold2", mask2);

		if (waitKey(10) == 27) break;
	}
	return 0;
}