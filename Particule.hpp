// Particule.hpp

#ifndef PARTICULE_HPP
#define PARTICULE_HPP

#include "Vecteur3D.hpp"

class Particule {
private:
    // Attributs
    double masse;
    Vecteur3D position;
    Vecteur3D vitesse;
    Vecteur3D acceleration;

public:
    // Constructeur
    Particule(double masse, const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration);

    // Fonction pour update les attributs de la particule
    void update(double time);

    // Getters
    double getMasse() const;
    Vecteur3D getPosition() const;
    Vecteur3D getVitesse() const;
    Vecteur3D getAcceleration() const;
};

#endif // PARTICULE_HPP