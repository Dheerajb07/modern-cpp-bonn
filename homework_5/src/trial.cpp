#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

int main(){
    // get current path
    std::filesystem::path imgPath = std::filesystem::current_path() / "data/lenna.png";
    // std::cout << imgPath << std::endl;
    
    // Read image
    cv::Mat img = cv::imread(imgPath, cv::IMREAD_COLOR);

    // return error if image not found
    if(!img.data){
        std::cerr << "No Image data" << std::endl;
        return 1;
    }

    // create window to display image
    const std::string window_name{"Display Image"};
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    // show image
    cv::imshow(window_name, img);
    cv::waitKey(0);

    return 0;
}