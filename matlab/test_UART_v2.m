function test_UART_v2()
% start interrupt : 1(%d)
% require point information interrupt : 2(%d)

COMPORT = 'COM13';
BaudRate = 115200;
DATA_NUM = 1;

fclose('all');
s1 = serial(COMPORT, 'BaudRate', BaudRate);
fopen(s1);

point_empty = 1;%default value

while(point_empty)
    try
        reply = fscanf(s1, '%d\n');
        % please send data with a format fprintf('%d\n',1) or
        % fprintf('%s\n','1')
    catch err
        display(err);
        fclose(s1);
        break;
    end
    display('Passed first block!');
    if reply == 1
        start = 1;
    else
        start = 0;
    end
    display('Passed second block!');
    try
        if(start)
            point = [randi(2,15,1)-1, randi(2,15,1)-1, randi(2,15,1)-1];
        else
            point = [];
        end
        point_empty = 0;%isempty(point);
    catch err
        display(err);
        fclose(s1);
        break;
    end
    display('Passed third block!');
    % require point information interrupt
    %
    point = point';
    while(~point_empty)
        interrupt = fscanf(s1,'%d\n');
        if interrupt == 2
            try
                fprintf(s1, '%d %d %d\n', point(:,1:DATA_NUM));
            catch err
                display(err);
                fclose(s1);
                break;
            end
            point = point(:,DATA_NUM+1:end);
            point_empty = isempty(point);
        end
        display('Received Interrupt!');
    end
    break;
end

fclose(s1);
delete(s1);