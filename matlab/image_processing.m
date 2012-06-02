function img_edge = image_processing(img_original, debug)
if nargin == 1
    debug = 0;
end

MASK_SIZE = 5;
BINARY_BW = 0.55;
CONST = 0.9;
blur_mask = 1/(MASK_SIZE^2).*ones(MASK_SIZE);

[R C ~] = size(img_original);
img_hsv = rgb2hsv(img_original);
img = img_hsv(:,:,3);

% img_blur = conv2(blur_mask, img);
img_sharpen = conv2([0 0 -0.075 0 0;
    0 -0.075 -0.125 -0.075 0;
    -0.075 -0.125 2 -0.125 -0.075;
    0 -0.075 -0.125 -0.075 0;
    0 0 -0.075 0 0], img); %image enhancing
img = (1-CONST).*img + CONST.*img_sharpen(3:end-2,3:end-2);%modified img
img_bw = im2bw(img, BINARY_BW);

img_bw_new = img_bw;
for i=1+(MASK_SIZE-1)/2:R-(MASK_SIZE-1)/2
    for j=1+(MASK_SIZE-1)/2:C-(MASK_SIZE-1)/2
        img_bw_new(i,j) = (sum(sum(img_bw(i-(MASK_SIZE-1)/2:i+(MASK_SIZE-1)/2,j-(MASK_SIZE-1)/2:j+(MASK_SIZE-1)/2).*blur_mask))>0.5);
    end
end
img_edge = edge(img, 'canny', [0.04 0.4], 2);
img_bw_edge = edge(img_bw_new, 'canny', [0.04 0.4], 2);

point = find_pt(img_edge);

if debug
    subplot(231);imshow(img);
    subplot(232);imshow(img_bw);
    subplot(233);imshow(img_bw_new);
    subplot(234);imshow(img_edge);
    subplot(235);imshow(img_bw_edge);
    subplot(236);point = sampling(point);drawline(point);
end
