% Predicate to perform addition
add(X, Y, Result) :-
    Result is X + Y.

% Predicate to perform subtraction
subtract(X, Y, Result) :-
    Result is X - Y.

% Predicate to perform multiplication
multiply(X, Y, Result) :-
    Result is X * Y.

% Predicate to perform division
divide(X, Y, Result) :-
    Y \= 0,           % Ensure the divisor is not zero
    Result is X / Y.
