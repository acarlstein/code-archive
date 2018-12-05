/* Example 1: Check the prefix of a list. */

/* Base case */
/* When the list of prefix checked is empty means that we stop checking */
prefix([],_).

/* Recursive case */
/* Both head of the list must be the same */
prefix([Head|Tail_A], [Head|Tail_B]):-
    prefix(Tail_A, Tail_B).

?- prefix([1,b], [1,b,c,4]).
true.

?- prefix([1,b], [1,d,c,4]).
false.


/* prefix will search for each prefix everytime OR ';' is used */
?- prefix(Lst, [1,2,3,4]).
Lst = [] ;
Lst = [1] ;
Lst = [1, 2] ;
Lst = [1, 2, 3] ;
Lst = [1, 2, 3, 4] ;
false.

/* Generate a list where list [1,2,3,4] is the prefix and the tail is a dynamic variable */
?- prefix([1,2,3,4],Lst).
Lst = [1, 2, 3, 4|_G3713]. 

/* Example 2: Check the suffix of a list. */

/* Base case */
/* When both list are the same, we found the suffix */
suffix(Lst_tail, Lst_tail).

/* Recursive case */
/* We want to check always the tail of the list, so the base case can check if they are the same */
suffix([_|Tail], Lst) :-
    suffix(Tail, Lst).

?- suffix([a,2,c,4],[c,4]).
true.

?- suffix([a,2,c,d],[c,4]).
false.

/* Obtain the next tail everytime OR ';' is used */
?- suffix([1,2,3,4], Lst).
Lst = [1, 2, 3, 4] ;
Lst = [2, 3, 4] ;
Lst = [3, 4] ;
Lst = [4] ;
Lst = [].

/* Be careful, in this kind of cases prolog keep generating dynamic variables in from of the list */
?- suffix(Lst, [1,2,3,4]).
Lst = [1, 2, 3, 4] ;
Lst = [_G3704, 1, 2, 3, 4] ;
Lst = [_G3704, _G3707, 1, 2, 3, 4] ;
Lst = [_G3704, _G3707, _G3710, 1, 2, 3, 4] ;
Lst = [_G3704, _G3707, _G3710, _G3713, 1, 2, 3, 4] ;
Lst = [_G3704, _G3707, _G3710, _G3713, _G3716, 1, 2, 3, 4] ;
Lst = [_G3704, _G3707, _G3710, _G3713, _G3716, _G3719, 1, 2, 3|...] ;
... /* Keep generating dynamic variables */

 

/* Example 3: In this example, we are introducing append. append is the unification of two lists, List_A, List_B, into one list that we are going to call list AB, List_AB. */


/* The code of append is the follow: */

/* Base case */
/* Will stop recursion when List_A is empty indicating that all the elements are in List_AB */
append([], Lst, Lst).

/* Recursive case */
append([Head|Tail_A], List_B, [Head|Tail_AB]):-
    append(Tail_A, List_B, Tail_AB).

/* First append will move 1, 2,  and 3 atoms from List_A to List_AB using recursion: */

/* Recursive case */
append([Head|Tail_A], List_B, [Head|Tail_AB]):-
    append(Tail_A, List_B, Tail_AB).

append([1,2,3], [4,5,6], []) → append([2,3], [4,5,6], [1])  → append([3], [4,5,6], [1,2])  → append([], [4,5,6], [1,2,3])

/* When List_A is empty, then it will append List_B to List_AB as a tail of List_AB using the base case: */

/* Base case */
/* Will stop recursion when List_A is empty indicating that all the elements are in List_AB */
append([], Lst, Lst).


append([], [4,5,6], [1,2,3]) → append([], [], [1,2,3,4,5,6])  → List_AB = [1,2,3,4,5,6]

/* Example 4: Even do append seems to create a list by appending List_A with List_B, append can behave in a different ways depending of how it is used: */

/* Let see the code for append: */

append([], Lst, Lst). /* ← Base case */
append([Head|Tail_A], List_B, [Head|Tail_AB]):-  /* ← Recursive case */
    append(Tail_A, List_B, Tail_AB).

 

/* Lets say we do  append(List_A, [5,6], [1,2,3,4,5,6]). What would be the result?


As you can see List_AB have 1,2,3,4,5, and 6 while List_B have 5 and 6, Prolog will unify List_A with 1,2,3, and 4. */

?- append(List_A, [5,6], [1,2,3,4,5,6]).
List_A = [1, 2, 3, 4] .
