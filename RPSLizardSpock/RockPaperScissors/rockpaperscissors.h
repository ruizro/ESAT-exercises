/**ROCK-PAPER-SCISSORS-LIZARD-SPOCK
        by Sergio Ruiz Roig

        Configuration file

  -> Work in progress
*/

/// BASIC SETTINGS ///
/**@brief Number of moves possible in RPS-game

  The possible values that can be considered a move are:
      0 - Rock
      1 - Paper
      2 - Scissors
      3 - Lizard
      4 - Spock
*/
const int kNumberMoves = 5;

///@brief Number of opponents that'll be involved in RPS-game
const int kNumberOpponents = 10;

///@brief Maximum number of states that'll be involved in RPS-game
const int kNumberStates = 50;

/**@brief Width of the name's player (in struct Player)
    The file with the states must have the exact width for each state
    (for now)
*/
const int kStringWidth = 30;

///@brief Number of the match's states
int list_states[kNumberOpponents] = { 0 };

/// MATCH SETTINGS ///
/**@brief Contains all possible results of a round.

  First / horizontal values = user's move
  Second / vertical values = computer's move.

  The possible results for any match are:
      1 - User wins
      2 - Tie
      3 - Computer's player wins
*/ 
int tableresults[kNumberMoves][kNumberMoves] = { 2, 3, 1, 1, 3,
                                                 1, 2, 3, 3, 1,
                                                 3, 1, 2, 1, 3,
                                                 3, 1, 3, 2, 1,
                                                 1, 3, 1, 3, 2 };

///@brief Number of points obtained by winning a round
const int kVictoryPoints = 2;

///@brief Number of points obtained by a tie
const int kTiePoints = 1;