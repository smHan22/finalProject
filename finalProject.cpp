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
	rectangle(src, Rect(500, 0, 200, 100), Scalar(0, 0, 0), 2);		// save block
	rectangle(src, Rect(500, 100, 200, 100), Scalar(0, 0, 0), 2);		// load block
	rectangle(src, Rect(500, 200, 200, 100), Scalar(0, 0, 0), 2);		// clear block
	rectangle(src, Rect(500, 300, 200, 100), Scalar(0, 0, 0), 2);		// run block
	rectangle(src, Rect(500, 400, 200, 100), Scalar(0, 0, 0), 2);		// exit block
	const string text[] = { "Save", "Load", "Clear", "Run", "Exit" };
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 1.5;
	int thickness = 2;
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
			cout << "입력창 삭제됨" << endl;
			imshow("Windows", (*(Mat*)userdata));
		}
		else if (Point(x, y).inside(Rect(500, 0, 200, 100))) {		// save
			string fileName;
			Mat save = (*(Mat*)userdata)(Rect(1, 1, 499, 499)).clone();
			resize(save, save, Size(500, 500));
			cout << "파일명 입력: ";
			cin >> fileName;
			imwrite(fileName, save);
			cout << fileName << "이 저장됨" << endl;
		}
		else if (Point(x, y).inside(Rect(500, 100, 200, 100))) {		// load
			string fileName;
			cout << "파일명을 입력하시오: ";
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
		if (Rect(0, 0, 495, 500).contains(Point(x, y))) {
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