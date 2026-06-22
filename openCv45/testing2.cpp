#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	//string path = "Resources/test.png";
	//Mat img = imread(path);

	//Mat imgResize, imgCrop;

	//resize(img, imgResize, Size(),0.5,0.5);// syntax: resize(src, dst, dsize) 

	//Rect roi(100, 100, 300, 250); // x, y, width, height
	//imgCrop = img(roi);

	//imshow("Image", img);
	//imshow("Image Crop", imgCrop);
	//imshow("Image Resize", imgResize);
	//waitKey(0);



	// Blank Image 
	//Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));

	//circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED); //input directly into img, no need to create a new image
	//putText(img, "Murtaza's Workshop", Point(137, 262), FONT_HERSHEY_PLAIN, 5, Scalar(0, 0, 0), 2);


	/*imshow("Blank Image", img);
	waitKey(0);*/



	//string path = "Resources/cards.jpg";
	//Mat img = imread(path);
	//Mat matrix, imgWarp;

	//float w = 250, h = 350;

	//Point2f src[4] = { { 780, 107 },{ 1008, 89 },{ 842, 352 },{ 1110, 338 } };
	//Point2f dst[4] = { { 0.0f, 0.0f },{ w, 0.0f },{ 0.0f, h },{ w, h } };

	//matrix = getPerspectiveTransform(src, dst); //its to get the matrix for the perspective transform, it takes 2 arrays of points, the source and destination points
	//warpPerspective(img, imgWarp, matrix, Point(w, h));// syntax: warpPerspective(src, dst, M, dsize) where M is the transformation matrix and dsize is the size of the output image

	//for (int i = 0; i < 4; i++) {
	//	circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	//}

	//imshow("Image", img);
	//imshow("Warped Image", imgWarp);
	//waitKey(0);


	///////////////  Color Detection  //////////////////////

	//basically change color space from BGR to HSV and then use inRange function to create a mask for the color we want to detect, then we can use the mask to extract the color from the original image

	string path = "Resources/lambo.png";
	Mat img = imread(path);
	Mat imgHSV, mask;
	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;


	cvtColor(img, imgHSV, COLOR_BGR2HSV); //imgHSV is the image in HSV color space, COLOR_BGR2HSV is the conversion code from BGR to HSV (HSV is hue, saturation, value)

	//create a window with trackbars to adjust the HSV values
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}

}