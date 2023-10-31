#include "Phase.h"
#include "active.h"








int main() {
	Phase p;
	cv::Mat unwrapping = p.getref();


	std::fstream fs;
	std::vector<std::vector<float>> img_v;
	fs.open("output.csv", std::ios::in);
	std::string line;
	while (std::getline(fs, line)) {
		std::string str_buf;
		std::stringstream lineStream(line);
		std::vector<float> temp_v;

		while (std::getline(lineStream, str_buf, ',')) {
			temp_v.push_back(std::stof(str_buf));
		}
		img_v.push_back(temp_v);
	}
	fs.close();


	cv::Mat img((int)img_v.size(), (int)img_v.at(0).size(), CV_32FC1);

	for (int i = 0; i < img_v.size();i++) {
		for (int j = 0; j < img_v.at(i).size();j++) {
			img.at<float>(i, j) = img_v.at(i).at(j);
		}
	}

	/*cv::Mat img((int)img_v.at(0).size(), (int)img_v.size(), CV_32FC1);

	for (int i = 0; i < img_v.size();i++) {
		for (int j = 0;  j< img_v.at(i).size();j++) {
				img.at<float>(j, img_v.size()-1-i) = img_v.at(i).at(j);
		}
	}



	int col = img.cols;
	int row = img.rows;
	int t = 4700;

	int x = t * col / row;


	cv::resize(img, img, cv::Size(x, t));


	std::ofstream outputFile("output.csv");

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			outputFile << (int)img.at<float>(i, j);
			if (j < img.cols - 1) {
				outputFile << ",";
			}
		}
		outputFile << std::endl;
	}

	outputFile.close();*/






	Active com(p);

	com.play(img);




	/*cv::Mat img = unwrapping.clone();

	for (int i = 0; i < img_v.size();i++) {
		for (int j = 0; j < img_v.at(i).size();j++) {
			double h = img_v.at(i).at(j);

			if (h > 4000) {
				double k = 0;
				k = 0.6204*i +4560.4;
				img.at<float>(i, j) = unwrapping.at<float>(i, j) -h/k;
			}
		}
	}*/




}