% Example using CUT (!)
% The CUT prevents Prolog from backtracking to find other solutions after a match.
fruit(apple).
fruit(banana).
fruit(orange).
fruit(grape).

% This rule uses CUT. Once we find a fruit, no further backtracking happens.
find_fruit(X) :-
    fruit(X),
    !.          % Cut: No backtracking will occur beyond this point.

% Example using FAIL
% The FAIL predicate forces failure and triggers backtracking.
% This rule lists fruits, but forces failure, leading Prolog to backtrack and try other options.
list_fruits :-
    fruit(X),
    write(X), nl,
    fail.       % Always fails, forcing Prolog to backtrack and find the next fruit.

% Once all fruits are listed, stop using a base case.
list_fruits.   % This prevents the program from going into an infinite loop after backtracking.
