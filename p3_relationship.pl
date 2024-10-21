% Given facts based on the genealogical tree
father(a, b).
father(a, c).
father(b, d).
father(b, e).
father(c, f).

% Predicate to define X is the brother of Y
brother(X, Y) :-
    father(F, X),
    father(F, Y),
    X \= Y.

% Predicate to define X is the cousin of Y
cousin(X, Y) :-
    father(F1, X),
    father(F2, Y),
    brother(F1, F2).

% Predicate to define X is the grandson of Y
grandson(X, Y) :-
    father(Y, F),
    father(F, X).

% Predicate to define X is a descendant of Y
descendent(X, Y) :-
    father(Y, X).
descendent(X, Y) :-
    father(Y, F),
    descendent(X, F).
