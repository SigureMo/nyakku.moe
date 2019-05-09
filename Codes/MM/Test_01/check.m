A = [1, 1/3, 1/7, 3;
     3, 1, 1/5, 5;
     7, 5, 1, 7;
     1/3, 1/5, 1/7, 1];
[V, D] = eig(A);
D = diag(D);
[D, idx] = sort(D, 'descend');
lambda_max = D(1);
n = size(A, 1);
CI = (lambda_max - n) / (n - 1)