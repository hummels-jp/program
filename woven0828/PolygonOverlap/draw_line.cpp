#include <iostream>
#include <vector>
#include <cmath>

// 使用Bresenham算法绘制直线，返回所有像素点坐标
std::vector<std::pair<int, int>> draw_line(int x0, int y0, int x1, int y1) {
    std::vector<std::pair<int, int>> points;
    int dx = std::abs(x1 - x0), dy = std::abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        points.emplace_back(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
    return points;
}

int main() {
    int x0 = 2, y0 = 3, x1 = 15, y1 = 10;
    auto line_points = draw_line(x0, y0, x1, y1);
    std::cout << "Line points:" << std::endl;
    for (const auto& pt : line_points) {
        std::cout << "(" << pt.first << ", " << pt.second << ")" << std::endl;
    }
    return 0;
}