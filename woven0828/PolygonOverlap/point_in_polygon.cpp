#include <iostream>
#include <vector>

struct Point {
    double x, y;
};

bool pointInPolygon(const Point& pt, const std::vector<Point>& poly) {
    int n = poly.size();
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        const Point& a = poly[i];
        const Point& b = poly[(i + 1) % n];
        // 判断射线是否穿过边
        // (a.y > pt.y) != (b.y > pt.y) 判断点pt的水平射线是否与多边形当前边(a,b)相交
        // 只有当pt.y在a.y和b.y之间时，射线才可能穿过该边
        if ((a.y > pt.y) != (b.y > pt.y)) {
            // 计算交点的x坐标
            // (b.x - a.x) * (pt.y - a.y) / (b.y - a.y + 1e-20) + a.x
            // 作用：计算多边形边(a, b)与水平线y=pt.y的交点横坐标intersectX
            // 步骤解释：
            // 1. (pt.y - a.y) / (b.y - a.y + 1e-20)：计算pt.y在a.y到b.y之间的相对位置（比例）
            // 2. (b.x - a.x) * ... ：用这个比例乘以x方向的跨度，得到从a.x到交点的水平距离
            // 3. + a.x ：加上a.x得到交点的实际x坐标
            // 这样就得到了多边形边与点pt的水平射线的交点x坐标
            double intersectX = (b.x - a.x) * (pt.y - a.y) / (b.y - a.y + 1e-20) + a.x;
            // 如果pt.x小于交点x坐标，说明射线穿过该边
            if (pt.x < intersectX)
                cnt++;
        }
    }
    return cnt % 2 == 1;
}

int main() {
    // 示例多边形（逆时针或顺时针均可）
    std::vector<Point> polygon = {
        {0.0, 0.0},
        {10.0, 0.0},
        {10.0, 10.0},
        {0.0, 10.0}
    };

    Point pt = {-29.317074184905096, 14.70919261723742};

    if (pointInPolygon(pt, polygon)) {
        std::cout << "Point is inside the polygon." << std::endl;
    } else {
        std::cout << "Point is outside the polygon." << std::endl;
    }

    return 0;
}
