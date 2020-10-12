#include "bits/stdc++.h"

using namespace::std;

struct Matrix {
    int m[2][2] = {};
    Matrix() {
        Matrix(0, 0, 0, 0);
    }

    Matrix(int x00, int x01, int x10, int x11) {
        m[0][0] = x00;
        m[0][1] = x01;
        m[1][0] = x10;
        m[1][1] = x11;
    }

    Matrix& operator =(const Matrix &rhs) {
        if(this != &rhs) {
            m[0][0] = rhs.m[0][0];
            m[0][1] = rhs.m[0][1];
            m[1][0] = rhs.m[1][0];
            m[1][1] = rhs.m[1][1];
        }
        return *this;
    }

    Matrix operator +(const Matrix &mat) {
        Matrix res;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                res.m[i][j] = m[i][j] + mat.m[i][j];
            }
        }
        return res;
    }

    Matrix operator -(const Matrix &mat) {
        Matrix res;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                res.m[i][j] = m[i][j] - mat.m[i][j];
            }
        }
        return res;
    }

    Matrix operator *(const Matrix &mat) {
        Matrix res;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                res.m[i][j] = m[i][0] * mat.m[0][j] + m[i][1] * mat.m[1][j];
            }
        }
        return res;
    }

    Matrix exp(int n) {
        Matrix res(1,0,1,0);
        Matrix p = *this;
        while(n) {
            if(n & 1) res = res * p;
            n >>= 1;
            p = p * p;
        }
        return res;
    }

    void print() {
        cout << m[0][0] << ' ' << m[0][1] << ' ' << m[1][0] << ' ' << m[1][1] << '\n';
    }
};

