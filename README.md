# moteur_physique

## Compilation
Afin de compiler le projet, il est nécessaire d'installer le SDK Vulkan, ainsi que CMake et minGW, et qu'ils soient correctement ajoutés au PATH de Windows. Dans le fichier `.env.cmake`, il faut renseigner le chemin d'installation de Vulkan et MinGW. Ensuite, éxécuter le script minGWBuild.bat (rentrer `.\minGWBuild.bat` dans un terminal à la racine du projet) va compiler le projet, compiler les shaders et lancer l'éxecutable.

## Utilisation
Le déplacement s'effectue avec les touches ZQSD (en AZERTY), et la rotation de la caméra avec les flèches directionelles. La touche Entrée permet de faire apparaître des cubes démontrant les capacités de l'intégrateur.