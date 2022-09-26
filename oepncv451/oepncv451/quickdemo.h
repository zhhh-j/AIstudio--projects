#pragma once

#include<opencv2/opencv.hpp>

using namespace cv;



class QuickDemo {
	public:
		void colorSpace_Demo(Mat &image);
		void mat_creation_demo(Mat &image);
		void pixel_visit_demo(Mat &image);
		void operators_demo(Mat &image);
		void track_bar_demo(Mat &image);
		void key_demo(Mat &image);
		void color_map_demo(Mat &image);
		void bitwise_demo(Mat &image);
		void channels_demo(Mat &image);
		void inrange_demo(Mat &image);
		void pixel_statistic_Demo(Mat &image);
		void drawing_demo(Mat &image);
		void random_drawing();
		void polyline_drawing();
		void mouse_drawing_demo(Mat &image);
		void norm_demo(Mat &image);
		void resize_demo(Mat &image);
		void flip_demo(Mat &image);
		void warpAffine_demo(Mat &image);
		void video_demo();
		void showHistogram(Mat &image);
		void histogram_2d_demo(Mat &image);
		void histogram_eq_demo(Mat &image);
		void blur_demo(Mat &image);
		void face_detection_demo();
		void kmeans_demo(Mat &image);
		void mean_shift(Mat &image);
		void SingleScaleRetinex(const cv::Mat &src, cv::Mat &dst, int sigma);
		void MultiScaleRetinex(const cv::Mat &src, cv::Mat &dst, int k, std::vector<double> w, std::vector<double> sigmas);
		void MultiScaleRetinexCR(const cv::Mat &src, cv::Mat &dst, int k, std::vector<double> w, std::vector<double> sigmas, int alpha, int beta, int gain, int offset);
};