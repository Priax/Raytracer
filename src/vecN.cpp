/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** vecN
*/
#include "vecN.hpp"
#include <cmath>
#include <stdexcept>

template<typename T, size_t N>
VectorN<T, N>::VectorN() : e{} {}

template<typename T, size_t N>
VectorN<T, N>::VectorN(const T& val) {
    for (size_t i = 0; i < N; ++i) {
        e[i] = val;
    }
}

template<typename T, size_t N>
VectorN<T, N>::VectorN(const std::array<T, N>& arr) : e(arr) {}

template<typename T, size_t N>
T VectorN<T, N>::operator[](size_t i) const {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return e[i];
}

template<typename T, size_t N>
T& VectorN<T, N>::operator[](size_t i) {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return e[i];
}

template<typename T, size_t N>
VectorN<T, N>& VectorN<T, N>::operator+=(const VectorN& v) {
    for (size_t i = 0; i < N; ++i) {
        e[i] += v[i];
    }
    return *this;
}

template<typename T, size_t N>
VectorN<T, N>& VectorN<T, N>::operator-=(const VectorN& v) {
    for (size_t i = 0; i < N; ++i) {
        e[i] -= v[i];
    }
    return *this;
}

template<typename T, size_t N>
VectorN<T, N>& VectorN<T, N>::operator*=(const T& t) {
    for (size_t i = 0; i < N; ++i) {
        e[i] *= t;
    }
    return *this;
}

template<typename T, size_t N>
VectorN<T, N>& VectorN<T, N>::operator/=(const T& t) {
    if (t == 0) {
        throw std::invalid_argument("Division by zero");
    }
    for (size_t i = 0; i < N; ++i) {
        e[i] /= t;
    }
    return *this;
}

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const VectorN<T, N>& v) {
    out << "(";
    for (size_t i = 0; i < N; ++i) {
        out << v[i];
        if (i < N - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}

template<typename T, size_t N>
VectorN<T, N> operator+(const VectorN<T, N>& u, const VectorN<T, N>& v) {
    VectorN<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = u[i] + v[i];
    }
    return result;
}

template<typename T, size_t N>
VectorN<T, N> operator-(const VectorN<T, N>& u, const VectorN<T, N>& v) {
    VectorN<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = u[i] - v[i];
    }
    return result;
}

template<typename T, size_t N>
VectorN<T, N> operator*(const VectorN<T, N>& v, const T& t) {
    VectorN<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = v[i] * t;
    }
    return result;
}

template<typename T, size_t N>
VectorN<T, N> operator*(const T& t, const VectorN<T, N>& v) {
    return v * t;
}

// Explicit instantiations for supported types
// template class VectorN<double, 2>;
// template class VectorN<double, 3>;
// template class VectorN<double, 4>;
// template class VectorN<float, 2>;
// template class VectorN<float, 3>;
// template class VectorN<float, 4>;
// template std::ostream& operator<<(std::ostream& out, const VectorN<double, 2>& v);
// template std::ostream& operator<<(std::ostream& out, const VectorN<double, 3>& v);
// template std::ostream& operator<<(std::ostream& out, const VectorN<double, 4>& v);
// template std::ostream& operator<<(std::ostream& out, const VectorN<float, 2>& v);
// template std::ostream& operator<<(std::ostream& out, const VectorN<float, 3>& v);
// template std::ostream& operator<<(std::ostream& out, const VectorN<float, 4>& v);
// template VectorN<double, 2> operator+(const VectorN<double, 2>& u, const VectorN<double, 2>& v);
// template VectorN<double, 3> operator+(const VectorN<double, 3>& u, const VectorN<double, 3>& v);
// template VectorN<double, 4> operator+(const VectorN<double, 4>& u, const VectorN<double, 4>& v);
// template VectorN<float, 2> operator+(const VectorN<float, 2>& u, const VectorN<float, 2>& v);
// template VectorN<float, 3> operator+(const VectorN<float, 3>& u, const VectorN<float, 3>& v);
// template VectorN<float, 4> operator+(const VectorN<float, 4>& u, const VectorN<float, 4>& v);
// template VectorN<double, 2> operator-(const VectorN<double, 2>& u, const VectorN<double, 2>& v);
// template VectorN<double, 3> operator-(const VectorN<double, 3>& u, const VectorN<double, 3>& v);
// template VectorN<double, 4> operator-(const VectorN<double, 4>& u, const VectorN<double, 4>& v);
// template VectorN<float, 2> operator-(const VectorN<float, 2>& u, const VectorN<float, 2>& v);
// template VectorN<float, 3> operator-(const VectorN<float, 3>& u, const VectorN<float, 3>& v);
// template VectorN<float, 4> operator-(const VectorN<float, 4>& u, const VectorN<float, 4>& v);
// template VectorN<double, 2> operator*(const VectorN<double, 2>& v, const double& t);
// template VectorN<double, 3> operator*(const VectorN<double, 3>& v, const double& t);
// template VectorN<double, 4> operator*(const VectorN<double, 4>& v, const double& t);
// template VectorN<float, 2> operator*(const VectorN<float, 2>& v, const float& t);
// template VectorN<float, 3> operator*(const VectorN<float, 3>& v, const float& t);
// template VectorN<float, 4> operator*(const VectorN<float, 4>& v, const float& t);
// template VectorN<double, 2> operator*(const double& t, const VectorN<double, 2>& v);
// template VectorN<double, 3> operator*(const double& t, const VectorN<double, 3>& v);
// template VectorN<double, 4> operator*(const double& t, const VectorN<double, 4>& v);
// template VectorN<float, 2> operator*(const float& t, const VectorN<float, 2>& v);
// template VectorN<float, 3> operator*(const float& t, const VectorN<float, 3>& v);
// template VectorN<float, 4> operator*(const float& t, const VectorN<float, 4>& v);

template<typename T, size_t N>
VectorN<T, N> operator/(const VectorN<T, N>& v, const T& t) {
    if (t == 0) {
        throw std::invalid_argument("Division by zero");
    }
    VectorN<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = v[i] / t;
    }
    return result;
}

template<typename T, size_t N>
T VectorN<T, N>::length() const {
    return sqrt(length_squared());
}

template<typename T, size_t N>
T VectorN<T, N>::length_squared() const {
    T sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += e[i] * e[i];
    }
    return sum;
}

template<typename T, size_t N>
bool VectorN<T, N>::near_zero() const {
    const T s = static_cast<T>(1e-8);
    for (size_t i = 0; i < N; ++i) {
        if (std::fabs(e[i]) >= s) {
            return false;
        }
    }
    return true;
}

template<typename T, size_t N>
VectorN<T, N> VectorN<T, N>::normalized() const {
    const T len = length();
    return *this / len;
}

template<typename T, size_t N>
T VectorN<T, N>::dot(const VectorN& v) const {
    T dot_product = 0;
    for (size_t i = 0; i < N; ++i) {
        dot_product += e[i] * v[i];
    }
    return dot_product;
}

template<typename T, size_t N>
VectorN<T, N> VectorN<T, N>::cross(const VectorN<T, N>& v) const {
    if (N != 3) {
        throw std::out_of_range("Cross product is only defined for 3-dimensional vectors");
    }
    return VectorN<T, N>(e[1] * v.e[2] - e[2] * v.e[1],
                         e[2] * v.e[0] - e[0] * v.e[2],
                         e[0] * v.e[1] - e[1] * v.e[0]);
}

template<typename T, size_t N>
VectorN<T, N> VectorN<T, N>::random() {
    VectorN<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = Random::random_double();
    }
    return result;
}

template<typename T, size_t N>
VectorN<T, N> VectorN<T, N>::random(T min, T max) {
    VectorN<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = Random::random_double(min, max);
    }
    return result;
}
