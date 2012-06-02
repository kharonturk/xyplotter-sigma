function test_UART_v2(debug)
% start interrupt : 1(%d)
% require point information interrupt : 2(%d)
if nargin==0
    debug = '';
end

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
        if(strcmp(debug, 'DEBUG'))display(reply);end
        if reply == 1
            start = 1;
            if(strcmp(debug, 'DEBUG'))display('Started.');end
        elseif reply == 2
            try
                fprintf(s1, '%s\n', '0 0 0');
            catch err
                display(err);
                fclose(s1);
            end
            if(strcmp(debug, 'DEBUG'))display('Please press 1.');end
        end
    end
    if(strcmp(debug, 'DEBUG'))display('Passed first block!');end
    try
        if(start)
            point = [randi(4,15,1)-1, randi(4,15,1)-1, randi(4,15,1)-1];
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
    if(strcmp(debug, 'DEBUG'))display('Passed second block!');end
    % require point information interrupt
    %
    point = point';
    while(~point_empty)
        try
            interrupt = fscanf(s1,'%d\n');
            if(strcmp(debug, 'DEBUG'))display(interrupt);end
            if(strcmp(debug, 'DEBUG'))display('Received Interrupt!');end

            if (interrupt == 2)
                fprintf(s1, '%d\n', point(:, 1:DATA_NUM));
                if(strcmp(debug, 'DEBUG'))display('Send Led Data!');end

                point = point(:, DATA_NUM+1:end);
                point_empty = isempty(point);
                if(strcmp(debug, 'DEBUG'))display(point_empty);end
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