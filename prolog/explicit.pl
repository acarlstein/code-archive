/* Explicit: */

relationship(Z, Z).
is_related(X, Y):-
    relationship(X, b),
    relationship(a, Y).
?- check(First, Second).
First = b,
Second = a.

