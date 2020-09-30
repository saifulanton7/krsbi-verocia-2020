#include <iostream>
#include "std_msgs/String.h"
#include <std_msgs/UInt16.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
#include <vector>
#include <sstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cv.h>
#include "ros/ros.h"
#include <stdlib.h>
#include <fstream>

#define XMID 320
#define A_XMAX 55 	//right angle
#define A_XMIN 180	//left angle

#define YMID 240	//mid
#define A_YMAX 30 	//top angle
#define A_YMIN 140	//bottom angle
using namespace cv;
using namespace std;
int posX,posY,ada;
 int main (int argc, char** argv)
 {
	ros::init(argc, argv, "webcam");
	ros::NodeHandle n;
	ros::Publisher camera = n.advertise<std_msgs::String>("camera", 1000);
	ros::Rate loop_rate(10);

	VideoCapture cap(0); //capture the video from webcam	
	if ( !cap.isOpened() )  // if not success, exit program
    	{
        	cout << "Cannot open the web cam" << endl;
        	return -1;
    	}

 	//create a window called "Control"
	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int iLowH  = 0;
	int iHighH = 70;
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
 
	float Y_angle = 55;
	float X_angle = 115;
  	int a = 0;
	
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
		
		vector<vector<Point> > cont;
		vector<Vec4i> hire;

		findContours(imgThresholded,cont,hire,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point(0,0));

		vector<vector<Point> > pol(cont.size());
		vector<Point2f> center(cont.size());
		vector<float> radius(cont.size());
		Mat drawing = Mat::zeros(imgOriginal.size(), CV_8UC3);
                int ball=0;

			for (int i = 0;i < cont.size();i++) {
                        //az=0;bh
			approxPolyDP(Mat(cont[i]),pol[i],arcLength(Mat(cont[i]),true)*0.01,true);
			double a = contourArea(cont[i],false);
			//cout <<"Nilai aaau :"<< pol[i].size()<<" Nilai Luas :"<<a<<endl;
			if ((pol[i].size() >= 5)) {
				if ((a > 500)) {
					minEnclosingCircle(cont[i], center[i], radius[i]);
				}
				if ((radius[i] >= 3)) {
					Rect r = boundingRect(cont [i]);
				        double z=abs(1 - ((double)r.width / r.height));
                                        double w=abs(1 - (a / (3.14 * (radius[i] * radius[i]))));
                                       // cout <<"Nilai aaau :"<< z<<" Nilai Luas :"<<w<<endl;
					if (abs(1 - ((double)r.width / r.height)) <= 0.5 && abs(1 - (a / (3.14 * (radius[i] * radius[i])))) <= 0.5) {                                          
                                                ball++;
						Scalar color = Scalar(0, 0, 240);
						circle(imgOriginal, center[i], (int)radius[i], color, 2, 8, 0);
						circle(imgOriginal, center[i], 2, color, 2, 8, 0);
                                                cout<<"X : "<<center[i].x<<" Y : "<<center[i].y<<endl;
                                                int rads=radius[i];
                                                cout<<"Radius : "<<rads<<endl;
						ada = 1;
                                                //hasil<<rads<<endl;
                                                std_msgs::String msg;
						std::stringstream ss;
						ss << "{\"x\":" << center[i].x;			
						ss << ",\"y\":" << center[i].y;
						msg.data = ss.str() + "}";			
						ROS_INFO("%s", msg.data.c_str());
						camera.publish(msg);
						ros::spinOnce();
					}		
					else
					{


						if(ada==0)
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
							cout<<"X : "<<posX<<" Y : "<<posY<<endl;
                                 			ball = 1;
							std_msgs::String msg;
							std::stringstream ss;
							ss << "{\"x\":" << posX;			
							ss << ",\"y\":" << posY;
							msg.data = ss.str() + "}";			
							ROS_INFO("%s", msg.data.c_str());
							camera.publish(msg);
							ros::spinOnce();
						}
						else ball = 0;
					}
					ada =0;
				}
						
					
			}			
		}
		
		if(ball == 0)
		{
				
			std_msgs::String msg;
			std::stringstream ss;
			ss << "{\"x\":" << 0;			
			ss << ",\"y\":" << 0;
			msg.data = ss.str() + "}";			
			ROS_INFO("%s", msg.data.c_str());
			camera.publish(msg);
			ros::spinOnce();
		}
		cout<<"Jumlah Bola :"<<ball<<endl;
		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		// imshow("Circle Image", imgCircles);
		imshow("HSV", imgHSV);
		imgOriginal = imgOriginal + imgCircles;
  	  	imshow("Original", imgOriginal); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "I'm Out (Verocia20)" << endl;
			break; 
		}
		//return 0;
	}
}

  
