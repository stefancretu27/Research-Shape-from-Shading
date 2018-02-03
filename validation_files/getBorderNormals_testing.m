Position_cpp = dlmread('C:\Users\stefa_000\Documents\GitHubLocalRepos\Research-Shape-from-Shading\SIRfS\validation_files\dataBorderPosition.txt','');
test = Position_cpp==data.border.position;
[r c] = find(test == 0);

Normal_cpp = dlmread('C:\Users\stefa_000\Documents\GitHubLocalRepos\Research-Shape-from-Shading\SIRfS\validation_files\dataBorderNormal.txt','');
test = abs(Normal_cpp-data.border.normal) < 1e-15;
[r c] = find(test == 0);

Tangent_cpp = dlmread('C:\Users\stefa_000\Documents\GitHubLocalRepos\Research-Shape-from-Shading\SIRfS\validation_files\dataBorderTangent.txt','');
test = abs(Tangent_cpp-data.border.tangent) < 1e-15;
[r c] = find(test == 0);

Idx_cpp = dlmread('C:\Users\stefa_000\Documents\GitHubLocalRepos\Research-Shape-from-Shading\SIRfS\validation_files\dataBorderIdx.txt','');
Idx_cpp = Idx_cpp';
test = Idx_cpp == data.border.idx;
[r c] = find(test == 0);