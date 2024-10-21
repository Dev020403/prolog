% Base case: An empty list has 0 elements.
count_elements([], 0).

% Recursive case: If the list is not empty, count the head and recurse on the tail.
count_elements([_|Tail], Count) :-
    count_elements(Tail, CountTail),   % Count elements in the tail.
    Count is CountTail + 1.             % Increment count by 1 for the head.
