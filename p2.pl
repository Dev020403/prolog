% Facts (as before)
parent(john, mary).
parent(john, mike).
parent(anna, mary).
parent(anna, mike).
parent(mary, lisa).
parent(mary, tom).
parent(mike, jack).

male(john).
male(mike).
male(tom).
male(jack).

female(anna).
female(mary).
female(lisa).

% Rule: X is a father if X is male and a parent.
father(X, Y) :-
    parent(X, Y),
    male(X).

% Rule: X is a mother if X is female and a parent.
mother(X, Y) :-
    parent(X, Y),
    female(X).

% Rule: X is a grandparent of Y if X is the parent of Z, and Z is the parent of Y.
grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

% Rule: X is a sibling of Y if they share the same parent.
sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.  % Ensure X and Y are not the same person.

% Rule: X is a sister of Y if X is female and a sibling of Y.
sister(X, Y) :-
    sibling(X, Y),
    female(X).
