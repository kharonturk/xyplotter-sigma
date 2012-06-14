function point = find_cam_edge_pt(start)
% point = find_cam_edge_pt(start)

if(start)
    try
        vid = videoinput(ADAPTORNAME, DEVICEID, FORMAT);
        %        vid = videoinput('winvideo', 2, 'RGB24_640x480');%Modify as computer
        
        display('3');
        pause(1);
        display('2');
        pause(1);
        display('1');
        
        img = getsnapshot(vid);
        display('Shot!');
    catch err
        display(err);
    end
    img_rgb = YUY2toRGB(img);
    img_edge = image_processing(img_rgb);
    point = find_pt(img_edge);
    
    % sampling point data to reduce information
    point = sampling(point);
else
    point = [];
end