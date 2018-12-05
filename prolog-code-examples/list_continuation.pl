/* In this part of this practical tutorial, we are going to do some coding involving facts, rules, recursion, and lists.

Example 1: Obtain the head of the list, obtain the tail of the list. */

/* Get the head of the list */
get_head(Head, [Head|_]).

/* Get the tail of the list */
get_tail(Tail, [_|Tail]).

?- get_head(Head_is, [a,b,c,d]).
Head_is = a.

?- get_tail(Tail_is, [a,b,c,d]).
Tail_is = [b, c, d].

/* Example 2: Find out if an element is a member of a list. */

/* Base case - We find the element inside the list */
/* The element is found if the head of the list can be unified with the element we are searching */
member(Element, [Element|_]).

/* Recursive function that call member with the tail without taking care of the head of the list */
/* The idea is that the base case will be called and check if the element is found */
member(Element, [_|Tail]) :-
    member(Element, Tail).    

?- member(a, [a,1,3,b,c]).
true .

/* Using OR ';', we ask Prolog to search for another element in the list */
?- member(a, [a,1,a,b,c]).
true ;
true ;
false.

/* Element is not found in the list */
?- member(a, [c,1,3,b,c]).
false.

/* Example 3: Find an specific element member inside a list in a determined position. */

/* Base case */
/* The element was found in the list was found, set Position to 1 to stop recursion */
get_member_at(1, [Head|_], Head).

/* Recursive case */
/* Go thought the list until position is less than 1 indicating that member was found */
get_member_at(Position, [_|Tail], Element):-
    Position > 1,
    Temp_Position is Position - 1,
    get_member_at(Temp_Position, Tail,  Element).

/* Get the member at position 3 of the list */
?- get_member_at(3, [1,3,5,7], Lst).
Lst = 5. 

/* This fails when trying to get an element out or bounds of the list */
?- get_member_at(5, [1,3,5,7], Lst).
false. 

/* BE CAREFUL, Sometimes prolog can behave weird base on how you use your functors eg.*/

/* The follow is when prolog create dynamic variables because doesn't now the limit of the list */
?- get_member_at(5, Lst, Lst).
Lst = [_G455, _G458, _G461, _G464, **|_G468].

/* In this case, not only produce dynamic variables to be instanciated, but also add
the list [1,a,b] as the fifth head element of the list */
?- get_member_at(5, Lst, [1,a,b]).
Lst = [_G473, _G476, _G479, _G482, [1, a, b]|_G486] ;

/* Example 4: Lets obtain the numbers of elements that belong to a simple list. */

/* Base case - When the list is empty, unify with zero */
number_of_elements([], 0).

/* Recursive case */
number_of_elements([_|Tail], Number_counted) :-
    number_of_elements(Tail, counter),
    Number_counted is counter + 1.

/* In the recursive case, Prolog will call number_of_elements passing the tail of the list until the list is empty. Then, for every time number_of_elements was call it would return the counter + 1 to the previous call. At the end, we will obtain the total number of elements in the list. */

?- number_of_elements([a,1,b,2,^, &], Counted).
Counted = 6.

/* In this case the sublist [1,2,3] inside the list is considerate an element as a whole */
?- number_of_elements([a,b,c,[1,2,3]], Counted).
Counted = 4.

?- number_of_elements([[a,b,c,1,2,3]], Counted).
Counted = 1.

/* If inside the code we would had the unification symbol instead of the word 'is', we would have a different result: */

/* Base case - When the list is empty, unify with zero */
number_of_elements([], 0).

/* Recursive case */
number_of_elements([_|Tail], Number_counted) :-
    number_of_elements(Tail, counter),

    Number_counted is counter + 1.

?- number_of_elements([a,1,b,2,^, &], Counted).
Counted = 0+1+1+1+1+1+1.

/* Example 5: Lets sort a list of elements */

/* Base case - Empty list */
sort_list([]).

/* Base case - [_] indicate we don't case about the element, there is only one, the list is sorted */
sort_list([_]).

/* Recursion case */
sort_list([First_element, Second_element|Tail]):-
    First_element =< Second_element,
    sorted([Second_element|Tail]).

?- is_list_sorted([1,2,3,4]).
true .

?- is_list_sorted([1,2,3,4]).
true ;
false.

?- is_list_sorted([1,3,3,4]).
true.

?- is_list_sorted([1,3,5,4]).
false.