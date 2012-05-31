function [next_pt touch] = nearest_pt(data, pt)

DISTANCE_LIMIT = 2;

[L ~] = size(data);

data_dist = data - [pt(1).*ones(L,1) pt(2).*ones(L,1)];
data_dist = remove_from_data(data_dist, [0 0]);
distance = data_dist(:,1).^2 + data_dist(:,2).^2;
[length idx] = min(distance);

if(length>DISTANCE_LIMIT)
    touch = 0;
else
    touch = 1;
end

next_pt = data_dist(idx,:)+[pt(1) pt(2)];