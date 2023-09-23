#include "Particule.hpp"

namespace Physics{
    Particule::Particule(const std::string& gameObjectFilePath) 
        : masse(1), position(Vecteur3D::vecteurNull()), vitesse(Vecteur3D::vecteurNull()), acceleration(Vecteur3D::vecteurNull()), gameObjectFilePath(gameObjectFilePath) {}
    Particule::Particule(const Vecteur3D& position, const std::string& gameObjectFilePath)
        : masse(1), position(position), vitesse(Vecteur3D::vecteurNull()), acceleration(Vecteur3D::vecteurNull()), gameObjectFilePath(gameObjectFilePath) {}
    Particule::Particule(double masse, const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, const std::string& gameObjectFilePath)
        : masse(masse), position(position), vitesse(vitesse), acceleration(acceleration), gameObjectFilePath(gameObjectFilePath){}
    
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
    std::string Physics::Particule::getGameObjectFilePath() const
    {
        return gameObjectFilePath;
    }
}

