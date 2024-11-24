#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

struct Point {
    double x;
    double y;
};

std::uniform_real_distribution<> getDistribution(double x, double y) {
    std::random_device device;
    return std::uniform_real_distribution<>(x, y);
}

Point getRandomPoint(std::uniform_real_distribution<> distribution_x, std::uniform_real_distribution<> distribution_y, std::mt19937 &generator) {
    Point point;
    point.x = distribution_x(generator);
    point.y = distribution_y(generator);
    return point;
}

bool isPointInCircle(Point point, double radius, Point center) {
    return radius * radius >= (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y);
}

double getSquare(Point p1, Point p2, Point p3, double r1, double r2, double r3, std::mt19937 &generator) {
    double l_border = std::min(p1.x - r1, std::min(p2.x - r2, p3.x - r3));
    double d_border = std::min(p1.y - r1, std::min(p2.y - r2, p3.y - r3));
    double r_border = std::max(p1.x + r1, std::max(p2.x + r2, p3.x + r3));
    double u_border = std::max(p1.y + r1, std::max(p2.y + r2, p3.y + r3));
    auto distribution_x = getDistribution(l_border, r_border);
    auto distribution_y = getDistribution(d_border, u_border);
    double S = (u_border - d_border) * (r_border - l_border);
    long long N = 10000000;
    int M = 0;
    int ind = 0;
    while (ind < N) {
        Point point = getRandomPoint(distribution_x, distribution_y, generator);
        if (isPointInCircle(point, r1, p1) && isPointInCircle(point, r2, p2) && isPointInCircle(point, r3, p3)) {
            M++;
        }
        ind++;
    }
    return S * M / N;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Point point1;
    Point point2;
    Point point3;
    double radius1;
    double radius2;
    double radius3;
    std::cin >> point1.x >> point1.y >> radius1;
    std::cin >> point2.x >> point2.y >> radius2;
    std::cin >> point3.x >> point3.y >> radius3;
    std::random_device device;
    std::mt19937 generator(device());
    double square = getSquare(point1, point2, point3, radius1, radius2, radius3, generator);
    std::cout << square << std::endl; 
    return 0;
}
