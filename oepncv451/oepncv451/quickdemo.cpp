#include"quickdemo.h"
#include<opencv2/dnn.hpp>

using namespace cv;
using namespace std;

void QuickDemo::colorSpace_Demo(Mat &image) {
	Mat gray, hsv;

	// H 0~180 S,V 0-255  ��V���ȣ� ��S���Ͷȣ� H��ɫ����
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("HSV", hsv);
	imshow("�Ҷ�", gray);
	//imwrite("D:/cvwk/oepncv451/pics/hsv.png",hsv);
	//imwrite("D:/cvwk/oepncv451/pics/gray.png", gray);
}

void QuickDemo::mat_creation_demo(Mat &image) {
	//Mat m1, m2;
	//m1 = image.clone();
	//image.copyTo(m2);

	// �����հ�ͼ��
	// 8UC1 8λ�޷��� 3ͨ�� 
	// Mat::ones()
	Mat m3 = Mat::zeros(Size(512, 512), CV_8UC3);

	//����ָ����ֵ
	m3 = Scalar(255, 127, 0);
	std::cout << "width:" << m3.cols << " height" << m3.rows <<" channels:"<<m3.channels()<<std::endl; //���
	imshow("test", m3);

	Mat m4 = m3; //��ֵ m4��m3ָ��ͬһ����ַ 

	//std::cout << m3 << std::endl;
}

void QuickDemo::pixel_visit_demo(Mat &image) {
	int w = image.cols; //uchar��
	int h = image.rows;
	int dims = image.channels();

	// �����±�
	/* 
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) { //�Ҷ�ͼ��
				int pv = image.at<uchar>(row, col); //�õ�ͼ����(row,col)��������(y,x)
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3) { //��ɫͼ��
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	} 
	*/

	//����ָ��
	for (int row = 0; row < h; row++) {
		uchar *current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) { //�Ҷ�ͼ��
				int pv = *current_row; //�õ�ͼ����(row,col)��������(y,x)
				*current_row++ = 255 - pv;
				
			}
			if (dims == 3) { //��ɫͼ��
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	} 
	imshow("���ظı�", image);
}

void QuickDemo::operators_demo(Mat &image) {
	Mat dst;
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(50, 50, 50);

	//����
	dst = image/Scalar(2, 2, 2);

	//�˷����Զ��ضϣ�������255ֵ��Ϊ255
	multiply(image, m, dst);
	// imshow("�˷�����", dst);

	int w = image.cols; //uchar��
	int h = image.rows;
	int dims = image.channels();
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
				Vec3b p1 = image.at<Vec3b>(row, col);
				Vec3b p2 = m.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);
				image.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
				image.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
			
		}
	}

	// ���üӼ��˳�
	add(image, m, dst);
	subtract(image, m, dst);
	divide(image, m, dst);

	imshow("�ӷ�����", image);
}


class my_all {
public:
	Mat image1;
	Mat image2;
	int Max_value = 100;//�������λ��
};



// ����ȫ�ֱ����ķ�ʽ����TrackBar
//Mat m, src, dst;
//int lightness = 50;
//static void on_track(int, void*){
//	m = Scalar(lightness, lightness, lightness);
//	add(src, m, dst);
//	imshow("���ȵ���", dst);
//}
//
//
//void QuickDemo::track_bar_demo(Mat &image) {
//	namedWindow("���ȵ���", WINDOW_AUTOSIZE);
//	dst = Mat::zeros(image.size(), image.type());
//	m = Mat::zeros(image.size(), image.type());
//	src = image;
//	int max_value = 100;
//	createTrackbar("Vlue Bar", "���ȵ���", &lightness, max_value, on_track);
//	on_track(50, 0); 
//}


// ���ò������ݵķ���

static void on_lightness(int b, void* userdata) {
	// �� void*  ��Ϊ Mat* ���͵�ָ��
	Mat src = *((Mat*)userdata);
	Mat m = Mat::zeros(src.size(), src.type());
	Mat dst = Mat::zeros(src.size(), src.type());
	addWeighted(src, 1, m, 0, b, dst);
	imshow("���ȵ�����Աȶȵ���", dst);
}

static void on_contrastness(int b, void* userdata) {
	// �� void*  ��Ϊ Mat* ���͵�ָ��
	Mat src = *((Mat*)userdata);
	Mat m = Mat::zeros(src.size(), src.type());
	Mat dst = Mat::zeros(src.size(), src.type());
	double contrast = b / 100.0;
	addWeighted(src, contrast, m, 0.0, 0, dst);
	imshow("���ȵ�����Աȶȵ���", dst);
}

void QuickDemo::track_bar_demo(Mat &image) {
	namedWindow("���ȵ�����Աȶȵ���", WINDOW_AUTOSIZE);
	int max_value = 100;

	int lightness = 50;
	int contrast_value = 100;
	// �� (&image) ��Ϊ void* ���͵�ָ��
	createTrackbar("Vlue Bar", "���ȵ�����Աȶȵ���", &lightness, max_value, on_lightness, (void*)&image);
	createTrackbar("Contrast", "���ȵ�����Աȶȵ���", &contrast_value, 200, on_contrastness, (void*)&image);
	//on_contrastness(100, &image);
}

void QuickDemo::key_demo(Mat &image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat delta = Mat::zeros(image.size(), image.type());
		delta = Scalar(50, 50, 50);
	while (true)
	{
		int c = waitKey(100);
		if (c == 27) {//�˳�
			break;
		}
		if (c == 49) {// key#1�����лҶ�ת��
			std::cout << "your enter: " << c << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		if (c == 50) {// key#2
			std::cout << "your enter: " << c << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		if (c == 51) {// key#3
			std::cout << "your enter: " << c << std::endl;
			add(image, delta, dst);
		}
		imshow("������Ӧ", dst);
	}
}

void QuickDemo::color_map_demo(Mat &image){
	int colormap[] = {
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_JET,
		COLORMAP_WINTER,
		COLORMAP_RAINBOW,
		COLORMAP_OCEAN,
		COLORMAP_SUMMER,
		COLORMAP_SPRING,
		COLORMAP_COOL,
		COLORMAP_PINK,
		COLORMAP_HOT,
		COLORMAP_PARULA,
		COLORMAP_MAGMA,
		COLORMAP_INFERNO,
		COLORMAP_PLASMA,
		COLORMAP_VIRIDIS,
		COLORMAP_CIVIDIS,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED
	};
	Mat dst = Mat::zeros(image.size(), image.type());
	int index = 0;
	String path;
	while (true)
	{
		int c = waitKey(2000);
		if (c == 27) {//�˳�
			break;
		}
		if (c == 49) { // ��1����
			path = "D:/cvwk/oepncv451/pics/" + typeToString(colormap[index % 19]) + "out.jpg";
			imwrite(path, dst);
			std::cout << "��ǰ����ѱ���" << std::endl<<"·��:"<< path;

		}
		applyColorMap(image, dst, colormap[index%19]);
		index++;
		imshow("��ɫ���", dst);
	}

}

void QuickDemo::bitwise_demo(Mat &image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(150, 255, 0), -1, LINE_8);
	rectangle(m2, Rect(100, 100, 80, 100), Scalar(0, 255, 255), -1, LINE_8);
	Mat dst, dst2;
	bitwise_and(m1, m2, dst);
	imshow("m1", m1);
	imshow("m2", m2);
	imshow("and", dst);
}

void QuickDemo::channels_demo(Mat &image) { 
	std::vector<Mat> mv;

	// split��ͨ��;
	split(image, mv);
	imshow("��ɫ", mv[0]);
	imshow("��ɫ", mv[1]);
	imshow("��ɫ", mv[2]);

	Mat dst;
	//mv[0] = 0;
	//mv[1] = 0;
	mv[2] = 0;

	// mergeͨ���ĺϳ�;
	merge(mv, dst);
	imshow("�ϳ�", dst);

	// ����ͨ��˳��;
	int from_to[] = { 0, 2, 1, 1, 2, 0 };
	mixChannels(&image,1, &dst,1, from_to, 3);
	imshow("ͨ�����", dst);
}

void QuickDemo::inrange_demo(Mat &image) {
	Mat hsv, mask;
	Mat redback = Mat::zeros(image.size(), image.type());
	cvtColor(image, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(0, 0, 46), Scalar(180, 43, 220), mask);
	imshow("����", mask);

	redback = Scalar(20, 20, 220);
	bitwise_not(mask, mask);
	image.copyTo(redback, mask);
	imshow("change background", redback);

	imshow("����", image);
}

void QuickDemo::pixel_statistic_Demo(Mat &image) {
	double minv, maxv;
	Point locmin, locmax;
	std::vector<Mat> mv;
	split(image, mv);
	for (int i = 0; i < mv.size(); i++) {
		minMaxLoc(mv[i], &minv, &maxv, &locmin, &locmax);
		cout << "No.channel" << i << " min:" << minv << " max:" << maxv << endl;
		cout << "locmin:" << locmin << " locmax:" << locmax<< endl;
	}

	Mat mean, stddev;
	meanStdDev(image, mean, stddev);
	cout << mean << endl;
	cout << stddev << endl;

	// ����ȡֵ
	cout << mean.at<double>(0,0);

}

void QuickDemo::drawing_demo(Mat &image) {
	// �����κ�Բ
	Rect rect = { 0, 0, 150, 100 };
	Mat bg = Mat::zeros(image.size(), image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);
	circle(image, Point(150, 100), 15, Scalar(0, 120, 150), 1, 8, 0);
	line(bg, Point(0, 0), Point(150, 100), Scalar(255, 0, 0), 2, 8, 0);

	// ������Բ;
	RotatedRect rrt;
	rrt.center = Point(80, 80);
	rrt.size = Size(100, 150);
	rrt.angle = 90.0;
	ellipse(bg, rrt, Scalar(0, 255, 0), 2, 8);

	Mat dst;
	addWeighted(image, 0.7, bg, 0.3, 0, dst);
	imshow("drawing", bg);
}

void QuickDemo::random_drawing() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	RNG rng(12345);
	int w = canvas.cols;
	int h = canvas.rows;
	while (true) {
		int c = waitKey(100);
		if (c == 27) {//�˳�
			break;
		}
		int x1 = rng.uniform(0, w);
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);
		int y2 = rng.uniform(0, h);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);

		canvas = Scalar(0, 0, 0);
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 2, 8);
		imshow("����", canvas);
	}
}

void QuickDemo::polyline_drawing() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(100, 100);
	Point p2(350, 100);
	Point p3(450, 280);
	Point p4(320, 450);
	Point p5(80, 400);

	vector<Point> pts;
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);

	// ���ƣ� ������ǵ㼯�ļ���
	polylines(canvas, pts, true, Scalar(0, 0, 255), 2, 8, 0);
	
	// ���
	vector<vector<Point>> contours;
	contours.push_back(pts);
	drawContours(canvas, contours, -1, Scalar(255, 0, 0), -1);

	imshow("�����", canvas);
}



// ���ƾ��β��ü�
Point sp(-1, -1);
Point ep(-1, -1);
double d;
Mat temp;
static void on_draw(int event, int x, int y, int flags, void *userdata){
	Mat image = *(Mat*)userdata;
	if (event == EVENT_LBUTTONDOWN) {
		sp.x = x;
		sp.y = y;
	}
	else if (event == EVENT_LBUTTONUP) {
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;

		// ����Բ
		//if (dx > 0 && dy > 0) {
		//	d = sqrt(dx ^ 2 + dy ^ 2);
		//	circle(image, sp, d, Scalar(255, 0, 0), 1, 8);
		//	imshow("������", image);
		//	sp.x = -1;
		//	sp.y = -1;
		//}

		if (dx > 0 && dy > 0) {
			Rect box(sp.x, sp.y, dx, dy);
			rectangle(image, box, Scalar(0, 255, 255), 2, 8);
			imshow("ROI", image(box));
			imshow("������", image);
			sp.x = -1;
			sp.y = -1;
		}
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0) {
				temp.copyTo(image);
				Rect box(sp.x, sp.y, dx, dy);
				rectangle(image, box, Scalar(255, 0, 0), 2, 8);
				imshow("������", image);
			}
		}
	}
}

void QuickDemo::mouse_drawing_demo(Mat &image) {
	namedWindow("������", WINDOW_AUTOSIZE);
	setMouseCallback("������",on_draw, (void*)&image);
	imshow("������", image); 
	temp = image.clone();
}

void QuickDemo::norm_demo(Mat &image) {
	Mat img;
	cout << image.type() << endl;

	// ���й�һ������ǰҪ��ɸ����ͣ���һ��Ҫת����0-1֮��
	image.convertTo(image, CV_32F);
	cout << image.type() << endl;

	normalize(image, img, 1.0, 0, NORM_MINMAX);
	cout << img.type() << endl;

	imshow("ͼ�����ݹ�һ��", img);
}

void QuickDemo::resize_demo(Mat &image) {
	Mat zoomin, zoomout;
	int h = image.rows;
	int w = image.cols;
	resize(image, zoomin, Size(w * 0.5, h * 0.5), 0, 0, INTER_LINEAR);
	resize(image, zoomout, Size(w * 2, h * 2), 0, 0, INTER_CUBIC);
	namedWindow("min", WINDOW_FREERATIO);
	imshow("min", zoomin); 
	imshow("max", zoomout);
	cout << image.size() << endl;
	cout << zoomin.size();

}

void QuickDemo::flip_demo(Mat &image) {
	Mat dst;
	flip(image, dst, 0); //����
	flip(image, dst, 1); // ����
	flip(image, dst, -1);
	imshow("��ת", dst);
}

void QuickDemo::warpAffine_demo(Mat &image) {
	Mat dst, M;
	int w = image.cols;
	int h = image.rows;
	M = getRotationMatrix2D(Point(w / 2, h / 2), 45, 1.0);

	double sin = abs(M.at<double>(0, 0));
	double cos = abs(M.at<double>(0, 1));
	int nw = cos*w + sin*h;
	int nh = sin*w + cos*h;
	M.at<double>(0, 2) +=   (nw / 2 - w / 2);
	M.at<double>(1, 2) +=  (nh / 2 - h / 2);
	warpAffine(image, dst, M, Size(nw, nh), INTER_CUBIC, 0, Scalar(255,0,0));
	imshow("��ת", dst);
}


void QuickDemo::video_demo() {
	// 0����ͷ
	// Ҳ�ɴ���Ƶ�ļ�·��
	VideoCapture capture(0);
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);

	// ��֡����ÿ��֡��
	int count = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);

	// ������Ƶ
	VideoWriter writer("C:/Users/�Ժ���/Desktop/�½��ļ���/zhj.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);
	
	cout << frame_width << " " << frame_height << " " << count <<" "<< fps;

	Mat frame;
	while (true)
	{	
		capture.read(frame);
		// �ı侵ͷ�ľ���
		flip(frame, frame, 1);
		writer.write(frame);
		//colorSpace_Demo(frame);
		if (frame.empty()) {
			break;
		}
		imshow("frame", frame);
		// todo something
		int c = waitKey(5);
		if (c == 27) {
			break;
		}
	}
	capture.release();
	writer.release();
}

void QuickDemo::showHistogram(Mat &image) {
	std::vector<Mat> bgr_plane;
	// split��ͨ��;
	split(image, bgr_plane);

	// ������Ʋ���
	const int channel[1] = { 0 };
	const int bins[1] = { 256 };
	float hrange[2] = { 0, 255 };

	// ����ָ��
	const float *range[1] = { hrange };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;

	// ����ֱ��ͼ
	calcHist(&bgr_plane[0], 1, channel, Mat(), b_hist, 1, bins, range);
	calcHist(&bgr_plane[1], 1, channel, Mat(), g_hist, 1, bins, range);
	calcHist(&bgr_plane[2], 1, channel, Mat(), r_hist, 1, bins, range);

	// ��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);

	// ��һ��ֱ��ͼ����
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// ����ֱ��ͼ����
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), (bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i)))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), (bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i)))), Scalar(0, 0, 255), 2, 8, 0);
	}
	namedWindow("histogram demo", WINDOW_AUTOSIZE);
	imshow("histogram demo", histImage);


}



void QuickDemo::histogram_2d_demo(Mat &image) {
	// ת��Ϊhsv��ɫ��ֻʣ2ά��
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	int hist_bins[] = { 30, 32 };
	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 255 };
	float *hist_ranges[] = { h_range, s_range};
	int hs_channels[] = { 0, 1 };
	// calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hist_ranges, true, false);

}

void QuickDemo::histogram_eq_demo(Mat &image) {
	// ֻ֧�ֵ���ͨ����
	// �ı�Ҷȵķֱ�ʹ���ɾ��ȷֲ���
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	Mat dst;

	// һ������
	equalizeHist(gray, dst);
	imshow("ֱ��ͼ���⻯", dst);

	// ��ɫ���⣿ �ֲ����⣿

}

void QuickDemo::blur_demo(Mat &image) {
	Mat dst, dst1;
	//blur(image, dst, Size(-1, -1), Point(-1, -1));
	// imshow("�������", dst);
	GaussianBlur(image, dst, Size(5, 5), 15);

	// ˫���˲�,��������
	bilateralFilter(image, dst1, 0, 50, 10);

	imshow("˫��ģ��", dst1);
	imshow("�������", dst);
}

void QuickDemo::face_detection_demo() {
	string root_dir = "C:/opencv/sources/samples/dnn/face_detector/";
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");
	VideoCapture capture(0);
	Mat frame;
	while (true)
	{
		capture.read(frame);
		// �ı侵ͷ�ľ���
		flip(frame, frame, 1);

		//colorSpace_Demo(frame);
		if (frame.empty()) {
			break;
		}

		// todo something
		// ׼������, ģ��Ҫ��300 * 300
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104,177, 123), false, false);
		net.setInput(blob);// NCHW������
		// �������
		Mat probs = net.forward(); // index, 3:���ٸ���
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr <float>());
		//�������,NCHW
		for (int i = 0; i < detectionMat.rows; i++)
		{
			float confidence = detectionMat.at<float>(i, 2);
			cout << "0:" << detectionMat.at<float>(i, 0)<<" 1:"<< detectionMat.at<float>(i, 1)<< endl;
			if (confidence > 0.5) {
				// ת��Int
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3)*frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4)*frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5)*frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6)*frame.rows);
				Rect box(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, box, Scalar(255, 0, 255), 2, 8, 0);
				
			}	
			imshow("���������ʾ", frame);
		}
		

		int c = waitKey(5);
		if (c == 27) {
			break;
		}
	}
	capture.release();

}


void QuickDemo::kmeans_demo(Mat &src) {
	Scalar colorTab[] = {    //������ɫ����
		Scalar(0,0,255),
		Scalar(255,0,255),
		Scalar(0,255,0),
		Scalar(255,0,0),
		Scalar(0,255,255),
		Scalar(255,255,255),
	};
	int width = src.cols; //ͼ���
	int height = src.rows; //ͼ���
	int channels = src.channels(); //ͨ����
	//��ʼ������
	int clusterCount = 6;//4����
	int sampleCount = width * height;//����������
	Mat points(sampleCount, channels, CV_32F, Scalar(10));
	Mat labels;
	Mat centers(clusterCount, 1, points.type());

	//RGBת������������
	int index = 0;
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			index = row * width + col;
			Vec3b bgr = src.at<Vec3b>(row, col);
			//��ȡÿ��ͨ����ֵ
			points.at<float>(index, 0) = static_cast<int>(bgr[0]);
			points.at<float>(index, 1) = static_cast<int>(bgr[1]);
			points.at<float>(index, 2) = static_cast<int>(bgr[2]);
		}
	}
	//����KMeans
	TermCriteria cirteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 1, 0.1);
	kmeans(points, clusterCount, labels, cirteria, 3, KMEANS_PP_CENTERS, centers);

	//��ʾͼ��ָ���

	Mat result = Mat::zeros(src.size(), src.type());
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			index = row * width + col;
			int label = labels.at<int>(index, 0);

			result.at<Vec3b>(row, col)[0] = colorTab[label][0];
			result.at<Vec3b>(row, col)[1] = colorTab[label][1];
			result.at<Vec3b>(row, col)[2] = colorTab[label][2];
		}
	}

	namedWindow("����", WINDOW_FREERATIO);
	imshow("����", result);
	waitKey(0);
}

void QuickDemo::mean_shift(Mat &image) {
	Mat res; //�ָ��ͼ��
	int spatialRad = 5;  //�ռ䴰�ڴ�С
	int colorRad = 20;   //ɫ�ʴ��ڴ�С
	int maxPyrLevel = 2;  //����������
	pyrMeanShiftFiltering(image, res, spatialRad, colorRad, maxPyrLevel); //ɫ�ʾ���ƽ���˲�
	namedWindow("�˲����", WINDOW_FREERATIO);
	imshow("�˲����", res);
	RNG rng = theRNG();
	Mat mask(res.rows + 2, res.cols + 2, CV_8UC1, Scalar::all(0));  //��ģ
	for (int y = 0; y < res.rows; y++)
	{
		for (int x = 0; x < res.cols; x++)
		{
			if (mask.at<uchar>(y + 1, x + 1) == 0)  //��0����Ϊ1����ʾ�Ѿ�������䣬���ٴ���
			{
				Scalar newVal(rng(256), rng(256), rng(256));
				floodFill(res, mask, Point(x, y), newVal, 0, Scalar::all(5), Scalar::all(5)); //ִ����ˮ���
			}
		}
	}
	namedWindow("���", WINDOW_FREERATIO);
	imshow("���", res);
	waitKey();
}

void QuickDemo::SingleScaleRetinex(const cv::Mat &src, cv::Mat &dst, int sigma)
{
	cv::Mat doubleI, gaussianI, logI, logGI, logR;

	src.convertTo(doubleI, CV_64FC3, 1.0, 1.0);                    //ת����Χ������ͼ��Ԫ������1.0��֤cvlog����
	cv::GaussianBlur(doubleI, gaussianI, cv::Size(0, 0), sigma);    //SSR�㷨�ĺ���֮һ����˹ģ������sizeΪ��ʱ��ͨ��sigma�Զ����м���
	cv::log(doubleI, logI);
	cv::log(gaussianI, logGI);
	logR = logI - logGI;                                           //Retinex��ʽ��Log(R(x,y))=Log(I(x,y))-Log(Gauss(I(x,y)))
	cv::normalize(logR, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);     //SSR�㷨�ĺ���֮��,�������� (�ƺ���������ʱ��û��˭�Ὣ Log[R(x,y)]����Exp�����������ֱ�ӵõ�R(x,y))
}



void QuickDemo::MultiScaleRetinex(const cv::Mat &src, cv::Mat &dst, int k, std::vector<double> w, std::vector<double> sigmas) {
	cv::Mat doubleI, logI;
	cv::Mat logR = cv::Mat::zeros(src.size(), CV_64FC3);
	src.convertTo(doubleI, CV_64FC3, 1.0, 1.0);                    //ת����Χ������ͼ��Ԫ������1.0��֤cvlog����
	cv::log(doubleI, logI);

	for (int i = 0; i < k; i++)
	{//Retinex��ʽ��Log(R(x,y)) += w_k(Log(I(x,y))-Log(Gauss_k(I(x,y))))
		cv::Mat tempGI;
		cv::GaussianBlur(doubleI, tempGI, cv::Size(0, 0), sigmas[i]);
		cv::Mat templogGI;
		cv::log(tempGI, templogGI);
		logR += w[i] * (logI - templogGI);
	}
	cv::normalize(logR, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);  //SSR�㷨�ĺ���֮��,�������� (�ƺ���������ʱ��û��˭�Ὣ Log[R(x,y)]����Exp�����������ֱ�ӵõ�R(x,y))
}


void QuickDemo::MultiScaleRetinexCR(const cv::Mat &src, cv::Mat &dst, int k, std::vector<double> w, std::vector<double> sigmas, int alpha, int beta, int gain, int offset)
{


	cv::Mat doubleIl, logI;
	cv::Mat logMSR = cv::Mat::zeros(src.size(), CV_64FC3);

	src.convertTo(doubleIl, CV_64FC3, 1.0, 1.0);                    //ת����Χ������ͼ��Ԫ������1.0��֤cvlog����
	cv::log(doubleIl, logI);

	for (int i = 0; i < k; i++)
	{//Retinex��ʽ��Log(R(x,y)) += w_k(Log(I(x,y))-Log(Gauss_k(I(x,y))))
		cv::Mat tempGI;
		cv::GaussianBlur(doubleIl, tempGI, cv::Size(0, 0), sigmas[i]);
		cv::Mat templogGI;
		cv::log(tempGI, templogGI);
		logMSR += w[i] * (logI - templogGI);
	}


	std::vector<cv::Mat> logMSRc(3);
	cv::split(logMSR, logMSRc);

	cv::Mat doubleI;
	src.convertTo(doubleI, CV_64FC3);

	std::vector<cv::Mat> doubleIc(3);
	cv::split(doubleI, doubleIc);


	cv::Mat sumDoubleIc = cv::Mat::zeros(doubleI.size(), CV_64FC1);
	for (int i = 0; i < doubleI.rows; i++)
	{
		for (int j = 0; j < doubleI.cols; j++)
		{
			sumDoubleIc.ptr<double>(i)[j] = doubleI.ptr<cv::Vec3d>(i)[j][0] + doubleI.ptr<cv::Vec3d>(i)[j][1] + doubleI.ptr<cv::Vec3d>(i)[j][2];
		}
	}


	std::vector<cv::Mat> divideDoubleIc(3);
	std::vector<cv::Mat> Cc(3);
	std::vector<cv::Mat> MSRCRc(3);
	cv::Mat tempResult;

	for (int i = 0; i < 3; i++)
	{
		cv::divide(doubleIc[i], sumDoubleIc, divideDoubleIc[i]);
		divideDoubleIc[i].convertTo(divideDoubleIc[i], CV_64FC1, 1.0, 1.0);
		cv::log(alpha * divideDoubleIc[i], Cc[i]);
		Cc[i] *= beta;
		MSRCRc[i] = Cc[i].mul(logMSRc[i]);
	}


	cv::merge(MSRCRc, tempResult);
	cv::normalize(tempResult, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);
}