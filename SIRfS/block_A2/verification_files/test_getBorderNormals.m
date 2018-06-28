fid = fopen('TangentM.txt', 'wt');
for i = 1:size(data.border.tangent, 1)
fprintf(fid, '%.15d %.15d\n', data.border.tangent(i, 1), data.border.tangent(i, 2));
end
fclose(fid)

fid = fopen('NormalM.txt', 'wt');
for i = 1:size(data.border.normal, 1)
fprintf(fid, '%.15d %.15d\n', data.border.normal(i, 1), data.border.normal(i, 2));
end
fclose(fid)

fid = fopen('PositionM.txt', 'wt');
for i = 1:size(data.border.position, 1)
fprintf(fid, '%d %d\n', data.border.position(i, 1), data.border.position(i, 2));
end
fclose(fid)

fid = fopen('IdxM.txt', 'wt');
for i = 1:size(data.border.idx, 1)
fprintf(fid, '%d\n', data.border.idx(i)); 
end
flcose(fid)