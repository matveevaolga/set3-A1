#include <iostream> 
#include <vector>
#include <cmath> 
#include <random> 
#include <algorithm> 
#include <iomanip>
#define _USE_MATH_DEFINES

struct Point {
    double x;
    double y;
};

std::uniform_real_distribution<> getDistribution(double x, double y) {
    std::random_device device;
    return std::uniform_real_distribution<>(x, y);
}

bool isPointInCircle(Point point, double radius, Point center) {
    return radius * radius >= (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y);
}

Point getRandomPoint(std::uniform_real_distribution<> distribution_x, std::uniform_real_distribution<> distribution_y, std::mt19937 &generator) {
    Point point;
    point.x = distribution_x(generator);
    point.y = distribution_y(generator);
    return point;
}

void print(const std::vector<long long>& vec) {
    size_t size = vec.size();
    for (size_t ind = 0; ind < size; ind++) {
        if (ind != size - 1) std::cout << vec[ind] << ", ";
        else std::cout << vec[ind];
    }
    std::cout << std::endl << std::endl;
}

void print(const std::vector<double>& vec) {
    size_t size = vec.size();
    for (size_t ind = 0; ind < size; ind++) {
        if (ind != size - 1) std::cout << vec[ind] << ", ";
        else std::cout << vec[ind];
    }
    std::cout << std::endl << std::endl;
}

double getSquare(Point p1, Point p2, Point p3, double r1, double r2, double r3, std::mt19937 &generator, long long N) {
    double l_border = std::min(p1.x - r1, std::min(p2.x - r2, p3.x - r3));
    double d_border = std::min(p1.y - r1, std::min(p2.y - r2, p3.y - r3));
    double r_border = std::max(p1.x + r1, std::max(p2.x + r2, p3.x + r3));
    double u_border = std::max(p1.y + r1, std::max(p2.y + r2, p3.y + r3));
    double S = (u_border - d_border) * (r_border - l_border);
    auto distribution_x = getDistribution(l_border, r_border);
    auto distribution_y = getDistribution(d_border, u_border);
    long long M = 0;
    long long ind = 0;
    while (ind < N) {
        Point point = getRandomPoint(distribution_x, distribution_y, generator);
        if (isPointInCircle(point, r1, p1) && isPointInCircle(point, r2, p2) && isPointInCircle(point, r3, p3)) M++;
        ind++;
    }
    return S * M / N;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Point p1 = {1.5, 2}; 
    Point p2 = {1, 1};
    Point p3 = {2, 1.5}; 
    double r1 = std::sqrt(5) / 2;
    double r2 = 1; 
    double r3 = r1; 
    double correct_S = 0.25 * M_PI + 1.25 * std::asin(0.8) - 1; 
    std::vector<long long> vect_of_n; 
    std::vector<double> calculated_squares; 
    std::vector<double> diffs;
    std::random_device device;
    std::mt19937 generator(device());
    long long N = 100; 
    while (N <= 100000) { 
        double S = getSquare(p1, p2, p3, r1, r2, r3, generator, N);
        calculated_squares.push_back(S); 
        vect_of_n.push_back(N);
        diffs.push_back(100.0 * std::abs((S - correct_S) / correct_S)); 
        N += 500; 
    } 
    print(vect_of_n); 
    print(calculated_squares); 
    print(diffs);  
    return 0; 
}