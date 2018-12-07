/* Implicit: */

relationship(Z, Z).
?- is_related(relationship(First, b), relationship(a, Second)).
First = a,
Second = b.
