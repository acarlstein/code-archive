/* Predicate are clauses using the same head with different bodies, eg:*/

/* A Person is_parent_of the Child if (:-) the Person is_mother_of the Child */
is_parent_of(Person, Child) :- is_mother_of(Person, Child).

/* A Person is_parent_of the Child if (:-) the Person is_father_of the Child */
is_parent_of(Person, Child) :- is_father_of(Person, Child).

/* Note: Every code written before '?-' are facts and rules. Code written following '?-' are queries, and all code after '?-' are the results that prolog returns. eg: */

is_mother_of(Marina, Marcos).   /* This is a fact */
is_parent_of(Person, Child) :- is_mother_of(Person, Child). /* This is a rule */
?- is_parent_of(Marina, Marcos). /* This is a query */
True /* This is a result. note that this comment will not show up */
?- is_parent_of(Marina, Lucia). /* This is a query */
False