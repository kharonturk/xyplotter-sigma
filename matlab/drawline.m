function drawline(point_in,MODE)
% drawline(point_in)
if nargin == 1
    MODE = '';
end

[L ~] = size(point_in);
figure();
hold on;
axis([-1600 1600 -1600 1600]);

for i=1:L-1
    if(point_in(i+1,3)==1)
        plot(point_in(i:i+1,1),point_in(i:i+1,2));%original
        %        plot(point_in(i:i+1,2),640-point_in(i:i+1,1));%just visual
        if(strcmp(MODE,'ANIMATE'))
            drawnow;
            pause(0.005);
        end
    end
end