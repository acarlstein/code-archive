/* Prolog have a powerful way to work data by the use of lists. A list is normally a group of elements in each elements would have to pointers, one to the value and another to the next element or rest of the of the list. Just to clarify, we don't see these pointers.

A list is represented in this way: T = [1, 2, 3, 4, 5] in which T is unified with this list and each number is an element of the list.

You can have also a list inside the list: T = [1, [a, b], 3, 4, 5].

The follows are some examples of how to work with list in Prolog:

Example 1: Lets have two variables, Head and Tail, we want the first element of the list to be unified with the Head variable and the rest of the list to be unified with the tail. */

?- [Head|Tail] = [1,2,3,4,5].
H = 1,
T = [2, 3, 4, 5].

/* Example 2: Let say we wish to obtain the first two elements of the list, First_element and Second_element, and the rest of the list to the variable Tail. */

?- [First_element, Second_element|Tail] = [1,2,3,4,5].
First_element = 1,
Second_element = 2,
Tail = [3, 4, 5].

/* If there are just two elements in the list, the Tail will be pointing to an empty list. An empty list is represented by [] */

?- [First_element, Second_element|Tail] = [1,2].
First_element = 1,
Second_element = 2,
Tail = [].

/* A list with less elements that needed, Prolog will indicate us cannot be done. */

?- [First_element, Second_element|Tail] = [1].
False

/* Here [A] = [1] means that A is unified with 1, while B is unified with 2,3,4,5 */
?- [[A]|B] = [[1],2,3,4,5].
A = 1,
B = [2, 3, 4, 5].

/* [A|B] = [1,2], C = [3,4,5] → A = 1, B = [2], C = [3,4,5] */
?- [[A|B]|C] = [[1,2],3,4,5].
A = 1,
B = [2],
C = [3, 4, 5].

?- [[A|B]|C] = [[1,2,3],4,5,6].
A = 1,
B = [2, 3],
C = [4, 5, 6].

?- [[A|B]|[C|D]] = [[1,2,3],4,5,6].
A = 1,
B = [2, 3],
C = 4,
D = [5, 6].

/* There are cases in which we can use the feature that Prolog provide of unification. */

/* This case, we have the same Head. Notice we have two 3's, one inside the sublist and one of the list */
?- [[Head|Tail_A]|[Head|Tail_B]] = [[3,4,5],3,6,7].
Head = 3,
Tail_A = [4, 5],
Tail_B = [6, 7].

/* The following case would fails because the first list [Head|Tail_A] would unify with [3, 4, 5] and the second [Head|Tail_B] list would unify with [2,6,7], since the atom 3 is not the same as the atom 2 then it false. */

?- [[Head|Tail_A]|[Head|Tail_B]] = [[3,4,5],2,6,7].
false.

/* The follow is the same example but using different atoms: */

?- [[A|B]|[A|D]] = [[a,b,c],a,e,f].
A = a,
B = [b, c],
D = [e, f].

?- [[A|B]|[A|D]] = [[a,b,c],d,e,f].
false.

?- [[A|B]|[_|D]] = [[a,b,c],a,e,f].
A = a,
B = [b, c],
D = [e, f].

?- [[_|B]|[_|D]] = [[a,b,c],a,e,f].
B = [b, c],
D = [e, f].

?- [[A|T]|[B|T]] = [[a,b,c],d,b,c].
A = a,
T = [b, c],
B = d.

/* This proves that Prolog consider  numbers as atoms (constants) in the same way as lower case characters/names and strings such as 'abc'.

Using an underscore inside the brackets indicate that we don't care about that element or elements: */

?- [_|Tail] = [1,2,3,4,5].
Tail = [2, 3, 4, 5].

?- [_|Tail] = [1,2,3,4,5].
Tail = [2, 3, 4, 5].

?- [_|_] = [1,2,3,4,5].
True