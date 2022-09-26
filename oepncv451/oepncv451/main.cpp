#include<quickdemo.h>
#include<iostream>

using namespace std;




int main(int argc, char** aggv) {
	// ����͸��ͨ��  Mat src = imread("D:/cvwk/oepncv451/pics/s.jpg", IMREAD_UNCHANGED);
	Mat src = imread("//Ds418/nas3/ZHC/22V19-LG-black/raw_data/20220920/©������/0920-���22v19����©��-35pcs/4_3_1_2.bmp"); // BGR
	//Mat src = imread("D:/cvwk/oepncv451/pics/TEST.png"); // BGR
	Mat dst = Mat(src.size(), CV_32FC3);
	// ���ɴ���
	if (src.empty()) {
		printf("could not load image\n");
		return -1;
	}
	cv::resize(src, src, Size(0, 0), 0.125, 0.125);
	namedWindow("���봰��", WINDOW_FREERATIO);
	imshow("���봰��", src); // ������8λ��
	
	

	QuickDemo qd;
	int k = 3;
	vector<double> w = {0.33, 0.33, 0.34};
	vector<double> sigmas = {15, 80, 200};
	qd.MultiScaleRetinexCR(src, dst, k, w, sigmas, 1, 1, 1, 0);

	//imwrite("D:/cvwk/oepncv451/pics/14_3_1_2.bmp", dst);
	imshow("���봰��", dst); // ������8λ��
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}



