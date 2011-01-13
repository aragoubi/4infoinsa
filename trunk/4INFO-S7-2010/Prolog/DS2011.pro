%%%%%%%%%%%%%%%%%%
% DS prolog 2010 %
%%%%%%%%%%%%%%%%%%

% Question 1.1
%-------------

applatit2([], []).
applatit2([A|S], [A|R]) :- integer(A), !, applatit2(S, R).
applatit2([A|S], L) :- applatit2(A, B), applatit2(S, R), append(B, R, L).

% ?- applatit2([4,[[6,7],2],[5]], L).
% L = [4, 6, 7, 2, 5].

% Question 1.2
%-------------

applatit3([], L, L).
applatit3([A|S], R, L) :- integer(A), !, applatit3(S, [A|R], L).
applatit3([A|S], R, L) :- applatit3(A, R, T), applatit3(S, T, L).

% ?- applatit3([4,[[6,7],2],[5]], [], L).
% L = [5, 2, 7, 6, 4].

% Question 2.1
%-------------

graphe --> ["{"], somsucc, rsomsucc, ["}"].
rsomsucc --> [].
rsomsucc --> [','], somsucc, rsomsucc.
somsucc --> ["("], som, [','], ["{"], succs, ["}"], [")"].
succs --> [].
succs --> som, rsom.
rsom --> [].
rsom --> [','], som, rsom.
som --> [A], {atomic(A)}.

% pas testé

% Question 2.2
%-------------

graphe(g(Ls, La)) --> ["{"], somsucc(g(Ls1, La1)), rsomsucc(g(Ls2, La2)), ["}"], {append(Ls1, Ls2, Ls), append(La1, La2, La)}.
rsomsucc(g([], [])) --> [].
rsomsucc(g(Ls, La)) --> [','], somsucc(g(Ls, La)), rsomsucc(g(Ls, La)).
somsucc(g([A|Ls], La)) --> ["("], [A], {atomic(A)}, [','], ["{"], succs(g(Ls, La)), ["}"], [")"].
succs(g(_, [])) --> [].
succs(g([A|Ls], [arc(A,S)|La])) --> [S], {atomic(S)}, rsom(g([A|Ls], La)).
rsom(g(_, [])) --> [].
rsom(g([A|Ls], [arc(A,S)|La])) --> [','], [S], {atomic(S)}, rsom(g([A|Ls], La)).

% pour tester :
analex(Lx, Lt) :- read_token(X, T), sanalex(X, T, Lx, Lt).
sanalex('.', fullstop, [], []).
sanalex(X, T, [X|L1], [T|L2]) :- \=(X, '.'), analex(L1, L2).

% ?- analex(X,_), phrase(graphe(G),X).
% {(a,{b,c,d}),(b,{b,a}),(c,{}),(d,{b}),(e,{})}.

% TDMM vaincra !

