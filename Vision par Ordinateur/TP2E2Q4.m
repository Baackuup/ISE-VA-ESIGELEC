% Fermer toutes les fenêtres, effacer les variables et effacer la console
close all;
clear all;
clc;

% Charger l'image bruitée
image_bruitee = imread('X:\Semestre_8\Vision par ordinateur\TP3\Image_embarquée.bmp');

% Appliquer un filtre médian pour lisser l'image et atténuer le bruit
taille_fenetre = 3; % Taille de la fenêtre du filtre médian
image_lissee = medfilt2(image_bruitee, [taille_fenetre, taille_fenetre]);

% Appliquer un opérateur de détection de contours (gradient de Sobel) sur l'image lissée
[dx, dy] = gradient(double(image_lissee));
magnitude_gradient = sqrt(dx.^2 + dy.^2);

% Afficher l'image bruitée, l'image lissée et l'image avec les contours détectés
figure;
subplot(1, 3, 1);
imshow(image_bruitee);
title('Image bruitée');

subplot(1, 3, 2);
imshow(image_lissee);
title('Image lissée (filtre médian)');

subplot(1, 3, 3);
imshow(magnitude_gradient, []);
title('Contours détectés (gradient de Sobel)');
