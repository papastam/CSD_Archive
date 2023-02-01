disp("\n---------------------------------------------------\n                      ERWTHMA A:\n");
disp(roots([1,0,0,2]));
disp("\n");
disp(roots([1,1,0,0,6,0,-1]));
disp("\n");
disp(roots([(1-j),8]));


disp("\n---------------------------------------------------\n                      ERWTHMA B:\n");
disp("\n ASKISI 1:\nA.");

syms z x y;

disp(solve((z+4-3j)/(z+2)==-4));
disp("\nB.")

eq1=2*x+3*y == j;
eq2= x-2*y+1 == 0;
sol = solve([eq1,eq2], [x,y]);
disp("x=");
disp(sol.x);
disp("\ny=");
disp(sol.y);

disp("\n ASKISI 2:");
disp(solve(z^2 == -4));

disp("\n ASKISI 3:\nA.");
disp(solve((x^4) - 1 == 0));
disp("\nB.")
disp(solve((z^3) - (1+j) == 0));
disp("\nC.")
disp(solve((z^10) - 100 == 0));

disp("\n---------------------------------------------------\n                      ERWTHMA G:\n");
dt1 = 0.01;                      % Sampling step
t1 = 0:dt1:8;                    % Time vector
x1 = 2*(e.^-t1)-(e.^-(3*t1));    % Function
plot(t1, x1, "b-");              % Visualize
grid on;                         % Enforce grid
title("A: 2(e^-t)-(e^-3t)");     % Make plot pretty
xlabel("Time (s)");              % Make plot pretty

dt2 = 0.01;                         % Sampling step
t2 = -5:dt2:5;                      % Time vector
x2 = 2*cos(pi*t2) + cos(20*pi*t2);  % Function
figure;                             % Open new figure
plot(t2, x2, "b-");                 % Visualize
grid on;                            % Enforce grid
title("B: 2cos(πt) + cos(20πt)");   % Make plot pretty
xlabel("Time (s)");                 % Make plot pretty

dt3 = 0.01;                         % Sampling step
t3 = -3:dt3:3;                      % Time vector
x3 = (t3.^3) + 3;                   % Function
figure;                             % Open new figure
plot(t3, x3, "b-");                 % Visualize
grid on;                            % Enforce grid
title("C: (t^3) + 3");              % Make plot pretty
xlabel("Time (s)");                 % Make plot pretty

dt4 = 0.01;                         % Sampling step
t4 = pi:dt4:(2*pi);                      % Time vector
x4 = (t4.*(e.^t4)) ./ (t4 + sin(100.*t4));                   % Function
figure;                             % Open new figure
plot(t4, x4, "b-");                 % Visualize
grid on;                            % Enforce grid
title("D: te^t / t + sin(100t)");              % Make plot pretty
xlabel("Time (s)");                 % Make plot pretty