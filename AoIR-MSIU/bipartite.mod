param Lnum;
param Rnum;

param z{i in 1..Lnum,j in 1..Rnum};
param w{i in 1..Lnum,j in 1..Rnum};

var y{i in 1..Lnum,j in 1..Rnum} binary;
var obj1;

maximize weight: obj1;

subject to c01:
obj1=sum{i in 1..Lnum}sum{j in 1..Rnum}y[i,j]*w[i,j]*z[i,j];

subject to c02 {i in 1..Lnum}:
sum{j in 1..Rnum}y[i,j]*z[i,j]=1;

subject to c2 {j in 1..Rnum}:
sum{i in 1..Lnum}y[i,j]*z[i,j]<=1;

subject to c3 {i in 1..Lnum}:
sum{j in 1..Rnum}y[i,j]*z[i,j]<=1;
