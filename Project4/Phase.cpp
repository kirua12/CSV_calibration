#include "Phase.h"

Phase::Phase()
{
	cv::Mat g_im_00 = cv::imread("1.bmp", cv::IMREAD_UNCHANGED);
	cv::Mat g_im_90 = cv::imread("2.bmp", cv::IMREAD_UNCHANGED);
	cv::Mat g_im_180 = cv::imread("3.bmp", cv::IMREAD_UNCHANGED);
	cv::Mat g_im_270 = cv::imread("4.bmp", cv::IMREAD_UNCHANGED);
	g_im_00.convertTo(g_im_00, CV_32FC1);
	g_im_90.convertTo(g_im_90, CV_32FC1);
	g_im_180.convertTo(g_im_180, CV_32FC1);
	g_im_270.convertTo(g_im_270, CV_32FC1);

	cv::Mat im_00 = cv::imread("img/1.bmp", cv::IMREAD_UNCHANGED);
	cv::Mat im_90 = cv::imread("img/2.bmp", cv::IMREAD_UNCHANGED);
	cv::Mat im_180 = cv::imread("img/3.bmp", cv::IMREAD_UNCHANGED);
	cv::Mat im_270 = cv::imread("img/4.bmp", cv::IMREAD_UNCHANGED);
	im_00.convertTo(im_00, CV_32FC1);
	im_90.convertTo(im_90, CV_32FC1);
	im_180.convertTo(im_180, CV_32FC1);
	im_270.convertTo(im_270, CV_32FC1);
	cv::Mat sub_img1 = im_00 - im_180;
	cv::Mat sub_img2 = im_270 - im_90;
	cv::Mat phase = sub_img2.clone();


	cv::Mat g_sub_img1 = g_im_00 - g_im_180;
	cv::Mat g_sub_img2 = g_im_270 - g_im_90;
	cv::Mat g_phase = g_sub_img2.clone();

	std::vector<float> period;
	period.push_back(0);
	int data = 0;


	for (int i = 0;i < g_im_270.cols;i++) {
		for (int j = 0; j < g_im_270.rows;j++) {

			g_phase.at<float>(i, j) = (std::atan2(g_sub_img1.at<float>(i, j), g_sub_img2.at<float>(i, j)));
			phase.at<float>(i, j) = (std::atan2(sub_img1.at<float>(i, j), sub_img2.at<float>(i, j)));
			if (j == g_im_270.cols / 2 && i > 1) {

				if ((std::abs(g_phase.at<float>(i, j) - g_phase.at<float>(i - 1, j)) > 3) && (std::abs(data - i) > 200)) {
					data = i;
					period.push_back(data);
				}
			}

		}
	}


	cv::Mat unwrapping = g_phase.clone();

	int count = 0;
	double pi = std::acos(-1);
	for (int i = 0;i < g_im_270.cols;i++) {
		for (int j = 0; j < g_im_270.rows;j++) {

			if (count + 1 < period.size()) {

				if (i == period.at(count + 1))
					count++;
			}

			if (g_phase.at<float>(i, j) < -2.5 && std::abs(period.at(count) - i) > 500) {
				unwrapping.at<float>(i, j) = g_phase.at<float>(i, j) + 2 * (count + 1) * pi;
			}
			else if (g_phase.at<float>(i, j) > 2.5 && std::abs(period.at(count) - i) < 500) {
				unwrapping.at<float>(i, j) = g_phase.at<float>(i, j) + 2 * (count - 1) * pi;
			}
			else {
				unwrapping.at<float>(i, j) = g_phase.at<float>(i, j) + 2 * count * pi;
			}


		}
	}

	m_phase = phase;
	m_ref = unwrapping;





}

cv::Mat Phase::getPhase()
{
	return m_phase;
}

cv::Mat Phase::getref()
{
	return m_ref;
}
