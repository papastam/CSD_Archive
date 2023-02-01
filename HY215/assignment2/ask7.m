pkg load symbolic;

%i

dt = 0.0001;
t = 0:dt:pi;
x = sin(4*t).*cos(5*t);
res = dt * sum(x);

clear;

%ii

syms t;
x = 1./(5/4 - cos(t));
res = int(x, t, 0, 2*pi);

%iii

dt = 0.0001;
t = 0:dt:1;
x = log(t)./(1 + t);
res = dt * sum(x);

clear;

%iv
dt = 0.0001;
t = 1:dt:2;
x = (t.^ 2 - 4) ./ (t .^ 2);
res = dt * sum(x);