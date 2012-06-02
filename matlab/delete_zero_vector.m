function pt_out = delete_zero_vector(pt)

zero_vector = ~(pt(:,1)|pt(:,2)|pt(:,3));
idx = find(zero_vector == 1);
[R C] = size(pt);

for i=1:R
    
end