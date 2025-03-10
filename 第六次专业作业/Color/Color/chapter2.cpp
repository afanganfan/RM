//////////////////LAB颜色空间阈值处理//////////////////




#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int a_min1 = 0, a_max1 = 255;
int b_min1 = 0, b_max1 = 255;
int a_min2 = 0, a_max2 = 255;
int b_min2 = 0, b_max2 = 255;

int main()
{
	VideoCapture cap(0);

	namedWindow("LAB Threshold1", WINDOW_AUTOSIZE);
	namedWindow("LAB Threshold2", WINDOW_AUTOSIZE);

	createTrackbar("A Min1", "LAB Threshold1", &a_min1, 255);
	createTrackbar("A Max1", "LAB Threshold1", &a_max1, 255);
	createTrackbar("B Min1", "LAB Threshold1", &b_min1, 255);
	createTrackbar("B Max1", "LAB Threshold1", &b_max1, 255);

	createTrackbar("A Min2", "LAB Threshold2", &a_min2, 255);
	createTrackbar("A Max2", "LAB Threshold2", &a_max2, 255);
	createTrackbar("B Min2", "LAB Threshold2", &b_min2, 255);
	createTrackbar("B Max2", "LAB Threshold2", &b_max2, 255);

	Mat frame, lab, mask1, mask2;
	vector<vector<Point>> contours;

	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		cvtColor(frame, lab, COLOR_BGR2Lab);

		inRange(lab, Scalar(0, a_min1, b_min1),
			Scalar(255, a_max1, b_max1), mask1);

		inRange(lab, Scalar(0, a_min2, b_min2),
			Scalar(255, a_max2, b_max2), mask2);

		Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
		morphologyEx(mask1, mask1, MORPH_OPEN, kernel);
		morphologyEx(mask2, mask2, MORPH_OPEN, kernel);

		auto draw_contours = [&](Mat& mask, Scalar color) {
			findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			for (const auto& contour : contours) {
				if (contourArea(contour) > 500) {
					Rect rect = boundingRect(contour);
					rectangle(frame, rect, color, 2);
				}
			}
			};

		draw_contours(mask1, Scalar(0, 0, 255));
		draw_contours(mask2, Scalar(0, 255, 0));

		imshow("Camera", frame);
		imshow("LAB Threshold1", mask1);
		imshow("LAB Threshold2", mask2);

		if (waitKey(10) == 27) break;
	}
	return 0;
}