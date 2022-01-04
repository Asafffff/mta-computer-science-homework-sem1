#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Player Properties */
#define FIRST_NAME_MAX_LENGTH 20
#define UNINITIALIZED_PLAYER_INDEX -1
#define ACTION_WITHDRAW_FROM_DECK 0
#define ACTION_FINISH_OPEN_TAKI 0

/* Card Properties */
#define INITIAL_NUMBER_OF_CARDS 4
#define CARD_MAX_STRING_LENGTH 6
#define NUMBER_OF_UNIQUE_CARD_VALUES 14
#define NUMBER_OF_UNIQUE_CARD_COLORS 4
#define RANDOM_CARD_VALUE -1
#define TAKI_CARD "TAKI"
#define TAKI_CARD_VALUE 0
#define COLOR_CHANGE_CARD "COLOR"
#define COLOR_CHANGE_CARD_VALUE 10
#define STOP_CARD "STOP"
#define STOP_CARD_VALUE 11
#define PLUS_CARD "+"
#define PLUS_CARD_VALUE 12
#define DIRECTION_CHANGE_CARD "<->"
#define DIRECTION_CHANGE_CARD_VALUE 13

/* Colors */
#define NO_COLOR -1
#define NO_COLOR_STRING ""
#define RED 0
#define RED_STRING "R"
#define GREEN 1
#define GREEN_STRING "G"
#define BLUE 2
#define BLUE_STRING "B"
#define YELLOW 3
#define YELLOW_STRING "Y"

struct GameSettings {
  bool isGameOver;
  bool isStopNextPlayerTurn;
  bool isRoundDirectionClockwise;
  int numberOfPlayers;
  int withdrawnCardsStatistics[NUMBER_OF_UNIQUE_CARD_VALUES];
};
typedef struct GameSettings GameSettings;

struct Card {
  int value;
  int color;
};
typedef struct Card CARD;

struct CardStatistics {
  char cardValue[CARD_MAX_STRING_LENGTH];
  int numberOfWithdrawals;
};
typedef struct CardStatistics CARD_STATISTICS;

struct Player {
  char firstName[FIRST_NAME_MAX_LENGTH];
  CARD* cards;
  int numberOfCards;
};
typedef struct Player PLAYER;

void printWelcomeMessage();
int getNumberOfPlayersFromInput();
void initPlayersByNumberOfPlayers(PLAYER players[], int numberOfPlayers);
PLAYER getPlayerFirstNameFromInput(PLAYER player, int playerNumber);
PLAYER initPlayerCards(PLAYER player);
CARD getRandomCard();
CARD getCardByValue(int value, int color);
CARD getOpeningCard();
void printCard(CARD card);
void printCardBorder(int borderWidth);
void printCardEmptySeparator(int separatorWidth);
void getCardValueInText(CARD card, char cardValueInText[]);
void getCardColorInText(CARD card, char cardColorInText[]);
void printCardWithInnerTextValue(char innerText[], int cardWidth);
int mapStupidUnorderedChangeColorResults(int unorderedColorValue);
void executeOpenTaki(PLAYER* player, int cardIndex, CARD* heapUpperCardPtr, GameSettings* globalGameSettings);
void executeChangeColor(PLAYER* player, int cardIndex, CARD* heapUpperCardPtr);
void executePlusCard(PLAYER* player, int cardIndex, CARD* heapUpperCardPtr, GameSettings* globalGameSettings);
void executeStopCard(PLAYER* player, int cardIndex, CARD* heapUpperCardPtr, GameSettings* globalGameSettings);
void executeChangeDirection(GameSettings* globalGameSettings);
void printPlayerCards(PLAYER player);
PLAYER playerPlayTurn(PLAYER player, CARD* heapUpperCardPtr, GameSettings* globalGameSettings);
void removeCardFromPlayerDeck(PLAYER* player, int cardIndex);
bool isValidNextCard(CARD chosenCard, CARD* heapUpperCardPtr);
void withdrawCardFromDeck(PLAYER* player, int cardValue, GameSettings* globalGameSettings);
PLAYER executeCardAction(PLAYER player, int cardIndex, CARD* heapUpperCardPtr, bool* isTurnedFinishedPtr,
                         GameSettings* globalGameSettings);
int getPlayerActionChoice();
void mergeSort(CARD_STATISTICS arr[], int size);
void merge(CARD_STATISTICS arr1[], int size1, CARD_STATISTICS arr2[], int size2, CARD_STATISTICS resultArr[]);
void copyCardStatisticsArrays(CARD_STATISTICS fromArr[], CARD_STATISTICS toArr[], int size);
void printHeapUpperCard(CARD heapUpperCard);
int getIndexOfNextPlayer(int currentPlayerIndex, GameSettings* globalGameSettings);
void buildGameStatistics(int withdrawnCardsStatistics[], CARD_STATISTICS orderedWithdrawnCardsStatistics[]);
void printGameStatistics(CARD_STATISTICS orderedWithdrawnCardsStatistics[]);
void checkAlloc(CARD* pointer);
void* customRealloc(CARD* oldArray, int currentSize, int newSize);

void main() {
  GameSettings globalGameSettings = {.isGameOver = false,
                                     .isStopNextPlayerTurn = false,
                                     .isRoundDirectionClockwise = true,
                                     .numberOfPlayers = 0,
                                     .withdrawnCardsStatistics = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  CARD heapUpperCard;
  CARD openingCard;
  CARD_STATISTICS orderedWithdrawnCardsStatistics[NUMBER_OF_UNIQUE_CARD_VALUES];
  int i;

  srand(time(NULL));

  printWelcomeMessage();
  globalGameSettings.numberOfPlayers = getNumberOfPlayersFromInput();

  PLAYER players[globalGameSettings.numberOfPlayers];

  initPlayersByNumberOfPlayers(players, globalGameSettings.numberOfPlayers);

  heapUpperCard = getOpeningCard();

  int currentPlayerIndex = UNINITIALIZED_PLAYER_INDEX;
  while (!globalGameSettings.isGameOver) {
    currentPlayerIndex = getIndexOfNextPlayer(currentPlayerIndex, &globalGameSettings);

    printHeapUpperCard(heapUpperCard);

    PLAYER player = players[currentPlayerIndex];
    player = playerPlayTurn(player, &heapUpperCard, &globalGameSettings);

    if (player.numberOfCards == 0) {
      globalGameSettings.isGameOver = true;
      printf("The winner is... %s! Congratulations!\n", player.firstName);
    }

    players[currentPlayerIndex] = player;
  }

  // Free the allocated memory of players cards
  for (i = 0; i < globalGameSettings.numberOfPlayers; i++) {
    free(players[i].cards);
    players[i].cards = NULL;
  }

  buildGameStatistics(globalGameSettings.withdrawnCardsStatistics, orderedWithdrawnCardsStatistics);
  printGameStatistics(orderedWithdrawnCardsStatistics);
}

/**
 * @brief Prints welcome message
 *
 */
void printWelcomeMessage() {
  printf("************ Welcome to TAKI game !!! ************\n");
}

/**
 * @brief Get the Number Of Players From Input
 *
 * @return int number of players
 */
int getNumberOfPlayersFromInput() {
  int numberOfPlayers;

  printf("Please enter the number of players:\n");
  scanf("%d", &numberOfPlayers);

  return numberOfPlayers;
}

/**
 * @brief Initialize Players, by Number Of Players
 *
 * @param players Array of players to fill
 * @param numberOfPlayers Number of players
 */
void initPlayersByNumberOfPlayers(PLAYER players[], int numberOfPlayers) {
  int i;

  for (i = 0; i < numberOfPlayers; i++) {
    players[i] = getPlayerFirstNameFromInput(players[i], i + 1);
    players[i] = initPlayerCards(players[i]);
  }

  return;
}

/**
 * @brief Get the Player First Name From Input object
 *
 * @param player player struct
 * @param playerNumber the number of the player
 * @return PLAYER modified player with the first name
 */
PLAYER getPlayerFirstNameFromInput(PLAYER player, int playerNumber) {
  printf("Please enter the first name of player #%d:\n", playerNumber);
  scanf("%s", player.firstName);

  return player;
}

/**
 * @brief Initialize Player Cards
 *
 * @param player player struct
 * @return PLAYER modified player with the cards
 */
PLAYER initPlayerCards(PLAYER player) {
  int i;
  CARD *cards, card;
  cards = (CARD*)malloc(INITIAL_NUMBER_OF_CARDS * sizeof(CARD));
  checkAlloc(cards);

  for (i = 0; i < INITIAL_NUMBER_OF_CARDS; i++) {
    card = getRandomCard();
    cards[i] = card;
  }

  player.cards = cards;
  player.numberOfCards = INITIAL_NUMBER_OF_CARDS;

  return player;
}

/**
 * @brief Get a predefined card
 *
 * @return CARD
 */
CARD getCardByValue(int value, int color) {
  CARD card;

  card.value = value;
  card.color = color;

  return card;
}

/**
 * @brief Get a Random Card struct
 *
 * @return CARD
 */
CARD getRandomCard() {
  CARD card;

  int cardValueRandomNumber = rand() % NUMBER_OF_UNIQUE_CARD_VALUES, cardColorRandomNumber;
  card.value = cardValueRandomNumber;

  if (card.value != COLOR_CHANGE_CARD_VALUE) {
    cardColorRandomNumber = rand() % NUMBER_OF_UNIQUE_CARD_COLORS;
    card.color = cardColorRandomNumber;
  } else {
    card.color = NO_COLOR;
  }

  return card;
}

/**
 * @brief Get the Opening Card struct, which can only be a number between 1-9
 *
 * @return CARD
 */
CARD getOpeningCard() {
  CARD card;

  while (true) {
    card = getRandomCard();

    // Check if card value is a regular number, and not a special card
    if (card.value > 0 && card.value < 10) {
      break;
    }
  }

  return card;
}

/**
 * @brief Print card by predefined width
 *
 * @param card card to print
 */
void printCard(CARD card) {
  int i, j;
  int cardWidth = 9;

  char cardValueInText[CARD_MAX_STRING_LENGTH];
  char cardColorInText[CARD_MAX_STRING_LENGTH];

  getCardValueInText(card, cardValueInText);
  getCardColorInText(card, cardColorInText);

  printCardBorder(cardWidth);
  printCardEmptySeparator(cardWidth);
  printCardWithInnerTextValue(cardValueInText, cardWidth);
  printCardWithInnerTextValue(cardColorInText, cardWidth);
  printCardEmptySeparator(cardWidth);
  printCardBorder(cardWidth);
}

/**
 * @brief Prints card border
 *
 * @param borderWidth width of the border
 */
void printCardBorder(int borderWidth) {
  int i;

  for (i = 0; i < borderWidth; i++) {
    printf("*");
  }
  printf("\n");
}

/**
 * @brief Prints border only on margins, and fill with empty spaces.
 *
 * @param separatorWidth width of the separator line
 */
void printCardEmptySeparator(int separatorWidth) {
  int i;

  for (i = 0; i < separatorWidth; i++) {
    // If it is the first or last iteration, print the border, else, print an empty space.
    if (i == 0 || i == separatorWidth - 1) {
      printf("*");
    } else {
      printf(" ");
    }
  }
  printf("\n");
}

/**
 * @brief Get the Card Value In String
 *
 * @param card Card to get the value of
 * @param cardValueInText An array to store the string value into
 */
void getCardValueInText(CARD card, char cardValueInText[]) {
  switch (card.value) {
    case 0:
      strcpy(cardValueInText, TAKI_CARD);
      break;
    case 1:
      strcpy(cardValueInText, "1");
      break;
    case 2:
      strcpy(cardValueInText, "2");
      break;
    case 3:
      strcpy(cardValueInText, "3");
      break;
    case 4:
      strcpy(cardValueInText, "4");
      break;
    case 5:
      strcpy(cardValueInText, "5");
      break;
    case 6:
      strcpy(cardValueInText, "6");
      break;
    case 7:
      strcpy(cardValueInText, "7");
      break;
    case 8:
      strcpy(cardValueInText, "8");
      break;
    case 9:
      strcpy(cardValueInText, "9");
      break;
    case 10:
      strcpy(cardValueInText, COLOR_CHANGE_CARD);
      break;
    case 11:
      strcpy(cardValueInText, STOP_CARD);
      break;
    case 12:
      strcpy(cardValueInText, PLUS_CARD);
      break;
    case 13:
      strcpy(cardValueInText, DIRECTION_CHANGE_CARD);
      break;
  }
}

/**
 * @brief Get the Card Color In String
 *
 * @param card Card to get the value of
 * @param cardValueInText An array to store the string color into
 */
void getCardColorInText(CARD card, char cardColorInText[]) {
  switch (card.color) {
    case RED:
      strcpy(cardColorInText, RED_STRING);
      break;
    case GREEN:
      strcpy(cardColorInText, GREEN_STRING);
      break;
    case BLUE:
      strcpy(cardColorInText, BLUE_STRING);
      break;
    case YELLOW:
      strcpy(cardColorInText, YELLOW_STRING);
      break;
    case NO_COLOR:
      strcpy(cardColorInText, NO_COLOR_STRING);
      break;
  }
}

/**
 * @brief Prints card with inner text
 *
 * @param innerText Text to write between the borders
 * @param cardWidth desired width of the card
 */
void printCardWithInnerTextValue(char innerText[], int cardWidth) {
  int i, j;

  int cardValueInTextLength = strlen(innerText);

  if (cardWidth - 2 - cardValueInTextLength <= 0) {
    printf("ERROR: Card width is too small to print the card value.\n");
    exit(-1);
  }

  for (i = 0; i < cardWidth - cardValueInTextLength + 1; i++) {
    // If it is the first or last iteration, print the border
    if (i == 0 || i == cardWidth - cardValueInTextLength) {
      printf("*");
    } else {
      // Print card inner text, depending on inner text length.
      if (i == (cardWidth - cardValueInTextLength) / 2) {
        // If the card value length is even, print the card value with a preceding space, and skip one iteration.
        // Else, print the card value normally.
        if (cardValueInTextLength % 2 == 0) {
          printf(" %s", innerText);
          i++;
        } else {
          printf("%s", innerText);
        }
      } else {
        // Print an empty space on the margins of the inner text.
        printf(" ");
      }
    }
  }
  printf("\n");
}

/**
 * @brief Map the unordered requirements of colors to their original values
 *
 * @param unorderedColorValue Unordered color value
 * @return int Ordered color value
 */
int mapStupidUnorderedChangeColorResults(int unorderedColorValue) {
  switch (unorderedColorValue) {
    case 1:
      return YELLOW;
    case 2:
      return RED;
    case 3:
      return BLUE;
    case 4:
      return GREEN;
    default:
      return NO_COLOR;
  }
}

/**
 * @brief Execute color changing card
 *
 * @param player Player who executes the command
 * @param cardIndex Index of the card to execute, in the player's deck
 * @param heapUpperCardPtr Pointer to the upper card of the game's heap
 */
void executeChangeColor(PLAYER* player, int cardIndex, CARD* heapUpperCardPtr) {
  int newColor;
  CARD card = player->cards[cardIndex];

  if (card.value != COLOR_CHANGE_CARD_VALUE) {
    printf("ERROR: The card is not a color change card.\n");
    return;
  }

  while (true) {
    printf("Please enter your color choice:\n"
           "1 - Yellow\n"
           "2 - Red\n"
           "3 - Blue\n"
           "4 - Green\n");

    scanf("%d", &newColor);

    if (newColor >= 1 && newColor <= 4) {
      break;
    }
  }

  card.color = mapStupidUnorderedChangeColorResults(newColor);

  *heapUpperCardPtr = card;
  removeCardFromPlayerDeck(player, cardIndex);

  return;
}

/**
 * @brief Prints the cards of a player
 *
 * @param player Player to print the cards of
 */
void printPlayerCards(PLAYER player) {
  int i;

  for (i = 0; i < player.numberOfCards; i++) {
    printf("Card #%d:\n", i + 1);
    printCard(player.cards[i]);
    printf("\n");
  }
}

/**
 * @brief Remove a card from a player's deck
 *
 * @param player Player to remove the card from
 * @param cardIndex Index of the card to remove
 */
void removeCardFromPlayerDeck(PLAYER* player, int cardIndex) {
  int i;

  for (i = cardIndex; i < player->numberOfCards - 1; i++) {
    player->cards[i] = player->cards[i + 1];
  }

  player->cards = customRealloc(player->cards, player->numberOfCards, player->numberOfCards - 1);

  player->numberOfCards -= 1;
  return;
}

/**
 * @brief The action of playing the turn of a player
 *
 * @param player A player who plays the turn
 * @param heapUpperCardPtr Pointer to the upper card of the game's heap
 * @return PLAYER modified player after the turn
 */
PLAYER playerPlayTurn(PLAYER player, CARD* heapUpperCardPtr, GameSettings* globalGameSettings) {
  int playerActionChoice, cardIndex;
  bool isTurnFinished = false;
  CARD withdrawnCard, playerCard;

  printf("%s's turn:\n", player.firstName);
  printPlayerCards(player);

  while (!isTurnFinished) {
    playerActionChoice = getPlayerActionChoice(player.numberOfCards);

    if (playerActionChoice == ACTION_WITHDRAW_FROM_DECK) {
      withdrawCardFromDeck(&player, RANDOM_CARD_VALUE, globalGameSettings);
      isTurnFinished = true;
    } else {
      cardIndex = playerActionChoice - 1;
      player = executeCardAction(player, cardIndex, heapUpperCardPtr, &isTurnFinished, globalGameSettings);
    }
  }

  return player;
}

/**
 * @brief Get the "Open Taki" Player Choice result, if player chooses to continue or not
 *
 * @param numberOfCards number of cards in the player's deck
 * @return int Player's choice, in an integer value
 */
int getOpenTakiPlayerChoice(int numberOfCards) {
  int playerActionChoice;

  while (true) {
    printf(
        "Please enter 0 if you want to finish your turn or 1-%d if you want to put one of your cards in the middle:\n",
        numberOfCards);
    scanf("%d", &playerActionChoice);
    if (playerActionChoice >= 0 && playerActionChoice <= numberOfCards) {
      break;
    }
  }

  return playerActionChoice;
}

/**
 * @brief Executes "Open Taki" card action
 *
 * @param player The player who executes the action
 * @param cardIndex The index of the open taki card
 * @param heapUpperCardPtr Pointer to the upper card of the game's heap
 * @param globalGameSettings Pointer to global game settings
 */
void executeOpenTaki(PLAYER* player, int cardIndex, CARD* heapUpperCardPtr, GameSettings* globalGameSettings) {
  int playerActionChoice, currentCardIndex;
  CARD lastCard = player->cards[cardIndex];

  removeCardFromPlayerDeck(player, cardIndex);
  printPlayerCards(*player);

  playerActionChoice = getOpenTakiPlayerChoice(player->numberOfCards);

  while (playerActionChoice != ACTION_FINISH_OPEN_TAKI) {
    currentCardIndex = playerActionChoice - 1;
    if (isValidNextCard(player->cards[currentCardIndex], heapUpperCardPtr)) {
      if (player->cards[currentCardIndex].value == COLOR_CHANGE_CARD_VALUE) {
        executeChangeColor(player, currentCardIndex, heapUpperCardPtr);
        lastCard = *heapUpperCardPtr;
        playerActionChoice = ACTION_FINISH_OPEN_TAKI;
        break;
      }

      lastCard = player->cards[currentCardIndex];
      removeCardFromPlayerDeck(player, currentCardIndex);
      printPlayerCards(*player);
    } else {
      printf("ERROR: The card you chose is not valid. Please try again.\n");
    }

    if (player->numberOfCards == 0) {
      playerActionChoice = ACTION_FINISH_OPEN_TAKI;
    } else {
      playerActionChoice = getOpenTakiPlayerChoice(player->numberOfCards);
    }
  }

  if (lastCard.value == PLUS_CARD_VALUE) {
    withdrawCardFromDeck(player, PLUS_CARD_VALUE, globalGameSettings);
    executePlusCard(player, player->numberOfCards - 1, heapUpperCardPtr, globalGameSettings);
  } else if (lastCard.value == STOP_CARD_VALUE) {
    executeStopCard(player, player->numberOfCards - 1, heapUpperCardPtr, globalGameSettings);
  } else if (lastCard.value == DIRECTION_CHANGE_CARD_VALUE) {
    executeChangeDirection(globalGameSettings);
  }

  *heapUpperCardPtr = lastCard;

  return;
}

/**
 * @brief Checks if the card the player wants to put in the middle is valid
 *
 * @param chosenCard Player's chosen card
 * @param heapUpperCardPtr Current heap latest card
 * @return true If the card is valid
 * @return false If the card is not valid
 */
bool isValidNextCard(CARD chosenCard, CARD* heapUpperCardPtr) {
  return heapUpperCardPtr->color == chosenCard.color || heapUpperCardPtr->value == chosenCard.value ||
         chosenCard.value == COLOR_CHANGE_CARD_VALUE;
}

/**
 * @brief Executes the action of "Change Direction" card
 *
 * @param globalGameSettings Pointer to global game settings
 */
void executeChangeDirection(GameSettings* globalGameSettings) {
  globalGameSettings->isRoundDirectionClockwise = !globalGameSettings->isRoundDirectionClockwise;
}

/**
 * @brief Executes the action of "Stop" card
 *
 * @param player The player who executes the action
 * @param cardIndex The index of the plus card
 * @param heapUpperCardPtr Pointer to the upper card of the game's heap
 * @param globalGameSettings Pointer to global game settings
 */
void executeStopCard(PLAYER* player, int cardIndex, CARD* heapUpperCardPtr, GameSettings* globalGameSettings) {
  if (globalGameSettings->numberOfPlayers == 2 && player->numberOfCards == 1) {
    withdrawCardFromDeck(player, RANDOM_CARD_VALUE, globalGameSettings);
  } else {
    globalGameSettings->isStopNextPlayerTurn = true;
  }
}

/**
 * @brief Executes the action of "Plus" card
 *
 * @param player The player who executes the action
 * @param cardIndex The index of the plus card
 * @param heapUpperCardPtr Pointer to the upper card of the game's heap
 * @param globalGameSettings Pointer to global game settings
 */
void executePlusCard(PLAYER* player, int cardIndex, CARD* heapUpperCardPtr, GameSettings* globalGameSettings) {
  *heapUpperCardPtr = player->cards[cardIndex];
  removeCardFromPlayerDeck(player, cardIndex);
  *player = playerPlayTurn(*player, heapUpperCardPtr, globalGameSettings);
}

/**
 * @brief Get a new random card from the deck, and adds it to the player's deck.
 * Also, adds the card to the statistics of the game.
 *
 * @param player The player to add the card to
 */
void withdrawCardFromDeck(PLAYER* player, int cardValue, GameSettings* globalGameSettings) {
  CARD withdrawnCard;

  if (cardValue == RANDOM_CARD_VALUE) {
    withdrawnCard = getRandomCard();
  } else {
    withdrawnCard = getCardByValue(cardValue, NO_COLOR);
  }

  player->cards = customRealloc(player->cards, player->numberOfCards, player->numberOfCards + 1);

  player->cards[player->numberOfCards] = withdrawnCard;
  player->numberOfCards++;

  globalGameSettings->withdrawnCardsStatistics[withdrawnCard.value] += 1;
}

/**
 * @brief The general action which controls the input of specific card actions
 *
 * @param player The player who executes the action
 * @param cardIndex The index of the card to execute
 * @param heapUpperCardPtr Pointer to the upper card of the game's heap
 * @return PLAYER modified player after the action
 */
PLAYER executeCardAction(PLAYER player, int cardIndex, CARD* heapUpperCardPtr, bool* isTurnedFinishedPtr,
                         GameSettings* globalGameSettings) {
  CARD playerCard;

  playerCard = player.cards[cardIndex];

  if (isValidNextCard(playerCard, heapUpperCardPtr)) {
    switch (playerCard.value) {
      case TAKI_CARD_VALUE:
        executeOpenTaki(&player, cardIndex, heapUpperCardPtr, globalGameSettings);
        break;
      case COLOR_CHANGE_CARD_VALUE:
        executeChangeColor(&player, cardIndex, heapUpperCardPtr);
        break;
      case PLUS_CARD_VALUE:
        executePlusCard(&player, cardIndex, heapUpperCardPtr, globalGameSettings);
      case STOP_CARD_VALUE:
        executeStopCard(&player, cardIndex, heapUpperCardPtr, globalGameSettings);
      case DIRECTION_CHANGE_CARD_VALUE:
        executeChangeDirection(globalGameSettings);
      default:
        *heapUpperCardPtr = player.cards[cardIndex];
        removeCardFromPlayerDeck(&player, cardIndex);
        break;
    }
    *isTurnedFinishedPtr = true;
  } else {
    printf("Invalid card! Try again.\n");
    *isTurnedFinishedPtr = false;
  }

  return player;
}

/**
 * @brief Get the Player Action Choice object
 *
 * @param numberOfCards Number of cards in the player's deck
 * @return int The player's choice in an integer value
 */
int getPlayerActionChoice(int numberOfCards) {
  int playerActionChoice;

  while (true && numberOfCards > 0) {
    printf(
        "Please enter 0 if you want to take a card from the deck or 1-%d if you want to put one of your cards in the "
        "middle:\n",
        numberOfCards);
    scanf("%d", &playerActionChoice);

    if (playerActionChoice >= 0 && playerActionChoice <= numberOfCards) {
      break;
    } else {
      printf("ERROR: Invalid input. Please try again.\n");
    }
  }

  return playerActionChoice;
}

/**
 * @brief Get the Index Of Next Player, according to the round direction and "stop" condition.
 * If the round is clockwise, the next player is the next player in the list.
 * If the round is counterclockwise, the next player is the previous player in the list.
 * @param currentPlayerIndex Current player index
 * @param numberOfPlayers Number of players in the game
 * @return int Index of the next player
 */
int getIndexOfNextPlayer(int currentPlayerIndex, GameSettings* globalGameSettings) {
  int nextPlayerIndex = currentPlayerIndex;
  int indexToAdd = globalGameSettings->isRoundDirectionClockwise ? 1 : globalGameSettings->numberOfPlayers - 1;

  if (globalGameSettings->isStopNextPlayerTurn) {
    globalGameSettings->isStopNextPlayerTurn = false;
    nextPlayerIndex += indexToAdd;
  }

  nextPlayerIndex += indexToAdd;

  return (nextPlayerIndex % globalGameSettings->numberOfPlayers);
}

/**
 * @brief Prints heap's upper card
 *
 * @param heapUpperCard Heap's card struct
 */
void printHeapUpperCard(CARD heapUpperCard) {
  printf("Upper card:\n");
  printCard(heapUpperCard);
  printf("\n");
}

void buildGameStatistics(int withdrawnCardsStatistics[], CARD_STATISTICS orderedWithdrawnCardsStatistics[]) {
  int i;
  char cardValueInText[CARD_MAX_STRING_LENGTH];
  CARD fakeCardValue;
  CARD_STATISTICS cardStatistics;

  // Build Card Statistics Array
  for (i = 0; i < NUMBER_OF_UNIQUE_CARD_VALUES; i++) {
    // Get the card value in text
    fakeCardValue.value = i;
    getCardValueInText(fakeCardValue, cardValueInText);

    // Build card statistics struct
    strcpy(cardStatistics.cardValue, cardValueInText);
    cardStatistics.numberOfWithdrawals = withdrawnCardsStatistics[i];

    orderedWithdrawnCardsStatistics[i] = cardStatistics;
  }

  mergeSort(orderedWithdrawnCardsStatistics, NUMBER_OF_UNIQUE_CARD_VALUES);
}

void printGameStatistics(CARD_STATISTICS orderedWithdrawnCardsStatistics[]) {
  printf("\n\n");
  printf("************ Game Statistics ************\n"
         "Card # | Frequency\n"
         "__________________\n");

  for (int i = 0; i < NUMBER_OF_UNIQUE_CARD_VALUES; i++) {
    printf("%6s | %9d\n", orderedWithdrawnCardsStatistics[i].cardValue,
           orderedWithdrawnCardsStatistics[i].numberOfWithdrawals);
  }
}

void merge(CARD_STATISTICS arr1[], int size1, CARD_STATISTICS arr2[], int size2, CARD_STATISTICS resultArr[]) {
  int firstArrIndex, secondArrIndex, resultArrIndex;

  firstArrIndex = secondArrIndex = resultArrIndex = 0;

  while ((firstArrIndex < size1) && (secondArrIndex < size2)) {
    if (arr1[firstArrIndex].numberOfWithdrawals >= arr2[secondArrIndex].numberOfWithdrawals) {
      resultArr[resultArrIndex] = arr1[firstArrIndex];
      firstArrIndex += 1;
    } else {
      resultArr[resultArrIndex] = arr2[secondArrIndex];
      secondArrIndex += 1;
    }
    resultArrIndex += 1;
  }

  while (firstArrIndex < size1) {
    resultArr[resultArrIndex] = arr1[firstArrIndex];
    firstArrIndex += 1;
    resultArrIndex += 1;
  }

  while (secondArrIndex < size2) {
    resultArr[resultArrIndex] = arr2[secondArrIndex];
    secondArrIndex += 1;
    resultArrIndex += 1;
  }

  return;
}

void mergeSort(CARD_STATISTICS arr[], int size) {
  CARD_STATISTICS* tmpArr = NULL;
  int halfSize = size / 2;

  if (size <= 1) {
    return;
  }

  mergeSort(arr, halfSize);
  mergeSort(arr + halfSize, size - halfSize);

  tmpArr = (CARD_STATISTICS*)malloc(size * sizeof(CARD_STATISTICS));

  if (tmpArr == NULL) {
    printf("ERROR! Can not allocate memory.");
    exit(1);
  }

  merge(arr, halfSize, arr + halfSize, size - halfSize, tmpArr);
  copyCardStatisticsArrays(tmpArr, arr, size);
  free(tmpArr);

  return;
}

void copyCardStatisticsArrays(CARD_STATISTICS fromArr[], CARD_STATISTICS toArr[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    toArr[i] = fromArr[i];
  }

  return;
}

void checkAlloc(CARD* pointer) {
  if (pointer == NULL) {
    exit(1);
  }
}

void* customRealloc(CARD* oldArray, int currentSize, int newSize) {
  int i;
  CARD* newArray = NULL;

  newArray = (CARD*)malloc(newSize * sizeof(CARD));
  checkAlloc(newArray);

  for (i = 0; i < currentSize && i < newSize; i++) {
    newArray[i] = oldArray[i];
  }

  free(oldArray);
  oldArray = NULL;

  return newArray;
}