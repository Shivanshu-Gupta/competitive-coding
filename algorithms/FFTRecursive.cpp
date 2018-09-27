#include <iostream>
#include <vector>
#include <complex>

using namespace std;

typedef long double Double;
typedef complex<long double> Complex;

struct RecursiveFFT {
    vector<Complex> DFT(vector<Complex> A, bool inverse);
    vector<Double> convolution(vector<Double> &a, vector<Double> &b);
};

vector<Complex> RecursiveFFT::DFT(vector<Complex> a, bool inverse) {
    int n = a.size();
    if(n == 1) {
        return vector<Complex>(1, a[0]);
    }
    vector<Complex> ae, ao;
    for (int i = 0; i < n; ++i) {
        ((i & 1) ? ao : ae).push_back(a[i]);
    }
    vector<Complex> Ae = DFT(ae, inverse), Ao = DFT(ao, inverse);

    vector<Complex> A(n);
    Complex w = 1, wn = exp(Complex(0, 2.0 * M_PI / n));
    if(inverse == 1) wn = Complex(1, 0) / wn;
    for (int k = 0; k < (n/2); ++k) {
        A[k] = Ae[k] + w * Ao[k];
        A[k + n/2] = Ae[k] - w * Ao[k];
        w *= wn;
    }

    //if (inverse == 1) for (int i = 0; i < n; i++) A[i] /= n;
    return A;
}

vector<Double> RecursiveFFT::convolution(vector<Double> &a, vector<Double> &b) {
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
    for (int i = 0; i < a.size() + b.size() - 1; i++) c.push_back(cc[i].real()/n);

    return c;
}

int FFTRecursiveTest() {
    vector<Double> a = {1, 3, 4, 5, 7};
    vector<Double> b = {2, 4, 6};

    RecursiveFFT fft;
    vector<Double> c = fft.convolution(a, b);
    for(auto ci : c) {
        cout<<ci<<'\t';
    }
    cout<<endl;

    return 0;
}
