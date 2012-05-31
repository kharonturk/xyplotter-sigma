function img = captureEdgeData_v2(image_filename)

MASK_SIZE = 5;
BINARY_BW = 0.55;

if(nargin == 0)
    vid = videoinput('winvideo', 1, 'YUY2_320x240');
    R = 240;
    C = 320;
else
    img = imread(image_filename);
    [R C ~] = size(img);
end

signal = 1;
mask = 1/(MASK_SIZE^2).*ones(MASK_SIZE);

while(1)
    if(signal)
        if(nargin == 0)
            img = getsnapshot(vid);
        end
%        img = imrotate(img, 15);
        img_bw = im2bw(img, BINARY_BW);
        
        img_bw_new = img_bw;
        for i=1+(MASK_SIZE-1)/2:R-(MASK_SIZE-1)/2
            for j=1+(MASK_SIZE-1)/2:C-(MASK_SIZE-1)/2
                img_bw_new(i,j) = (sum(sum(img_bw(i-(MASK_SIZE-1)/2:i+(MASK_SIZE-1)/2,j-(MASK_SIZE-1)/2:j+(MASK_SIZE-1)/2).*mask))>0.5);
            end
        end
        
        corners = corner(img_bw_new, 10000000);
        img_edge = edge(img_bw_new, 'canny', [0.04 0.4], 2);
        
        subplot(231);imshow(img);
        subplot(232);imshow(img_bw);
        subplot(233);imshow(img_bw_new);
        subplot(234);imshow(uint8(img_bw_new).*100+100);
        hold on; plot(corners(:,1), corners(:,2), 'r.');
        subplot(235);imshow(img_edge);
        
        subplot(236);
        point = find_pt(img_edge);
        drawline(point);
        axis square;
    end
    
    reply = input('Continue?','s');
    if reply == 'y'
        signal = 1;
        continue;
    elseif reply == 'n'
        break;
    else
        signal = 0;
    end
end