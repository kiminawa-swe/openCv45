#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


///////////////  Images  //////////////////////

void main() {
	/*VideoCapture cap(0);
	Mat img*/;
	string path = "Resources/gettyimages-95722086-640_adpp.mp4";
	VideoCapture cap(path);
	Mat img;


	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	vector<Rect> plate;

	while (true) {
		cap.read(img);
		if (img.empty())
		{
			cout << "Image not loaded" << endl;
			continue;
		}

		plateCascade.detectMultiScale(img, plate, 1.1, 10);
		for (int i = 0; i < plate.size(); i++)
		{
			Mat imgCrop = img(plate[i]);
			imshow("Plate", imgCrop);
			imwrite("Resources/Plates/plate" + to_string(i) + ".jpg", imgCrop);
			rectangle(img, plate[i].tl(), plate[i].br(), Scalar(255, 0, 255), 3);
		}
		imshow("Image", img);
		waitKey(1);
	}

}