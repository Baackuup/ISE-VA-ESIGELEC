% Charger l'image couleur 'lenna.bmp'
lenna = imread('lenna.bmp');

% Convertir l'image en double pour le traitement
lenna_double = im2double(lenna);

% Séparer les canaux de couleur
red_channel = lenna_double(:,:,1);
green_channel = lenna_double(:,:,2);
blue_channel = lenna_double(:,:,3);

% Amélioration de chaque canal par égalisation d'histogramme
enhanced_red_channel = histeq(red_channel);
enhanced_green_channel = histeq(green_channel);
enhanced_blue_channel = histeq(blue_channel);

% Recombiner les canaux améliorés en une seule image
enhanced_lenna = cat(3, enhanced_red_channel, enhanced_green_channel, enhanced_blue_channel);

% Création d'une seule figure pour afficher tout
figure;

% Affichage de l'image originale et ses histogrammes
subplot(2, 4, 1);
imshow(lenna);
title('Image originale');
subplot(2, 4, 5);
imhist(red_channel);
title('Histogramme du canal rouge');
subplot(2, 4, 6);
imhist(green_channel);
title('Histogramme du canal vert');
subplot(2, 4, 7);
imhist(blue_channel);
title('Histogramme du canal bleu');

% Affichage de l'image améliorée et ses histogrammes
subplot(2, 4, 2);
imshow(enhanced_lenna);
title('Image améliorée');
subplot(2, 4, 3);
imhist(enhanced_red_channel);
title('Histogramme amélioré du canal rouge');
subplot(2, 4, 4);
imhist(enhanced_green_channel);
title('Histogramme amélioré du canal vert');
subplot(2, 4, 8);
imhist(enhanced_blue_channel);
title('Histogramme amélioré du canal bleu');
