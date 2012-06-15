function point_out = find_pt(img)
% point_out = find_pt(img)
% img is logical image file
% and find nearest point, start from origin (0, 0).
% as find point, we remove that point from the register data matrix and
% find moreover.
%
% point_out : data_x, data_y and whether or not you draw line.
% if distance from a point to another point, this line is not a part of
% drawings. so third element of output(means touch) is 0.
% otherwise, if line is a part of drawings, and then third element of
% output is 1.

[x y] = find(img == 1);
data = [x y];
[L ~] = size(data);

point_out = zeros(L+floor(L/2), 3);
current_pt = [0 0];

offset = 0;

h = waitbar(0,'Please wait...');

for i=1:L+L/2
    if(isempty(data))
        if(distance(start_pt, current_pt) < DISTANCE_LIMIT)
            point_out(i+offset,:) = [start_pt 1];
        end
        break;
    end
    
    [next_pt touch] = nearest_pt(data, current_pt);
    if touch==0
        if (i~= 1 && distance(start_pt, current_pt) < DISTANCE_LIMIT)
            point_out(i+offset,:) = [start_pt 1];
            offset = offset+1;
        end
        start_pt = next_pt;
    end
    
    data = remove_from_data(data,current_pt+[-1 0]);
    data = remove_from_data(data,current_pt+[-1 1]);
    data = remove_from_data(data,current_pt+[0 1]);
    data = remove_from_data(data,current_pt+[1 1]);
    data = remove_from_data(data,current_pt+[1 0]);
    data = remove_from_data(data,current_pt+[1 -1]);
    data = remove_from_data(data,current_pt+[0 -1]);
    data = remove_from_data(data,current_pt+[-1 -1]);
    data = remove_from_data(data,current_pt);
    
    current_pt = next_pt;
    point_out(i+offset,:) = [next_pt touch];
    
    waitbar(i/L);
end

[~, idx] = find_element(point_out(2:end,1:2),[0 0]);
point_out = point_out(1:idx,:);

close(h);
