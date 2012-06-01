function image_processing(image_filename)

MASK_SIZE = 5;
BINARY_BW = 0.55;
CONST = 0.6;

img = imread(image_filename);
[R C ~] = size(img);
img_hsv = rgb2hsv(img);

img = img_hsv(:,:,3);

mask = 1/(MASK_SIZE^2).*ones(MASK_SIZE);
mask_unsharp = [-1 -1 -1;-1 8 -1;-1 -1 -1];
img_sharpen = conv2(mask_unsharp, img);
img = img + CONST.*img_sharpen(2:end-1,2:end-1);

img_bw = im2bw(img, BINARY_BW);

img_bw_new = img_bw;
for i=1+(MASK_SIZE-1)/2:R-(MASK_SIZE-1)/2
    for j=1+(MASK_SIZE-1)/2:C-(MASK_SIZE-1)/2
        img_bw_new(i,j) = (sum(sum(img_bw(i-(MASK_SIZE-1)/2:i+(MASK_SIZE-1)/2,j-(MASK_SIZE-1)/2:j+(MASK_SIZE-1)/2).*mask))>0.5);
    end
end
img_edge = edge(img, 'canny', [0.04 0.4], 2);
img_bw_edge = edge(img_bw_new, 'canny', [0.04 0.4], 2);

subplot(231);imshow(img);
subplot(232);imshow(img_bw);
subplot(233);imshow(img_bw_new);
subplot(234);imshow(img_edge);
subplot(235);imshow(img_bw_edge);
subplot(236);
point = find_pt(img_bw_edge);
drawline(point);
axis square;
