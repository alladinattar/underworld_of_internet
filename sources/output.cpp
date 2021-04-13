#include "output.hpp"
#include <iostream>
#include <fstream>
#include "ThreadPool.h"
void outPut::writeFile(std::vector<std::string> imgs) {

  try{
    for (auto& img : imgs){
      file<<img<<std::endl;
    }
  }catch (std::exception& e){
    std::cerr<<e.what()<<std::endl;
  }

  std::cout<<path_<<std::endl;


}


void outPut::writeIMG(std::vector<std::string> imgs){

  pool.enqueue([imgs,this](){

    this->writeFile(imgs);

  });
}
