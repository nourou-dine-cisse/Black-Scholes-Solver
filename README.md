# Black-Scholes PDE Solver: Finite Difference Schemes in C++ & SDL Visualization

> **Cadre académique** : ENSIIE — Projet Mathématiques Financières & Programmation Orientée Objet C++  
> **Auteur** : Mohamed Nourou Dine CISSE  
> **Domaine** : `Quantitative Finance, Numerical Analysis & Scientific Computing`  
> **Stack Technique** : `C++ (Modern C++17)` `Schémas aux Différences Finies` `Crank-Nicolson` `Schéma Implicite` `Algorithme de Thomas` `SDL 2.0` `Doxygen`

---

## 📌 Présentation Réelle du Projet (Honest Overview)

Ce projet implémente un solveur numérique en **C++** résolvant l'Équation aux Dérivées Partielles (EDP) de **Black-Scholes** pour le pricing d'options vanilles européennes (*Call* et *Put*). 

Pour s'affranchir de la dépendance exclusive à la formule analytique fermée et préparer le pricing d'options plus complexes (américaines ou à barrières), le projet discrétise l'EDP temporelle et spatiale à l'aide de trois schémas aux différences finies :
1. **Schéma Explicite** : Simple mais soumis à la condition de stabilité de Courant-Friedrichs-Lewy (CFL).
2. **Schéma Implicite** : Inconditionnellement stable, nécessitant la résolution d'un système linéaire tridiagonal par l'algorithme de Thomas à chaque pas de temps.
3. **Schéma de Crank-Nicolson** : Moyenne pondérée implicite-explicite offrant une précision d'ordre 2 en temps et en espace ($\mathcal{O}(\Delta t^2 + \Delta S^2)$).

Une interface graphique développée avec la bibliothèque **SDL 2.0** trace en temps réel l'évolution temporelle de la courbe de prix de l'option et les erreurs résiduelles par rapport au prix de référence analytique.

---

## 🏗️ Structure du Répertoire

```text
06_Black_Scholes_PDE_Solver/
├── README.md                      # Présentation et documentation
├── reports/
│   ├── Rapport_Black_Scholes.pdf  # Rapport théorique et d'analyse numérique complet
│   ├── Sujet_Projet.pdf           # Énoncé et cahier des charges académique
│   └── rapport_source.tex         # Code source LaTeX du rapport
├── visuals/
│   ├── UML.png                    # Diagramme de classes orienté objet
│   ├── call.png                   # Trajectoire numérique d'un Call européen
│   ├── Put.png                    # Trajectoire numérique d'un Put européen
│   ├── erreur call.png            # Profil d'erreur absolue Call vs Black-Scholes analytique
│   └── erreur Put.png             # Profil d'erreur absolue Put vs Black-Scholes analytique
└── src/
    ├── main.cpp                   # Point d'entrée de simulation et benchmarks
    ├── Option.hpp / Option.cpp    # Classes de base pour options vanilles (Call, Put, Payoff)
    ├── EDP.hpp                    # Modélisation générique de l'EDP de diffusion
    ├── DifferenceFinie.hpp        # Classe générique des schémas aux différences finies
    ├── Implicite.cpp              # Implémentation du schéma implicite (Thomas)
    ├── CrankNicholson.cpp         # Implémentation du schéma Crank-Nicolson
    ├── Sdl.hpp / Sdl.cpp          # Rendu graphique dynamique des courbes avec SDL 2
    └── Doxyfile                   # Configuration de génération de documentation Doxygen
```

---

## 📐 Formulation Mathématique

L'EDP de Black-Scholes vérifiée par le prix d'un produit dérivé $V(S, t)$ sous taux sans risque $r$ et volatilité $\sigma$ s'écrit :
$$\frac{\partial V}{\partial t} + rS \frac{\partial V}{\partial S} + \frac{1}{2}\sigma^2 S^2 \frac{\partial^2 V}{\partial S^2} - rV = 0$$

Avec les conditions terminales (payoff à maturité $T$) :
- Call : $V(S, T) = \max(S - K, 0)$
- Put : $V(S, T) = \max(K - S, 0)$

### Condition de Stabilité & Convergence :
Le schéma de Crank-Nicolson garantit une stabilité inconditionnelle tout en conservant une vitesse de convergence quadratique observée numériquement sur nos maillages de simulation (100 à 1000 pas).

---

## 🚀 Compilation & Exécution

### Prérequis (macOS / Linux)
- Compilateur C++ supportant C++17 (`g++` ou `clang++`)
- Bibliothèque SDL 2 :
  - Sur macOS : `brew install sdl2`
  - Sur Ubuntu/Debian : `sudo apt-get install libsdl2-dev`

### Compilation
```bash
cd src
g++ -std=c++17 -O3 main.cpp Option.cpp Implicite.cpp CrankNicholson.cpp Sdl.cpp -I. $(sdl2-config --cflags --libs) -o black_scholes_solver
```

### Exécution
```bash
./black_scholes_solver
```

---

## 📄 Preuves & Livrables Inclus
- 📄 **Rapport d'Analyse Numérique** : [`reports/Rapport_Black_Scholes.pdf`](reports/Rapport_Black_Scholes.pdf)
- 📊 **Visualisations d'Erreur & Courbes** : Dossier [`visuals/`](visuals/)

---

## 📬 Profil de l'Auteur
- **Mohamed Nourou Dine CISSE**
- **ENSIIE** & **Université Paris-Saclay** — Double diplôme, Master 2 Intelligence Artificielle (M2IA)
- Échange académique : **McMaster University** (Canada)
- **GitHub** : [@nourou-dine-cisse](https://github.com/nourou-dine-cisse)
