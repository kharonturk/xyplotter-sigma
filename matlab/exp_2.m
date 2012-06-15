function exp_2
s1 = serial(COMPORT, 'BaudRate', BAUD_RATE);
fopen(s1);

try
    point = [randi(30,15,1)-1, randi(30,15,1)-1, randi(2,15,1)-1];
    point = point';

    point_empty = 0;

    fprintf(s1, '%c','p');
    fprintf(s1, '%c\n','r');
    while(~point_empty)
        d = fscanf(s1, '%d\n');display(d);
        fprintf(s1, 'S%d %d %dE', [point(1, 1), point(2, 1), point(3, 1)]);
        display('fprintf');
        display(point(:,1));
         a = fscanf(s1, '%d\n');display(a);
         b = fscanf(s1, '%d\n');display(b);
         c = fscanf(s1, '%d\n');display(c);
        point = point(:, 2:end);
        point_empty = isempty(point);
    end
catch err
    display(err);
    fclose(s1);
end