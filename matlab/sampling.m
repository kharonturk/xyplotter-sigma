function pt_out = sampling(pt)

PROB = 0.8;

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