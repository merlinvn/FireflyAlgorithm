//
// Created by Merlin on 24-Jul-15.
//

#ifndef FIREFLYALGORITHM_FIREFLY_H
#define FIREFLYALGORITHM_FIREFLY_H

#include <vector>

class FireFly {
public:
    std::vector<double> position;
    double error;
    double intensity;

public:
    FireFly(const int &dim=0);
    virtual ~FireFly();


    bool operator< (const FireFly& rhs) {
        return this->error < rhs.error;
    }

    bool operator> (const FireFly& rhs) {
        return this->error > rhs.error;
    }

    bool operator== (const FireFly& rhs) {
        return this->error == rhs.error;
    }

    bool operator >= (const FireFly& rhs) {
        return this->error >= rhs.error;
    }
    bool operator <= (const FireFly& rhs) {
        return this->error <= rhs.error;
    }

};


#endif //FIREFLYALGORITHM_FIREFLY_H
