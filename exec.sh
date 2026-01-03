#!/bin/bash

# 1. Nettoyage (Optionnel : supprime l'ancien exécutable)
rm -f projet

# 2. Compilation (Selon les consignes strictes du PDF)
echo "Compilation en cours..."
g++ -std=c++11 -g -Wall -Wextra -o projet *.cpp $(pkg-config --cflags --libs sdl2)

# 3. Vérification et Exécution
# Si la compilation a réussi ($? == 0), on lance le programme
if [ $? -eq 0 ]; then
    echo "Compilation réussie ! Lancement du projet..."
    echo "--------------------------------------------"
    ./projet
else
    echo "ERREUR : La compilation a échoué."
fi
