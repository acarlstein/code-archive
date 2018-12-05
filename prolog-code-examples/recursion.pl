/*
Lets begin with cases related with recursion:

In an imperative style,  you would use a loop to produce a result, while in an functional style, it is common to use recursion to produce the same result.

The most common example related with recursion is the factorial recursion, in which for example the factorial of 6 (6! = 5 * 4 * 3 * 2 * 1) would give us
*/

/* Base case of the factorial, when N is 0 then return 1 */
factorial(0, 1).

factorial(N, M) :-
    N1 is N - 1,
    factorial(N1, M1),
    M is N * M1.

?- factorial(6, T).
T = 720;
ERROR: Out of local stack

/* Note: As you can see, when we added the OR ';', prolog tried to find another  answer and went out of bound.
To prevent this we can do an small modification as follows: */

/* Base case of the factorial, when N is 0 then return 1 */
factorial(0, 1).

factorial(N, M) :-
    N > 0
    N1 is N - 1,
    factorial(N1, M1),
    M is N * M1.

?- factorial(6, T).
T = 720;
False

/* In this case, when we tell Prolog that we wish to find another possible answer, Prolog would indicate false since it cannot find any other possible solution.

Lets go over some examples:

Example 1: We have a family and we wish to know the descendent of some individual. */

/* Maria is_mother_of Pedro */
is_mother_of(Maria, Pedro).

/* Susana is_mother_of Maria */
is_mother_of(Susana, Maria).

/* Pepe is_father_of Pedro */
is_father_of(Pepe, Pedro).

/* Diego is_father_of Pepe */
is_father_of(Diego, Pepe).

/* Person is_parent_of Child if Person is_mother_of Child */
is_parent_of(Person, Child):- is_mother_of(Person, Child).

/* OR */

/* Person is_parent_of Child if Person is_father_of_Child */
is_parent_of(Person, Child):- is_father_of(Person, Child) */

/* Begin RECURSION */

/* Recursion Base */

/* Person is_decendent_of Adult if Adult is_parent_of Person */
is_decendent_of(Person, Adult) :- is_parent_of(Adult, Person).

/* Recursion */
/* Person is_decendent_of Adult if Older(person) is_parent_of Person AND Older is_decendent_of Adult */
 is_decendent_of(Person, Adult) :- is_parent_of(Older, Person), is_decendent_of(Older, Adult).

/* Example 2: Fibonacci (http://en.wikipedia.org/wiki/Fibonacci_number) is an integer sequence such as 0, 1, 1, 2, 3, 5, 8... As you may notice, the first two numbers are 0 and 1, an the subsequence is form by a number created from the sum of the two previous numbers: 0 + 1 = 1 (0,1,1) , 1 + 1 = 2 (1,1,2), 1 + 2 = 3 (1,2,3), 2 + 3 = 5 (2,3,5) ... */

/* Recursion base case */
fibonacci(0, 0).

/* Recursion base case */
fibonacci(1, 1).

/* Recursion */
fibonacci(N, F) :-
    N1 is N - 1,
    N2 is N - 2,
    fibonacci(N1, F1),
    fibonacci(N2, F2),
    F is F1 + F2.

?- fibonacci(8, T).
T = 21;
ERROR: Out of local stack

/* Again in this case, when asking prolog to find another answer, it would go out of bounds because there is no case that stop it to keep calling itself. We need to modify this program: */

/* Recursion base cases */
fibonacci(0, 0).
fibonacci(1, 1).

/* Recursion */
fibonacci(N, F) :-
    N > 0,
    N1 is N - 1,
    N2 is N - 2,
    fibonacci(N1, F1),
    fibonacci(N2, F2),
    F is F1 + F2. ?- fibonacci(8, T).
T = 21;
False

/* Again, Prolog couldn't find a different answer when we ask it to search for it and let it know by returning false after the OR ';'.

Example 3: The following code is the Ackermann's predicate (http://en.wikipedia.org/wiki/Ackermann_function).
One of the purposes to doing this kind of function could be to test the limits of the compiler.
The Ackermann's functions is defined as follows: */
ackermann( m,n ) =    n + 1                                                             if m = 0
ackermann( m,n ) =    ackermann(m - 1, 1)                                if n = 0 and m > 0
ackermann( m,n ) =    ack( m-1, ackermann( m, n-1 ) )          if n >0 and m > 0

/* ackermann(m, n) = n + 1 if m = 0 */
ackermann(Mi, Ni, No):- Mi = 0, No is Ni + 1.

/* ackermann(m, n) = ackermann(m - 1, ackermann(m, n - 1)) if n > 0 and m > 0 */
ackermann(Mi, Ni, No):-
    Mi > 0, Ni > 0,
    Mi2 is Mi - 1, Ni2 is Ni - 1,
    ackermann(Mi, Ni2, No2),
    ackermann(Mi2, No2, No).

/* ackermann(m, n) = ackermann(m - 1, 1) if n = 0 and m > 0 */
ackermann(Mi, Ni, No):-
    Mi > 0, Ni = 0,
    Mi2 is Mi - 1, Ni2 is 1,
    ackermann(Mi2, Ni2, No).