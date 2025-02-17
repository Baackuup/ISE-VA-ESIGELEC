% Fermer toutes les fenêtres, effacer les variables et effacer la console
close all;
clear all;
clc;

% Charger l'image cameraman.tif
cameraman = imread('cameraman.tif');

% Créer le filtre de mouvement horizontal avec une longueur de 8 et un angle de 0 degré
filtre_mouvement_horizontal = fspecial('motion', 8, 0);

% Appliquer le filtre de mouvement horizontal à l'image
image_filtree = imfilter(cameraman, filtre_mouvement_horizontal, 'conv', 'replicate');

% Afficher l'image originale et l'image filtrée
figure;
subplot(1, 2, 1);
imshow(cameraman);
title('Image originale (cameraman.tif)');
subplot(1, 2, 2);
imshow(image_filtree);
title('Image filtrée avec filtre de mouvement horizontal');

% Calculer la valeur moyenne des intensités des pixels de l'image filtrée
valeur_moyenne = mean(image_filtree(:));

% Afficher la valeur moyenne
disp(['La valeur moyenne des intensités des pixels de l''image filtrée est : ', num2str(valeur_moyenne)]);

