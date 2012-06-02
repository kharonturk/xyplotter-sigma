function drawline(point_in)

[L ~] = size(point_in);

hold on;

for i=1:L-1
    if(point_in(i+1,3)==1)
%        plot(point_in(i:i+1,1),point_in(i:i+1,2));%original
       plot(point_in(i:i+1,2),640-point_in(i:i+1,1));%just visual
    end
end