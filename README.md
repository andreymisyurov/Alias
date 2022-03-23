# Alias

Development of «Alias» - terminal application for learning English words. The first version will be a terminal version, then, as desired and the ability to configure a graphical one, it may be a server version :))

Now our application will be - two loops of while. There is timer in first loop. Second loop - will be menu, where ''-'' is skip, and ''+'' is move to the next word. The screen should show a timer and the number of points. Words must be read from the bases line by line. Bases will be ‘’.txt’’ documents in which words are written line by line by difficulty levels and directions (500 simple everyday words, 500 more difficult words, 500 programming (can be slang) terms, etc.) The project will be on github and sometimes updated, refresh with databases of new words.

## Realized

* Database
  * initial database interface for reading files by strokes
  * UNIX-based way to search files in specified folder
  * debug method to display all the .txt files contents in specified folder,
  amount of total records and records in each file
  * function to get all records from all files
  * function to get records count from specified opened file
  * function to read record in opened file and at specified line
  * method to skip one record without memorizing it

## TODO

* make a function that read random line from database (line by line, for example ’’developer разработчик’), and throw word in output. words shouldn’t repeat in one game.
* realize func timer for one minute which will break game
* create database for 500 simple english words
* create database for 500 more difficult english words

example for database will be in .txt files

I want and I hope create first version our application next weekend.
