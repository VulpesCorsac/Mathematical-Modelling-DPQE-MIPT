#ifndef TICHONOV_HPP_INCLUDED
#define TICHONOV_HPP_INCLUDED

#include <vector>
#include <assert.h>

#define EPS 1e-8

template < class T >
class Tichonov {
private:
	int N;
	T tay;
	T delta;
	std::vector < T >  Y;
	std::vector < T >  Z;
	std::vector < T > _Z;

	T SQR(const T &x) {
		return x * x;
	}

	T ABS(const T &x) {
		if (x < 0)
			return -x;
		return x;
	}

	T Smth(const std::vector < T > &A, const std::vector < T > &B) {
		assert(A.size() == B.size() && "A and B have different sizes!\n");
		T ans = 0;
		for (size_t i = 0; i < A.size(); i++) {
			ans += SQR(A[i] - B[i]);
		}
		ans /= A.size();
		return ans;
	}

	T sigma(void) {
		return Smth(this->Z, this->_Z);
	}

	T ro(void) {
		return Smth(this->Z, this->Y);
	}

	void Fill(const T &alpha, std::vector < T > &a, std::vector < T > &c, std::vector < T > &b, std::vector < T > &f) {
		a.clear(); a.resize(this->N + 1);
		c.clear(); c.resize(this->N + 1);
		b.clear(); b.resize(this->N + 1);
		f.clear(); f.resize(this->N + 1);

		a[0] = 0;
		c[0] = 1 + alpha + alpha / SQR(this->tay);
		b[0] = -alpha / SQR(this->tay);
		f[0] = this->Y[0];
		for (int i = 1; i < this->N; i++) {
			a[i] = -alpha / SQR(this->tay);
			c[i] = 1 + alpha + 2 * alpha / SQR(this->tay);
			b[i] = a[i];
			f[i] = this->Y[i];
		}
		a[this->N] = -alpha / SQR(this->tay);
		c[this->N] = 1 + alpha / SQR(this->tay);
		b[this->N] = 0;
		f[this->N] = this->Y[this->N];

	}

	/**
	* n - число уравнений (строк матрицы)
	* b - диагональ, лежащая над главной (нумеруется: [0;n-2])
	* c - главная диагональ матрицы A (нумеруется: [0;n-1])
	* a - диагональ, лежащая под главной (нумеруется: [1;n-1])
	* f - правая часть (столбец)
	* x - решение, массив x будет содержать ответ
	* Данный код работает при предположении, что a[0] = 0, b[n - 1] = 0.
	*/
	void solveMatrix(int n, std::vector < T > &a, std::vector < T > &c, std::vector < T > &b, std::vector < T > &f, std::vector < T > &x) {
		assert(a.size() == n && "Vector a has size not equal to n!");
		assert(b.size() == n && "Vector b has size not equal to n!");
		assert(c.size() == n && "Vector c has size not equal to n!");
		assert(f.size() == n && "Vector f has size not equal to n!");
		x.clear();
		x.resize(n);

		T m;
		for (int i = 1; i < n; i++) {
			m = a[i] / c[i - 1];
			c[i] = c[i] - m*b[i - 1];
			f[i] = f[i] - m*f[i - 1];
		}
		x[n - 1] = f[n - 1] / c[n - 1];
		for (int i = n - 2; i >= 0; i--)
			x[i] = (f[i] - b[i] * x[i + 1]) / c[i];
		return;
	}

public:

	void Set_Data(const size_t &_N, const T &_tay, const std::vector < T > &_Y) {
		assert(_Y.size() == _N + 1 && "Data setting size is not equal N + 1!");
		this->N = _N;
		this->tay = _tay;
		this->Y = _Y;
		return;
	}

	std::vector < T > Get_Data(const bool &noise_amplitude_is_known, const T &noise_amplitude) {
		T alpha = 1;
		T this_sigma = 1000;
		T prev_sigma = this_sigma;

		std::vector < T > a, b, c, f;
		Fill(alpha, a, c, b, f);
		solveMatrix(this->N + 1, a, c, b, f, this->Z);
		while (true) {
			_Z = Z;
			prev_sigma = this_sigma;
			alpha *= 0.5;
			Fill(alpha, a, c, b, f);
			solveMatrix(this->N + 1, a, c, b, f, this->Z);
			this_sigma = sigma();
			if (noise_amplitude_is_known) {
				if (ro() - SQR(noise_amplitude) <= 0) {
					cerr << "alpha = " << alpha << endl;
					return this->Z;
				}
			}
			else {
				//				if (this_sigma > prev_sigma) {
				if (alpha < noise_amplitude) {
					cerr << "alpha = " << alpha << ", sigma = " << this_sigma << endl;
					return this->Z;
				}
			}
		}
	}

	Tichonov(const int &_N, const T &_tay, const std::vector < T > &_Y) {
		Set_Data(_N, _tay, _Y);
	}

	Tichonov() {

	}

	~Tichonov() {

	}

};

#endif // TICHONOV_HPP_INCLUDED