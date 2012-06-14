function captureEdgeData_v3

fclose('all');
clear all;

s1 = serial(COMPORT, 'BaudRate', BAUD_RATE);
fopen(s1);
set(s1, 'Timeout',60);

start = 0;
point_empty = 1;%default value

while(point_empty)

    try
        % Press the button to take a Picture.
        start = StartXYPlotter(s1, start);
        
        % Take a Picture and find point data.
        [point point_empty] = Take_Picture_Find_Point(start);
        
        % Send a Data Packet as occuring Interrupt.
        [point_empty start] = Send_Data_Packet(s1, point, point_empty);
        
    catch err
        display(err);
        fclose(s1);
        break;
    end
    
end

fclose(s1);
delete(s1);
end

function start = StartXYPlotter(s1, start)

while(~start)
    reply = fscanf(s1, '%d\n');
    % please send data with a format fprintf('%d\n',START_INT) or
    % fprintf('%s\n','START_INT')
    if reply == START_INT
        start = 1;
    elseif reply == SEND_INT
        dummy = zeros(3,DATA_NUM);
        fprintf(s1, '%d\n', dummy);
    end
end

end

function [point point_empty] = Take_Picture_Find_Point(start)

% point = [randi(2,15,1)-1, randi(2,15,1)-1, randi(2,15,1)-1];
point = find_cam_edge_pt(start);
point_empty = isempty(point);

% Scaling Point Data
point(:,1:2) = point(:,1:2)*5-1600;

point = point';

end

function [point_empty start] = Send_Data_Packet(s1, point, point_empty)

while(~point_empty)
    interrupt = fscanf(s1,'%d\n');
    
    if (interrupt == SEND_INT)
        if(size(point,2) < DATA_NUM)
            zero = zeros(3, DATA_NUM - size(point,2));%fill insufficient data packet to zeros.
            point_end = [point zero];
            fprintf(s1, '%d\n', point_end(:, 1:end));
        else
            fprintf(s1, '%d\n', point(:, 1:DATA_NUM));
        end
        
        point = point(:, DATA_NUM+1:end);
        point_empty = isempty(point);
    end
end

start = 0;

end