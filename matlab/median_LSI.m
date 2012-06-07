function img_new = median_LSI(img, N)
if nargin == 1
    N = 3;
end

img_new(:,:,1) = medfilt2(img(:,:,1),N);
img_new(:,:,2) = medfilt2(img(:,:,2),N);
img_new(:,:,3) = medfilt2(img(:,:,3),N);
