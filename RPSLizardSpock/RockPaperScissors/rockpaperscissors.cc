/**ROCK-PAPER-SCISSORS-LIZARD-SPOCK GAME
          by Sergio Ruiz Roig
              Version 1.0.

  -> Work in progress
*/
#define _CRT_SECURE_NO_DEPRECATE

#include "rockpaperscissors.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

///@brief Structure of an RPS player
struct Player{
  char name[30];
  int move;
  Player *next_player;
};

///@brief Number of moves possible in RPS-game
const int kNumberMoves = 5;

///@brief Maximum number of states that'll be involved in RPS-game
const int kNumberStates = 50;

///@brief Number of the match's states
int list_states[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/**@brief Gives a name for the human player

  This function uses a string for give the player a name.
  The process just repeats itself until the string isn't empty

  @return human Player's name
  @param human Player's structure
*/
struct Player InputName(Player human) {
  while (strlen(human.name) == 0) {
    printf("Give yourself a name: ");
    fgets(human.name, 30, stdin);
    human.name[strlen(human.name) - 1] = 0;
    fflush(stdin);
  }
  return human;
}

/**@brief Determine if a value exists in an array

  This function searches a value inside an array, returning a boolean
  (true or false) with the result.

  @return bool Boolean value
  @param sequence[10] Array with 10 values
  @param num_state Number we want to search
*/
bool StateExists(int sequence[10], int num_state) {
  for (int j = 0; j < 10; ++j) {
    if (sequence[j] == num_state) {
      return true;
    }
  }
  return false;
}

/**@brief Determine if states.txt exists

  This function ckecks for file "states.txt", as is needed in order to
  give states' names to the CPU's players.

  @return bool Boolean value
*/
bool FileExists() {
  ///@brief File with USA's states
  FILE *usa = fopen("states.txt", "r");

  if (usa == NULL) {
    return false;
  } else {
    fclose(usa);
    return true;
  }
}

/**@brief Gets the number of the states involved in the match.

The function gives random numbers between 1 and the limit delimited by
constant kNumberStates, in order to fill the array of states that will
play Rock-Paper-Scissors afterwards. The loop is redone if any of the
values obtained is repeated.

@param list_states[10] Array filled with states' number.
*/
void GetComputerStates() {
  ///@brief Saves a random number and searches it on the array
  int random_number = 0;

  ///@brief Says if random_number is found on the array or not
  bool state_found = false;

  srand(time(NULL));
  for (int i = 0; i < 10; ++i) {
    state_found = true;
    while (state_found) {
      random_number = rand() % kNumberStates + 1;
      if (!StateExists(list_states, random_number)) {
        list_states[i] = random_number;
        state_found = false;
      }
    }
  }
}

/**@brief Creates a list with all CPU players included.

  The function gets the sequence of CPU that'll be used in the game,
  giving each one a state name and a move.

  @return list Pointer with all CPU's players
  @param *list An empty pointer.
*/
struct Player* GetMatchList(struct Player *list) {
  ///@brief Auxiliar struct used to expand *list pointer
  struct Player *aux_list = NULL;

  ///@brief File with USA's states
  FILE *usa = fopen("states.txt", "r");

  ///@brief Counts how many states have been found at states.txt and searches it
  int state_count = 0;

  list = new (Player);
  list->next_player = NULL;

  while (!feof(usa)) {
    aux_list = new (Player);
    aux_list->next_player = NULL;
    fread(&aux_list->name, sizeof(aux_list->name), 1, usa);
    aux_list->name[strlen(aux_list->name) - 10] = '\0';
    ++state_count;
    if (!feof(usa) && StateExists(list_states, state_count)) {
      aux_list->move = rand() % kNumberMoves + 1;
      aux_list->next_player = list;
      list = aux_list;
    }
  }
  fclose(usa);
  return list;
}

/**@brief Transform a char to ROCK, PAPER or SCISSORS

  Just asks the player for any move, uses getchar() for unveil the player's
  move. The function repeats if the char isn't R, P, S, L or K.

  @return value Number of the move
*/
int PlayerInput() {
  ///@brief Saves a char selected by the user with getchar()
  char player_move = '\0';

  printf("\n");
  while (player_move != 'r' || player_move != 's' || player_move != 'p' ||
         player_move != 'l' || player_move != 'k') {
    printf("What's your move? (R/P/S/L/K): ");
    player_move = getchar();
    fflush(stdin);
    switch (player_move) {
      case 'r': case 'R': {
        printf("You've played ROCK.");
        return 1;
      }
      case 'p': case 'P': {
        printf("You've played PAPER.");
        return 2;
      }
      case 's': case 'S': {
        printf("You've played SCISSORS.");
        return 3;
      }
      case 'l': case 'L': {
        printf("You've played LIZARD.");
        return 4;
      }
      case 'k': case 'K': {
        printf("You've played SPOCK.");
        return 5;
      }
      default: {
        break;
      }
    }
  }
}

/**@brief Determine match's winner

  This function compares both players' move and determine who wins,
  loses or tie, returning a number with the resolution.
  1 - Human player wins
  2 - Draw
  3 - Computer player wins

  @return value Result of the match.
  @param player_move As it says, user's move.
  @param computer_move As it says, computer's move.
*/
int DetermineMatchWinner(int player_move, int computer_move) {
  switch (player_move) {
    case 1: { switch (computer_move) {
                case 1: { //Rock vs Rock
                  printf("\nIt's a draw!");
                  return 2;
                }
                case 2: { //Rock vs Paper
                  printf("\nPAPER covers ROCK.");
                  printf("\nYou lose!");
                  return 3;
                }
                case 3: { //Rock vs Scissors
                  printf("\nROCK crushes SCISSORS.");
                  printf("\nYou win!");
                  return 1;
                }
                case 4: { //Rock vs Lizard
                  printf("\nROCK crushes LIZARD.");
                  printf("\nYou win!");
                  return 1;
                }
                case 5: { //Rock vs Spock
                  printf("\nSPOCK vaporizes ROCK.");
                  printf("\nYou lose!");
                  return 3;
                }
                default: { //Unknown value
                  printf("\nComputer's move not recognised.");
                  return 4;
                }
              }
              break;
    }
    case 2: { switch (computer_move) {
                case 1: { //Paper vs Rock
                  printf("\nPAPER covers ROCK.");
                  printf("\nYou win!");
                  return 1;
                }
                case 2: { //Paper vs Paper
                  printf("\nIt's a draw!");
                  return 2;
                }
                case 3: { //Paper vs Scissors
                  printf("\nSCISSORS cut PAPER.");
                  printf("\nYou lose!");
                  return 3;
                }
                case 4: { //Paper vs Lizard
                  printf("\nLIZARD eats PAPER.");
                  printf("\nYou lose!");
                  return 3;
                }
                case 5: { //Paper vs Spock
                  printf("\nPAPER disproves SPOCK.");
                  printf("\nYou win!");
                  return 1;
                }
                default: { //Unknown value
                  printf("\nComputer's move not recognised.");
                  return 4;
                }
              }
              break;
    }
    case 3: { switch (computer_move) {
                case 1: { //Scissors vs Rock
                  printf("\nROCK crushes SCISSORS.");
                  printf("\nYou lose!");
                  return 3;
                }
                case 2: { //Scissors vs Paper
                  printf("\nSCISSORS cut PAPER.");
                  printf("\nYou win!");
                  return 1;
                }
                case 3: { //Scissors vs Scissors
                  printf("\nIt's a draw!");
                  return 2;
                }
                case 4: { //Scissors vs Lizard
                  printf("\nSCISSORS decapitate LIZARD.");
                  printf("\nYou win!");
                  return 1;
                }
                case 5: { //Scissors vs Spock
                  printf("\SPOCK smashes SCISSORS.");
                  printf("\nYou lose!");
                  return 3;
                }
                default: { //Unknown value
                  printf("\nComputer's move not recognised.");
                  return 4;
                }
              }
              break;
    }
    case 4: { switch (computer_move) {
                case 1: { //Lizard vs Rock
                  printf("\nROCK crushes LIZARD.");
                  printf("\nYou lose!");
                  return 3;
                }
                case 2: { //Lizard vs Paper
                  printf("\nLIZARD eats PAPER.");
                  printf("\nYou win!");
                  return 1;
                }
                case 3: { //Lizard vs Scissors
                  printf("\nSCISSORS decapitate LIZARD.");
                  printf("\nYou lose!");
                  return 3;
                }
                case 4: { //Lizard vs Lizard
                  printf("\nIt's a draw!");
                  return 2;
                }
                case 5: { //Lizard vs Spock
                  printf("\nLIZARD poisons SPOCK.");
                  printf("\nYou win!");
                  return 1;
                }
                default: {
                  printf("\nComputer's move not recognised.");
                  return 4;
                }
              }
              break;
    }
    case 5: { switch (computer_move) {
                case 1: { //Spock vs Rock
                  printf("\nSPOCK vaporizes ROCK.");
                  printf("\nYou win!");
                  return 1;
                }
                case 2: { //Spock vs Paper
                  printf("\nPAPER disproves SPOCK.");
                  printf("\nYou lose!");
                  return 3;
                }
                case 3: { //Spock vs Scissors
                  printf("\nSPOCK smashes SCISSORS.");
                  printf("\nYou win!");
                  return 1;
                }
                case 4: { //Spock vs Lizard
                  printf("\nLIZARD poisons SPOCK.");
                  printf("\nYou lose!");
                  return 3;
                }
                case 5: { //Spock vs Spock
                  printf("\nIt's a drwa!");
                  return 2;
                }
                default: {
                  printf("\nComputer's move not recognised.");
                  return 4;
                }
              }
              break;
    }
    default: { //Unknown value
      printf("\nPlayer's move not recognised");
      return 4;
    }
  }
}

///@brief Shows the move done by the CPU
void ComputerMoveMessage(struct Player *computer) {
  switch (computer->move) {
    case 1: {
      printf("\n%s plays ROCK", computer->name);
      break;
    }
    case 2: {
      printf("\n%s plays PAPER", computer->name);
      break;
    }
    case 3: {
      printf("\n%s plays SCISSORS", computer->name);
      break;
    }
    case 4: {
      printf("\n%s plays LIZARD", computer->name);
      break;
    }
    case 5: {
      printf("\n%s plays SPOCK", computer->name);
      break;
    }
    default: {
      printf("\nMovement not recognised");
      break;
    }
  }
}

///@brief Shows move represented at the value
void ShowComputerMove(int num) {
  if (num == 1) {
    printf("ROCK      ");
  }
  if (num == 2) {
    printf("PAPER     ");
  }
  if (num == 3) {
    printf("SCISSORS  ");
  }
  if (num == 4) {
    printf("LIZARD    ");
  }
  if (num == 5) {
    printf("SPOCK     ");
  }
}

/**@brief Runs the RPS game

  This function executes the actual RPS game, reading the pointer of enemies
  defined by the parameter. The game runs until list->next_player = NULL
  (user wins) or when user loses any round.

  @return score Quantity of points earned by the user
  @param score Saves the user's score
  @param human Saves user's data and moves
  @param *enemies Depletes the enemies contained in it
*/
int GameStart(int score, struct Player human, struct Player *enemies) {
  ///@brief Auxiliar struct used to read *enemies pointer
  struct Player *aux_enemies = NULL;

  ///@brief Number of rounds of the game
  int round_count = 1;

  ///@brief Saves if the game has ended or not (if user loses or not)
  bool game_ended = false;

  printf("\n");
  for (aux_enemies = enemies; aux_enemies != NULL;
       aux_enemies = aux_enemies->next_player) {
    if (!game_ended && aux_enemies->next_player != NULL) {
      printf("\nROUND %d: vs %s", round_count, aux_enemies->name);
      human.move = PlayerInput();
      ComputerMoveMessage(aux_enemies);
      switch (DetermineMatchWinner(human.move, aux_enemies->move)) {
        case 1: { //Game won
          score = score + 2;
          printf("\nYou've won 2 points. Total: %d\n", score);
          break;
        }
        case 2: { //Tie
          ++score;
          printf("\nYou've won 1 point. Total: %d\n", score);
          break;
        }
        case 3: { //Game lost
          game_ended = true;
          printf(" GAME OVER.");
          printf("\n\nPress any button to see any remaining players:\n");
          break;
        }
        case 4: { //Unknown values, game over
          game_ended = true;
          printf("\nMatch undetermined. GAME OVER.");
          printf("\nPress any button to see any remaining players:\n");
          return 0;
        }
        default: { //Unkwown of the Unknown
          break;
        }
      }
      _getch();
      ++round_count;
    } else if ((aux_enemies->next_player == NULL) && (!game_ended)) {
        printf("\nYou have defeated all CPU's players!!");
        return score;
    } else if (aux_enemies->next_player != NULL) {
        ShowComputerMove(aux_enemies->move);
        printf("%s\n", aux_enemies->name);
    }
  }
  return score;
}

/**@brief Writes user's name and score in a file

  This function just saves name and score of the player in a file called
  "scores.txt".

  @param score User's score
  @param human Saves user's data and moves
*/
void AddScore(int score, struct Player human) {
  FILE *points = fopen("scores.txt", "a");
  fputs(human.name, points);
  fprintf(points, " %2d \n", score);
  fclose(points);
}

int main()
{
  ///@brief Basic struct of the player
  struct Player human = { '\0', 0 };

  ///@brief A pointer that will save all CPU's players
  struct Player *computer = NULL;

  ///@brief As it says, the score of the game
  int score = 0;

  if (!FileExists()) {
    printf("File -states.txt- not found.");
    _getch();
    return 1;
  }
  printf("--------------------------------------\n");
  printf(" Alex Kidd & Sheldon Cooper presents: \n");
  printf("   ROCK-PAPER-SCISSORS-LIZARD-SPOCK   \n");
  printf("--------------------------------------\n");
  printf("         by Sergio Ruiz Roig          \n");
  printf("\nPush any button to start the game.\n");
  _getch();
  human = InputName(human);
  GetComputerStates();
  computer = GetMatchList(computer);
  score = GameStart(score, human, computer);
  AddScore(score, human);
  printf("\n\nFinal score: %d", score);
  _getch();
  return 0;
}
                                                                                