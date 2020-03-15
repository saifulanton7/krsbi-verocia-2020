#include <iostream>
#include "std_msgs/String.h"
#include <vector>
#include <sstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cv.h>
#include "ros/ros.h"
#include <stdlib.h>

#define XMID 320
#define A_XMAX 55 	//right angle
#define A_XMIN 180	//left angle

#define YMID 240	//mid
#define A_YMAX 30 	//top angle
#define A_YMIN 140	//bottom angle
using namespace cv;
using namespace std;
int posX = 0;
int posY = 0;

 int main(int argc, char** argv)
 {
	ros::init(argc, argv, "wabcam");
	ros::NodeHandle n;
	ros::Publisher camera = n.advertise<std_msgs::String>("camera", 1000);
	ros::Rate loop_rate(10);
	
	//ambil gambar dari kamera
	VideoCapture cap(0); //capture the video from webcam
	
	if ( !cap.isOpened() )  // if not success, exit program
    	{
        	cout << "Cannot open the web cam" << endl;
        	return -1;
    	}

 	//create a window called "Control"
	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int iLowH  = 0;
	int iHighH = 140;
	int iLowS  = 58; 
	int iHighS = 255;
	int iLowV  = 193;
	int iHighV = 255;

	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);
	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);
	createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp); 

	//Create a black image with the size as the camera output
	//Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
	Mat imgCircles = Mat::zeros( imgTmp.size(), CV_8UC3 );;
 
	//PROGRAM LOOPING
	while (ros::ok())
	{
        	Mat imgOriginal;
		imgCircles = Mat::zeros(imgTmp.size(), CV_8UC3);
		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
	        {
	             cout << "Cannot read a frame from video stream" << endl;
	             break;
	        }

	    	Mat imgHSV;
	   	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV 
	  	Mat imgThresholded;
	   	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

		//morphological closing (removes small holes from the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

		//Calculate the moments of the thresholded image
		Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

   		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
	  	if(dArea < 100000)
	  	{
			posX = 0;
			posY = 0;
			printf("ROBOT CARI BOLA \n");
	  	}

	  	else
	  	{
			//calculate the position of the ball
			posX = dM10 / dArea;
			posY = dM01 / dArea;         
			Point CircleCenter;
			CircleCenter=Point(posX,posY);
			int Radius;
			Scalar Color;
			int Thickness;
			int Shift;
			Radius=45;
			Color=CV_RGB(0,0,255);
			Thickness=3;
			Shift = 0;
			circle(imgCircles,CircleCenter,Radius,Color,Thickness,CV_AA,Shift); 
		}

		//publish string ros
		std_msgs::String msg;
		std::stringstream ss;
		ss << "{'x':" << posX;
		ss << ",'y':" << posY;
		msg.data = ss.str() + "}";
		ROS_INFO("%s", msg.data.c_str());
		camera.publish(msg);
		ros::spinOnce();

		
		if(posX<=200)
		{
			printf("ROBOT BELOK KIRI \n");
		}

		else if(posX>=430)
		{
			printf("ROBOT BELOK KANAN \n");
		}

		else
		{
			printf("ROBOT MAJU \n");
		}
		

		//tampilkan frame gambar original dan threshold
		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		// imshow("Circle Image", imgCircles);
		imgOriginal = imgOriginal + imgCircles;
  	  	imshow("Original", imgOriginal); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break; 
		}

		loop_rate.sleep();	//wait till next loop		
   }
   return 0;
}
