% Définition de la fonction flouImage
function [imgFilt, filt] = flouImage(img, sigma)
    % Calculer la taille du masque du filtre
    W = ceil(6 * sigma);
    
    % Créer le filtre gaussien
    filt = fspecial('gaussian', [W W], sigma);
    
    % Appliquer le filtre gaussien à l'image
    imgFilt = imfilter(img, filt);
end

% Charger l'image
lenna = imread('X:\Semestre_8\Vision par ordinateur\TP3\lenna.bmp');

% Valeur de sigma
sigma = 1.5;

% Appliquer le flou gaussien
[imgFilt, ~] = flouImage(lenna, sigma);

% Afficher l'image originale et l'image filtrée
figure;
subplot(1, 2, 1);
imshow(lenna);
title('Image originale');
subplot(1, 2, 2);
imshow(imgFilt);
title('Image filtrée avec flou gaussien');
