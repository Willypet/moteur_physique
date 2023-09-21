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
			Vecteur3D operator+(const Vecteur3D& other);
			Vecteur3D operator-(const Vecteur3D& other);
			Vecteur3D operator*(const float other);
			Vecteur3D operator/(const float other);
			Vecteur3D operator^(const Vecteur3D& other);

			float magnitude();
			void normalize();
			Vecteur3D normalized();

			Vecteur3D cross(const Vecteur3D& other);
			static float dot(const Vecteur3D& lhs, const Vecteur3D& rhs);
	};

	Vecteur3D operator*(const float lhs, Vecteur3D rhs);
}
#endif