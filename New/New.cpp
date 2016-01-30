// 

#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>

//using namespace cv;
//using namespace std;

int main(){

	cv::Mat image;
	image = cv::imread("../image/ru.jpg");   // Read the file
	uchar *pixptr;
	double a;		//for determine the dark side
	double b;
	double color;
	double cons;

	std::cout << "調色(1~5):";
	std::cin >> color;
	std::cout << "對比度(1~5):";
	std::cin >> cons;

	color = color * 10;
	cons = cons * 10;

	int k;
	if(image.empty()){
		std::cout << "圖片不見了QQ";
		system ("pause");
		return 0;
	}
	for(int i=0; i<image.rows; i++){
		pixptr = image.ptr<uchar>(i);
		for(int j=0; j<image.cols; j++){
			/*if (pixptr[2] < 128){
				if (pixptr[2] < 25.5) pixptr[2] = 0;
				else pixptr[2] = pixptr[2] * 1.3 - 33;
			}
			else pixptr[2] = pixptr[2] * 0.68 + 40;

			pixptr[1] = pixptr[1] * 0.68 + 40;
			
			if (pixptr[2] < 128) pixptr[2] = pixptr[0] * 0.68 + 40;
			*/

			a = pixptr[0] + pixptr[1] + pixptr[2];

			if (a < 390){
				b = (390 - a)/color;
				
				if (pixptr[2] < b) pixptr[2] = 0;		//red
				else pixptr[2] = pixptr[2] - b;

				if (pixptr[1]>(255 - b)) pixptr[1] = 255;
				else pixptr[1] = pixptr[1] + b;		//green

				if (pixptr[0]>(255 - b)) pixptr[0] = 255;
				else pixptr[0] = pixptr[0] + b;		//blue
				
				if (a < 195){
					b = (195-a) / cons;
					b = b*b;
				}
	
				else {
					b = (a-195) / cons;
					b = b*b;
				}

				a = 195 / cons;
				a = a*a;

				for (k = 0; k < 3; k++){
					if (pixptr[k] < a- b) pixptr[k] = 0;
					else if ((pixptr[k] - a + b)>255) pixptr[k] = 255;
					else pixptr[k] = pixptr[k] - a + b;
				}
			}
			
			else {												//light color
				b = (a - 390)/color;
				if (pixptr[2] < b) pixptr[2] = 0;
				else pixptr[2] = pixptr[2] -b ;		//red
				
				if (pixptr[1] < b) pixptr[1] = 0;
				else pixptr[1] = pixptr[1] -b ;		//green
			
				if (a < 578){
					b = (578-a) / cons;
					b = b*b;
				}
				else {
					b = (a-578) / cons;
					b = b*b;
				}

				a = 187 / cons;
				a = a*a;

				for (k = 0; k < 3; k++){
					if ((pixptr[k]+a-b) > 255) pixptr[k] = 255;
					else if (pixptr[k] < (b - a)) pixptr[k] = 0;
					else pixptr[k] = pixptr[k] + a - b;
				}
			}
			
			/*if (pixptr[0]>212) pixptr[0] = 255;
			else pixptr[0] = pixptr[0] * 1.2; //blue
			
			if (pixptr[1]>212) pixptr[1] = 255;
			else pixptr[1] = pixptr[1] * 1.1; //green
			pixptr[2] = pixptr[2] * 0.9; //red
			*/
			
			pixptr+=3;
		}
	}
	cv::imwrite("../image/Result_ru.png", image);
	cv::imshow("Traverse result", image);
    cv::waitKey(0);
	return(0);
}