#include <opencv2/opencv.hpp>
#include <iostream>
#define train_pictures_per_number 1000	// Number of pictures we want for a given number in train_data.
#define test_pictures_per_number 100 // Number of pictures we want for a given number in test_data.
#define INF 1000000007
#define K_value 11	// Find the K-nearest neighbor.

using namespace cv;
using namespace std;

typedef pair<long long int, int> P;
typedef struct Num_data
{
	int number;
	Mat picture;
}Num_data;

Mat cut(Mat &img);
Mat process(Mat &img);
int read_train_data(Num_data data[]);
int predict(Mat &image, Num_data data[], int train_data_count);
long long int find_distance(Mat &img1, Mat &img2);
void print_img(Mat &img);
