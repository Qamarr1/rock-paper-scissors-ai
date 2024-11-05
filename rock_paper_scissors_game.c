#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#define ROCK 'R'
#define PAPER 'P'
#define SCISSOR 'S'
#define PLAYER1_WIN 1
#define PLAYER2_WIN 2
#define DRAW 0

// ANSI escape codes for text colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Function declarations
int rock_paper_scissor(char player1, char player2);
char get_user_input(const char* player_prompt, int hide_input);
void print_word(char v);
void print_colorful_result(int result, int is_ai_game);
char getch();
void print_final_scores(int player1_score, int player2_score, int is_ai_game);
void declare_winner(int player1_score, int player2_score, int is_ai_game);
void play_against_ai();
void play_multiplayer();
void display_history(char player1_history[], char player2_history[], int rounds_played, int is_ai_game);
void clear_input_buffer();

// Function to read a character without echoing to the terminal
char getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) {
        perror("tcsetattr()");
    }
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr ICANON");
    }
    if (read(0, &buf, 1) < 0) {
        perror("read()");
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror("tcsetattr ~ICANON");
    }
    return buf;
}

// Function to clear the input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    srand(time(0));  // Initialize random seed

    printf("WELCOME TO THE ROCK-PAPER-SCISSORS GAME\n");
    printf("If the game is in multiplayer mode:\n");
    printf("If the game is draw, the message will be displayed in red.\n");
    printf("If Player 1 wins the game, the message will be displayed in green.\n");
    printf("If Player 2 wins the game, the message will be displayed in red.\n");
    printf("If the game is in AI(A) mode:\n");
    printf("If the game is draw, the message will be displayed in red.\n");
    printf("If User wins the game, the message will be displayed in green.\n");
    printf("If AI wins the game, the message will be displayed in red.\n");
    printf("Press 'M' for multiplayer or 'A' to play against AI: ");

    while (1) {
        char start;
        while (1) {
            start = getchar();
            clear_input_buffer();
            start = toupper(start);
            if (start == 'M') {
                play_multiplayer();
                break;
            } else if (start == 'A') {
                printf(ANSI_COLOR_YELLOW "AI Mode Active\n" ANSI_COLOR_RESET);
                play_against_ai();
                break;
            } else {
                printf("Invalid input, please enter 'M' for multiplayer or 'A' to play against AI.\n");
            }
        }

        char play_again;
        while (1) {
            printf("Do you want to play again? Press 'Y' to play again, 'N' to exit: ");
            play_again = getchar();
            clear_input_buffer();
            play_again = toupper(play_again);
            if (play_again == 'Y' || play_again == 'N') {
                break;
            }
            printf("Invalid input, please enter 'Y' or 'N'.\n");
        }

        if (play_again == 'N') {
            printf("Exiting the game. Goodbye!\n");
            return 0;
        }
    }

    return 0;
}

// Main game loop for multiplayer mode
void play_multiplayer() {
    int player1_score = 0, player2_score = 0;
    int quit = 0;

    while (!quit) {
        int round = 1;
        int player1_round_wins = 0, player2_round_wins = 0;
        int rounds_played = 0;
        char player1_history[100], player2_history[100];

        // Play 3 rounds
        while (rounds_played < 3) {
            printf("\nRound %d\n", round);
            printf("Player 1's turn:\n");
            char player1_input = get_user_input("Choose an option (input will be hidden):\nR. Rock\nP. Paper\nS. Scissor\n", 1);

            printf("Player 2's turn:\n");
            char player2_input = get_user_input("Choose an option (input will be hidden):\nR. Rock\nP. Paper\nS. Scissor\n", 1);

            player1_history[rounds_played] = player1_input;
            player2_history[rounds_played] = player2_input;

            printf("Both players have made their choices.\n");

            int result = rock_paper_scissor(player1_input, player2_input);

            printf("Player 1 chose: ");
            print_word(player1_input);
            printf("Player 2 chose: ");
            print_word(player2_input);

            print_colorful_result(result, 0);

            if (result == PLAYER1_WIN) {
                player1_round_wins++;
            } else if (result == PLAYER2_WIN) {
                player2_round_wins++;
            }

            round++;
            rounds_played++;

            // If a player wins the first two rounds, prompt to play again
            if (player1_round_wins == 2 || player2_round_wins == 2) {
                break;
            }
        }

        player1_score += player1_round_wins;
        player2_score += player2_round_wins;

        printf("\n--------------------------------------------------\n");
        printf("Player 1 score: %d\n", player1_score);
        printf("Player 2 score: %d\n", player2_score);
        printf("--------------------------------------------------\n");

        display_history(player1_history, player2_history, rounds_played, 0);

        declare_winner(player1_score, player2_score, 0);
        
        while (1) {
            printf("\nDo you want to play another set of rounds? Press 'Y' to continue, 'N' to terminate: ");
            char start = getchar();
            clear_input_buffer();
            start = toupper(start);
            if (start == 'Y' || start == 'N') {
                if (start == 'N') {
                    quit = 1;
                }
                break;
            }
            printf("Invalid input, please enter 'Y' or 'N'.\n");
        }
    }

    print_final_scores(player1_score, player2_score, 0);
}

// Main game loop for AI mode
void play_against_ai() {
    int player_score = 0, ai_score = 0;
    int quit = 0;

    while (!quit) {
        int round = 1;
        int player_round_wins = 0, ai_round_wins = 0;
        int rounds_played = 0;
        char player_history[100], ai_history[100];

        // Play 3 rounds
        while (rounds_played < 3) {
            printf("\nRound %d\n", round);
            printf("Your turn:\n");
            char player_input = get_user_input("Choose an option:\nR. Rock\nP. Paper\nS. Scissor\n", 0);

            char ai_input = "RPS"[rand() % 3];
            ai_history[rounds_played] = ai_input;

            player_history[rounds_played] = player_input;

            printf("Both you and the AI have made your choices.\n");

            int result = rock_paper_scissor(player_input, ai_input);

            printf("You chose: ");
            print_word(player_input);
            printf("AI chose: ");
            print_word(ai_input);

            print_colorful_result(result, 1);

            if (result == PLAYER1_WIN) {
                player_round_wins++;
            } else if (result == PLAYER2_WIN) {
                ai_round_wins++;
            }

            round++;
            rounds_played++;

            // If a player wins the first two rounds, prompt to play again
            if (player_round_wins == 2 || ai_round_wins == 2) {
                break;
            }
        }

        player_score += player_round_wins;
        ai_score += ai_round_wins;

        printf("\n--------------------------------------------------\n");
        printf("Your score: %d\n", player_score);
        printf("AI score: %d\n", ai_score);
        printf("--------------------------------------------------\n");

        display_history(player_history, ai_history, rounds_played, 1);

        declare_winner(player_score, ai_score, 1);
        
        while (1) {
            printf("\nDo you want to play another set of rounds? Press 'Y' to continue, 'N' to terminate: ");
            char start = getchar();
            clear_input_buffer();
            start = toupper(start);
            if (start == 'Y' || start == 'N') {
                if (start == 'N') {
                    quit = 1;
                }
                break;
            }
            printf("Invalid input, please enter 'Y' or 'N'.\n");
        }
    }

    print_final_scores(player_score, ai_score, 1);
}

// Function to print the word corresponding to the choice
void print_word(char v) {
    switch (v) {
        case ROCK:
            printf("Rock\n");
            break;
        case PAPER:
            printf("Paper\n");
            break;
        case SCISSOR:
            printf("Scissor\n");
            break;
    }
}

// Function to determine the result of a round
int rock_paper_scissor(char player1, char player2) {
    if (player1 == ROCK && player2 == PAPER) {
        return PLAYER2_WIN;
    } else if (player1 == ROCK && player2 == SCISSOR) {
        return PLAYER1_WIN;
    } else if (player1 == PAPER && player2 == ROCK) {
        return PLAYER1_WIN;
    } else if (player1 == PAPER && player2 == SCISSOR) {
        return PLAYER2_WIN;
    } else if (player1 == SCISSOR && player2 == ROCK) {
        return PLAYER2_WIN;
    } else if (player1 == SCISSOR && player2 == PAPER) {
        return PLAYER1_WIN;
    } else {
        return DRAW;
    }
}

// Function to get user input
char get_user_input(const char *player_prompt, int hide_input) {
    char choice;
    do {
        printf("%s", player_prompt);
        if (hide_input) {
            choice = toupper(getch());  // Read input without echoing and convert to uppercase
            printf("\n");  // Newline for better readability
        } else {
            choice = getchar();
            clear_input_buffer();
            choice = toupper(choice);
        }

        if (choice != 'R' && choice != 'P' && choice != 'S') {
            printf("Invalid input, please enter R, P, or S.\n");
        }
    } while (choice != 'R' && choice != 'P' && choice != 'S');

    return choice;
}

// Function to print the result of a round in color
void print_colorful_result(int result, int is_ai_game) {
    switch (result) {
        case DRAW:
            printf(ANSI_COLOR_BLUE "It is a draw.\n" ANSI_COLOR_RESET);
            break;
        case PLAYER1_WIN:
            if (is_ai_game) {
                printf(ANSI_COLOR_GREEN "User wins and AI loses the round.\n" ANSI_COLOR_RESET);
            } else {
                printf(ANSI_COLOR_GREEN "Player 1 wins and Player 2 loses the round.\n" ANSI_COLOR_RESET);
            }
            break;
        case PLAYER2_WIN:
            if (is_ai_game) {
                printf(ANSI_COLOR_RED "AI wins and User loses the round.\n" ANSI_COLOR_RESET);
            } else {
                printf(ANSI_COLOR_RED "Player 2 wins and Player 1 loses the round.\n" ANSI_COLOR_RESET);
            }
            break;
        default:
            printf("Unexpected result code.\n");
    }
}

// Function to print the final scores at the end of the game
void print_final_scores(int player1_score, int player2_score, int is_ai_game) {
    printf("\nFinal Score...\n");
    printf("--------------------------------------------------\n");
    if (is_ai_game) {
        printf("User score: %d\n", player1_score);
        printf("AI score: %d\n", player2_score);
    } else {
        printf("Player 1 score: %d\n", player1_score);
        printf("Player 2 score: %d\n", player2_score);
    }
    printf("--------------------------------------------------\n");

    if (player1_score == player2_score) {
        printf(ANSI_COLOR_BLUE "GAME WAS A DRAW\n" ANSI_COLOR_RESET);
    } else if (player1_score > player2_score) {
        if (is_ai_game) {
            printf(ANSI_COLOR_GREEN "USER WINS THE GAME\n" ANSI_COLOR_RESET);
        } else {
            printf(ANSI_COLOR_GREEN "PLAYER 1 WINS THE GAME\n" ANSI_COLOR_RESET);
        }
    } else {
        if (is_ai_game) {
            printf(ANSI_COLOR_RED "AI WINS THE GAME\n" ANSI_COLOR_RESET);
        } else {
            printf(ANSI_COLOR_RED "PLAYER 2 WINS THE GAME\n" ANSI_COLOR_RESET);
        }
    }
}

// Function to declare the current leader during the game
void declare_winner(int player1_score, int player2_score, int is_ai_game) {
    if (player1_score > player2_score) {
        if (is_ai_game) {
            printf(ANSI_COLOR_GREEN "User is currently leading!\n" ANSI_COLOR_RESET);
        } else {
            printf(ANSI_COLOR_GREEN "Player 1 is currently leading!\n" ANSI_COLOR_RESET);
        }
    } else if (player2_score > player1_score) {
        if (is_ai_game) {
            printf(ANSI_COLOR_RED "AI is currently leading!\n" ANSI_COLOR_RESET);
        } else {
            printf(ANSI_COLOR_RED "Player 2 is currently leading!\n" ANSI_COLOR_RESET);
        }
    } else {
        printf(ANSI_COLOR_BLUE "The game is currently a draw!\n" ANSI_COLOR_RESET);
    }
}

// Function to display the history of rounds
void display_history(char player1_history[], char player2_history[], int rounds_played, int is_ai_game) {
    printf("\nRound History:\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < rounds_played; i++) {
        printf("Round %d: ", i + 1);
        if (is_ai_game) {
            printf("User chose ");
            print_word(player1_history[i]);
            printf("AI chose ");
            print_word(player2_history[i]);
        } else {
            printf("Player 1 chose ");
            print_word(player1_history[i]);
            printf("Player 2 chose ");
            print_word(player2_history[i]);
        }
    }
    printf("--------------------------------------------------\n");
}
