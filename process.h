#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat cut(Mat img)
{
	int left, right, up, down;

	bool x = true;

	for (size_t nrow = 0; nrow < img.rows; nrow++)
	{
		for (size_t ncol = 0; ncol < img.cols; ncol++)
		{
			uchar val = img.at<uchar>(nrow, ncol);
			if ((val > 200) && x == true) {
				up = nrow;
				left = ncol;
				right = ncol;
				x = false;
			}
			else if ((val > 200) && x == false) {
				down = nrow;
				if (ncol < left) {
					left = ncol;
				}
				else if (ncol > right) {
					right = ncol;
				}
			}
		}
	}

	Rect rect(left, up, right - left, down - up); //創一個矩形，(左上角x，左上角y，寬度，高度) 

	return Mat(img, rect);//從圖中切下指定範圍
}


Mat process(Mat img) {          //主要引用的函式
	Mat result, gray_img, t_img, open_img, cut_img;

	cvtColor(img, gray_img, COLOR_BGR2GRAY);//灰階

	threshold(gray_img, t_img, 100, 255, 1);//黑字

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));//自定義核

	morphologyEx(t_img, open_img, MORPH_OPEN, element);//開運算消雜質

	cut_img = cut(open_img);//切下數字

	Mat resize_img(28, 28, cut_img.type());//範本尺寸為28*28

	resize(cut_img, resize_img, resize_img.size(), 0, 0, INTER_LINEAR);//縮放大小

	return resize_img;
}
