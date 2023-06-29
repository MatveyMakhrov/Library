#include<iostream>
#include <string>
#include "interpolation/interpolation.hpp"

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		std::cout << "Not enough arguments\n";
		std::cout << "Usage: " << "<program name> " << "<height> " << "<width> " << "<method> " << "<input file path> " << "[output file path]";
		return 1;
	}
	std::string str_width{ argv[1] };
	std::string str_height{ argv[2] };
	std::string str_method{ argv[3] };
	int myint1;
	int myint2;
	try {
		myint1 = std::stoi(str_height);
		myint2 = std::stoi(str_width);
	}
	catch (const std::out_of_range& oor) {
		std::cout << "\n\n\n\n\n" << "Height or width are out of range" << "\n\n\n\n\n";
		return -1;
	}
	catch (const std::invalid_argument& ia) {
		std::cout << "\n\n\n\n\n" << "Invalid height or width" << "\n\n\n\n\n";
		return 1;
	}
	if (myint1 <= 0 || myint2 <= 0) {
		std::cout << "Height and width should be positive";
		return 1;
	}
	std::string input{ argv[4] };
	std::string output;

	if (argc == 5) {
		output = "output.png";
	}
	else {
		output = argv[5];
	}

	std::cout << output;
	cv::Mat src = cv::imread(input);
	cv::Mat result;
	if (!src.data) {
		std::cout << "\n\n\n\n\nCouldn't read the file\n\n\n\n\n";
		return -1;
	}
	cv::imshow("src", src);
	if (str_method == "Nearest_neighbor") {
		result = Nearest_neighbor(src, myint1, myint2);
	}
	else if (str_method == "Bilinear") {
		result = Bilinear(src, myint1, myint2);
	}
	else if (str_method == "Bicubic") {
		result = Bicubic(src, myint1, myint2);
	}
	else {
		std::cout << "\n\n\n\n\n\nCouldn't choose the interpolation method. Please choose from these: \nNearest_neighbor\nBilinear\nBicubic\n\n\n\n\n";
		return 1;
	}



	bool outcome = false;
	try
	{
		outcome = cv::imwrite(output, result);
	}
	catch (const cv::Exception& ex)
	{
		printf("Exception converting image: %s\n", ex.what());
	}
	if (outcome)
		printf(" Saved file.\n");
	else
		printf("ERROR: Can't save file.\n");



	cv::imshow("dst", result);
	cv::waitKey(0);
}
