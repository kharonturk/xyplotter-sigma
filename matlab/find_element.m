function [rtn index] = find_element(data, pt)
% data : m by 2 matrix
% pt : 1 by 2 element
[L ~] = size(data);

data = data - [pt(1).*ones(L,1) pt(2).*ones(L,1)];
logical = data(:,1)|data(:,2);
index = find(logical == 0);
if(index)
    rtn = 1;
else
    rtn = 0;
end