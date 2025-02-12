# Projet ISE-VA-ESIGELEC

Bienvenue dans le dépôt du département **ISE-VA-ESIGELEC** ! Ce projet regroupe plusieurs modules vus en cours : fusion de données, l'intelligence artificielle, la planification et le suivi de trajectoires, méthodes et outils pour la qualité logicielle.

## Table des Matières

- [Description du Projet](#description-du-projet)
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Structure du Projet](#structure-du-projet)
- [Utilisation](#utilisation)
- [Contributeurs](#contributeurs)
- [Licence](#licence)

## Description du Projet

Ce projet est composé de plusieurs sous-projets et modules :

- **Fusion de Données pour la Localisation** : Mise en place de méthodes avancées de fusion de données pour améliorer la précision et la fiabilité de la localisation du véhicule.
- **Intelligence Artificielle pour le Véhicule Autonome** : Algorithmes de décision basés sur des réseaux neuronaux et l'apprentissage machine.
- **Méthodes et Outils pour la Qualité Logicielle** : Tests unitaires, outils de vérification, et bonnes pratiques pour assurer la robustesse du logiciel.
- **Planification & Suivi de Trajectoire** : Implémentation d'algorithmes pour planifier et suivre des trajectoires optimales.

## Prérequis

Avant de commencer, assurez-vous d'avoir les outils et environnements suivants installés :

- **Python** (>= 3.8)
- **ROS1**
- **Bibliothèques Python** :
  - `numpy`
  - `pandas`
  - `matplotlib`
  - `scikit-learn`
- **CMake** et un compilateur compatible (GCC ou Clang)
- Jupyter Notebook (si vous souhaitez exécuter les notebooks inclus)

## Installation

1. Clonez ce dépôt :
   ```bash
   git clone https://github.com/Baackuup/ISE-VA-ESIGELEC.git
   cd ISE-VA-ESIGELEC
   ```
2. Installez les dépendances Python :
   ```bash
   pip install -r requirements.txt
   ```
3. Configurez les environnements ROS et CMake selon les modules que vous souhaitez utiliser.

## Structure du Projet

Le dépôt est organisé comme suit :

```plaintext
ISE-VA-ESIGELEC/
|— Fusion de Données pour la Localisation/
|— Intelligence Artificielle pour le Véhicule Autonome/
|— Méthodes et Outils pour la Qualité Logicielle/
|— Planification & Suivi de Trajectoire/
    |— catkin_ws/
|— README.md
|— requirements.txt
```

- Chaque dossier contient des fichiers liés à un module particulier.
- `requirements.txt` inclut les dépendances Python nécessaires.

## Utilisation

### Exemple de Lancement d'un Module

1. **Fusion de Données pour la Localisation** :
   - Naviguez dans le dossier correspondant :
     ```bash
     cd "Fusion de Données pour la Localisation"
     ```
   - Lancez un notebook Jupyter :
     ```bash
     jupyter notebook
     ```
   - Exécutez les cellules pour voir les résultats.

2. **Planification & Suivi de Trajectoire** :
   - Configurez votre environnement ROS2 :
     ```bash
     source /opt/ros/foxy/setup.bash
     ```
   - Lancez les noeuds ROS :
     ```bash
     ros launch trajectoire_planner planner_launch.py
     ```

## Contributeurs

- [Paul BLIGNY](https://github.com/Baackuup)

## Licence

Ce projet est sous licence [MIT](LICENSE). Vous êtes libre de l'utiliser, le modifier et le distribuer, sous réserve de conserver les droits d'auteur et la licence.

---

Contact : blignypaul@gmail.com

