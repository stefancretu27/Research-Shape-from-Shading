[x y v] = find(data.A_median_filter_mat);
AM = horzcat(x, y, v);
[~,idx] = sort(AM(:,1));
AM = AM(idx,:);
fid = fopen('AM.txt', 'wt');
Am(:, 1:3) = AM(1:2:end, 1:3);
Am(:, 4:6) = AM(2:2:end, 1:3);
for i = 1:size(Am, 1)
fprintf(fid, '%d %d %d %d %d %d', Am(i, 1), Am(i, 2), Am(i, 3), Am(i, 4), Am(i, 5), Am(i, 6));
fprintf(fid, '\n');
end