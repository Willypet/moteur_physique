#include "Vecteur3D.hpp"
#include <cmath>
#include "Vecteur3D.hpp"

namespace Physics{
	Vecteur3D::Vecteur3D(const float x, const float y, const float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vecteur3D::Vecteur3D() : x(0), y(0), z(0) {}

	Vecteur3D::Vecteur3D(const Vecteur3D &other){
		x = other.x;
		y = other.y;
		z = other.z;
	}

	Vecteur3D& Vecteur3D::operator=(const Vecteur3D& other){
		if (this != &other) { 
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	Vecteur3D& Vecteur3D::operator+=(const Vecteur3D& other){
		return *this = Vecteur3D(x + other.x, y + other.y, z + other.z);
	}

	Vecteur3D Vecteur3D::operator+(const Vecteur3D& other) {
		return Vecteur3D(x + other.x, y + other.y, z + other.z);
	}

	Vecteur3D& Vecteur3D::operator-=(const Vecteur3D& other){
		return *this = Vecteur3D(x - other.x, y - other.y, z - other.z);
	}

	Vecteur3D Vecteur3D::operator-(const Vecteur3D& other) {
		return Vecteur3D(x - other.x, y - other.y, z - other.z);
	}

	Vecteur3D& Vecteur3D::operator*=(const float other){
		return *this = Vecteur3D(x * other, y * other, z * other);
	}

	Vecteur3D& Vecteur3D::operator/=(const float other){
		if (abs(other) < 10e-6){
			throw "DivisionByZero";
		}
		else{
			return *this = Vecteur3D(x / other, y / other, z / other);

		}
	}

	Vecteur3D& Vecteur3D::operator^(const Vecteur3D& other){
		return *this = Vecteur3D(y * other.z - z * other.y, 
								 z * other.x - x * other.z, 
								 x * other.y - y * other.x);
	}

	float Vecteur3D::magnitudeSquared() {
		return x * x + y * y + z * z;
	}

	float Vecteur3D::magnitude(){
		return std::sqrt(x * x + y * y + z * z);
	}

	void Vecteur3D::normalize(){
		*this = this->normalized();
	}

	Vecteur3D Vecteur3D::normalized(){
		float magnitude = this->magnitude();
		if(magnitude < 10e-6){
			throw "NullNormalization";
			//return *(new Vecteur3D());
		}
		else{
			Vecteur3D res (*this);
			res = res / magnitude;
			return res;
		}
	}

	Vecteur3D Vecteur3D::cross(const Vecteur3D& other){
		return *this^other;
	}

	float Vecteur3D::dot(const Vecteur3D& lhs, const Vecteur3D& rhs){
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	Vecteur3D Vecteur3D::vecteurNull()
	{
		return Vecteur3D(0,0,0);
	}



	Vecteur3D operator*(const float f, Vecteur3D v){
		return Vecteur3D(v.x * f, v.y * f, v.z * f);
	}

	Vecteur3D operator*(Vecteur3D v, const float f) {
		return Vecteur3D(v.x * f, v.y * f, v.z * f);
	}

	Vecteur3D operator/(Vecteur3D v, const float f) {
		if (f < 10e-6) {
			throw "NullNormalization";
		}
		return Vecteur3D(v.x / f, v.y / f, v.z / f);
	}
}