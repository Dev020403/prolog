% Base case: An empty board has no queens and no conflict.
nqueens(N, Solution) :-
    length(Solution, N),
    place_queens(Solution, N),
    safe(Solution).

% Place queens in all columns.
place_queens([], _).
place_queens([Q|Qs], N) :-
    place_queens(Qs, N),
    between(1, N, Q).

% Ensure no two queens are in the same row, column, or diagonal.
safe([]).
safe([Q|Qs]) :-
    safe(Qs),
    no_attack(Q, Qs, 1).

% Ensure the queen does not attack others.
no_attack(_, [], _).
no_attack(Q, [Q1|Qs], D) :-
    Q =\= Q1,
    abs(Q - Q1) =\= D,
    D1 is D + 1,
    no_attack(Q, Qs, D1).
