#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
#include <vector>
#include <math.h>
#include "process.h"

using namespace cv;
using namespace std;

Mat cut(Mat &img)
{
	int left = -1, right = -1, up = -1, down = -1;

	bool x = true;

	for (size_t nrow = 0; nrow < img.rows; nrow++)
	{
		uchar *val = img.ptr<uchar>(nrow);
		for (size_t ncol = 0; ncol < img.cols; ncol++)
		{
			if ((val[ncol] > 200) && x == true) {
				up = nrow;
				left = ncol;
				right = ncol;
				x = false;
			}
			else if ((val[ncol] > 200) && x == false) {
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
	Rect rect(left,	up, right - left, down - up); //創一個矩形，(左上角x，左上角y，寬度，高度)
	Mat image = Mat(img, rect);

	return image;
}

Mat process(Mat &img) {          //主要引用的函式
	Mat cut_img;

	//cvtColor(img, gray_img, COLOR_BGR2GRAY);//灰階

	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));//自定義核

	//morphologyEx(t_img, open_img, MORPH_OPEN, element);//開運算消雜質

	cut_img = cut(img);//切下數字

	Mat resize_img(28, 28, cut_img.type());//範本尺寸為28*28

	resize(cut_img, resize_img, resize_img.size(), 0, 0, INTER_LINEAR);//縮放大小

	threshold(resize_img, resize_img, 128, 255, CV_THRESH_BINARY);

	return resize_img;
}

void print_img(Mat &img)
{
	for (int r = 0; r < img.rows; r++) {
		uchar *val = img.ptr<uchar>(r);
		for (int c = 0; c < img.cols; c++) {
			printf("%3d ", val[c]);
		}
		printf("\n");
	}
}

int read_train_data(Num_data data[])
{
	int data_count = 0;
	// Number from 0 to 9.
	for (int n = 0; n <= 9; n++) {
		// Record how many picture do we get.
		int pic_read = 0;
		for (int i = 1; pic_read != train_pictures_per_number; i++) {
			Mat image;
			char pathname[20] = {};
			// Read picture from ./train/n_i.
			sprintf(pathname, "./train/%d_%d.jpg", n, i);	// You can change this pathname whenever you want !
			image = imread(pathname, 0);
			// Assert that we always get 100 picture.
			if ( !image.data ) {
				continue;
			} else {
				image = process(image);
				data[data_count].number = n;
				data[data_count].picture = image;
				pic_read++;
				data_count++;
			}
		}
	}
	return data_count;
}

int predict(Mat &image, Num_data data[], int train_data_count)
{
	// Try by KNN. Just for test.
	priority_queue<P, vector<P>, greater<P> > que;
	long long int distance;

	for (int i = 0; i < train_data_count; i++) {
		distance = find_distance(image, data[i].picture);
		que.push(P(distance, data[i].number));
	}

	int number[10] = {};

	for (int i = 0; i < K_value; i++) {
		P get_p = que.top();
		int num = get_p.second;
		que.pop();
		number[num] += 1;
	}

	int select_num;
	int max_appears = -1*INF;

	for (int n = 0; n <= 9; n++) {
		if (number[n] > max_appears) {
			select_num = n;
			max_appears = number[n];
		}
	}

	//printf("Number %d appears %d times.\n", select_num, max_appears);

	return select_num;
}

long long int find_distance(Mat &img1, Mat &img2)
{
	int row = img1.rows;
	int col = img1.cols * img1.channels();
	long long int distance = 0;

	for (int r = 0; r < row; r++) {
		uchar *pic1 = img1.ptr<uchar>(r);
		uchar *pic2 = img2.ptr<uchar>(r);
		for (int c = 0; c < col; c++) {
			distance += sqrt((pic1[c] - pic2[c]) * (pic1[c] - pic2[c]));
		}
	}
	return distance;
}
