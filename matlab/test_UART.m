function test_UART(version)

s = serial('COM13','BaudRate',115200);
fopen(s);

if(version == 1)
    while(1)
        try
            d = fscanf(s,'%d\n');
        catch err
            display(err);
            fclose(s);
            break;
        end
        
        if(d == 0)
            fclose(s);
            break;
        end
        display(d);
    end
    
elseif(version == 2)
    try
        fprintf(s, '%d\n',1);
        pause(1);
        fprintf(s, '%d\n',2);
    catch err
        display(err);
        fclose(s);
    end
elseif(version == 3)
    for i=1:2
        try
            re = fscanf(s,'%d\n');
            if re == 1
                display('1 received!');
            else
                display(re);
                display(' received!');
            end
        catch err
            display(err);
            fclose(s);
        end
    end
elseif(version == 4)
    for i=1:3
        try
            re = fscanf(s,'%d\n');
            if re == 1
                display('1 received!');
                fprintf(s,'%d\n',1);
            else
                display(re);
                display(' received!');
                fprintf(s,'%d\n',re);
            end
        catch err
            display(err);
            fclose(s);
        end
    end
end


fclose(s);