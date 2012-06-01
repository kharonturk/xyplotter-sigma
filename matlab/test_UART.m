function test_UART()

s = serial('COM13','BaudRate',115200);
fopen(s);

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