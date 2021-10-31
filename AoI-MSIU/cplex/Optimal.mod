param m;#the number of source nodes
param n;#the total number of all contents
param alpha;
param y{i in 1..m, j in 1..n};# y[i,j]=1: SN i can provide content j; y[i,j]=0, cannot provide
param v{i in 1..m, j in 1..n};#the value
param t{i in 1..m, j in 1..n};#the AoI
param r{i in 1..m};#the capacity of SN i

var x{i in 1..m, j in 1..n} binary;
var T{i in 1..m};
var obj;
var objU;

maximize revenue: obj;

#i: source node; j: content
subject to c0:
obj=objU-alpha*sum{i in 1..m}T[i];

subject to c1{i in 1..m,j in 1..n}:
T[i]>=t[i,j]*x[i,j];

subject to c2{i in 1..m}:
sum{j in 1..n}x[i,j]<=r[i];

subject to c3{j in 1..n}:
sum{i in 1..m}x[i,j]<=1;

subject to c4{i in 1..m, j in 1..n}:
x[i,j]<=y[i,j];

subject to c5:
objU=sum{i in 1..m, j in 1..n}y[i,j]*x[i,j]*v[i,j];
	