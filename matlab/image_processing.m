function img_edge = image_processing(img, debug)
% img_edge = image_processing(img, debug)
if nargin == 1
    debug = '';
end

img_1 = filter_LSI(img, 'gaussian', 5, 2);
img_2 = filter_LSI(img_1, 'median', 7);
img_3 = filter_LSI(img_2, 'unsharp',1);

% img_4 = rgb2hsv(img_3);
% img_4 = img_4(:,:,3);

if(size(img_3,3) ~= 1)
    img_4 = rgb2gray(img_3);
else
    img_4 = img_3;
end

img_edge = edge(img_4, 'canny',[],1);%, [0.04 0.4], 2);

if strcmp(debug,'DEBUG')
    subplot(231);imshow(img);
    subplot(232);imshow(img_3);
    subplot(233);imshow(img_4);
    subplot(234);imshow(img_edge);
    subplot(236);drawline(point);
end
