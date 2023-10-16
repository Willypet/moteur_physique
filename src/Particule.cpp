#include "Particule.hpp"

namespace Physics{
    Particule::Particule(const std::string& gameObjectFilePath) 
        : masse(1), 
        position(Vecteur3D::vecteurNull()), 
        vitesse(Vecteur3D::vecteurNull()), 
        acceleration(Vecteur3D::vecteurNull()), 
        gameObjectFilePath(gameObjectFilePath),
        idGameObject(0) {}
    Particule::Particule(const Vecteur3D& position, const std::string& gameObjectFilePath)
        : masse(1), 
        position(position), 
        vitesse(Vecteur3D::vecteurNull()), 
        acceleration(Vecteur3D::vecteurNull()), 
        gameObjectFilePath(gameObjectFilePath),
        idGameObject(0) {}
    Particule::Particule(double masse, const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, const std::string& gameObjectFilePath)
        : masse(masse), 
        position(position), 
        vitesse(vitesse),
        acceleration(acceleration), 
        gameObjectFilePath(gameObjectFilePath),
        idGameObject(0){}
    // TODO : Setter pour update
    /*void Particule::update(double deltaTime) {
        vitesse += acceleration * deltaTime;
        position += vitesse * deltaTime;
    }*/

    void Particule::setPosition(const Vecteur3D& new_position) {
        position = new_position;
    }

    void Particule::setVitesse(const Vecteur3D& new_vitesse) {
        vitesse = new_vitesse;
    }

    void Particule::setAcceleration(const Vecteur3D& new_acceleration) {
        acceleration = new_acceleration;
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
    std::string Physics::Particule::getGameObjectFilePath() const
    {
        return gameObjectFilePath;
    }
}

