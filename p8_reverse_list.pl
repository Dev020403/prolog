% Base case: The reverse of an empty list is an empty list.
reverse_list([], []).

% Recursive case: Reverse the tail, then append the head to the end.
reverse_list([Head|Tail], Reversed) :-
    reverse_list(Tail, ReversedTail),       % Reverse the tail.
    append(ReversedTail, [Head], Reversed). % Append the head to the reversed tail.
