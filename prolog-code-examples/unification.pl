/* Lets talk about unification. */

/* A unified with B if and only if A and B are the same */
?- =(A, B).
A = B.

/* This is the same as =(A, B) */
?- A = B.
A = B.

/* Note that A = 1 + 2 will not give you 3 but A = 1 + 2 which means you are unifying A with 1 + 2. */
/* If you to obtain a mathemarical result you should use the following code, eg: */

?- A is 1 + 2.
A = 3.

/* The follows are some examples of unification:*/

/* a is a constant (also known as an atom) */
/* Since constants can unify with themselves then this is true */
?- a = a.
True

/* a and b are constants, but b is not the same as a, when trying to unify a with b, this will give you false */
?- a = b.
False

/* In case you are unifying facts with constants */
?- foo(a, b) = foo(a, b).
True.

/* This case fails since in both facts, at least one of the constants are nor the same */
?- foo(a, b) = foo(a, c).
False.

?- foo(a, b) = foo(b, a).
False.

/* Unification can also being use to unify a constant with a variable (Variables start with capital letter), eg: */

?- A = a.
A = a.

/* In this case for example we can unify A with c and B with d */
?- foo(A, B) = foo(c, d).
A = c,
B = d.

/* Note that in Prolog, a variable cannot be modified after */
