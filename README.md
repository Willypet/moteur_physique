# moteur_physique
Ce projet est réalisé dans le cadre du cours Mathématiques et physique pour le jeu vidéo de l'UQAC, enseigné par M. David Gagnon. L'objectif est de développer un moteur physique.

## Compilation
Afin de compiler le projet, il est nécessaire d'installer le SDK Vulkan, ##

### Visual Studio
Pour compiler avec Visual Studio, il suffit de lancer le projet depuis la solution.

### CMake
Pour compiler le projet avec CMake, que CMake et minGW, doivent être correctement ajoutés au PATH de Windows. Dans le fichier `.env.cmake`, il faut renseigner le chemin d'installation de Vulkan et MinGW. Ensuite, éxécuter le script minGWBuild.bat (rentrer `.\minGWBuild.bat` dans un terminal à la racine du projet) va compiler le projet, compiler les shaders et lancer l'éxecutable.


## Utilisation
Le déplacement s'effectue avec les touches ZQSD (en AZERTY), et la rotation de la caméra avec les flèches directionelles. 
La touche Entrée permet de faire apparaître des cubes démontrant les capacités de l'intégrateur.
La touche Escape permet de quitter l'application.

## Moteur visuel
Le moteur visuel a été fait en suivant la série de tutoriels youtube de [Brendan Galea](https://www.youtube.com/playlist?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR) (jusqu'à la vidéo 21 : Diffuse shading). QUelque morceaux de codes ont été modifiés afin de fonctionner avec le moteur physique. 