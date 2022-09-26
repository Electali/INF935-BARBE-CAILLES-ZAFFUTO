# INF935-BARBE-CAILLES-ZAFFUTO

Notre projet contient sur la branche "main" plusieurs fichiers de type "Compile.bat".
- CompileMain.bat genere un executable Main.exe qui contient une serie de tests affichant les resultats de divers calculs permettant de montrer les differentes operations que nous avons implementees autour des vecteurs.
- CompileApple.bat genere un executable Apple.exe qui contient un petit jeu permettant de choisir une hauteur a partir de laquelle on souhaite faire tomber une pomme sur Newton. A la fin de la simulation, le jeu nous dit le temps mis a atteindre ce dernier. La vitesse est egalement visible.

Pour executer un fichier .bat, il suffit de faire la commande "./CompileExemple.bat" dans un terminal, de meme pour le fichier "./Main.exe".
NOTE : L'execution des fichiers .bat demande egalement de posseder g++ en 64 bits afin de pouvoir compiler le code.
Attention, pour le fichier Apple.exe, il faut ajouter la hauteur souhaitee apres la commande comme ceci : "./Apple.exe 300". Ici, la pomme sera lachee de 300m de hauteur.

Par ailleurs, la branche "Graphics" contient quelques essais d'affichage de formes en OpenGL, pas termines pour l'instant.