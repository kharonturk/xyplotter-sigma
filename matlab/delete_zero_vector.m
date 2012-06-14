function pt_out = delete_zero_vector(pt)
% pt_out = delete_zero_vector(pt)
zero_vector = ~(pt(:,1)|pt(:,2)|pt(:,3));
[R C] = size(pt);
pt_out = zeros(R-sum(zero_vector), C);

j=1;
for i=1:R
    if(~zero_vector(i))
        pt_out(j,:) = pt(i,:);
        j = j+1;
    end
end