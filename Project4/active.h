#pragma once
#include "Phase.h"


class Active
{
public:
	Phase m_p;
	int m_s_x;
	int m_s_y;
	int m_x_w;
	int m_y_w;
	int m_skew;



	Active(Phase p);

	void play(cv::Mat img);

	void key_event(cv::Mat n_img, cv::Mat n_phase);

	void save(cv::Mat n_img);
};

