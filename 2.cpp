#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/types.hpp>
#include <cstdio>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;



int main()
{
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	CascadeClassifier mouth_cascade;
	CascadeClassifier cascade, nestedCascade;
	Mat grayscale, frame;
	VideoCapture video;
	vector<Rect> V;

	if (!face_cascade.load(
		"D://qqwe/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"))
	{
		cout << "--(!)Error loading face cascade\n";
		return -1;
	}
	if (!eyes_cascade.load(
		"D://qqwe/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml"))
	{
		cout << "--(!)Error loading eyes cascade\n";
		return -1;
	}
	
	if (!mouth_cascade.load(
		"./harrcascade/haarcascade_smile.xml"))
	{
		cout << "--(!)Error loading smile cascade\n";
		return -1;
	}

	
	if (!video.open(0))
	{
		cout << "Capture from camera #" << 0 << " didn't work" << endl;
		return 1;
	}
	
	if (video.isOpened())
	{
		cout << "Video capturing has been started ..." << endl;
		while(1)
		{
			
			if (!video.read(frame))
				break;
			
			cvtColor(frame, grayscale, COLOR_BGR2GRAY);
			equalizeHist(grayscale, grayscale);
			face_cascade.detectMultiScale(grayscale, V, 1.1, 1, 0, Size(150,150), Size(500,500));
			std::vector<Rect> eyes;
			for (size_t i = 0; i < V.size(); i++)
			{
				Point center(V[i].x + V[i].width / 2, V[i].y + V[i].height / 2);
				ellipse(frame, center, Size(V[i].width / 2, V[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 2);
				Mat faceROI = grayscale(V[i]);
				//-- In each face, detect eyes
				//std::vector<Rect> eyes;
				eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2);
				for (size_t j = 0; j < eyes.size(); j++)
				{
					Point eye_center(V[i].x + eyes[j].x + eyes[j].width / 2, V[i].y + eyes[j].y + eyes[j].height / 2);
					int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
					circle(frame, eye_center, radius, Scalar(255, 0, 0), 2);
				}
			}

			imshow("Capture - Face detection", frame);

			char c = (char)waitKey(10);
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
	//Mat img = cv::imread("./face1.jpg");
	////cascade.load("lenna.jpg");
	//if (img.empty())
	//{
	//	cout << "Couldn't read imgfile" << endl;
	//	return 1;
	//}
	//
	//cvtColor(img, grayscale, COLOR_BGR2GRAY);
	//equalizeHist(grayscale, grayscale);
	//
	//face_cascade.detectMultiScale(grayscale, V);

	////cascade.detectMultiScale(grayscale, V, 1.1, 2, 0| CASCADE_DO_CANNY_PRUNING, Size(30, 30),Size(150,150));
	//cout << V.size()<<"\n"<<endl;
	//std::vector<Rect> eyes;
	//for (size_t i = 0; i < V.size(); i++)
	//{
	//	Point center(V[i].x + V[i].width / 2, V[i].y + V[i].height / 2);
	//	ellipse(img, center, Size(V[i].width / 2, V[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 2);
	//	Mat faceROI = grayscale(V[i]);
	//	//-- In each face, detect eyes
	//	//std::vector<Rect> eyes;
	//	eyes_cascade.detectMultiScale(faceROI, eyes);
	//	for (size_t j = 0; j < eyes.size(); j++)
	//	{
	//		Point eye_center(V[i].x + eyes[j].x + eyes[j].width / 2, V[i].y + eyes[j].y + eyes[j].height / 2);
	//		int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
	//		circle(img, eye_center, radius, Scalar(255, 0, 0), 2);
	//	}
	//}
	//
	//imshow("Capture - Face detection", img);
	//
	//
	//
	//for (size_t i = 0; i < eyes.size(); i++) {
	//	cout << eyes[i].x << " " << eyes[i].y << " " << eyes[i].width << " " << eyes[i].height << endl;
	//}


	//waitKey();
	//
}