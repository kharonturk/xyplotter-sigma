function point = captureEdgeData_v2()

MASK_SIZE = 5;
BINARY_BW = 0.5;%mean percent of black
COMPORT = 'COM13';
BaudRate = 115200;

vid = videoinput('winvideo', 2, 'RGB24_320x240');%Modify as computer
size = get(vid, 'VideoResolution');
R = size(2); C = size(1);

signal = 1;
mask = 1/(MASK_SIZE^2).*ones(MASK_SIZE);

fclose('all');
s1 = serial(COMPORT, 'BaudRate', BaudRate);
fopen(s1);

while(1)
    try
        if(signal)
            img = getsnapshot(vid);
            img_bw = im2bw(img, BINARY_BW);
            
            img_bw_new = img_bw;
            for i=1+(MASK_SIZE-1)/2:R-(MASK_SIZE-1)/2
                for j=1+(MASK_SIZE-1)/2:C-(MASK_SIZE-1)/2
                    img_bw_new(i,j) = (sum(sum(img_bw(i-(MASK_SIZE-1)/2:i+(MASK_SIZE-1)/2,j-(MASK_SIZE-1)/2:j+(MASK_SIZE-1)/2).*mask))>0.5);
                end
            end
            
            img_edge = edge(img_bw_new, 'canny', [0.04 0.4], 2);
            point = find_pt(img_edge);
            
        end
        
        reply = fscanf(s1);
        if reply == '1'
            signal = 1;
            continue;
        elseif reply == '0'
            break;
        else
            signal = 0;
        end
    catch
        display('Error ');
        fclose(s1);
    end
end

fclose(s1);