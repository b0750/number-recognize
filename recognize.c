#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>
#include <math.h>
#include "process.h"

using namespace std;
using namespace cv;

Num_data data[100000];
int main()
{
	int train_data_count;
	train_data_count = read_train_data(data);

	cout << "Read train data = " << train_data_count << endl;

	// Just test for one picture.
	char pathname[20] = {};
	sprintf(pathname, "./test/%d.jpg", 1);

	Mat image = imread(pathname, 0);
	if ( !image.data ) {
		printf("No such image !\n");
		return -1;
	}


	image = process(image);

	//print_img(image);

	cout << "Predict number is : "  << predict(image, data, train_data_count) << endl;

  	// 建立視窗
  	namedWindow("Display Image", WINDOW_AUTOSIZE);

  	// 用視窗顯示影像
  	imshow("Display Image", image);

  	// 顯示視窗，直到任何鍵盤輸入後才離開
  	waitKey(0);

	return 0;
}
