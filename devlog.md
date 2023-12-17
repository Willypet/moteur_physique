# Phase 1

Aucune difficulté particulière n'est apparue pendant cette phase. Le rendu est basé sur Vulkan, avec une architecture développée précedemment par Benjamin pour un autre projet, ce qui a permis de se concentrer sur la partie physique à proprement parler.
L'intégrateur est cependant rudimentaire, et cause des ralentissements selon la machine utilisée.

# Phase 2

Les générateurs de force implémentés sont les suivants : gravité, friction, ressort ancré à un point fixe, ressort entre 2 particules, ainsi que des cables et des tiges. Pour la collision, un algorithme naïf comparant toutes les paires de particules est utilisé. L'unique subtilité dans cet algorithme est de s'assurer de ne pas traiter les contacts 2 fois (particule1 - particule 2 et particule2 - particule 1) mais ceci est de toute façon nécessaire pour une résolution physiquement correcte. Le système gère également les contacts au repos. La résolution de contact est basée sur les algorithmes présentés dans *Game Physics Engine Development* de Ian Millington.

# Phase 3

Cette phase a été plus ardue, notamment par le fait que William n'y a pas participé. Les corps rigides sont cependant fonctionnels, avec des forces appliquant correctement mouvement linéaire et rotationnel. Un bug visuel est demeuré qui amène les objet à ne pas tourner correctement autour de certains axes.

# Phase 4

Cette phase a été particulièrement complexe à cause d'une mauvaise planification sur les autres projets amenant à un temps réduit consacré à ce projet, et également car William n'y a pas non plus participé.
La Broad Phase est assurée par un système d'Octree, reconstruit à chaque frame pour partitionner correctement l'espace. Afin d'optimiser, il serait possible de construire un octree pour les objets statiques, qui ne serait pas reconstruit, et un octree pour les objets dynamiques, qui serait alors plus petit. Compte tenu du nombre d'objets considérés ici et des contraintes de temps, cela n'a pas été fait.
La détection précise de collisions fonctionnent, sauf pour les collisions boite-boite qui ne sont pas correctement détectées.
La résolution des collisions génère également des comportements étranges au niveau rotationnel.