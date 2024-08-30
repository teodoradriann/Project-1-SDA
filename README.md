# tema1-SDA

This is my implementation for Assignment 1. I chose to modularize the code as much as possible for easier reading, better organization, and to work in a cleaner environment. By using this technique, I was able to split each part of the code along with its respective methods and data structures.

I found the assignment easy; it would have been more fun if it had been a bit more challenging. The search function was the most interesting, and I approached it as follows: I decided to search for the first letter of the word to determine if it’s possible that the searched word is in the list. If the first letter doesn’t exist in the list, it means that the word is not in the list. Otherwise, I continue searching letter by letter for strlen(word) - 1 letters because the first one has already been found. Here, I encountered the first bug in the program because if I had a match for, say, 3/4 letters but hadn’t reached the terminator yet, my program would mark the word as not found without continuing to search until the terminator. To fix this bug, I decided to mark the entire search from the first letter with a “retry” mark so that if I don’t find a potential word and haven’t reached the terminator, I can restart the search.
The same approach was applied for search-left/right.

In train.c, I implemented the methods for the doubly linked list with sentinel, and in queue.c, I implemented the command queue. In main.c, I handled the actual reading of the data and its processing.

The methods are basic list operations; I don’t think it’s necessary to go into detail, as each one is commented on in the file where it’s located.

Overall, I found the assignment nice, but I would have preferred it to be much more difficult. Maybe this aspect will be considered in the future.
