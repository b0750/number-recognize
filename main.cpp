#include <iostream>

#include "mnist.h"

using namespace cv;
using namespace std;

string trainImage = "C:\\opencv\\mnist\\train-images.idx3-ubyte";
string trainLabel = "C:\\opencv\\mnist\\train-labels.idx1-ubyte";
string testImage = "C:\\opencv\\mnist\\t10k-images.idx3-ubyte";
string testLabel = "C:\\opencv\\mnist\\t10k-labels.idx1-ubyte";



int main()
{
	readAndSave(trainImage, trainLabel);
	return 0;
}
