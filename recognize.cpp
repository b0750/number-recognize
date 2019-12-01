#include <iostream>
#include <opencv2/opencv.hpp>
#include "process.h"

using namespace std;
using namespace cv;

void Test(Num_data data[], int train_data_count);

Num_data data[100000];
int main()
{
	int train_data_count;

	train_data_count = read_train_data(data);

	cout << "Read train data = " << train_data_count << endl;

	Test(data, train_data_count);

	// Just test for one picture.
	/*char pathname[20] = {};

	sprintf(pathname, "./test/%d.jpg", 1);

	Mat image = imread(pathname, 0);
	if ( !image.data ) {
		printf("No such image !\n");
		return -1;
	}

	image = process(image);

	print_img(image);

	int number = predict(image, data, train_data_count);

	cout << "Predict number is : "  << number << endl;

	sprintf(pathname, "./predict/%d.jpg", number);

	image = imread(pathname, 0);

  	// 建立視窗
  	namedWindow("Display Image", WINDOW_AUTOSIZE);

  	// 用視窗顯示影像
  	imshow("Display Image", image);

  	// 顯示視窗，直到任何鍵盤輸入後才離開
  	waitKey(0);*/

	return 0;
}

void Test(Num_data data[], int train_data_count)
{
	Mat image;
	int total = 0;
	int error = 0;

	for (int n = 0; n <= 9; n++) {
		int count = 0;
		int num_err = 0;
		for (int i = 4000; count != test_pictures_per_number; i++) {
			char pathname[20] = {};
			sprintf(pathname, "./test/%d_%d.jpg", n, i);
			image = imread(pathname, 0);
			if (image.data) {
				total++;
				count++;
				image = process(image);
				int predict_num = predict(image, data, train_data_count);
				if (predict_num != n) {
					error++;
					num_err++;
				}
			}
		}
		printf("%d error times = %d\n", n, num_err);
	}
	printf("Total = %d error times = %d\n", total, error);
	printf("Error rate = %.4f\n", float(error) / total);
}
