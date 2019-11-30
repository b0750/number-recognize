#include <iostream>
#include <opencv2/opencv.hpp>
#include "process.h"
#define train_pictures_per_number 200	// Number of pictures we want for a given number in train_data.
#define test_pictures_per_number 1 // Number of pictures we want for a given number in test_data.
#define INF 1000000007

using namespace std;
using namespace cv;

typedef struct Num_data
{
	int number;
	Mat picture;
}Num_data;

int read_train_data();
int predict(Mat &image);
int find_distance(Mat &img1, Mat &img2);

Num_data data[10000];
int train_data_count;

int main()
{
	train_data_count = read_train_data();

	cout << "Read train data = " << train_data_count << endl;

	// Just test for one picture.
	char pathname[20] = {};
	sprintf(pathname, "./test/%d.jpg", 1);

	Mat image = imread(pathname, 1);
	if ( !image.data ) {
		printf("No such image !\n");
		return -1;
	}


	//image = process(image);	// This process may break the picture !
	cout << "Predict number is : "  << predict(image) << endl;

  	// 建立視窗
  	namedWindow("Display Image", WINDOW_AUTOSIZE);

  	// 用視窗顯示影像
  	imshow("Display Image", image);

  	// 顯示視窗，直到任何鍵盤輸入後才離開
  	waitKey(0);

	return 0;
}

int read_train_data()
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
			image = imread(pathname, 1);
			// Assert that we always get 100 picture.
			if ( !image.data ) {
				continue;
			} else {
				data[data_count].number = n;
				data[data_count].picture = image;
				pic_read++;
				data_count++;
			}
		}
	}
	return data_count;
}

int predict(Mat &image)
{
	// Try by 1NN. Just for test.
	int nearest_num;
	int nearest_distance = INF;
	int distance;

	for (int i = 0; i < train_data_count; i++) {
		distance = find_distance(image, data[i].picture);
		if (distance < nearest_distance) {
			nearest_num = data[i].number;
			nearest_distance = distance;
		}
	}

	return nearest_num;
}

int find_distance(Mat &img1, Mat &img2)
{
	int row = img1.rows;
	int col = img1.cols * img1.channels();
	int distance = 0;

	for (int r = 0; r < row; r++) {
		uchar *pic1 = img1.ptr<uchar>(r);
		uchar *pic2 = img2.ptr<uchar>(r);
		for (int c = 0; c < col; c++) {
			distance += (pic1[c] - pic2[c]) * (pic1[c] - pic2[c]);
		}
	}
	return distance;
}
