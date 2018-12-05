/* You may have notice the comma after A = c. In Prolog, ',' have the same meaning as AND, while a new line or ';' means OR. Example: */

/* Lets say that prolog provide us with an answer */
?- foo(a, X) = foo(a, b).
X = b; /* <- if we add this semicolon ';' instead of a newline to ask another answer (OR) */
False  /* We get a false because there is no other case */

/* Person is_parent_of Child if Person is_mother_of Child OR Person is_father_of Child */
is_parent_of(Person, Child) :- is_mother_of(Person, Child).
is_parent_of(Person, Child) :- is_father_of(Person, Child).

/* Person is_mother_of Child if Person is_parent_of Child AND Person is_female */
is_mother_of(Person, Child) :- is_parent_of(Person, Child), is_female(Person).

/* Another example of AND and unification */
/* A is unified with B AND A is unified with constant z AND B is unified with Y */
?- A = B, A = z, B = Y.
A = z, /* A was unified with z */
B = z, /* Since A = B and A = z then B = z */
Y = z. /* Since B = A = z then Y = z */
