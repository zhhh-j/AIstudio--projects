#include<quickdemo.h>
#include<iostream>

using namespace std;




int main(int argc, char** aggv) {
	// 加载透明通道  Mat src = imread("D:/cvwk/oepncv451/pics/s.jpg", IMREAD_UNCHANGED);
	Mat src = imread("//Ds418/nas3/ZHC/22V19-LG-black/raw_data/20220920/漏检数据/0920-左侧22v19菱格黑漏检-35pcs/4_3_1_2.bmp"); // BGR
	//Mat src = imread("D:/cvwk/oepncv451/pics/TEST.png"); // BGR
	Mat dst = Mat(src.size(), CV_32FC3);
	// 自由窗口
	if (src.empty()) {
		printf("could not load image\n");
		return -1;
	}
	cv::resize(src, src, Size(0, 0), 0.125, 0.125);
	namedWindow("输入窗口", WINDOW_FREERATIO);
	imshow("输入窗口", src); // 必须是8位的
	
	

	QuickDemo qd;
	int k = 3;
	vector<double> w = {0.33, 0.33, 0.34};
	vector<double> sigmas = {15, 80, 200};
	qd.MultiScaleRetinexCR(src, dst, k, w, sigmas, 1, 1, 1, 0);

	//imwrite("D:/cvwk/oepncv451/pics/14_3_1_2.bmp", dst);
	imshow("输入窗口", dst); // 必须是8位的
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}



