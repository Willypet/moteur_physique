#pragma once

#ifndef VECTEUR3D_H
#define VECTEUR3D_H

namespace Physics{
	class Vecteur3D{
		public:
			float x;
			float y;
			float z;

			Vecteur3D(const float x, const float y, const float z);
			Vecteur3D();
			Vecteur3D(const Vecteur3D &other);

			Vecteur3D& operator=(const Vecteur3D& other);
			Vecteur3D& operator+=(const Vecteur3D& other);
			Vecteur3D operator+(const Vecteur3D& other) const;
			Vecteur3D& operator-=(const Vecteur3D& other);
			Vecteur3D operator-(const Vecteur3D& other) const;
			Vecteur3D& operator*=(const float other);
			Vecteur3D& operator/=(const float other);
			Vecteur3D& operator^=(const Vecteur3D& other);
			Vecteur3D operator^(const Vecteur3D& other) const;

			float magnitudeSquared();
			float magnitude();
			void normalize();
			Vecteur3D normalized();

			Vecteur3D cross(const Vecteur3D& other) const;
			static float dot(const Vecteur3D& lhs, const Vecteur3D& rhs);

			static Vecteur3D vecteurNull();
	};

	Vecteur3D operator*(const float f, const Vecteur3D v);
	Vecteur3D operator*(const Vecteur3D v, const float f);
	Vecteur3D operator/(const Vecteur3D v, const float f);
	Vecteur3D operator-(const Vecteur3D v);
}
#endif