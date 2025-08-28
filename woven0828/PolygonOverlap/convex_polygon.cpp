#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
    double x, y;
};

typedef std::vector<Point> Polygon;

// 计算叉积
/*
cross函数用于计算向量OA和OB的叉积（二维情况下）：
- O为起点，A和B为终点。
- (A.x - O.x, A.y - O.y) 表示向量OA
- (B.x - O.x, B.y - O.y) 表示向量OB
- 叉积公式：(A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x)

几何意义：
- 结果为正：OB在OA的逆时针方向（左侧）
- 结果为负：OB在OA的顺时针方向（右侧）
- 结果为零：三点共线
*/
double cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// 判断点是否在多边形内（射线法，适用于凸/非凸）
/*
is_point_in_polygon函数实现如下：

1. 遍历多边形的每一条边(a, b)。
2. 判断点pt的水平射线是否与当前边相交：
   - ((a.y <= pt.y && pt.y < b.y) || (b.y <= pt.y && pt.y < a.y))
     判断pt.y是否在a.y和b.y之间（不包含上端点，包含下端点），即射线可能与边相交。
   - pt.x < (b.x - a.x) * (pt.y - a.y) / (b.y - a.y + 1e-12) + a.x
     计算多边形边(a, b)与y=pt.y的交点横坐标，如果pt.x小于交点x坐标，说明射线穿过该边。
3. 每遇到一次穿过，cnt加1。
4. 最后判断cnt是否为奇数（cnt%2==1），奇数则点在多边形内，偶数则在外。

该算法适用于任意简单多边形（凸或非凸），并能处理浮点精度问题。
*/
bool is_point_in_polygon(const Point& pt, const Polygon& poly) {
    int n = poly.size();
    int cnt = 0;
    for(int i=0; i<n; i++) {
        Point a = poly[i], b = poly[(i+1)%n];
        if (((a.y <= pt.y && pt.y < b.y) || (b.y <= pt.y && pt.y < a.y)) &&
            pt.x < (b.x - a.x) * (pt.y - a.y) / (b.y - a.y + 1e-12) + a.x)
            cnt++;
    }
    return cnt%2==1;
}

// 判断两线段是否相交
/*
segments_intersect函数用于判断两条线段(p1,p2)和(q1,q2)是否严格相交（不包含端点重合的情况）。

- cross(q1, q2, p1) 和 cross(q1, q2, p2)：分别计算p1和p2在q1q2这条线段的哪一侧（叉积符号）。
- cross(p1, p2, q1) 和 cross(p1, p2, q2)：分别计算q1和q2在p1p2这条线段的哪一侧。

判断条件：
- ((d1>0 && d2<0) || (d1<0 && d2>0))：p1和p2在q1q2的两侧。
- ((d3>0 && d4<0) || (d3<0 && d4>0))：q1和q2在p1p2的两侧。

只有当两条线段的端点分别在对方的两侧时，线段才严格相交，返回true，否则返回false。
*/
bool segments_intersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2) {
    auto d1 = cross(q1, q2, p1);
    auto d2 = cross(q1, q2, p2);
    auto d3 = cross(p1, p2, q1);
    auto d4 = cross(p1, p2, q2);
    if (((d1>0 && d2<0) || (d1<0 && d2>0)) && ((d3>0 && d4<0) || (d3<0 && d4>0)))
        return true;
    return false;
}

// 判断多边形是否相交
/*
polygons_intersect函数用于判断两个多边形poly1和poly2是否相交，具体步骤如下：

1. 边相交检测：
   - 遍历poly1的每一条边(a1, a2)。
   - 对于poly2的每一条边(b1, b2)，判断(a1, a2)和(b1, b2)是否相交（调用segments_intersect）。
   - 只要有一对边相交，立即返回true，表示多边形相交。

2. 包含关系检测：
   - 如果没有边相交，判断poly1的第一个点是否在poly2内部（调用is_point_in_polygon）。
   - 如果poly1的第一个点在poly2内部，返回true。
   - 同理，判断poly2的第一个点是否在poly1内部，如果在，也返回true。

3. 如果上述都不满足，说明两个多边形既没有边相交，也没有包含关系，返回false，表示不相交。
*/
bool polygons_intersect(const Polygon& poly1, const Polygon& poly2) {
    // 边相交
    for(int i=0; i<poly1.size(); i++) {
        Point a1 = poly1[i], a2 = poly1[(i+1)%poly1.size()];
        for(int j=0; j<poly2.size(); j++) {
            Point b1 = poly2[j], b2 = poly2[(j+1)%poly2.size()];
            if (segments_intersect(a1, a2, b1, b2)) return true;
        }
    }
    // 一个多边形在另一个内部
    if (is_point_in_polygon(poly1[0], poly2)) return true;
    if (is_point_in_polygon(poly2[0], poly1)) return true;
    return false;
}

// 多边形面积
double polygon_area(const Polygon& poly) {
    double area = 0;
    int n = poly.size();
    for(int i=0; i<n; i++) {
        area += poly[i].x * poly[(i+1)%n].y - poly[(i+1)%n].x * poly[i].y;
    }
    return fabs(area)/2.0;
}

// Sutherland-Hodgman多边形裁剪
Polygon polygon_intersection(const Polygon& subject, const Polygon& clip) {
    Polygon output = subject;
    for(int i=0; i<clip.size(); i++) {
        Polygon input = output;
        output.clear();
        Point A = clip[i], B = clip[(i+1)%clip.size()];
        for(int j=0; j<input.size(); j++) {
            Point P = input[j], Q = input[(j+1)%input.size()];
            double cp1 = cross(A, B, P);
            double cp2 = cross(A, B, Q);
            if(cp1>=0 && cp2>=0) {
                output.push_back(Q);
            } else if(cp1>=0 && cp2<0) {
                // P在内 Q在外
                double t = cp1/(cp1-cp2+1e-12);
                Point I = {P.x + t*(Q.x-P.x), P.y + t*(Q.y-P.y)};
                output.push_back(I);
            } else if(cp1<0 && cp2>=0) {
                // P在外 Q在内
                double t = cp1/(cp1-cp2+1e-12);
                Point I = {P.x + t*(Q.x-P.x), P.y + t*(Q.y-P.y)};
                output.push_back(I);
                output.push_back(Q);
            }
            // 否则都在外，不加点
        }
    }
    return output;
}

int main() {
    Polygon poly1 = {{0,0},{4,0},{4,4},{0,4}};
    Polygon poly2 = {{2,2},{6,2},{6,6},{2,6}};
    if(polygons_intersect(poly1, poly2)) {
        std::cout << "相交" << std::endl;
        Polygon inter = polygon_intersection(poly1, poly2);
        double area = polygon_area(inter);
        std::cout << "交面积为: " << area << std::endl;
    } else {
        std::cout << "不相交" << std::endl;
    }
    return 0;
}