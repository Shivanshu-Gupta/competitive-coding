#include <iostream>
#include <vector>
#include <complex>

using namespace std;

typedef long double Double;
typedef complex<long double> Complex;

struct FFT {
    int ReverseBits(int x, int &L);
    vector<Complex> DFT(vector<Complex> A, bool inverse);
    vector<Double> convolution(vector<Double> &a, vector<Double> &b);
};

/**
 * @brief Reverse bits of an integer
 *
 * @param x the number
 * @param L number of bits from the left to reverse
 *
 * @return bit-reversed number
 */
int FFT::ReverseBits(int x, int &L) {
    int res = 0;
    for(int i = 0; i < L; i++) {
        res = (res << 1) | (x & 1);
        x >>= 1;
    }
    return res;
}

/**
 * @brief Fast Fourier Transform
 * @details This function performs the Fast Fourier Transform to compute the
 * fourier transform of the input array.
 *
 * @param A input array
 * @param inverse compute DFT if true else compute IDFT
 *
 * @return DFT/IDFT of A
 */
vector<Complex> FFT::DFT(vector<Complex> A, bool inverse) {
    int n = A.size();
    int L = __builtin_ctz(n);

    // Reorder the inputs in-place according to the bit-reversed order.
    for(int i = 0; i < n; i++) {
        int j = ReverseBits(i, L);
        if(i < j) swap(A[i], A[j]);
    }

    Complex w = 1;
    for(int s = 1; s <= L; s++) {
        // size of each sub-array
        int m = (1 << s);

        Complex wm = exp(Complex(0, 2.0 * M_PI / m));
        if(inverse == 1) wm = Complex(1, 0) / wm;

        // compute the FT for each sub-array.
        for (int k = 0; k < n; k += m) {
            Complex w = 1;
            for (int j = 0; j < m/2; j++) {
                Complex u = A[k + j];
                Complex t = w * A[k + j + m/2];
                A[k + j] = u + t;
                A[k + j + m/2] = u - t;
                w *= wm;
            }
        }
    }

    if (inverse) for (int i = 0; i < n; i++) A[i] /= n;
    return A;
}

/**
 * @brief Convolution of two arrays
 * @details This function convolves two arrays a = a0,...,am-1 and b = b0,...,bn-1
 *
 * @param a the first array a0,...,am-1
 * @param b the second array b0,...,bn-1
 *
 * @return c = a * b where c[k] = summ(a[k-j], b[j]);
 */
vector<Double> FFT::convolution(vector<Double> &a, vector<Double> &b) {
    int L = 1, n;
    while((1 << L) < a.size()) L++;
    while((1 << L) < b.size()) L++;
    n = 1 << (L);

    vector<Complex> aa(n), bb(n);
    for(int i = 0; i < a.size(); i++) aa[i] = Complex(a[i], 0);
    for(int i = 0; i < b.size(); i++) bb[i] = Complex(b[i], 0);

    vector<Complex> AA = DFT(aa, 0);
    vector<Complex> BB = DFT(bb, 0);
    vector<Complex> CC(n);
    for (int i = 0; i < n; ++i) {
        CC[i] = AA[i] * BB[i];
        // cout<<AA[i]<<'\t'<<BB[i]<<'\t'<<CC[i]<<endl;
    }

    vector<Complex> cc = DFT(CC, 1);

    vector<Double> c;
    for (int i = 0; i < a.size() + b.size() - 1; i++) c.push_back(cc[i].real());

    return c;
}

int FFTTest() {
    vector<Double> a = {1, 3, 4, 5, 7};
    vector<Double> b = {2, 4, 6};

    FFT fft;
    vector<Double> c = fft.convolution(a, b);
    for(auto ci : c) {
        cout<<ci<<'\t';
    }
    cout<<endl;

    return 0;
}
