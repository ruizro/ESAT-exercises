/**ROCK-PAPER-SCISSORS GAME
   by Sergio Ruiz Roig

   Version pre 1.0.
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
struct player{
  char name[30];
  int move;
  player *next_player;
};

///@brief Number of moves possible in RPS-game
const int kNumberMoves = 3;

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
struct player InputName(player human) {
  while (strlen(human.name) == 0) {
    printf("Give yourself a name: ");
    fgets(human.name, 30, stdin);
    human.name[strlen(human.name)-1] = 0;
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
  int random_number = 0;
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
struct player* GetMatchList(struct player *list) {
  struct player *aux_list = NULL;
  FILE *usa = fopen("states.txt", "r");
  int state_count = 0;
  
  list = new (player);
  list->next_player = NULL;

  while (!feof(usa)) {
    aux_list = new (player);
    aux_list->next_player = NULL;
    fread(&aux_list->name, sizeof(aux_list->name), 1, usa);
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
  move. The function repeats if the char isn't R, P or S.

  @return value Number of the move. 1 - Rock, 2 - Paper, 3 - Scissors
*/
int PlayerInput() {
  char player_move = '\0';
  
  printf("\n");
  while (player_move != 'r' || player_move != 's' || player_move != 'p') {
    printf("What's your move? (R/P/S): ");
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
                //Rock vs Rock
                case 1: {
                  printf("\nIt's a draw!");
                  return 2;
                }
                //Rock vs Paper
                case 2: {
                  printf("\nPAPER covers ROCK.");
                  printf("\nYou lose!");
                  return 3;
                }
                //Rock vs Scissors
                case 3: {
                  printf("\nROCK crushes SCISSORS.");
                  printf("\nYou win!");
                  return 1;
                }
                //Unknown value
                default: {
                  printf("\nComputer's move not recognised.");
                  return 4;
                }
              }
              break;
    }
    case 2: { switch (computer_move) {
                //Paper vs Rock
                case 1: {
                  printf("\nPAPER covers ROCK.");
                  printf("\nYou win!");
                  return 1;
                }
                //Paper vs Paper
                case 2: {
                  printf("\nIt's a draw!");
                  return 2;
                }
                //Paper vs Scissors
                case 3: {
                  printf("\nSCISSORS cut paper.");
                  printf("\nYou lose!");
                  return 3;
                }
                //Unknown value
                default: {
                  printf("\nComputer's move not recognised.");
                  return 4;
                }
              }
              break;
    }
    case 3: { switch (computer_move) {
                //Scissors vs Rock
                case 1: {
                  printf("\nROCK crushes SCISSORS.");
                  printf("\nYou lose!");
                  return 3;
                }
                //Scissors vs Paper
                case 2: {
                  printf("\nSCISSORS cut paper.");
                  printf("\nYou win!");
                  return 1;
                }
                //Scissors vs Scissors
                case 3: {
                  printf("\nIt's a draw!");
                  return 2;
                }
                //Unknown value
                default: {
                   printf("\nComputer's move not recognised.");
                   return 4;
                }
              }
              break;
    }
    //Unknown value
    default: {
      printf("\nPlayer's move not recognised");
      return 4;
    }
  }
}

///@brief Shows the move done by the CPU
void ComputerMoveMessage(struct player *computer) {
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
}

int GameStart(int score, struct player human, struct player *enemies) {
  struct player *aux_enemies = NULL;
  int round_count = 1;
  bool game_ended = false;

  printf("\n");
  for (aux_enemies = enemies; aux_enemies != NULL; aux_enemies = aux_enemies->next_player) {
    if (!game_ended && aux_enemies->next_player != NULL) {
      printf("\nROUND %d: vs %s", round_count, aux_enemies->name);
      human.move = PlayerInput();
      ComputerMoveMessage(aux_enemies);
      switch (DetermineMatchWinner(human.move, aux_enemies->move)) {
        case 1: { //Game won
          score = score + 2;
          printf("\nYou've won 2 points. Total: %d\n",score);
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
      printf("%s\n",aux_enemies->name);
    }
  }
  return score;
}

void AddScore(struct player human, int score) {
  FILE *points = fopen("scores.txt", "a");
  fputs(human.name, points);
  fprintf(points, " %2d \n", score);
  fclose(points);
}

int main()
{
  struct player human = { '\0', 0 };
  struct player *computer = NULL;

  int score = 0;
  bool endgame = false;
  
  if (!FileExists()) {
    printf("File -states.txt- not found.");
    _getch();
    return 1;
  }
  printf("-----------------------------\n");
  printf("     Alex Kidd presents:     \n");
  printf("     ROCK-PAPER-SCISSORS     \n");
  printf("-----------------------------\n");
  printf("     by Sergio Ruiz Roig     \n");
  printf("\nPush any button to start the game.\n");
  _getch();
  human = InputName(human);
  GetComputerStates();
  computer = GetMatchList(computer);
  score= GameStart(score, human, computer);
  AddScore(human, score);
  printf("\n\nFinal score: %d", score);
  _getch();
  return 0;
}