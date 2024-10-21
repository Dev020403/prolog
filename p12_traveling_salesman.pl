% Base case: The distance between two cities is known.
distance(a, b, 10).
distance(a, c, 15).
distance(a, d, 20).
distance(b, c, 35).
distance(b, d, 25).
distance(c, d, 30).
distance(b, a, 10).
distance(c, a, 15).
distance(d, a, 20).
distance(c, b, 35).
distance(d, b, 25).
distance(d, c, 30).

% TSP: Find the minimal tour starting from Start.
tsp(Start, Tour, Cost) :-
    findall(T, permute([a,b,c,d], T), Permutations),
    min_tour(Start, Permutations, Tour, Cost).

% Helper function to calculate minimal tour cost.
min_tour(_, [], [], inf).
min_tour(Start, [Tour|Rest], MinTour, MinCost) :-
    cost([Start|Tour], C1),
    min_tour(Start, Rest, T2, C2),
    (C1 < C2 -> (MinTour = [Start|Tour], MinCost = C1) ; (MinTour = T2, MinCost = C2)).

% Calculate the cost of a given route.
cost([_], 0).
cost([City1, City2|Rest], Cost) :-
    distance(City1, City2, C),
    cost([City2|Rest], CostRest),
    Cost is C + CostRest.

% Generate all permutations of the cities.
permute([], []).
permute(List, [H|Perm]) :-
    select(H, List, Rest),
    permute(Rest, Perm).