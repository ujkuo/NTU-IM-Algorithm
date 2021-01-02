/*
 * UVa1754.cpp
 * Copyleft (ɔ) 2021 wildfootw <wildfootw@wildfoo.tw>
 *
 * Distributed under terms of the MIT license.
 */

// [x] Accepted

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

static const unsigned long long int INF = 1e18;

class UVa1754
{
public:
    UVa1754(size_t total_d, size_t total_k):
        total_d(total_d), total_k(total_k),
        squared_errors(total_d, vector< vector<unsigned long long int> >
                      (total_d + 1, vector<unsigned long long int>
                      (total_k + 1, INF))), // squared_errors[D][D][K] = INF
        pixels(total_d)                     // pixels[D]
    {

    }
    unsigned long long int get_answer()
    {
        return get_sum_squared_errors(0, total_d, total_k);
    }
    void input()
    {
        for(size_t i = 0;i < total_d;++i)
            cin >> pixels[i].first >> pixels[i].second;
    }
private:
    size_t total_d, total_k;
    vector< vector< vector<unsigned long long int> > > squared_errors;
    vector< pair<int, unsigned long long int> > pixels;

    unsigned long long int get_sum_squared_errors(size_t pos, size_t d, size_t k)
    {
        if(squared_errors[pos][d][k] != INF) return squared_errors[pos][d][k];
        if(k == 1) return squared_errors[pos][d][k] = get_squared_errors(pos, d);
        unsigned long long int ret = INF;
        for(size_t i = 1;i <= (d - k + 1);++i) // first block d
        {
            ret = min(ret, get_sum_squared_errors(pos, i, 1) + get_sum_squared_errors(pos + i, d - i, k - 1));
        }
        return squared_errors[pos][d][k] = ret;
    }

    unsigned long long int get_squared_errors(size_t pos, size_t d) // Binary Linear Equation
    {
        long double a = 0, b = 0;
        for(size_t i = pos;i < (pos + d);++i) // a*x^2 - b*x + c
        {
            a += pixels[i].second;
            b += pixels[i].first * 2 * pixels[i].second;
        }
        int value_new = round(b / a / 2);
        unsigned long long int ret = 0;
        for(size_t i = pos;i < (pos + d);++i)
        {
            ret += (pow(pixels[i].first - value_new, 2) * pixels[i].second);
        }
        return ret;
    }
};

int main()
{
    size_t d, k;
    while(cin >> d >> k)
    {
        UVa1754 solver(d, k);
        solver.input();
        unsigned long long int answer = solver.get_answer();
        cout << answer << endl;
    }

    clog << "Time used = " << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}

