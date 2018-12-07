/* Example 2: Lets do some adding. This is a way that you can do adding by using successor(0)
as a numeral. */

/* When 0 is the same as 0, then Y = 0 */
add(0, Y, Y).

/* */
add(successor(X), Y, successor(Z)) :- add(X, Y, Z).

/* Example of behavior when used in the wrong way */

?- add(A, B, C).
A = 0,
B = C;
A = successor(0),
C = successor(B);
A = successor(successor(0)),
C = successor(successor(B));
... /* This keeps on going if you use OR ';' */

/* Example of behavior when used in the wrong way */
?- add(A, 0, C).
A = 0,
C = 0;
A = successor(0),
C = successor(0);
A = successor(successor(0)),
C = successor(successor(0));
... /* This keeps on going if you use OR ';' */

/* Example of behavior when used in the wrong way */
?- add(0, B, C).
A = 0,
B = 0.

/* Example of behavior when used in the wrong way */
?- add(0, 1, C).
false.

/* Do 1 + 1 = 2: successor(0) + successor(0) = successor(successor(0)). */
?- add(successor(0), successor(0), X).
X = successor(successor(0)).

/* Do 2 + 1 = 3. */
/* successor(successor(0)) + successor(0) = successor(successor(successor(0))). */
?- add(successor(successor(0)), successor(0), X).
X = successor(successor(successor(0))).

/* Notice that a rule can behave different depending who you define your inputs and outputs. */

/* Here we find that we are doing -1 + 1 = 0 */
?- add(successor(0), X, successor(0)).
X = 0.

/* Here we have 2 - 1 = 1 */
?- add(successor(0), X, successor(successor(0))).
X = successor(0).

/* While this give you X = 0, it would fail in a different case */
?- add(X, successor(0), successor(0)).
X = 0

/* Here this fails */
?- add(X, successor(successor(0)), successor(0)).
false.
