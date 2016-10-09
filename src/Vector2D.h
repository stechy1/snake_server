#ifndef SNAKE_VECTOR2D
#define SNAKE_VECTOR2D

#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>

using namespace std;

namespace SnakeServer {

	template<class T>
	class Vector2D {
	public:
		// Konstruktor se souřadnicemi X a Y
		Vector2D<T>(): x(T(0)), y(T(0)) {}
    	Vector2D<T>(const T& vx, const T& vy): x(vx), x(vy) {}
		~Vector2D<T>();

		// Přetížení operátorů - standartní operace
		Vector2D<T>& operator+=(const Vector2D<T>& v) { x += v.x; y += v.y; return *this; }
		Vector2D<T>& operator-=(const Vector2D<T>& v) { x -= v.x; y -= v.y; return *this; }
		Vector2D<T>& operator*=(const Vector2D<T>& v) { x *= v.x; y *= v.y; return *this; }
		Vector2D<T>& operator/=(const Vector2D<T>& v) { x /= v.x; y /= v.y; return *this; }

		// Přetížení operátorů - porovnávací operace
		friend bool operator==(const Vector2D<T>& L, const Vector2D<T>& R) { return std::tie(L.x, L.y) == std::tie(R.x, R.y); }
    	friend bool operator!=(const Vector2D<T>& L, const Vector2D<T>& R) { return !(L == R); }
	   	friend bool operator< (const Vector2D<T>& L, const Vector2D<T>& R) { return std::tie(L.x, L.y) < std::tie(R.x, R.y); }
	    friend bool operator>=(const Vector2D<T>& L, const Vector2D<T>& R) { return !(L < R); }
	    friend bool operator> (const Vector2D<T>& L, const Vector2D<T>& R) { return   R < L ; }
	    friend bool operator<=(const Vector2D<T>& L, const Vector2D<T>& R) { return !(R < L); }

	    // Negativní operátor - vrátí opačný vektor
	    Vector2D<T>& operator-() const { return Vector2D<T>(-x, -y); }

	    // Skalární operace
	    Vector2D<T>& operator*=(const T& s) { x *= s; y *= s; return *this; }
    	Vector2D<T>& operator/=(const T& s) { x /= s; y /= s; return *this; }

    	T mag() { return sqrt(this->magSq()); }
    	T magSq() { return (x * x + y * y); }
    	T dot(const T _x, const T _y) { return x * _x + y * _y; }
		T cross(const Vector2D<T>& other) { return x * other.y - y * other.x; }
		T dist(const Vector2D<T>& other) {
			Vector2D temp(other);
			temp -= this;

			return temp.mag();
		}

    	Vector2D<T>& normalize() { return this->mag() == 0 ? *this : this->div(this->mag()); }
    	Vector2D<T>& limit(const T max) {
    		T mSq = this->magSq();
    		if (mSq > max * max) {
    			this->div(sqrt(mSq));
    			this *= max;
    		}

    		return *this;
    	}

    	Vector2D<T>& setMag(const T n) { return *(this->normalize() *= n); }
    	Vector2D<T>& rotate(const T degrees) { return rotateRad(degrees * M_PI / 180); }
    	Vector2D<T>& rotateRad(const T radians) { 
    		T _cos = (T)cos(radians);
    		T _sin = (T)sin(radians);

    		T newX = x * _cos - y * _sin;
    		T newY = y * _sin + y * _cos;

    		x = newX;
    		y = newY;

    		return *this;
    	}
    	
    	Vector2D<T>& lerp(const Vector2D<T>& other, T amt) { return this->lerp(other.x, other.y, amt); }

    	Vector2D<T>& lerp(const T _x, const T _y, const T amt) {
    		x += (_x - x) * amt;
    		y += (_y - y) * amt;

    		return *this;
    	}

    	Vector2D<T>& constrain(const Vector2D<T>& min, const Vector2D<T>& max) { return constrain(min.x, min.y, max.x, max.y); }

    	Vector2D<T>& constrain(const T minX, const T minY, const T maxX, const T maxY) {
    		if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
    			return *this;
    		}

    		if (x < minX)
    			x = maxX;

    		if (x > maxX)
    			x = minX;

    		if (y < minY)
    			y = maxY;

    		if (y > maxY)
    			y = minY;

    		return *this;
    	}

	private:
		T x;
		T y;

	}; // end class

	template<class T> Vector2D<T> operator+(const Vector2D<T>& L, const Vector2D<T>& R) { return Vector2D<T>(L) += R; }
	template<class T> Vector2D<T> operator-(const Vector2D<T>& L, const Vector2D<T>& R) { return Vector2D<T>(L) -= R; }
	template<class T> Vector2D<T> operator*(const Vector2D<T>& L, const Vector2D<T>& R) { return Vector2D<T>(L) *= R; }
	template<class T> Vector2D<T> operator/(const Vector2D<T>& L, const Vector2D<T>& R) { return Vector2D<T>(L) /= R; }

	template<class T> Vector2D<T> operator*(const T& s, const Vector2D<T>& v) { return Vector2D<T>(v) *= s; }
	template<class T> Vector2D<T> operator*(const Vector2D<T>& v, const T& s) { return Vector2D<T>(v) *= s; }
	template<class T> Vector2D<T> operator/(const T& s, const Vector2D<T>& v) { return Vector2D<T>(v) /= s; }
	template<class T> Vector2D<T> operator/(const Vector2D<T>& v, const T& s) { return Vector2D<T>(v) /= s; }

} // end namespace

#endif