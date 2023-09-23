#pragma once

#ifndef PARTICULE_HPP
#define PARTICULE_HPP

#include "Vecteur3D.hpp"
#include <string>

namespace Physics{
    class Particule {
        private:
            // Attributs
            double masse;
            Vecteur3D position;
            Vecteur3D vitesse;
            Vecteur3D acceleration;
            std::string gameObjectFilePath;

        public:
            // Constructeur
            Particule(const std::string& gameObjectFilePath);
            Particule(const Vecteur3D& position, const std::string& gameObjectFilePath);
            Particule(double masse, const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, const std::string& getGameObjectFilePath);

            // Fonction pour update les attributs de la particule
            void update(double time);

            // Getters
            double getMasse() const;
            Vecteur3D getPosition() const;
            Vecteur3D getVitesse() const;
            Vecteur3D getAcceleration() const;
            std::string getGameObjectFilePath() const;
    };
}

#endif // PARTICULE_HPP