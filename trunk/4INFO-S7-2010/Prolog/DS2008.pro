%%%%%%%%%%%%%%%%%%
% DS prolog 2008 %
%%%%%%%%%%%%%%%%%%

% Question 1.1
%-------------

conc([], Y, Y).
conc([A|X], Y, [A|Z]) :- conc(X, Y, Z).

recouvre(X, Y, N, Z) :- conc(_, B, X), conc(B, C, Y), conc(X, C, Z), length(B, N), !. 
% coupure pour ne garder que la première solution qui est la meilleure

% recouvre([a,c,t,a,t], [t,a,t,g,a,c], N, Z).
% N = 3
% Z = [a, c, t, a, t, g, a, c]
% Yes (0.00s cpu)

% Question 1.2
%-------------

recouvreg([], 0, []).
recouvreg([A|R], L, Z) :- recouvreg(R, N, Y), recouvre(A, Y, M, Z), is(L, M+N).

% recouvreg([[a,c,t,a,t], [t,a,t,g,a,c], [a,c,g,a,c]], N, Z).
% N = 5
% Z = [a, c, t, a, t, g, a, c, g, a, c]
% Yes (0.00s cpu)

% Question 2.1
%-------------

map(_, [], []).
map(T, [A|S], [B|R]) :- map(T, S, R), =..(T, [F|X]), append(X, [A, B], Y), =..(Z, [F| Y]), Z.

% map(append([1, 2]), [[3], [3, 4, 5]], R).
% R = [[1, 2, 3], [1, 2, 3, 4, 5]]
% Yes (0.00s cpu)

% Question 2.2
%-------------

add5(A, Z) :- is(Z, A+5).

% map(add5, [1, 2, 3], Z).
% Z = [6, 7, 8]
% Yes (0.00s cpu)

% Question 3.1
%-------------

lbr(A, [A]) :- atomic(A).
lbr(A, L) :- compound(A), =..(A, [B|R]), map(lbr, R, S), map(append([B]), S, L). 

% lbr( s(t(c,d),b(d,c,d),g), L).
% L = [[s, [t, c], [t, d]], [s, [b, d], [b, c], [b, d]], [s, g]]
% Yes (0.00s cpu)

% enjoy !

