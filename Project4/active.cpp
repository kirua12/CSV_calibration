#include "active.h"




Active::Active(Phase p) {
	m_p = p;
}

void Active::play(cv::Mat img)
{

	cv::Mat phase = m_p.getPhase();
	cv::Mat n_phase;
	cv::normalize(phase, n_phase, 0, 255, cv::NORM_MINMAX);
	n_phase.convertTo(n_phase, CV_8U);


	cv::Mat n_img;
	cv::normalize(img, n_img, 0, 255, cv::NORM_MINMAX);
	n_img.convertTo(n_img, CV_8U);



	key_event(n_img, n_phase);
	save(img);


}

void Active::key_event(cv::Mat n_img, cv::Mat n_phase)
{

	int flag = 0;
	int big_size = 6042;


	if (n_img.rows < n_img.cols)
		flag = 1;

	int r_row = 0;
	int r_col = 0;
	if (flag == 1) {
		r_row = big_size * n_img.rows / n_img.cols;
		r_col = big_size;
	}
	else {
		r_row = big_size;
		r_col = big_size * n_img.rows / n_img.cols;
	}


	cv::resize(n_img, n_img, cv::Size(r_col, r_row));


	if (n_img.rows > 3904) {

		n_img = n_img(cv::Rect(0, 0, n_img.cols, 3904));

	}

	int x_w = 0;
	int y_w = -460;
	double skew = -89;

	cv::namedWindow("matching", cv::WINDOW_NORMAL);
	cv::resizeWindow("matching", 1280, 1280);

	while (1) {

		int col = n_img.cols;
		int row = n_img.rows;
		cv::Mat zeros = cv::Mat::zeros(cv::Size(3904, 3904), CV_8U);

		cv::Mat temp2;
		cv::Mat temp;
		int width;
		int height;
		if (3904 - x_w > col) {
			width = col;

		}

		else if (3904 - x_w < col) {
			width = 3904 - x_w;

		}

		if (3904 - y_w < row) {
			height = 3904 - y_w;
		}
		else if (3904 - y_w > row) {
			height = 3904 - y_w;

		}


		if (y_w > 0) {

			temp2 = n_img(cv::Rect(0, 0, width, height));
			temp = zeros(cv::Rect(x_w, y_w, width, height));
		}
		else {

			if (row + y_w - 1 > 3904) {
				height = 3904;
			}
			else
				height = row + y_w - 1;


			temp2 = n_img(cv::Rect(0, -y_w, width, height));
			temp = zeros(cv::Rect(x_w, 0, width, height));

		}




		temp2.copyTo(temp);
		cv::Mat warpMatrix = cv::getRotationMatrix2D(cv::Point(zeros.cols / 2, zeros.rows / 2), skew, 1);

		// X축 방향으로 기울이기 위한 변환 행렬



		cv::warpAffine(
			zeros,
			zeros,
			warpMatrix,
			zeros.size(),
			cv::INTER_LINEAR,
			cv::BORDER_CONSTANT
		);




		cv::Mat img;
		cv::addWeighted(zeros, 0.5, n_phase, 0.5, 0, img);

		cv::imshow("matching", img);
		int key = cv::waitKeyEx();


		if (key == 27) { // 'Esc' 키를 누르면 종료
			m_s_x = n_img.cols;
			m_s_y = n_img.rows;
			m_x_w = x_w;
			m_y_w = y_w;
			m_skew = skew;


			break;
		}
		else if (key == 0x250000)// 왼쪽 방향키
		{
			x_w -= 5;
			if (x_w < 0)
				x_w = 5;
		}
		else if (key == 0x260000)// 위쪽 방향키
		{
			y_w -= 5;



		}
		else if (key == 0x270000)// 오른쪽 방향키
		{
			x_w += 5;
			if (x_w > 1500)
				x_w = 1500;
		}
		else if (key == 0x280000)// 아래쪽 방향키
		{
			y_w += 5;
			if (y_w > 1500)
				y_w = 1500;

		}
		else if (key == 'z')// 줌 키
		{

			int col = n_img.cols;
			int row = n_img.rows;

			int x = (row + 10) * col / row;


			if (row + 10 > 3904) {
				n_img = n_img(cv::Rect(0, 0, n_img.cols, n_img.rows-10));

			}
			else {
				cv::resize(n_img, n_img, cv::Size(x, row + 10));

			}


		}
		else if (key == 'x')// 감소 키
		{

			int col = n_img.cols;
			int row = n_img.rows;

			int x = (row - 10) * col / row;


			cv::resize(n_img, n_img, cv::Size(x, row - 10));
		}

		else if (key == 'c')// 기울기 키
		{

			skew += 1;
		}

		else if (key == 'v')// 기울기 키
		{

			skew -= 1;
		}


	}



}

void Active::save(cv::Mat n_img)
{


	cv::resize(n_img, n_img, cv::Size(m_s_x, m_s_y));
	if (n_img.rows > 3904) {

		n_img = n_img(cv::Rect(0, 0, n_img.cols, 3904));

	}

	int col = n_img.cols;
	int row = n_img.rows;
	cv::Mat zeros = cv::Mat::zeros(cv::Size(3904, 3904), CV_32FC1);

	cv::Mat temp2;
	cv::Mat temp;
	int width;
	int height;
	if (3904 - m_x_w > col) {
		width = col;

	}

	else if (3904 - m_x_w < col) {
		width = 3904 - m_x_w;

	}

	if (3904 - m_y_w < row) {
		height = 3904 - m_y_w;
	}
	else if (3904 - m_y_w > row) {
		height = 3904 - m_y_w;

	}
	if (m_y_w > 0) {

		temp2 = n_img(cv::Rect(0, 0, width, height));
		temp = zeros(cv::Rect(m_x_w, m_y_w, width, height));
	}
	else {

		temp2 = n_img(cv::Rect(0, -m_y_w, width, row + m_y_w - 1));

		if (row + m_y_w - 1 > 3904)
			height = 3904;
		else
			height = row + m_y_w - 1;
		temp = zeros(cv::Rect(m_x_w, 0, width, height));

	}





	temp2.copyTo(temp);
	cv::Mat warpMatrix = cv::getRotationMatrix2D(cv::Point(zeros.cols / 2, zeros.rows / 2), m_skew, 1);

	// X축 방향으로 기울이기 위한 변환 행렬

	cv::warpAffine(
		zeros,
		zeros,
		warpMatrix,
		zeros.size(),
		cv::INTER_LINEAR,
		cv::BORDER_CONSTANT
	);


	cv::Mat unwrapping = m_p.getref();
	cv::Mat img = unwrapping.clone();

	for (int i = 0; i < zeros.rows;i++) {
		for (int j = 0; j < zeros.cols;j++) {
			double h = zeros.at<float>(i, j);

			if (h > 4000) {
				double k = 0;
				k = 0.6204 * i + 4560.4;
				img.at<float>(i, j) = unwrapping.at<float>(i, j) - h / k;
			}
		}
	}


	std::ofstream outputMFile("height_m.csv");

	for (int i = 0; i < zeros.rows; i++) {
		for (int j = 0; j < zeros.cols; j++) {
			outputMFile << zeros.at<float>(i, j);
			if (j < zeros.cols - 1) {
				outputMFile << ",";
			}
		}
		outputMFile << std::endl;
	}

	outputMFile.close();

	std::ofstream outputFile("unwrapping.csv");

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			outputFile << img.at<float>(i, j);
			if (j < img.cols - 1) {
				outputFile << ",";
			}
		}
		outputFile << std::endl;
	}
	outputFile.close();

}
