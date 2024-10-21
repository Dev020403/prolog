% Base case: Moving 1 disk is a simple move from Source to Destination.
hanoi(1, Source, Destination, _) :- 
    write('Move disk from '), 
    write(Source), 
    write(' to '), 
    write(Destination), nl.

% Recursive case: Move N-1 disks to Auxiliary, move the Nth disk, and then move the N-1 disks back to Destination.
hanoi(N, Source, Destination, Auxiliary) :-
    N > 1,
    N1 is N - 1,
    hanoi(N1, Source, Auxiliary, Destination), % Move N-1 disks from Source to Auxiliary
    hanoi(1, Source, Destination, _),          % Move the Nth disk from Source to Destination
    hanoi(N1, Auxiliary, Destination, Source). % Move N-1 disks from Auxiliary to Destination
