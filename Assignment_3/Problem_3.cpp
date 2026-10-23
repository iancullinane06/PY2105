#include <vector>
using namespace std;

class least_squares_fit {
public:
    least_squares_fit(vector<pair<double, double>> v, int n) {
    double sum_x = 0;
    double sum_y = 0;
    double sum_x2 = 0;
    double sum_xy = 0;
    for (int i = 0; i < n; i++) {
        double x = v[i].first;
        double y = v[i].second;
        sum_x += x;
        sum_y += y;
        sum_x2 += x * x;
        sum_xy += x * y;
    }
    double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double intercept = (sum_y - slope * sum_x) / n;
    m_slope = slope;
    m_intercept = intercept;
    }
    double get_slope() const { return m_slope; }
    double get_intercept() const { return m_intercept; }
private:
    double m_slope;
    double m_intercept;
};