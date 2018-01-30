 for j = 1:size(A{i},1)
    [x, y, v] = find(A{i}(j, :));
    AM(j, 1) = j; AM(j, 2) = y(1); AM(j, 3) = v(1);
    AM(j, 4) = j; AM(j, 5) = y(2); AM(j, 6) = v(2);
 end
 
 Acpp = dlmread('C:\Users\stefa_000\Documents\GitHubLocalRepos\Research-Shape-from-Shading\SIRfS\validation_files\Acpp0.txt',' ');
test = Acpp == AM;
[r c] = find(test==0);
clear Acpp;
