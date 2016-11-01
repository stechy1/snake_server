#ifndef SNAKE_VECTOR2D
#define SNAKE_VECTOR2D

#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>
#include <random>
#include <memory>
#include <iostream>

// Kvůli překladu ve woknech
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace SnakeServer {

class Vector2D {
public:
    // Konstruktor se souřadnicemi X a Y
    Vector2D() : m_x(0), m_y(0) {}

    // Standartní kostruktor
    Vector2D(const double t_x, const double t_y) : m_x(t_x), m_y(t_y) {}

    // Kopy konstruktor
    Vector2D(const Vector2D &other) {
        m_x = other.m_x;
        m_y = other.m_y;
    }

    ~Vector2D() {};

    // Přetížení operátorů - standartní operace
    Vector2D &operator+=(const Vector2D &v) {
        m_x += v.m_x;
        m_y += v.m_y;
        return *this;
    }

    Vector2D &operator+=(const double value) {
        m_x += value;
        m_y += value;
        return *this;
    }

    Vector2D &operator-=(const Vector2D &v) {
        m_x -= v.m_x;
        m_y -= v.m_y;
        return *this;
    }

    Vector2D &operator-=(const double value) {
        m_x -= value;
        m_y -= value;
        return *this;
    }

    Vector2D &operator*=(const Vector2D &v) {
        m_x *= v.m_x;
        m_y *= v.m_y;
        return *this;
    }

    Vector2D &operator*=(const double value) {
        m_x *= value;
        m_y *= value;
        return *this;
    }

    Vector2D &operator/=(const Vector2D &v) {
        m_x /= v.m_x;
        m_y /= v.m_y;
        return *this;
    }

    Vector2D &operator/=(const double value) {
        m_x /= value;
        m_y /= value;
        return *this;
    }

    Vector2D operator+(const double value) {
        return Vector2D(m_x + value, m_y + value);
    }

    Vector2D operator+(const Vector2D &value) {
        return Vector2D(m_x + value.m_x, m_y + value.m_y);
    }

    Vector2D operator-(const double value) {
        return Vector2D(m_x - value, m_y - value);
    }

    Vector2D operator-(const Vector2D &value) {
        return Vector2D(m_x - value.m_x, m_y - value.m_y);
    }

    Vector2D operator*(const double value) {
        return Vector2D(m_x * value, m_y * value);
    }

    Vector2D operator*(const Vector2D &value) {
        return Vector2D(m_x * value.m_x, m_y * value.m_y);
    }

    Vector2D operator/(const double value) {
        return Vector2D(m_x / value, m_y / value);
    }

    Vector2D operator/(const Vector2D &value) {
        return Vector2D(m_x / value.m_x, m_y / value.m_y);
    }

    // Přetížení operátorů - porovnávací operace
    friend bool operator==(const Vector2D &lhs, const Vector2D &rhs) {
        return (lhs.m_x == rhs.m_x) && (lhs.m_y == rhs.m_y);
    }

    friend bool operator!=(const Vector2D &lhs, const Vector2D &rhs) { return !(lhs == rhs); }

    friend bool operator<(const Vector2D &lhs, const Vector2D &rhs) {
        return (lhs.m_x < rhs.m_x) && (lhs.m_y < rhs.m_y);
    }

    friend bool operator>=(const Vector2D &lhs, const Vector2D &rhs) { return !(lhs < rhs); }

    friend bool operator>(const Vector2D &lhs, const Vector2D &rhs) { return rhs < lhs; }

    friend bool operator<=(const Vector2D &lhs, const Vector2D &rhs) { return !(rhs < lhs); }

    double mag() { return sqrt(this->magSq()); }

    double magSq() { return (m_x * m_x + m_y * m_y); }

    double dot(const double _x, const double _y) { return m_x * _x + m_y * _y; }

    double cross(const Vector2D &other) { return m_x * other.m_y - m_y * other.m_x; }

    double dist(const Vector2D &other) {
        Vector2D temp(other);
        temp -= *this;

        return temp.mag();
    }

    double X() {
        return m_x;
    }

    double Y() {
        return m_y;
    }

    Vector2D &normalize() {
        double mag = this->mag();
        if (mag == 0) {
            return *this;
        }

        m_x /= mag;
        m_y /= mag;

        return *this;
    }

    Vector2D &limit(const double max) {
        double mSq = this->magSq();
        if (mSq > max * max) {
            this->normalize();
            m_x *= max;
            m_y *= max;
        }

        return *this;
    }

    Vector2D &setMag(const double n) {
        this->normalize();
        m_x *= n;
        m_y *= n;
        return *this; }

    Vector2D &rotate(const double degrees) { return rotateRad(degrees * M_PI / 180); }

    Vector2D &rotateRad(const double radians) {
        double cosVal = cos(radians);
        double sinVal = sin(radians);

        m_x = m_x * cosVal - m_y * sinVal;
        m_y = m_y * sinVal + m_y * cosVal;

        return *this;
    }

    Vector2D &lerp(const Vector2D &other, double amt) { return this->lerp(other.m_x, other.m_y, amt); }

    Vector2D &lerp(const double _x, const double _y, const double amt) {
        m_x += (_x - m_x) * amt;
        m_y += (_y - m_y) * amt;

        return *this;
    }

    Vector2D &constrain(const Vector2D &min, const Vector2D &max) {
        return constrain(min.m_x, min.m_y, max.m_x, max.m_y);
    }

    Vector2D &constrain(const double minX, const double minY, const double maxX, const double maxY) {
        if (m_x >= minX && m_x <= maxX && m_y >= minY && m_y <= maxY) {
            return *this;
        }

        if (m_x < minX)
            m_x = maxX;

        if (m_x > maxX)
            m_x = minX;

        if (m_y < minY)
            m_y = maxY;

        if (m_y > maxY)
            m_y = minY;

        return *this;
    }

    Vector2D &set(const Vector2D &other) {
        m_x = other.m_x;
        m_y = other.m_y;

        return *this;
    }

    std::string to_string() {
        return "Vector2D{X=" + std::to_string(m_x) + ", Y=" + std::to_string(m_y) + "}";
    }

    static Vector2D ZERO() {
        return Vector2D(0, 0);
        //return vector;
    }

    static Vector2D ONES() {
        Vector2D vector(1, 1);
        return vector;
    }

    static Vector2D LEFT() {
        Vector2D vector(-1, 0);
        return vector;
    }

    static Vector2D RIGHT() {
        Vector2D vector(1, 0);
        return vector;
    }

    static Vector2D UP() {
        Vector2D vector(0, -1);
        return vector;
    }

    static Vector2D DOWN() {
        Vector2D vector(0, 1);
        return vector;
    }

    static Vector2D RANDOM() {
        int res = random(3, 1);

        switch(res) {
            case 0:
                return UP();
            case 1:
                return DOWN();
            case 2:
                return LEFT();
            default:
                return RIGHT();
        }

    }

    static Vector2D RANDOM(const double min, const double max) {
        return RANDOM(min, min, max, max);
    }

    static Vector2D RANDOM(const double minX, const double minY, const double maxX, const double maxY) {
        double x = random(minX, maxX);
        double y = random(minY, maxY);

        Vector2D vector(x, y);
        return vector;
    }

//    static Vector2D add(const Vector2D &l, const Vector2D &r) {
//        return add(l, r.m_x, r.m_y);
//    }
//
//    static Vector2D add(const Vector2D &vector, const double value) {
//        return add(vector, value, value);
//    }
//
//    static Vector2D add(const Vector2D &vector, const double x, const double y) {
//        return Vector2D(vector.m_x + x, vector.m_y + y);
//    }
//
//    static Vector2D sub(const Vector2D &l, const Vector2D &r) {
//        return sub(l, r.m_x, r.m_y);
//    }
//
//    static Vector2D sub(const Vector2D &vector, const double value) {
//        return sub(vector, value, value);
//    }
//
//    static Vector2D sub(const Vector2D &vector, const double x, const double y) {
//        return Vector2D(vector.m_x - x, vector.m_y - y);
//    }
//
//    static Vector2D mul(const Vector2D &l, const Vector2D &r) {
//        return mul(l, r.m_x, r.m_y);
//    }
//
//    static Vector2D mul(const Vector2D &vector, const double value) {
//        return mul(vector, value, value);
//    }
//
//    static Vector2D mul(const Vector2D &vector, const double x, const double y) {
//        return Vector2D(vector.m_x * x, vector.m_y * y);
//    }
//
//    static Vector2D div(const Vector2D &l, const Vector2D &r) {
//        return div(l, r.m_x, r.m_y);
//    }
//
//    static Vector2D div(const Vector2D &vector, const double value) {
//        return div(vector, value, value);
//    }
//
//    static Vector2D div(const Vector2D &vector, const double x, const double y) {
//        return Vector2D(vector.m_x / x, vector.m_y / y);
//    }

private:
    double m_x;
    double m_y;

    static double random(double min, double max) {
        double f = (double)rand() / RAND_MAX;
        return min + f * (max - min);
    }

}; // end class

} // end namespace

#endif