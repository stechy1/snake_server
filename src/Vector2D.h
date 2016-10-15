#ifndef SNAKE_VECTOR2D
#define SNAKE_VECTOR2D

#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>
#include <random>
#include <memory>

// Kvůli překladu ve woknech
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace SnakeServer {
    
    class Vector2D {
    public:
        // Konstruktor se souřadnicemi X a Y
        Vector2D() : m_x(0), m_y(0) {}

        Vector2D(const double t_x, const double t_y) : m_x(t_x), m_y(t_y) {}

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

//        Vector2D operator+(const Vector2D &L, const Vector2D &R) { return Vector2D(L) += R; }
//
//        Vector2D operator-(const Vector2D &L, const Vector2D &R) { return Vector2D(L) -= R; }
//
//        Vector2D operator*(const Vector2D &L, const Vector2D &R) { return Vector2D(L) *= R; }
//
//        Vector2D operator/(const Vector2D &L, const Vector2D &R) { return Vector2D(L) /= R; }
//
//        Vector2D operator*(const double &s, const Vector2D &v) { return Vector2D(v) *= s; }
//
//        Vector2D operator*(const Vector2D &v, const double &s) { return Vector2D(v) *= s; }
//
//        Vector2D operator/(const double &s, const Vector2D &v) { return Vector2D(v) /= s; }
//
//        Vector2D operator/(const Vector2D &v, const double &s) { return Vector2D(v) /= s; }

        // Přetížení operátorů - porovnávací operace
        friend bool operator==(const Vector2D &L, const Vector2D &R) {
            return std::tie(L.m_x, L.m_y) == std::tie(R.m_x, R.m_y);
        }

        friend bool operator!=(const Vector2D &L, const Vector2D &R) { return !(L == R); }

        friend bool operator<(const Vector2D &L, const Vector2D &R) {
            return std::tie(L.m_x, L.m_y) < std::tie(R.m_x, R.m_y);
        }

        friend bool operator>=(const Vector2D &L, const Vector2D &R) { return !(L < R); }

        friend bool operator>(const Vector2D &L, const Vector2D &R) { return R < L; }

        friend bool operator<=(const Vector2D &L, const Vector2D &R) { return !(R < L); }

        // Negativní operátor - vrátí opačný vektor
        //Vector2D &operator-() const { return Vector2D(-x, -y); }

        // Skalární operace
        Vector2D &operator*=(const double &s) {
            m_x *= s;
            m_y *= s;
            return *this;
        }

        Vector2D &operator/=(const double &s) {
            m_x /= s;
            m_y /= s;
            return *this;
        }

        double mag() { return sqrt(this->magSq()); }

        double magSq() { return (m_x * m_x + m_y * m_y); }

        double dot(const double _x, const double _y) { return m_x * _x + m_y * _y; }

        double cross(const Vector2D &other) { return m_x * other.m_y - m_y * other.m_x; }

        double dist(const Vector2D &other) {
            Vector2D temp(other);
            temp -= *this;

            return temp.mag();
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

        static std::unique_ptr<Vector2D> ZERO() {
            return std::make_unique<Vector2D>(Vector2D(0, 0));
        }

        static std::unique_ptr<Vector2D> ONES() {
            return std::make_unique<Vector2D>(Vector2D(0, 0));
        }

        static std::unique_ptr<Vector2D> LEFT() {
            return std::make_unique<Vector2D>(Vector2D(-1, 0));
        }

        static std::unique_ptr<Vector2D> RIGHT() {
            return std::make_unique<Vector2D>(Vector2D(1, 0));
        }

        static std::unique_ptr<Vector2D> UP() {
            return std::make_unique<Vector2D>(Vector2D(0, -1));
        }

        static std::unique_ptr<Vector2D> DOWN() {
            return std::make_unique<Vector2D>(Vector2D(0, 1));
        }

        static std::unique_ptr<Vector2D> RANDOM() {
            static std::default_random_engine e{};
            static std::uniform_int_distribution<int> randX{0, 3};

            int res = randX(e);

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

        static std::unique_ptr<Vector2D> RANDOM(const double min, const double max) {
            return RANDOM(min, min, max, max);
        }

        static std::unique_ptr<Vector2D> RANDOM(const double minX, const double minY, const double maxX, const double maxY) {
            double x = random(minX, maxX);
            double y = random(minY, maxY);


//            static std::default_random_engine e{};
//            static std::uniform_int_distribution<double> randX{minX, maxX};
//            static std::uniform_int_distribution<double> randY{minY, maxY};
            //7 return d(e);
            return std::make_unique<Vector2D>(Vector2D(x, y));
        }

    private:
        double m_x;
        double m_y;

        static double random(double min, double max) {
            static double doubleMax = std::numeric_limits<double>::max();
            double val = (double)rand() / doubleMax;

            return min + val * (max - min);
        }

    }; // end class

} // end namespace

#endif