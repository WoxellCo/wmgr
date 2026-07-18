#include <iostream>
#include <wmgr.hpp>
#include <wmgr.h>

int main() {
    wmgr::make_t make = wmgr::make("make.txt");
    wmgr::make_out(make);
    std::cout << WMGR_VER_STR << std::endl;
}