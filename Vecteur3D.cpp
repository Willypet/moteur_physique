#include <cmath>
namespace Physics{
	class Vecteur3D{
		public:
			float x;
			float y;
			float z;

			Vecteur3D(const float x, const float y, const float z){
				this->x = x;
				this->y = y;
				this->z = z;
			}

			Vecteur3D(){
				Vecteur3D(0, 0, 0);
			}

			Vecteur3D(const Vecteur3D &other){
				x = other.x;
				y = other.y;
				z = other.z;
			}

			Vecteur3D& operator=(const Vecteur3D& other){
				x = other.x;
				y = other.y;
				z = other.z;
				return *this;
			}

			Vecteur3D operator+(const Vecteur3D& other){
				Vecteur3D res;
				res.x = x + other.x;
				res.y = y + other.y;
				res.z = z + other.z;
				return res;
			}

			Vecteur3D operator-(const Vecteur3D& other){
				Vecteur3D res;
				res.x = x - other.x;
				res.y = y - other.y;
				res.z = z - other.z;
				return res;
			}

			Vecteur3D operator*(const float other){
				Vecteur3D res;
				res.x = x * other;
				res.y = y * other;
				res.z = z * other;
				return res;
			}

			Vecteur3D operator/(const float other){
				if (abs(other) < 10e-6){
					throw "DivisionByZero";
				}
				else{
					Vecteur3D res;
					res.x = x / other;
					res.y = y / other;
					res.z = z / other;
					return res;
				}
			}

			Vecteur3D operator^(const Vecteur3D& other){
				Vecteur3D res;
				res.x = y * other.z - z * other.y;
				res.y = z * other.x - x * other.z;
				res.z = x * other.y - y * other.x;
				return res;
			}

			float magnitude(){
				return std::sqrt(x * x + y * y + z * z);
			}

			void normalize(){
				*this = this->normalized();
			}

			Vecteur3D normalized(){
				float magnitude = this->magnitude();
				if(magnitude < 10e-6){
					throw "NullNormalization";
				}
				else{
					Vecteur3D res (*this);
					res = res / magnitude;
					return res;
				}
			}

			Vecteur3D cross(const Vecteur3D& other){
				return *this^other;
			}

			static float dot(const Vecteur3D& lhs, const Vecteur3D& rhs){
				return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
			}
	};

	Vecteur3D operator*(const float lhs, Vecteur3D rhs){
		Vecteur3D res (rhs);
		res.x *= lhs;
		res.y *= lhs;
		res.z *= lhs;
		return res;
	}
}