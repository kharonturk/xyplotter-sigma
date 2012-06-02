function pt_out = sampling(pt, PROB)
% pt : [inf 3]
if nargin == 1
    PROB = 0.5;
end

[R C] = size(pt);
pt_out = zeros(R,C);%approximation

for i=1:R
    if(pt(i,3)==0)
        pt_out(i,:) = pt(i,:);
    else
        pt_out(i,:) = (rand<=PROB).*pt(i,:);
    end
end

pt_out = delete_zero_vector(pt_out);