#include <iostream>
#include <vector>
#include <complex>

// source: EMAXX

namespace FFT {

    using base = std::complex<double>;
    const double PI = 3.14159265358979323846;

    uint32_t rev(uint32_t num, uint32_t log) {
        uint32_t res = 0;
        for (uint32_t i = 0; i < log; ++i) {
            if (num & (1 << i)) {
                res |= (1 << (log - i - 1));
            }
        }
        return res;
    }

    void fft(std::vector<base> &a, bool invert) {
        uint32_t n = a.size();
        uint32_t log = 0;

        while ((1 << log) != n) {
            ++log;
        }

        for (uint32_t i = 0; i < n; ++i) {
            if (i < rev(i, log)) {
                swap(a[i], a[rev(i, log)]);
            }
        }

        for (uint32_t len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            base wn(cos(ang), sin(ang));
            for (uint32_t i = 0; i < n; i += len) {
                base w = 1;
                for (uint32_t j = 0; j < len / 2; ++j) {
                    base u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wn;
                }
            }
        }

        if (invert) {
            for (uint32_t i = 0; i < n; ++i) {
                a[i] /= n;
            }
        }
    }

    void multiply(const std::vector<int32_t> &a,
                  const std::vector<int32_t> &b,
                  std::vector<int32_t> &res) {
        std::vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        uint32_t n = a.size();
        fft(fa, false);
        fft(fb, false);
        std::vector<base> fres(n);
        for (uint32_t i = 0; i < n; ++i) {
            fres[i] = fa[i] * fb[i];
        }
        fft(fres, true);
        for (uint32_t i = 0; i < n; ++i) {
            res[i] = llround(fres[i].real());
        }
    }
}