#pragma once

#include <opencv2/opencv.hpp>
#include <fstream>
#include <vector>
#include<cstring>
class Phase
{


public:

	cv::Mat m_ref; //reference
	cv::Mat m_phase;



	Phase();
	cv::Mat getPhase();
	cv::Mat getref();

};

