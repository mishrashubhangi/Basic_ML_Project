# ASSIGNMENT 2

## Part 1: Raichu Solver

#### In this problem we have to design a program for Raichu to play well. For this we define several functions namely:

pichu_valid_move_white** , pikachu_valid_move_white , raichu_valid_move_white,pichu_valid_move_black , pikachu_valid_move_black , raichu_valid_move_black: These functions define the valid moves for pichu,pikachu and raichu(for both white and black colors) for different cases provided in the question. I wrote the code for white pichus,pikachus and raichus while for the black ones(all three cases) I just inverted the board(i.e) took the mirror of the board, stored it in a variable mirror_board which was passed as a parameter in place of the board.
 
evaluation_function: This function is used for calculating the utility for the given board configuration. To do so I have assigned different weights for pichu(weight=1), pikachu(weight=3) and raichu(weight=5). I also calculate the number of white and black pieces of pichu on the opponents half i.e white on N-1 and N-2 row and black in the first(1) and second(2) row.

terminal_state: This function is used to determine the number of black and white pichus, pikachus and raichus present on the board for the given board configuration.

Successors: This function generates the successor for each player depending on whether the player is white or black.

min_method and max_method: These functions are a part of the minimax algorithm. Minimax algorithm is a backtracking algorithm which we primarily use in decision-making and game theory. Using both these functions we find the optimal move for the player assuming that the opponent is also playing optimally.min_method is used to get the lowest score possible whereas max_method is used to get the highest score possible.

alpha_beta_result:  To decrease the number of nodes present in the minimax algorithm we use alpha beta pruning. This algorithm increases the efficiency of the program. The result evaluated from alpha beta pruning is stored in the given function. 

find_best_move: The objective of this function is to decide which one is the max_player and which one the min_player on the basis of whether the player(that is the given pieces namely pichu,pikachu and raichu) is black or white in color.

Problems faced: Initially I faced a problem in defining the successor function but the purpose got solved later on. Afterwards I realized that my functions for valid moves are not working well. As a result I am unable to get any output but want my approach to be considered. Thank you!
