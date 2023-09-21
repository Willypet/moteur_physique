// Particule.cpp

#include "Particule.hpp"

Particule::Particule(double masse, const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration)
    : masse(masse), position(position), vitesse(vitesse), acceleration(acceleration) {}

void Particule::update(double time) {
    vitesse += acceleration * time;
    position += vitesse * time;
}

double Particule::getMasse() const {
    return masse;
}

Vecteur3D Particule::getPosition() const {
    return position;
}

Vecteur3D Particule::getVitesse() const {
    return vitesse;
}

Vecteur3D Particule::getAcceleration() const {
    return acceleration;
}
