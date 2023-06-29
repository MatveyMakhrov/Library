#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<cmath>
#include<iosfwd>


/** @defgroup interpolation ������� ������������
* @brief ������������ ������ � ������ ����������
*/

/**
 * @ingroup interpolation
 * @brief ����� ������������ ����������� ���������� ���������� ������
 * @param src - ������� �����������, ������� ����� ���������������
 * @param width - ���-�� �������� ����������� �� ������ ����� ����������������
 * @param height - ���-�� �������� ����������� �� ������ ����� ����������������
 * @return dst - ����������������� �����������
*/
cv::Mat Nearest_neighbor(cv::Mat& src, int width, int height);

/**
 * @ingroup interpolation 
 * @brief ����� ������������ ����������� ���������� ����������
 * @param src - ������� �����������, ������� ����� ���������������
 * @param width - ���-�� �������� ����������� �� ������ ����� ����������������
 * @param height - ���-�� �������� ����������� �� ������ ����� ����������������
 * @return dst - ����������������� �����������
*/
cv::Mat Bilinear(cv::Mat& src, int width, int height);

/**
 * @ingroup interpolation
 * @brief ����� ������������ ����������� ������������ ����������
 * @param src - ������� �����������, ������� ����� ���������������
 * @param width ���-�� �������� ����������� �� ������ ����� ����������������
 * @param height ���-�� �������� ����������� �� ������ ����� ����������������
 * @return dst - ����������������� �����������
*/
cv::Mat Bicubic(cv::Mat& src, int width, int height);
