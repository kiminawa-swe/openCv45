#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//project 1 virtual paint///////////////////////////


////////////////////  COLOR VALUES ////////////////////////////////

Mat img;
vector<vector<int>> newPoint; //vector to store the detected points in the format {x,y,colorIndex}

//detected color values
vector<vector<int>> myColors{ {68,0,195,179,255,255} //pink
	 }; //green

//color on canvas
vector<Scalar> myColorValues{ {255,0,255} //pink
	 }; //green


	
Point getContour(Mat imgDil) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;
		string objectType;


		if (area > 1000) {

			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;


			drawContours(img, conPoly, i, Scalar(255, 0, 255), 5); //draw the contours of the detected object with pink color
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

		}
	}



	return myPoint;
}

vector<vector<int>> findColor(Mat img){

	Mat imgHSV, mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV); //convert to HSV first

	for (int i = 0;i < myColors.size();i++) {

		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);  //basically we use the 2d array to get the color values for the lower and upper range of the color we want to detect
		inRange(imgHSV, lower, upper, mask);


		//imshow(to_string(i), mask);

		Point myPoint=getContour(mask);

		newPoint.push_back({ myPoint.x, myPoint.y, i }); //we push the detected point into the newPoint vector along with the color index

	}
	return newPoint;
}

void drawOnCanvas(vector<vector<int>> newPoint, vector<Scalar> myColorValues) {
	for (int i = 0; i < newPoint.size(); i++) {
		circle(img, Point(newPoint[i][0], newPoint[i][1]), 10, myColorValues[newPoint[i][2]], FILLED); //draw a circle on the detected point with the color of the detected object
	}
}

int main() {

	
	VideoCapture cap(0);
	

	while (true) {

		cap.read(img);
		
		newPoint=findColor(img);
		drawOnCanvas(newPoint, myColorValues);
		imshow("Image", img);
		waitKey(1);
	}
}


