## Groovy: Groovy Console: Solution for Input from User Bug from 2016

I am currently (Dec 13, 2016) taking a class on Groovy, and I found that the Groovy console have a huge bug which doesn’t allow it to obtain input from the user. System.console() gives ‘null’ and all the solutions involving the use of System.in or the input reader buffer seems to fail.

These input-from-user bugs seems to be known based on what the instructor told me when I showed this solution. After some research, I found that they were reported but nothing have being done so far to solve the issue.

Below is the only solution I found so far that works, creating a dialog in order to obtain the input from the user and execute a code.
Please notice that if you close the dialog (pressing the X button), you will kill the groovy console too.