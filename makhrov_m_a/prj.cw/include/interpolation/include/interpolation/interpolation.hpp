#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<cmath>
#include<iosfwd>


/** @defgroup interpolation —пособы интерпол€ции
* @brief »спользуемые методы в данной библиотеке
*/

/**
 * @ingroup interpolation
 * @brief ћетод интерпол€ции изображени€ алгоритмом ближайшего соседа
 * @param src - матрица изображени€, которую нужно интерполировать
 * @param width - кол-во пикселей изображени€ по ширине после интерполировани€
 * @param height - кол-во пикселей изображени€ по высоте после интерполировани€
 * @return dst - интерполированное изображение
*/
cv::Mat Nearest_neighbor(cv::Mat& src, int width, int height);

/**
 * @ingroup interpolation 
 * @brief ћетод интерпол€ции изображени€ билинейным алгоритмом
 * @param src - матрица изображени€, которую нужно интерполировать
 * @param width - кол-во пикселей изображени€ по ширине после интерполировани€
 * @param height - кол-во пикселей изображени€ по высоте после интерполировани€
 * @return dst - интерполированное изображение
*/
cv::Mat Bilinear(cv::Mat& src, int width, int height);

/**
 * @ingroup interpolation
 * @brief ћетод интерпол€ции изображени€ бикубическим алгоритмом
 * @param src - матрица изображени€, которую нужно интерполировать
 * @param width кол-во пикселей изображени€ по ширине после интерполировани€
 * @param height кол-во пикселей изображени€ по высоте после интерполировани€
 * @return dst - интерполированное изображение
*/
cv::Mat Bicubic(cv::Mat& src, int width, int height);
