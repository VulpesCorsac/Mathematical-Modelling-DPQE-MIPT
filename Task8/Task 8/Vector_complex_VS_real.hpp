#ifndef VECTOR_COMPLEX_VS_REAL_HPP_INCLUDED
#define VECTOR_COMPLEX_VS_REAL_HPP_INCLUDED

#include <vector>
#include <complex>
#include <assert.h>

template < class Type >
std::vector < std::complex < Type > > Vector_real_to_complex(const std::vector < Type > &V) {
	std::vector < std::complex < Type > > Ans(V.size());
	for (size_t i = 0; i < V.size(); i++)
		Ans[i] = std::complex < Type >(V[i]);
	return Ans;
}

template < class Type >
std::vector < std::complex < Type > > Vector_real_real_to_complex(const std::vector < Type > &R, const std::vector < Type > &I) {
	assert(R.size() == I.size());
	std::vector < std::complex < Type > > Ans(R.size());
	for (size_t i = 0; i < Ans.size(); i++)
		Ans[i] = std::complex < Type >(R[i], I[i]);
	return Ans;
}

template < class Type >
std::vector < std::complex < Type > > Vector_complex_to_real(const std::vector < Type > &V) {
	std::vector < std::complex < Type > > Ans(V.size());
	for (size_t i = 0; i < V.size(); i++)
		Ans[i] = (V[i].real());
	return Ans;
}

template < class Type >
std::vector < std::complex < Type > > Vector_complex_to_real_abs(const std::vector < Type > &V) {
	std::vector < std::complex < Type > > Ans(V.size());
	for (size_t i = 0; i < V.size(); i++)
		Ans[i] = (std::abs(V[i]));
	return Ans;
}

template < class Type >
std::vector < std::complex < Type > > Merge_vectors_to_complex(const std::vector < Type > &X, const std::vector < Type > &Y) {
	assert(X.size() == Y.size());
	std::vector < std::complex < Type > > Ans(X.size());
	for (size_t i = 0; i < Ans.size(); i++)
		Ans[i] = std::complex < Type >(X[i], Y[i]);
	return Ans;
}

template < class Type >
void Split_complex_vector(const std::vector < std::complex < Type > > &V, std::vector < Type > &X, std::vector < Type > &Y) {
	X.clear();
	Y.clear();
	X.resize(V.size());
	Y.resize(V.size());
	for (size_t i = 0; i < V.size(); i++) {
		X[i] = V[i].real();
		Y[i] = V[i].imag();
	}
	return;
}

#endif // VECTOR_COMPLEX_VS_REAL_HPP_INCLUDED
