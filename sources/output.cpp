#include "output.hpp"
#include <iostream>
#include <fstream>
#include "ThreadPool.h"
void outPut::writeFile(std::vector<std::string> imgs) {
  std::cout<<path_;
  std::ofstream file(path_);
  for (auto& img : imgs){
    file<<img<<std::endl;
  }
  file.close();

}


void outPut::writeIMG(std::vector<std::string> imgs){
  pool.enqueue([&](){
    this->writeFile(imgs);
  });
}
