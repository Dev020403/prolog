print_numbers(11) :- !.  % Base case: Stop when N is greater than 10.
print_numbers(N) :- 
    write(N),        % Print the current number followed by a newline.
    N1 is N + 1,         % Increment the number.
    print_numbers(N1).   % Recursive call with the incremented number.
