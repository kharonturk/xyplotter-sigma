function img_new = median_LSI(img, N)
% img_new = median_LSI(img, N)
if nargin == 1
    N = 3;
end

img_new = zeros(size(img));

for i = 1:size(img,3)
    img_new(:,:,i) = medfilt2(img(:,:,i),N);
end