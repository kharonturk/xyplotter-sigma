function data_out = remove_from_data(data, pt)
% data_out = remove_from_data(data, pt)
% remove element from the data.
% if there is not, data_out is preserved.
% but there is a element in data, data_out is the data except the pt,i.e. selected element data.

[rtn idx] = find_element(data,pt);
if(rtn)
    data_out1 = data(1:idx-1,:);
    data_out2 = data(idx+1:end,:);
    data_out = [data_out1;data_out2];
else
    data_out = data;
end