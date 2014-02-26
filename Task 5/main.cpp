#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <assert.h>

using namespace std;

class Generation {
public:
	long long GenerationAmmount;
	long long N;
	vector < pair < set < long long >, set < long long > > > Generations;

	long long sqr(long long x) {
		return x*x;
	}

    double sqr(double x) {
        return x*x;
    }

	double middle(const vector < double > &x, int st = 0) {
		double Ans = 0;
		for (size_t i = st; i < x.size(); i++)
			Ans += 1.0 * x[i] / x.size();
		return Ans;
	}

	Generation(long long _N = 160, long long _GenerationAmmount = 100, int _InitSrand = 0) {
		GenerationAmmount = _GenerationAmmount;
		N = _N;
		if (_InitSrand > 0)
			srand(_InitSrand);
		else
			srand(time(NULL));

		Generations.resize(GenerationAmmount);
		for (size_t i = 0; i < GenerationAmmount; i++) {
			Generations[i].first.clear();
			Generations[i].second.clear();
			for (int j = 0; j < N; j++)
				Generations[i].first.insert(j);
		}
	}

	~Generation() { }

	vector < vector < pair < long long, long long > > > Run1(long long iterations) {
		vector < vector < pair < long long, long long > > > res(GenerationAmmount, vector < pair < long long, long long > >(iterations, make_pair(0, 0)));
		for (int i = 0; i < iterations; i++) {
			for (int j = 0; j < GenerationAmmount; j++) {
				int k = rand() % N;
				if (Generations[j].first.count(k)) {
					Generations[j].first.erase(k);
					Generations[j].second.insert(k);
				}
				else {
					Generations[j].second.erase(k);
					Generations[j].first.insert(k);
				}
				res[j][i].first = Generations[j].first.size();
				res[j][i].second = Generations[j].second.size();
			}
		}
		return res;
	}

	vector < vector < pair < long long, long long > > > Run2(long long iterations) {
		vector < vector < pair < long long, long long > > > res(GenerationAmmount, vector < pair < long long, long long > >(iterations, make_pair(0, 0)));
        for (int j = 0; j < GenerationAmmount; j++) {
            for (int i = 0; i < iterations; i++) {
				int k = rand() % N;
				if (Generations[j].first.count(k)) {
					Generations[j].first.erase(k);
					Generations[j].second.insert(k);
				}
				else {
					Generations[j].second.erase(k);
					Generations[j].first.insert(k);
				}
				res[j][i].first = Generations[j].first.size();
				res[j][i].second = Generations[j].second.size();
			}
		}
		return res;
	}

	size_t St_time(const vector < vector < pair < long long, long long > > > &history) {
		size_t Ans = 0;
		for (size_t i = 0; i < history.size(); i++) {
			for (size_t j = 0; j < history[i].size(); j++)
			if (history[i][j].first == history[i][j].second) {
				Ans = max(Ans, j);
				break;
			}
		}
		return Ans;
	}

	void CalculateFirst (const vector < vector < pair < long long, long long > > > &history, vector < double > &sigma, vector < double > &_n, vector < double > &_n2, size_t st_time) {
		sigma.clear();
		   _n.clear();
		  _n2.clear();
		sigma.resize(history.size(), 0);
		   _n.resize(history.size(), 0);
		  _n2.resize(history.size(), 0);
		for (size_t i = 0; i < history.size(); i++) {
			for (size_t j = st_time; j < history[i].size(); j++) {
//				 _n[i] += 1.0 *     history[i][j].first  / (history[i].size() - st_time);
//				_n2[i] += 1.0 * sqr(history[i][j].first) / (history[i].size() - st_time);
				 _n[i] += 1.0 *     history[i][j].first ;
				_n2[i] += 1.0 * sqr(history[i][j].first);
			}
             _n[i] /= (history[i].size() - st_time);
            _n2[i] /= (history[i].size() - st_time);
			sigma[i] = sqrt(_n2[i] - sqr(_n[i]));
//			cerr << "    _n2[" << i << "]  = " << _n2[i] << endl;
//			cerr << "     _n[" << i << "]  = " << _n[i] << endl;
//			cerr << " sqr(_n[" << i << "]) = " << sqr(_n[i]) << endl;
//			cerr << "sigma^2[" << i << "]  = " << _n2[i] - sqr(_n[i]) << endl;
//			cerr << "  sigma[" << i << "]  = " << sigma[i] << endl;
//			cerr << endl;
		}
	}

	void CalculateSecond(const vector < vector < pair < long long, long long > > > &history, vector < double > &sigma, vector < double > &_n, vector < double > &_n2, size_t st_time) {
		sigma.clear();
		   _n.clear();
		  _n2.clear();
		sigma.resize(history[0].size() - st_time, 0);
		   _n.resize(history[0].size() - st_time, 0);
		  _n2.resize(history[0].size() - st_time, 0);

//        cerr << "\nHistory of " << history.size() << " - ";
//        for (int i = 0; i < history.size(); i++) {
//            cerr << history[i][st_time].first << " ";
//        }
//        cerr << "\n";

		for (size_t i = st_time; i < history[0].size(); i++) {
			for (size_t j = 0; j < history.size(); j++) {
//                cerr << "Ok!\n";
//                cerr << " i = " << i - st_time << endl;
//                if (i == st_time) {
//                    cerr << "Before: \n";
//                    cerr <<  _n[i - st_time] << ", ";
//                    cerr << _n2[i - st_time] << "\n";
//                }
				 _n[i - st_time] += 1.0 *     history[j][i].first  / history.size();
				_n2[i - st_time] += 1.0 * sqr(history[j][i].first) / history.size();
//                if (i == st_time) {
//                    cerr << "After: \n";
//                    cerr <<  _n[i - st_time] << ", ";
//                    cerr << _n2[i - st_time] << "\n";
//                }
			}
			sigma[i - st_time] = sqrt(_n2[i - st_time] - sqr(_n[i - st_time]));
//			cerr << "sigma[" << i - st_time << "] = " << sigma[i - st_time] << endl;

//          cerr << "i = " << i - st_time << ", _n[i] = " << _n[i - st_time] << ", _n2[i] = " << _n2[i - st_time] << ", sigma[i] = " << sigma[i - st_time] <<  endl;
		}
//        cerr << "\nHistory[0][st_time] = " << history[0][st_time].first;
//        cerr << "\n_n2[0] = " << _n2[0];
//        cerr << "\n_n[0]^2 = " << sqr(_n[0]);
//        cerr << "\nSigma Calculated = " << sqrt(_n2[0] - sqr(_n[0]));
//        cerr << "\nSigma = " << sigma[0];
//        cerr << "\n\n";
	}

};

int main(int argc, char *argv[]) {
	vector < double > sigma, _n, _n2;
	double __sigma, __n, __n2;
	int rr, kk;

	Generation G(160, 15);
	vector < vector < pair < long long, long long > > > history = G.Run2(5000);
	cout << "St_time = " << G.St_time(history) << endl << endl;

    G.CalculateFirst(history, sigma, _n, _n2, G.St_time(history));
	__sigma = G.middle(sigma);
        __n = G.middle(_n);
	   __n2 = G.middle(_n2);
    cout << "First:\n";
    cout << "Avarage:\n";
	cout << "Sigma = " << __sigma << ", <n> = " << __n << ", <n^2> = " << __n2 << endl;
	cout << "Sigma / <n> = " << __sigma / __n << ", 1 / sqrt(N) = " << 1.0 / sqrt(1.0*G.N) << endl << endl;
    rr = rand() % history.size();
	cout << "Random Number N     = " << rr + 1 << ":\n";
	cout << "Sigma = " << sigma[rr] << ", <n> = " << _n[rr] << ", <n^2> = " << _n2[rr] << endl;
	cout << "Sigma / <n> = " << sigma[rr] / _n[rr] << ", 1 / sqrt(N) = " << 1.0 / sqrt(1.0*G.N) << endl << endl;

	G.CalculateSecond(history, sigma, _n, _n2, G.St_time(history));
	__sigma = G.middle(sigma);
	__n = G.middle(_n);
	__n2 = G.middle(_n2);
	cout << endl;
	cout << "Second:\n";
	cout << "Average:\n";
	cout << "Sigma = " << __sigma << ", <n> = " << __n << ", <n^2> = " << __n2 << endl;
	cout << "Sigma / <n> = " << __sigma / __n << ", 1 / sqrt(N) = " << 1.0 / sqrt(1.0*G.N) << endl << endl;
    rr = rand() % history.size();
	cout << "Random Point t = " << rr + G.St_time(history) << ":\n";
	cout << "Sigma = " << sigma[rr] << ", <n> = " << _n[rr] << ", <n^2> = " << _n2[rr] << endl;
	cout << "Sigma / <n> = " << sigma[rr] / _n[rr] << ", 1 / sqrt(N) = " << 1.0 / sqrt(1.0*G.N) << endl;

//	system("pause");

	return 0;
}
