function captureEdgeData_v2()
% start interrupt : 1(%d)
% require point information interrupt : 2(%d)

COMPORT = 'COM13';
BaudRate = 115200;
DATA_NUM = 10;

fclose('all');
s1 = serial(COMPORT, 'BaudRate', BaudRate);
fopen(s1);

point_empty = 1;%default value

while(point_empty)
    % start captureEdgeData
    try
        reply = fscanf(s1, '%d\n');
        % please send data with a format fprintf('%d\n',1) or
        % fprintf('%s\n','1')
    catch err
        display(err);
    end

    if reply == 1
        start = 1;
    else
        start = 0;
    end
    
    % find point from cam
    try
        point = find_cam_edge_pt(start);
        point_empty = 0;%isempty(point);
    catch err
        display(err);
        fclose(s1);
    end
    
    % sampling point data to reduce information
    point = sampling(point);
    
    % require point information interrupt
    point = point';
    while(~point_empty)
        interrupt = fscanf(s1,'%d\n');
        if interrupt == 2
            fprintf(s1, '%d %d %d\n', point(:,1:DATA_NUM));
            point = point(:,DATA_NUM+1:end);
            point_empty = isempty(point);
        end
    end
end

fclose(s1);