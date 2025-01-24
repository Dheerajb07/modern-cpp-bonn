#include "convert_dataset.hpp"
#include <filesystem>

namespace ipb::serialization::sifts {
    void ConvertDataset(const std::filesystem::path& data_path){
        // find all .png paths
        for(auto &img_path : std::filesystem::directory_iterator(data_path)){
            
        }
        // for each img calc sifts

        // create a bin file and serialize data
    }
}