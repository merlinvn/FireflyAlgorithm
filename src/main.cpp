#define _USE_MATH_DEFINES

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

#include <random>

#include <time.h>
#include "FireFly.h"

using namespace std;

double Distance(const std::vector<double> &posA, const std::vector<double> &posB);

double Michalewicz(const std::vector<double> &xValues);

double Error(const std::vector<double> &xValues);

std::vector<double> Solve(int numFireflies, int dim, int seed, int maxEpochs);

double rand_double();

int main() {
    cout << "Begin FireFly Demo" << endl;

    //code here

    int numFireflies = 50;
    int dim = 10;
    int maxEpochs = 1000000;
    int seed = time(NULL);

    std::vector<double> bestPosition = Solve(numFireflies, dim, seed, maxEpochs);
    printf("Finished\n");

    printf("Best solution found: ");
    printf("x = %f\t%f\t%f\t%f\t%f\n", bestPosition[0], bestPosition[1], bestPosition[2], bestPosition[3],
           bestPosition[4]);

    double z = Michalewicz(bestPosition);
    printf("Value of function at best position = %f\n", z);

    double error = Error(bestPosition);
    printf("Error at best position = %f\n", error);


    cout << "End FireFly Demo" << endl;
    return 0;
}


double rand_double() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}


std::vector<double> Solve(int numFireflies, int dim, int seed, int maxEpochs) {
    srand(seed);
    double minX = 0.0;
    double maxX = 3.2;
    double B0 = 1.0;
    double g = 1.0;
    double a = 0.10;
    int displayInterval = maxEpochs / 100;

    double bestError = 1000000;
    double lastBestError = bestError;
    int number_epoch_not_change=0;

    std::vector<double> bestPosition; // Best ever
    std::vector<FireFly *> swarm;

    printf("initializing fireflies \n");
//    initialize n fireflies to random positions
    for (int i = 0; i < numFireflies; ++i) {
        FireFly *f = new FireFly(dim);
        swarm.push_back(f);
        for (int k = 0; k < dim; ++k) {// Random position
            swarm[i]->position[k] = (maxX - minX) * rand_double() + minX;
        }
        swarm[i]->error = Error(swarm[i]->position);

        if (swarm[i]->error < bestError) {
            bestError = swarm[i]->error;
            lastBestError = bestError;
            bestPosition = swarm[i]->position;
        }
        swarm[i]->intensity = 1 / ((swarm[i]->error - bestError)*(swarm[i]->error - bestError));
    }

//    loop maxEpochs times
    int epoch = 0;
    while (epoch < maxEpochs) {
        if (epoch % displayInterval == 0 && epoch < maxEpochs) {
            printf("epoch = %d ------------- error = %f\n", epoch, bestError);

        }
//    for i := 0 to n-1
//    for j := 0 to n-1
        for (int i = 0; i < numFireflies; ++i) // Each firefly
        {
            for (int j = 0; j < numFireflies; ++j) // Others
            {
                //    if intensity(i) < intensity(j)
                if (swarm[i]->intensity < swarm[j]->intensity) {
//    compute attractiveness
                    double r = Distance(swarm[i]->position, swarm[j]->position);
                    double beta = B0 * exp(-g * r * r);

                    // Move firefly(i) toward firefly(j)
                    for (int k = 0; k < dim; ++k) {
                        swarm[i]->position[k] += beta * (swarm[j]->position[k] - swarm[i]->position[k]);
                        swarm[i]->position[k] += a * (rand_double() - 0.5);
                        if (swarm[i]->position[k] < minX)
                            swarm[i]->position[k] = (maxX - minX) * rand_double() + minX;
                        if (swarm[i]->position[k] > maxX)
                            swarm[i]->position[k] = (maxX - minX) * rand_double() + minX;
                    }
                    //    update firefly(i) intensity
                    swarm[i]->error = Error(swarm[i]->position);
                    if (swarm[i]->error < bestError) {
                        bestError = swarm[i]->error;
                        bestPosition = swarm[i]->position;
                    }
                    swarm[i]->intensity = 1 / ((swarm[i]->error - bestError)*(swarm[i]->error - bestError));
                }
            }//    end for
        }//    end for

        //    sort fireflies
        std::sort(swarm.begin(), swarm.end());
        if (swarm[0]->error < bestError) {
            bestError = swarm[0]->error;
            bestPosition = swarm[0]->position;
        }


        if(lastBestError == bestError)
        {
            number_epoch_not_change += 1;
        }else
        {
            number_epoch_not_change=0;
        }



        if (number_epoch_not_change > 3000) {
            number_epoch_not_change = 0;
            printf("Replacement occurs! \n");
// remove and add new 10% fireflies
            int n_replacement = swarm.size() * 80 / 100;
            int i = 0;
            while (i < n_replacement) {
                i++;
                delete swarm.back();
                swarm.pop_back();
            }


            for (int i = 0; i < n_replacement; ++i) {
                FireFly *f = new FireFly(dim);
                swarm.push_back(f);
                for (int k = 0; k < dim; ++k) {// Random position
                    swarm[i]->position[k] = (maxX - minX) * rand_double() + minX;
                }
                swarm[i]->error = Error(swarm[i]->position);
                if (swarm[i]->error < bestError) {
                    bestError = swarm[i]->error;
                    bestPosition = swarm[i]->position;
                }
                swarm[i]->intensity = 1 / ((swarm[i]->error - bestError)*(swarm[i]->error - bestError));
            }
        }

        lastBestError = bestError;
        ++epoch;
    }//    end loop

    for (FireFly *fireFly:swarm) {
        delete fireFly;
    }
    swarm.clear();
//    return best position found
    return bestPosition;
}

double Distance(const std::vector<double> &posA, const std::vector<double> &posB) {
    double ssd = 0.0; // sum squared diffrences
    for (int i = 0; i < posA.size(); ++i)
        ssd += (posA[i] - posB[i]) * (posA[i] - posB[i]);
    return sqrt(ssd);
}


double Michalewicz(const std::vector<double> &xValues) {
    double result = 0.0;
    for (int i = 0; i < xValues.size(); ++i) {
        double a = sin(xValues[i]);
        double b = sin(((i + 1) * xValues[i] * xValues[i]) / M_PI);
        double c = pow(b, 20);
        result += a * c;
    }
    return -1.0 * result;
}


double Error(const std::vector<double> &xValues) {
//    int dim = xValues.size();
//    double trueMin = 0.0;
//    if (dim == 2)
//        trueMin = -1.8013; // Approx.
//    else if (dim == 5)
//        trueMin = -4.687658; // Approx.
//    double calculated = Michalewicz(xValues);
//    return (trueMin - calculated) * (trueMin - calculated);
    return Michalewicz(xValues);
}