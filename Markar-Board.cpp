#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#define mat Mat
#define str string

using namespace std;
using namespace cv;

  /*******************  Make Changes Here *****************/
 
 int webCamID = 0; //put your webcam ID here
 

 
 //HSV values
 //   format :
 //   hmin, smin, vmin, hma, smax, vmax;
 vector<vector<int>> myColors { { 68, 72, 156, 102, 126, 255 },  //Green Value  
                                {124, 48, 117, 143, 170, 255}};  //Purple Value
 
 //Scalar for green and purple colour
 vector<Scalar> myColorValues {{0, 255, 0},   //Green
	                         {255,0,255 }};   //Purplpe

   /******************** No Changes Below ********************/


 str path;
mat img;
vector<vector<int>> newPoints;



Point getContours(mat imgDil)
{
	vector<vector<Point>>  contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	Point myPoint(0, 0);


	for (int i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		cout << area << endl;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			boundRect[i] = boundingRect(conPoly[i]); 

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 1);
		}

	}
	return myPoint;
}



vector<vector<int>> findcolor(mat img)
{
	mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	 
	for (int i = 0; i < myColors.size(); i++)
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		mat mask;
		inRange(imgHSV, lower, upper, mask);

		//imshow(to_string(i), mask);
		
		Point myPoint = getContours(mask);
		if (myPoint.x != 0 && myPoint.y != 0) 
		{
			newPoints.push_back({myPoint.x, myPoint.y, i});
		}
	}
	return newPoints;
}



void DrawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColourValues)
{

	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, Point(newPoints[i][0],newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
} 


int main()
{
	VideoCapture cap(webCamID);
	while (true)
	{
		cap.read(img);
		newPoints = findcolor(img);
		DrawOnCanvas(newPoints, myColorValues);

		imshow("Web Cam", img);
		waitKey(1);
	}
	return 0;
}
