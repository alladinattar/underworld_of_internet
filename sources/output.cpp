#include "output.hpp"
#include <iostream>
#include <fstream>
void outPut::writeFile(std::string path, std::vector<std::string> imgs) {
  std::ofstream file(path);
  for (auto& img : imgs){
    file<<img;
  }
  file.close();

}