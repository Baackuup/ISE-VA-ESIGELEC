% Fermer toutes les fenêtres, effacer les variables et effacer la console
close all;
clear all;
clc;

% Charger l'image moon.tif
moon = imread('moon.tif');

% Valeur de sigma pour le filtre gaussien
sigma = 1.5;

% Calculer la taille du masque du filtre
W = ceil(6 * sigma);

% Créer le filtre gaussien
filt = fspecial('gaussian', [W W], sigma);

% Appliquer le filtre gaussien à l'image moon.tif avec sigma=20
sigma_moon = 20;
W_moon = ceil(6 * sigma_moon);
filt_moon = fspecial('gaussian', [W_moon W_moon], sigma_moon);
imgFiltMoon = imfilter(moon, filt_moon);

figure;

% Afficher l'image originale moon.tif
subplot(2, 2, 1);
imshow(moon);
title('Image originale (moon.tif)');

% Afficher le filtre gaussien
subplot(2, 2, 2);
imagesc(filt_moon);
colormap(gray);
axis equal;
axis off;
title('Filtre gaussien (sigma=20)');


% Afficher l'image filtrée moon.tif
subplot(2, 2, 3);
imshow(imgFiltMoon);
title('Image filtrée (moon.tif)');

subplot(2, 2, 4); surf(filt_moon);
title('filtre gaussien');
