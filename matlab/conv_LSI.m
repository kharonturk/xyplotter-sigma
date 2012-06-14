function Rtn = conv_LSI(img, mask)
% Rtn = conv_LSI(img, mask)
[R_m C_m] = size(mask);% R by R

img = double(img);
mask = double(mask);

for i=1:size(img,3)
    temp(:,:,i) = conv2(img(:,:,i),mask);
end

temp = uint8(temp);

Rtn = temp(1+R_m:end-R_m,1+C_m:end-C_m,:);
