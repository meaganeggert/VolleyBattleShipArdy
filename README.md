# Data Structures Class Final Project:
These were the instructions given to us.
We began with a blank slate besides being given a text file of questions to use for the quiz database, our professor's colors.h library and his read.h library. All students had the option to use either colors.h or ncurses for their TUI.

---

### VolleyBattleShipArdy

"I'm stronger than yesterday." -BS

Purpose: To teach you how to do networking using the simplest possible model
for a multi-user game - a single client connected to a single server.

Theme: You must build a two-player game (one player on the server, the other
on the client) that plays a game that is a combination of volleyball,
battleship, and Jeopardy. You can do this project solo or with a partner.

Demo Code: There is demo code on how to accept connections (as a server) and
make a connection (as a client). Basically, everything in networking has two
things: A) A hostname (you can use localhost to connect to the server you are
on, or you can use an IP address to connect to another machine) and B) a port
number (so one server can accept connections on multiple ports, allowing you
to do both SSH and HTTP and Volleybattleshipardy all at the same time). When
you run your server, you must pick a port number, and pick a port number
different from that of anyone else in the class (only one person can have a
given port open). When you run your client, you will punch in localhost (the
server you are on) and the port number you picked to connect to it. The demo
code will create an iostream that you can read and write to just like a file
or just like cin and cout.

Grading: You will get 10 points for each design criteria you complete.

1) Volleyball: There is a back and forth between the two players, such as if
one gets a trivia question right then the other has to answer the next
question faster and it goes back and forth until one fails to get it right.

2) Battleship: There is a setup phase in which ships are placed on a grid
hidden from the other player. When the person wins a round of volleyball they
get a series of 3 shots to make at the other person's grid. If you sink all of
their ships, you win!

3) Jeopardy: You must ask questions from CSCI 40. There is a file called
questions.txt that has every quiz question from 2021 in it. It is in the
format as follows:
Question (if there is an \n in the string then print an endl instead)
Answer (the first answer is the correct one)
Answer
Answer
Answer
Blank

If you want to use a different quiz database or alter the questions, ask me
first.

4) It must be networked using the tcp::iostream class as in the demo code with
a client-server model. It must be able to run across the internet, not just on
the localhost. I would recommend having two PuTTY instances open if you are
running solo - one terminal to run the server and one to run the client. You
can have the client and server talk to each other just like how you cin and
cout things, but you will need to figure out a protocol for the client and
server to talk to each other (ask yourself - how does the client tell the
server that it is shooting at B-4 on the grid? How does the server respond if
it is a hit or a miss?)

5) It must have a nice looking TUI (Text User Interface). Use the colors library (/public/colors.h)
and the read library (/public/read.h) to do nonblocking I/O, color text, and
printing text at different locations on the screen. (Alternatively you can use
NCURSES to do the same thing.) Visualize the grid for battleship and have an
area where the trivia questions can appear. Use nonblocking I/O to be able to
answer the trivia questions without having to hit enter. Have colors to make
it look nice.

==GIT==

You must use Github to check in each milestone of your project. This is how it
will be graded along with the screenshots you submit.

==TDD==

If you fail one of the milestones you can use gtest to substitute your points
in for it. So you need to make unit tests for your functions and that will
allow you to escape from one of the bullet points above. If you do all the
bullets points and TDD as well, then it is extra credit.

If you get stuck, once during the project you may message me "GONDOR CALLS FOR
AID" and I will help you with one of the bullet points. This offer is not
available in the 24 hours before the final checking, so if you need help ask
earlier rather than later.
