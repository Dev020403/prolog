% a. Insert an element into the list at the beginning.
insert(Element, List, [Element|List]).

% b. Replace an element in the list.
replace(_, _, [], []) :- !.   % Base case: Empty list remains empty.
replace(Old, New, [Old|Tail], [New|TailNew]) :-  % Replace head if it matches Old.
    replace(Old, New, Tail, TailNew).
replace(Old, New, [Head|Tail], [Head|TailNew]) :-  % Otherwise, recurse on the tail.
    replace(Old, New, Tail, TailNew).


% c. Delete an element from the list.
delete(_, [], []).   % Base case: Empty list remains empty.
delete(Element, [Element|Tail], Tail) :- !.  % Delete if the head matches the element.
delete(Element, [Head|Tail], [Head|TailNew]) :-  % Otherwise, recurse on the tail.
    delete(Element, Tail, TailNew).