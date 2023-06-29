#include<iostream>
#include "interpolation/interpolation.hpp"

//Реализация алгоритма ближайшего соседа
cv::Mat Nearest_neighbor(cv::Mat& src, int width, int height)
{
	CV_Assert(src.data != NULL);
	int srcRows = src.rows;
	int srcCols = src.cols;
	//Определение целевой функции
	cv::Mat dst = cv::Mat::zeros(height, width, src.type());
	double dstRows = dst.rows;
	double dstCols = dst.cols;
	//Коэффициент масштабирования
	double sx = src.cols / dstCols;
	double sy = src.rows / dstRows;
	for (int i = 0; i < dst.rows; i++)
	{
		//Находим координаты пикселей целевого изображения, соответствующих исходному изображению, чтобы выровнять центр целевого изображения с центром исходного изображения, используйте следующую формулу
		double index_i = (i + 0.5) * sy - 0.5;
		//Определяем, находится ли он за пределами
		if (index_i < 0)
			index_i = 0;
		if (index_i > src.rows - 1)
			index_i = src.rows - 1;
		int i1 = cvFloor(index_i + 0.5); // Округлить в ближайшую сторону
		for (int j = 0; j < dst.cols; j++)
		{
			double index_j = (j + 0.5) * sx - 0.5;
			if (index_j < 0)
				index_j = 0;
			if (index_j > src.cols - 1)
				index_j = src.cols - 1;
			int j1 = cvFloor(index_j + 0.5);
			if (src.channels() == 1)
				dst.at<uchar>(i, j) = src.at<uchar>(i1, j1);
			else
			{
				dst.at<cv::Vec3b>(i, j)[0] = src.at<cv::Vec3b>(i1, j1)[0];
				dst.at<cv::Vec3b>(i, j)[1] = src.at<cv::Vec3b>(i1, j1)[1];
				dst.at<cv::Vec3b>(i, j)[2] = src.at<cv::Vec3b>(i1, j1)[2];
			}
		}
	}
	return dst;
}

//Реализация билинейного алгоритма
cv::Mat Bilinear(cv:: Mat& src, int width, int height)
{
	CV_Assert(src.data != NULL);
	int srcRows = src.rows;
	int srcCols = src.cols;
	//Определение целевой функции
	cv::Mat dst = cv::Mat::zeros(height, width, src.type());
	double dstRows = dst.rows;
	double dstCols = dst.cols;
	//Коэффициент масштабирования
	double sx = src.cols / dstCols;
	double sy = src.rows / dstRows;
	for (int i = 0; i < dst.rows; i++)
	{
		//Находим координаты пикселей целевого изображения, соответствующих исходному изображению, чтобы выровнять центр целевого изображения с центром исходного изображения, используйте следующую формулу
		double index_i = (i + 0.5) * sy - 0.5;
		//Определяем, находится ли он за пределами
		if (index_i < 0)
			index_i = 0;
		if (index_i > src.rows - 1)
			index_i = src.rows - 1;
		int i1 = cvFloor(index_i); // Округлить в меньшую сторону
		int i2 = cvCeil(index_i);
		double v = index_i - i1;
		for (int j = 0; j < dst.cols; j++)
		{
			double index_j = (j + 0.5) * sx - 0.5;
			if (index_j < 0)
				index_j = 0;
			if (index_j > src.cols - 1)
				index_j = src.cols - 1;
			int j1 = cvFloor(index_j);
			int j2 = cvCeil(index_j);
			double u = index_j - j1;
			if (src.channels() == 1)
				dst.at<uchar>(i, j) = cvFloor((1 - u) * (1 - v) * src.at<uchar>(i1, j1) + (1 - u) * v * src.at<uchar>(i2, j1) + u * (1 - v) * src.at<uchar>(i1, j2) + u * v * src.at<uchar>(i2, j2));
			else
			{
				dst.at<cv::Vec3b>(i, j)[0] = cvFloor((1 - u) * (1 - v) * src.at<cv::Vec3b>(i1, j1)[0] + (1 - u) * v * src.at<cv::Vec3b>(i2, j1)[0] + u * (1 - v) * src.at<cv::Vec3b>(i1, j2)[0] + u * v * src.at<cv::Vec3b>(i2, j2)[0]);
				dst.at<cv::Vec3b>(i, j)[1] = cvFloor((1 - u) * (1 - v) * src.at<cv::Vec3b>(i1, j1)[1] + (1 - u) * v * src.at<cv::Vec3b>(i2, j1)[1] + u * (1 - v) * src.at<cv::Vec3b>(i1, j2)[1] + u * v * src.at<cv::Vec3b>(i2, j2)[1]);
				dst.at<cv::Vec3b>(i, j)[2] = cvFloor((1 - u) * (1 - v) * src.at<cv::Vec3b>(i1, j1)[2] + (1 - u) * v * src.at<cv::Vec3b>(i2, j1)[2] + u * (1 - v) * src.at<cv::Vec3b>(i1, j2)[2] + u * v * src.at<cv::Vec3b>(i2, j2)[2]);
			}
		}
	}
	return dst;
}

double coeffB(double x, double y, int i) { ///служебная функция для вычисления коэффициентов в бикубическом алгоритме
	//Оставим только дробную часть числа
	double ss;
	x = modf(x, &ss);
	y = modf(y, &ss);
	switch (i) {
	case 1:
		return (1.0 / 4) * (x - 1) * (x - 2) * (x + 1) * (y - 1) * (y - 2) * (y + 1);
	case 2:
		return (-1.0 / 4) * x * (x + 1) * (x - 2) * (y - 1) * (y - 2) * (y + 1);
	case 3:
		return (-1.0 / 4) * y * (x - 1) * (x - 2) * (x + 1) * (y + 1) * (y - 2);
	case 4:
		return (1.0 / 4) * x * y * (x + 1) * (x - 2) * (y + 1) * (y - 2);
	case 5:
		return (-1.0 / 12) * x * (x - 1) * (x - 2) * (y - 1) * (y - 2) * (y + 1);
	case 6:
		return (-1.0 / 12) * y * (x - 1) * (x - 2) * (x + 1) * (y - 1) * (y - 2);
	case 7:
		return (1.0 / 12) * x * y * (x - 1) * (x - 2) * (y + 1) * (y - 2);
	case 8:
		return (1.0 / 12) * x * y * (x + 1) * (x - 2) * (y - 1) * (y - 2);
	case 9:
		return (1.0 / 12) * x * (x - 1) * (x + 1) * (y - 1) * (y - 2) * (y + 1);
	case 10:
		return (1.0 / 12) * y * (x - 1) * (x - 2) * (x + 1) * (y - 1) * (y + 1);
	case 11:
		return (1.0 / 36) * x * y * (x - 1) * (x - 2) * (y - 1) * (y - 2);
	case 12:
		return (-1.0 / 12) * x * y * (x - 1) * (x + 1) * (y + 1) * (y - 2);
	case 13:
		return (-1.0 / 12) * x * y * (x + 1) * (x - 2) * (y - 1) * (y + 1);
	case 14:
		return (-1.0 / 36) * x * y * (x - 1) * (x + 1) * (y - 1) * (y - 2);
	case 15:
		return (-1.0 / 36) * x * y * (x - 1) * (x - 2) * (y - 1) * (y + 1);
	case 16:
		return (1.0 / 36) * x * y * (x - 1) * (x + 1) * (y - 1) * (y + 1);
	}
}


//Реализация бикубического алгоритма
cv::Mat Bicubic(cv::Mat& src, int width, int height)
{
	CV_Assert(src.data != NULL);
	int srcRows = src.rows;
	int srcCols = src.cols;
	cv::Mat src_ex = cv::Mat::zeros(srcRows + 4, srcCols + 4, src.type());
	copyMakeBorder(src, src_ex, 2, 2, 2, 2, cv::BORDER_REFLECT_101);
	//Определение целевой функции
	cv::Mat dst = cv::Mat::zeros(height, width, src.type());
	double dstRows = dst.rows;
	double dstCols = dst.cols;
	//Коэффициент масштабирования
	double sx = src.cols / dstCols;
	double sy = src.rows / dstRows;
	for (int i = 0; i < dst.rows; i++)
	{
		//Находим координаты пикселей целевого изображения, соответствующих исходному изображению, чтобы выровнять центр целевого изображения с центром исходного изображения, используйте следующую формулу
		double index_i = (i + 0.5) * sy - 0.5;
		//Определяем, находится ли он за пределами
		if (index_i < 0)
			index_i = 0;
		if (index_i > src.rows - 1)
			index_i = src.rows - 1;
		int i1 = cvFloor(index_i); // Округлить в меньшую сторону
		int i2 = cvCeil(index_i);
		int i3 = i2 + 1;
		int i0 = i1 - 1;
		for (int j = 0; j < dst.cols; j++)
		{
			double index_j = (j + 0.5) * sx - 0.5;
			if (index_j < 0)
				index_j = 0;
			if (index_j > src.cols - 1)
				index_j = src.cols - 1;
			int j1 = cvFloor(index_j);
			int j2 = cvCeil(index_j);
			int j3 = j2 + 1;
			int j0 = j1 - 1;
			double x = index_j;
			double y = index_i;
			if (src_ex.channels() == 1) {
				dst.at<uchar>(i, j) = coeffB(x, y, 11) * src_ex.at<uchar>(i0 + 2, j0 + 2) + coeffB(x, y, 6) * src_ex.at<uchar>(i0 + 2, j1 + 2) + 
					coeffB(x, y, 8) * src_ex.at<uchar>(i0 + 2, j2 + 2) + coeffB(x, y, 14) * src_ex.at<uchar>(i0 + 2, j3 + 2) + coeffB(x, y, 5) * src_ex.at<uchar>(i1 + 2, j0 + 2) + 
					coeffB(x, y, 1) * src_ex.at<uchar>(i1 + 2, j1 + 2) + coeffB(x, y, 2) * src_ex.at<uchar>(i1 + 2, j2 + 2) + coeffB(x, y, 9) * src_ex.at<uchar>(i1 + 2, j3 + 2) + 
					coeffB(x, y, 7) * src_ex.at<uchar>(i2 + 2, j0 + 2) + coeffB(x, y, 3) * src_ex.at<uchar>(i2 + 2, j1 + 2) + coeffB(x, y, 4) * src_ex.at<uchar>(i2 + 2, j2 + 2) + 
					coeffB(x, y, 12) * src_ex.at<uchar>(i2 + 2, j3 + 2) + coeffB(x, y, 15) * src_ex.at<uchar>(i3 + 2, j0 + 2) + coeffB(x, y, 10) * src_ex.at<uchar>(i3 + 2, j1 + 2) +
					coeffB(x, y, 13) * src_ex.at<uchar>(i3 + 2, j2 + 2) + coeffB(x, y, 16) * src_ex.at<uchar>(i3 + 2, j3 + 2);
			}
			else
			{
				dst.at<cv::Vec3b>(i, j)[0] = coeffB(x, y, 11) * src_ex.at<cv::Vec3b>(i0 + 2, j0 + 2)[0] + coeffB(x, y, 6) * src_ex.at<cv::Vec3b>(i0 + 2, j1 + 2)[0] + 
					coeffB(x, y, 8) * src_ex.at<cv::Vec3b>(i0 + 2, j2 + 2)[0] + coeffB(x, y, 14) * src_ex.at<cv::Vec3b>(i0 + 2, j3 + 2)[0] + coeffB(x, y, 5) * src_ex.at<cv::Vec3b>(i1 + 2, j0 + 2)[0] + 
					coeffB(x, y, 1) * src_ex.at<cv::Vec3b>(i1 + 2, j1 + 2)[0] + coeffB(x, y, 2) * src_ex.at<cv::Vec3b>(i1 + 2, j2 + 2)[0] + coeffB(x, y, 9) * src_ex.at<cv::Vec3b>(i1 + 2, j3 + 2)[0] + 
					coeffB(x, y, 7) * src_ex.at<cv::Vec3b>(i2 + 2, j0 + 2)[0] + coeffB(x, y, 3) * src_ex.at<cv::Vec3b>(i2 + 2, j1 + 2)[0] + coeffB(x, y, 4) * src_ex.at<cv::Vec3b>(i2 + 2, j2 + 2)[0] + 
					coeffB(x, y, 12) * src_ex.at<cv::Vec3b>(i2 + 2, j3 + 2)[0] + coeffB(x, y, 15) * src_ex.at<cv::Vec3b>(i3 + 2, j0 + 2)[0] + coeffB(x, y, 10) * src_ex.at<cv::Vec3b>(i3 + 2, j1 + 2)[0] +
					coeffB(x, y, 13) * src_ex.at<cv::Vec3b>(i3 + 2, j2 + 2)[0] + coeffB(x, y, 16) * src_ex.at<cv::Vec3b>(i3 + 2, j3 + 2)[0];
				dst.at<cv::Vec3b>(i, j)[1] = coeffB(x, y, 11) * src_ex.at<cv::Vec3b>(i0 + 2, j0 + 2)[1] + coeffB(x, y, 6) * src_ex.at<cv::Vec3b>(i0 + 2, j1 + 2)[1] + 
					coeffB(x, y, 8) * src_ex.at<cv::Vec3b>(i0 + 2, j2 + 2)[1] + coeffB(x, y, 14) * src_ex.at<cv::Vec3b>(i0 + 2, j3 + 2)[1] + coeffB(x, y, 5) * src_ex.at<cv::Vec3b>(i1 + 2, j0 + 2)[1] + 
					coeffB(x, y, 1) * src_ex.at<cv::Vec3b>(i1 + 2, j1 + 2)[1] + coeffB(x, y, 2) * src_ex.at<cv::Vec3b>(i1 + 2, j2 + 2)[1] + coeffB(x, y, 9) * src_ex.at<cv::Vec3b>(i1 + 2, j3 + 2)[1] + 
					coeffB(x, y, 7) * src_ex.at<cv::Vec3b>(i2 + 2, j0 + 2)[1] + coeffB(x, y, 3) * src_ex.at<cv::Vec3b>(i2 + 2, j1 + 2)[1] + coeffB(x, y, 4) * src_ex.at<cv::Vec3b>(i2 + 2, j2 + 2)[1] + 
					coeffB(x, y, 12) * src_ex.at<cv::Vec3b>(i2 + 2, j3 + 2)[1] + coeffB(x, y, 15) * src_ex.at<cv::Vec3b>(i3 + 2, j0 + 2)[1] + coeffB(x, y, 10) * src_ex.at<cv::Vec3b>(i3 + 2, j1 + 2)[1] +
					coeffB(x, y, 13) * src_ex.at<cv::Vec3b>(i3 + 2, j2 + 2)[1] + coeffB(x, y, 16) * src_ex.at<cv::Vec3b>(i3 + 2, j3 + 2)[1];
				dst.at<cv::Vec3b>(i, j)[2] = coeffB(x, y, 11) * src_ex.at<cv::Vec3b>(i0 + 2, j0 + 2)[2] + coeffB(x, y, 6) * src_ex.at<cv::Vec3b>(i0 + 2, j1 + 2)[2] + 
					coeffB(x, y, 8) * src_ex.at<cv::Vec3b>(i0 + 2, j2 + 2)[2] + coeffB(x, y, 14) * src_ex.at<cv::Vec3b>(i0 + 2, j3 + 2)[2] + coeffB(x, y, 5) * src_ex.at<cv::Vec3b>(i1 + 2, j0 + 2)[2] + 
					coeffB(x, y, 1) * src_ex.at<cv::Vec3b>(i1 + 2, j1 + 2)[2] + coeffB(x, y, 2) * src_ex.at<cv::Vec3b>(i1 + 2, j2 + 2)[2] + coeffB(x, y, 9) * src_ex.at<cv::Vec3b>(i1 + 2, j3 + 2)[2] + 
					coeffB(x, y, 7) * src_ex.at<cv::Vec3b>(i2 + 2, j0 + 2)[2] + coeffB(x, y, 3) * src_ex.at<cv::Vec3b>(i2 + 2, j1 + 2)[2] + coeffB(x, y, 4) * src_ex.at<cv::Vec3b>(i2 + 2, j2 + 2)[2] + 
					coeffB(x, y, 12) * src_ex.at<cv::Vec3b>(i2 + 2, j3 + 2)[2] + coeffB(x, y, 15) * src_ex.at<cv::Vec3b>(i3 + 2, j0 + 2)[2] + coeffB(x, y, 10) * src_ex.at<cv::Vec3b>(i3 + 2, j1 + 2)[2] +
					coeffB(x, y, 13) * src_ex.at<cv::Vec3b>(i3 + 2, j2 + 2)[2] + coeffB(x, y, 16) * src_ex.at<cv::Vec3b>(i3 + 2, j3 + 2)[2];
			}
		}
	}
	return dst;
}






