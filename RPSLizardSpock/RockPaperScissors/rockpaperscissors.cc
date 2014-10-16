/**ROCK-PAPER-SCISSORS-LIZARD-SPOCK GAME
          by Sergio Ruiz Roig
              Version 1.1.

  -> Work in progress
*/
#define _CRT_SECURE_NO_WARNINGS

#include "rockpaperscissors.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

///@brief Structure of an RPS player
struct Player {
  char name[kStringWidth];
  int move;
  Player *next_player;
};

///@brief Shows the game's logo
void GameLogo() {
  printf("--------------------------------------\n");
  printf(" Alex Kidd & Sheldon Cooper presents: \n");
  printf("   ROCK-PAPER-SCISSORS-LIZARD-SPOCK   \n");
  printf("--------------------------------------\n");
  printf("         by Sergio Ruiz Roig          \n");
  printf("\nPush any button to start the game.\n");
  _getch();
}

/**@brief Gives a name for the human player

  This function uses a string for give the player a name.
  The process just repeats itself until the string isn't empty

  @return human Player's name
  @param human Player's structure
//*/
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
  @param num_opponents Total of players
*/
bool StateExists(int sequence[kNumberOpponents], int num_state,
                 int num_opponents) {
  for (int j = 0; j < num_opponents; ++j) {
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
bool FileExists(const char* file_name) {
  ///@brief File we want to know if exists
  FILE *file = fopen(file_name, "r");

  if (file == NULL) {
    return false;
  } else {
    fclose(file);
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
  for (int i = 0; i < kNumberOpponents; ++i) {
    state_found = true;
    while (state_found) {
      random_number = rand() % kNumberStates;
      if (!StateExists(list_states, random_number, kStringWidth)) {
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

  list = new Player;
  list->next_player = NULL;

  while (!feof(usa)) {
    aux_list = new Player;
    aux_list->next_player = NULL;
    fread(&aux_list->name, sizeof(aux_list->name), 1, usa);
    aux_list->name[strlen(aux_list->name) - 10] = '\0';
    if (!feof(usa) && StateExists(list_states, state_count, kNumberOpponents)) {
      aux_list->move = rand() % kNumberMoves;
      aux_list->next_player = list;
      list = aux_list;
    }
    ++state_count;
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
        return 0;
      }
      case 'p': case 'P': {
        printf("You've played PAPER.");
        return 1;
      }
      case 's': case 'S': {
        printf("You've played SCISSORS.");
        return 2;
      }
      case 'l': case 'L': {
        printf("You've played LIZARD.");
        return 3;
      }
      case 'k': case 'K': {
        printf("You've played SPOCK.");
        return 4;
      }
      default: {
        break;
      }
    }
  }
}

///@brief Shows the move done by the CPU
void ComputerMoveMessage(struct Player *computer) {
  switch (computer->move) {
    case 0: {
      printf("\n%s plays ROCK", computer->name);
      break;
    }
    case 1: {
      printf("\n%s plays PAPER", computer->name);
      break;
    }
    case 2: {
      printf("\n%s plays SCISSORS", computer->name);
      break;
    }
    case 3: {
      printf("\n%s plays LIZARD", computer->name);
      break;
    }
    case 4: {
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
  if (num == 0) {
    printf("ROCK      ");
  }
  if (num == 1) {
    printf("PAPER     ");
  }
  if (num == 2) {
    printf("SCISSORS  ");
  }
  if (num == 3) {
    printf("LIZARD    ");
  }
  if (num == 4) {
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
      switch (tableresults[human.move][aux_enemies->move]) {
        case 1: { //Game won
          score = score + kVictoryPoints;
          printf("\nYou've won %d points. Total: %d\n", kVictoryPoints, score);
          break;
        }
        case 2: { //Tie
          score = score + kTiePoints;
          printf("\nYou've won %d point. Total: %d\n", kTiePoints, score);
          break;
        }
        case 3: { //Game lost
          game_ended = true;
          printf("\n -GAME OVER-.");
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
void SaveScore(int score, struct Player human, char* name_file) {
  FILE *file = fopen(name_file, "a");
  fputs(human.name, file);
  fprintf(file, " %3d \n", score);
  fclose(file);
}

int main()
{
  ///@brief Basic struct of the player
  struct Player human = { '\0', 0 };

  ///@brief A pointer that will save all CPU's players
  struct Player *computer = NULL;

  ///@brief As it says, the score of the game
  int score = 0;

  if (!FileExists("states.txt")) {
    printf("File -states.txt- not found.");
    _getch();
    return 1;
  }
  GameLogo();
  human = InputName(human);
  GetComputerStates();
  computer = GetMatchList(computer);
  score = GameStart(score, human, computer);
  SaveScore(score, human, "scores.txt");
  printf("\n\nFinal score: %d", score);
  _getch();
  return 0;
}
                                                                                
  ////// COSAS POR HACER /////////////////////////////////////////////////////
  /// -> Modo para poder seleccionar nº de jugadores                       ///
  /// -> Cambiar InputName de devolver struct al char (cadena)             ///
  /// -> Añadir parámetro de longitud de la array a StateExists            ///
  /// -> Ajustar cadenas para que tengan a posteriori 1 sólo espacio       ///
  /// -> Buscar memset()                                                   ///
  ////////////////////////////////////////////////////////////////////////////         