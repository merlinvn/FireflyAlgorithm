//
// Created by Merlin on 24-Jul-15.
//


#include "FireFly.h"

FireFly::FireFly(const int &dim) {
    this->position = std::vector<double>(dim, 0.0);
    this->error = 0.0;
    this->intensity = 0.0;
}

 FireFly::~FireFly() {

}
