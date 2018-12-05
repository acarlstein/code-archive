/* Example 1: Lets do a modification of the game of Yahtzee (http://en.wikipedia.org/wiki/Yahtzee).
Yahtzee is played with 5 dices, and depending of the combination you can obtain: Chance, Three-Of-A-Kind, Four-Of-A-Kind, Full House, Small Straight, Large Straight, and Yahtzee.
We are going to do only the Yahtzee combination for this example and the user will input values from 1 to 6. */

/* Establish the facts and rules */

/* Yahtzee: All five dices show the same face. */
yahtzee(A, A, A, A, A).
?- yahtzee(5,5,5,5,5).
True

?- yahtzee(5,4,5,4,5).
False
