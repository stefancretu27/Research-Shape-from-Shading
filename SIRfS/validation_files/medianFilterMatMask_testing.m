[x y v] = find(data.Z_median_filter_mat);
ZM = horzcat(x, y, v);
[~,idx] = sort(ZM(:,1));
ZM = ZM(idx,:);

Zcpp = dlmread('C:\Users\stefa_000\Documents\GitHubLocalRepos\Research-Shape-from-Shading\SIRfS\ZMedianFilterMat.txt', '');
Zcpp = vertcat(Zcpp(:, 1:3), Zcpp(:, 4:6));
[~,idx] = sort(Zcpp(:,1));
Zcpp = Zcpp(idx,:);

test = ZM==Zcpp;
[w q] = find(test==0);