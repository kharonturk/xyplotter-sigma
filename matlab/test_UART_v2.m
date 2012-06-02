function test_UART_v2()
% start interrupt : 1(%d)
% require point information interrupt : 2(%d)

COMPORT = 'COM13';
BaudRate = 115200;
DATA_NUM = 1;

fclose('all');
s1 = serial(COMPORT, 'BaudRate', BaudRate);
fopen(s1);
set(s1, 'Timeout',60);

start = 0;
point_empty = 1;%default value

while(point_empty)
    while(~start)
        try
            reply = fscanf(s1, '%d\n');
            % please send data with a format fprintf('%d\n',1) or
            % fprintf('%s\n','1')
        catch err
            display(err);
            fclose(s1);
            break;
        end
        display(reply);
        if reply == 1
            start = 1;
            display('Started.');
        elseif reply == 2
            fprintf(s1, '%d\n', 0);
            display('Please press 1.');
        end
    end
    display('Passed first block!');
    try
        if(start)
            point = randi(2,15,1)-1;%, randi(2,15,1)-1, randi(2,15,1)-1];
            display(point);
        else
            point = [];
        end
        point_empty = 0;%isempty(point);
    catch err
        display(err);
        fclose(s1);
        break;
    end
    display('Passed second block!');
    % require point information interrupt
    %
    point = point';
    while(~point_empty)
        try
            interrupt = fscanf(s1,'%d\n');
            display(interrupt);
            display('Received Interrupt!');
            
            if (interrupt == 2)
                fprintf(s1, '%d\n', point(1:DATA_NUM));
                display('Send Led Data!');
                
                point = point(DATA_NUM+1:end);
                point_empty = isempty(point);
                display(point_empty);
            end
        catch err
            display(err);
            fclose(s1);
            break;
        end
    end
    display('Passed all block! give me a 1');
    start = 0;
end

fclose(s1);
delete(s1);