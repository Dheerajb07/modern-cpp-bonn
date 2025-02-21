#ifndef IMAGE_HPP_
#define IMAGE_HPP_
#include <vector>
#include <cstdint>
#include <string>
#include "io_tools.hpp"

namespace igg {
class Image {
    private:
    int rows_;
    int cols_;
    std::vector<uint8_t> data_;
    
    public:
    Image(int rows, int cols): rows_(rows), cols_(cols){};
    
    int rows() const{ return rows_;};
    int cols() const{ return cols_;};

    uint8_t& at(int row, int col){ return data_[row*cols_ + col];};

    bool FillFromPgm(const std::string& file_name){
        igg::io_tools::ImageData img_data = igg::io_tools::ReadFromPgm(file_name);
        rows_ = img_data.rows;
        cols_ = img_data.cols;
        data_ = img_data.data;
    }

    



};
} // namespace igg

#endif