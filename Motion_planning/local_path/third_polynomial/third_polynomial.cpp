#include <iostream>
#include <vector>
using namespace std;

// 计算三次多项式系数
vector<double> cubicPolynomial(double s0, double v0, double s1, double v1, double T) {
    // s(t) = a0 + a1*t + a2*t^2 + a3*t^3
    double a0 = s0;
    double a1 = v0;
    double a2 = (3*(s1 - s0) - (2*v0 + v1)*T) / (T*T);
    double a3 = (-2*(s1 - s0) + (v0 + v1)*T) / (T*T*T);
    return {a0, a1, a2, a3};
}

// 计算曲线在t时刻的位置
double calcPos(const vector<double>& coeffs, double t) {
    return coeffs[0] + coeffs[1]*t + coeffs[2]*t*t + coeffs[3]*t*t*t;
}

// 计算曲线在t时刻的速度
double calcVel(const vector<double>& coeffs, double t) {
    return coeffs[1] + 2*coeffs[2]*t + 3*coeffs[3]*t*t;
}

int main() {
    double s0 = 0.0, v0 = 0.0;      // 起点位置和速度
    double s1 = 10.0, v1 = 0.0;     // 终点位置和速度
    double T = 5.0;                 // 规划时间

    auto coeffs = cubicPolynomial(s0, v0, s1, v1, T);

    cout << "三次多项式系数: ";
    for (auto c : coeffs) cout << c << " ";
    cout << endl;

    // 打印每秒的位置和速度
    for (double t = 0; t <= T; t += 1.0) {
        double pos = calcPos(coeffs, t);
        double vel = calcVel(coeffs, t);
        cout << "t=" << t << "  s=" << pos << "  v=" << vel << endl;
    }
    return 0;
}