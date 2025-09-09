#include <iostream>
#include <vector>
using namespace std;

// 计算五次多项式系数
vector<double> quinticPolynomial(double s0, double v0, double acc0,
                                 double s1, double v1, double acc1, double T) {
    // s(t) = a0 + a1*t + a2*t^2 + a3*t^3 + a4*t^4 + a5*t^5
    double a0 = s0;
    double a1 = v0;
    double a2 = acc0 / 2.0;

    double T2 = T * T, T3 = T2 * T, T4 = T3 * T, T5 = T4 * T;

    double c0 = s1 - (a0 + a1*T + a2*T2);
    double c1 = v1 - (a1 + 2*a2*T);
    double c2 = acc1 - (2*a2);

    double a3 = (10*c0 - 4*c1*T + 0.5*c2*T2) / (2*T3);
    double a4 = (-15*c0 + 7*c1*T - c2*T2) / (2*T4);
    double a5 = (6*c0 - 3*c1*T + 0.5*c2*T2) / (2*T5);

    return {a0, a1, a2, a3, a4, a5};
}

// 计算曲线在t时刻的位置
double calcPos(const vector<double>& coeffs, double t) {
    return coeffs[0] + coeffs[1]*t + coeffs[2]*t*t + coeffs[3]*t*t*t +
           coeffs[4]*t*t*t*t + coeffs[5]*t*t*t*t*t;
}

// 计算曲线在t时刻的速度
double calcVel(const vector<double>& coeffs, double t) {
    return coeffs[1] + 2*coeffs[2]*t + 3*coeffs[3]*t*t +
           4*coeffs[4]*t*t*t + 5*coeffs[5]*t*t*t*t;
}

// 计算曲线在t时刻的加速度
double calcAcc(const vector<double>& coeffs, double t) {
    return 2*coeffs[2] + 6*coeffs[3]*t + 12*coeffs[4]*t*t + 20*coeffs[5]*t*t*t;
}

int main() {
    double s0 = 0.0, v0 = 0.0, acc0 = 0.0;      // 起点位置、速度、加速度
    double s1 = 10.0, v1 = 0.0, acc1 = 0.0;     // 终点位置、速度、加速度
    double T = 5.0;                             // 规划时间

    auto coeffs = quinticPolynomial(s0, v0, acc0, s1, v1, acc1, T);

    cout << "五次多项式系数: ";
    for (auto c : coeffs) cout << c << " ";
    cout << endl;

    // 打印每秒的位置、速度、加速度
    for (double t = 0; t <= T; t += 1.0) {
        double pos = calcPos(coeffs, t);
        double vel = calcVel(coeffs, t);
        double acc = calcAcc(coeffs, t);
        cout << "t=" << t << "  s=" << pos << "  v=" << vel << "  a=" << acc << endl;
    }
    return 0;
}