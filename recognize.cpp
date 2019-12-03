#include <iostream>
#include <opencv2/opencv.hpp>
#include "process.h"

using namespace std;
using namespace cv;

Num_data data[100000];
int main()
{
	int train_data_count;

	train_data_count = load_model(data);

	cout << "Read train data = " << train_data_count << endl;

	//Test(data, train_data_count);
	
	char c;
	while((c = getc(stdin)) != EOF) {

		char pathname[20] = {};

		sprintf(pathname, "./play/%d.jpg", 1);

		Mat image = imread(pathname, 0);
		if ( !image.data ) {
			printf("No such image !\n");
			return -1;
		}

		image = process(image);

		int number = predict(image, data, train_data_count);

		cout << "Predict number is : "  << number << endl;
	}
	return 0;
}