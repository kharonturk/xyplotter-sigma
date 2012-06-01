function point = find_cam_edge_pt(start)

vid = videoinput('winvideo', 2, 'RGB24_640x480');%Modify as computer

if(start)
    try
        img = getsnapshot(vid);
    catch err
        display(err);
    end
    img_edge = image_processing(img);
    point = find_pt(img_edge);    
end