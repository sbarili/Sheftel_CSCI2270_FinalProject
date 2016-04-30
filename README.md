# Sheftel_CSCI2270_FinalProject
Final project for Data Structures, Spring 2016 - Rock, Paper, Scissors Analysis/Prediction

### Summary
In this project, the user will play **Rock, Paper, Scissors** while their moves are stored and analyzed. History of moves will be stored in a queue, then series of moves are read into a tree. Limits to the number of moves analyzed at once will limit the height and length of the queue and tree respectively.

The tree contains two types of nodes:
1. DecisionNode: point at which user would make a R/P/S decision; stores number of each decision
2. MoveNode: placeholder for move, directs to 2 DecisionNode's, one if the move won, the other if it lost

Options will be available to:

1. Display analysis of the user's moves.
2. Change bot's decision mode.
  * Random (1/3 probability for each)
  * Best move based on user's previous moves

### How to Run
Upload includes a Code::Blocks project file, but is not necessary. Compile with g++ for C++11

### Open Issues/Bugs
- needs to be structured/organized better
- difficulty testing prediction engine
- difficulty checking accuracy of tree

#### Possible Additions
- May add feature to have save file I/O for data.
- Best move based on research prediction
  - http://www.sussex.ac.uk/broadcast/read/34501
