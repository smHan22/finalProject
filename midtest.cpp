/*
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat src(500, 700, CV_8UC3, Scalar(255, 255, 255));;
Point pt0ld;
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main() {

	rectangle(src, Rect(0, 0, 700, 500), Scalar(0), 2);
	line(src, Point(500, 0), Point(500, 500), Scalar(0), 2);
	for (int i = 1; i < 5; i++) {
		line(src, Point(500, 500 * i / 5), Point(700, 500 * i / 5), Scalar(0), 2);
	}
	const string text[] = { "Save", "Load", "Clear", "Run", "Exit" };
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 1.5;
	int thickness = 3;

	for (int i = 0; i < 5; i++) {
		Size sizeText = getTextSize(text[i], fontFace, fontScale, thickness, 0);
		Size sizeImg = src.size();
		Point org(250 + (sizeImg.width - sizeText.width) / 2, 500 * i / 5 + (sizeImg.height + sizeText.height) / 8);
		putText(src, text[i], org, fontFace, fontScale, Scalar(0), thickness);
	}
	namedWindow("src");
	setMouseCallback("src", on_mouse);

	imshow("src", src);
	waitKey();
	return 0;
}
void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	Rect rect(0, 0, 495, 500);
	Rect rect1(500, 200, 200, 100);
	switch (event) {
	case EVENT_LBUTTONDOWN:
		pt0ld = Point(x, y);
		if (rect1.contains(Point(x, y))) {
			cout << "�Է�â ������" << endl;
			(*(Mat*)userdata)(Rect(1, 1, 498, 498)) = Scalar(255, 255, 255);
		}
		break;
	case EVENT_LBUTTONUP:
		break;
	case EVENT_MOUSEMOVE:
		if (rect.contains(Point(x, y))) {
			if (flags & EVENT_FLAG_LBUTTON) {
				line(src, pt0ld, Point(x, y), Scalar(0), 10);
				imshow("src", src);
				pt0ld = Point(x, y);
			}
		}
		break;
	default:
		break;
	}
}*/

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Point pt0ld;
void on_mouse(int event, int x, int y, int flags, void* userdata);
Mat src(500, 700, CV_8UC3, Scalar(255, 255, 255));
Mat drawLine();

int main() {
	Mat img = drawLine();
	namedWindow("Windows");
	setMouseCallback("Windows", on_mouse, &img);

	imshow("Windows", img);
	waitKey();
	return 0;
}

Mat drawLine() {
	rectangle(src, Rect(0, 0, 700, 500), Scalar(0, 0, 0), 2);
	rectangle(src, Rect(500, 0, 200, 100), Scalar(0, 0, 0), 2);		// save
	rectangle(src, Rect(500, 100, 200, 100), Scalar(0, 0, 0), 2);		// load
	rectangle(src, Rect(500, 200, 200, 100), Scalar(0, 0, 0), 2);		// clear
	rectangle(src, Rect(500, 300, 200, 100), Scalar(0, 0, 0), 2);		// run
	rectangle(src, Rect(500, 400, 200, 100), Scalar(0, 0, 0), 2);		// exit
	const string text[] = { "Save", "Load", "Clear", "Run", "Exit" };
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 1.5;
	int thickness = 3;
	for (int i = 0; i < 5; i++) {
		Size sizeText = getTextSize(text[i], fontFace, fontScale, thickness, 0);
		Size sizeImg = src.size();
		Point org(250 + (sizeImg.width - sizeText.width) / 2, 500 * i / 5 + (sizeImg.height + sizeText.height) / 8);
		putText(src, text[i], org, fontFace, fontScale, Scalar(0), thickness);
	}
	return src;
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		pt0ld = Point(x, y);
		if (Point(x, y).inside(Rect(500, 200, 200, 100))) {		// clear
			(*(Mat*)userdata)(Rect(0, 0, 500, 500)) = Scalar(255, 255, 255);
			cout << "�Է�â ������" << endl;
			imshow("Windows", (*(Mat*)userdata));
		}
		else if (Point(x, y).inside(Rect(500, 0, 200, 100))) {		// save
			string fileName;
			Mat save = (*(Mat*)userdata)(Rect(1, 1, 499, 499)).clone();
			resize(save, save, Size(500, 500));
			cout << "���ϸ� �Է�: ";
			cin >> fileName;
			imwrite(fileName, save);
			cout << fileName << "�� �����" << endl;
		}
		else if (Point(x, y).inside(Rect(500, 100, 200, 100))) {		// load
			string fileName;
			cout << "���ϸ��� �Է��Ͻÿ�: ";
			cin >> fileName;
			Mat numberImg = imread(fileName);
			rectangle(numberImg, Rect(0, 0, 500, 500), Scalar(0), 2);
			numberImg.copyTo((*(Mat*)userdata)(Rect(0, 0, 500, 500)));
			imshow("Windows", (*(Mat*)userdata));
		}
		else if (Point(x, y).inside(Rect(500, 400, 200, 100))) {		// exit
			exit(1);
		}
		else if (Point(x, y).inside(Rect(500, 300, 200, 100))) {		// run

		}
		break;
	case EVENT_MOUSEMOVE:
		if (Rect(0, 0, 500, 500).contains(Point(x, y))) {
			if (flags & EVENT_FLAG_LBUTTON) {
				line(src, pt0ld, Point(x, y), Scalar(0), 10);
				imshow("Windows", *(Mat*)userdata);
				pt0ld = Point(x, y);
	case EVENT_LBUTTONUP:
		pt0ld = Point(x, y);
		break;
	default:
		break;
			}
		}
	}
}

