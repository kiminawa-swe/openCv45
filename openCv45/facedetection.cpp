#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

////////////////////////face detection webcam///////////////////////////



	/*int  main() {

		string path = "Resources/multi face.jpg";
		Mat img = imread(path);

		CascadeClassifier faceCascade;
		faceCascade.load("Resources/haarcascade_frontalface_default.xml");

		if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }

		vector<Rect> faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("Image", img);
		waitKey(0);
	}
*/

int main() {

	VideoCapture cap(0);
	Mat img;

	

	// Optimize 2: Grayscale
	Mat gray;
	//cvtColor(img, gray, COLOR_BGR2GRAY);

	// Check if the webcam opened successfully
	if (!cap.isOpened()) {
		cout << "Error: Could not open webcam." << endl;
		return -1;
	}

	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");

	if (faceCascade.empty()) {
		cout << "XML file not loaded" << endl;
		return -1; // Stop execution if the XML is missing
	}

	while (true) {

		cap.read(img);
		cvtColor(img, gray, COLOR_BGR2GRAY);
		vector<Rect>faces;

		if (img.empty()) {
			cout << "Blank frame grabbed" << endl;
			break;
		}

		// 4. Run face detection on the current frame
		// Tip: You can lower the minNeighbors (e.g., to 3 or 5) for better real-time sensitivity
		faceCascade.detectMultiScale(gray, faces, 1.2, 3);
		

		//draw face with rectangle

		for (int i = 0;i < faces.size();i++) {

			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);

			// i want to put text on the rectangle with the name of my screen

			Point textPos(faces[i].x, faces[i].y - 10);
			putText(img, "Hakimi",textPos , FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 2);
		}

		imshow("webcam image", img);

		waitKey(1); // Wait for 1 ms before moving to the next frame


		


	}
}
