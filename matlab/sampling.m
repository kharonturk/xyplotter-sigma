function pt_out = sampling(pt)
% pt : [inf 3]
PROB = 0.5;

[R C] = size(pt);
pt_out = zeros(R,C);%approximation

for i=1:R
    pt_out(i,:) = (rand<=PROB).*pt(i,:);
end

pt_out = delete_zero_vector(pt_out);