/* Rules are clauses with a head and body (head():- body), eg: */
/* A Person is_parent_of the Child if (:-) the Person is_mother_of the Child */
is_parent_of(Person, Child) :- is_mother_of(Person, Child).

