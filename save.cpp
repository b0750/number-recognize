#include <iostream>
#include <assert.h>
#include "process.h"
using namespace std;
using namespace cv;

Num_data saver[100000];
int main()
{
	int train_data_count;
	train_data_count = read_train_data(saver);

	for (int i = 0; i < train_data_count; i++) {
		char pathname[30] = {};
		sprintf(pathname, "./train_model/%d_%d.jpg", saver[i].number, i);
		imwrite(pathname, saver[i].picture);
	}
	return 0;
}
