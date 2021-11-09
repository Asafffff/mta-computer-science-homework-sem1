#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Pizza Properties
 */
#define MIN_PIZZA_WIDTH 10
#define MIN_PIZZA_LENGTH 10
#define MAX_PIZZA_WIDTH 80
#define MAX_PIZZA_LENGTH 40

/**
 * Delivery Options
 */
#define DELIVERY 1
#define PICKUP 0

/**
 * Pizza Toppings
 */
#define TOPPING_OLIVES "Olives"
#define TOPPING_MUSHROOMS "Mushrooms"
// TODO: Hope who reads this will fix the "tomatos" typo
#define TOPPING_TOMATOES "Tomatos"
#define TOPPING_PINEAPPLE "Pineapple"

/**
 * Pizza Toppings - Characters Symbol
 */
#define OLIVES_CHAR 'O'
#define MUSHROOMS_CHAR 'M'
#define TOMATOES_CHAR 'T'
#define PINEAPPLE_CHAR 'P'
#define EMPTY_CHAR ' '

/**
 * Dough Types
 */
#define DOUGH_REGULAR 'r'
#define DOUGH_VEGAN 'v'
#define DOUGH_WHOLE_WHEAT 'w'
#define DOUGH_GLUTEN_FREE 'f'

struct Quarters {
  char first;
  char second;
  char third;
  char fourth;
};

struct Toppings {
  float olives;
  float mushrooms;
  float tomatoes;
  float pineapple;
};

struct Pizza {
  int number;
  int length;
  int width;
  char doughType;
  double relativeSize;
  struct Toppings toppings;
  double totalPrice;
};

struct PaymentChange {
  int amount;
  int inTens;
  int inFives;
  int inTwos;
  int inOnes;
};

void printWelcomeMessage();
int getCustomerIdFromInput();
bool isValidCustomerId(int customerId);
bool isValidCustomerIdLength(int customerId);
int hashLastDigit(int i, int lastDigit);
int calculateCheckDigit(int input);
bool isValidCustomerIdCheckDigit(int customerId);
void printMenu();
int getPizzasAmountFromInput();
bool isValidPizzasAmount();
struct Pizza buildPizza(int pizzaNumber);
void printHeaderForPizzaNumber(int pizzaNumber);
int getPizzaLengthFromInput();
int getPizzaWidthFromInput();
bool isValidPizzaLength();
bool isValidPizzaWidth();
char getPizzaDoughType();
bool isValidDoughType(char pizzaDoughType);
double calculateRelativePizzaSize(int pizzaLength, int pizzaWidth);
struct Pizza addToppingsToPizza(struct Pizza pizza);
void printToppingSelectionMenu(char toppingName[], bool isIgnoreToppingName);
float selectToppingForPizza();
bool isValidToppingPortion(float toppingPortion);
float mapToppingPortionsToValues(float toppingPortion);
bool isValidToppingSum(float sumOfToppingsPortions);
bool isToppingsCoverAllPizza(float sumOfToppingsPortions);
double calculatePizzaPriceByRelativeSize(double pizzaRelativeSize);
double calculateDoughPriceByRelativeSize(double pizzaRelativeSize, char pizzaDoughType);
double calculateToppingsPriceByRelativeSize(double pizzaRelativeSize, float olivesPortion, float mushroomsPortion,
                                            float tomatoesPortion, float pineapplePortion);
double calculatePizzaPrice(struct Pizza pizza);
void printPizzaSummary(struct Pizza pizza);
void printPizzaPreview(struct Pizza pizza);
int chooseDeliveryType();
bool isValidDeliveryType(int deliveryType);
int calculateDeliveryPriceByDeliveryType(int deliveryType);
void printOrderSummaryForCustomerId(int customerId, int pizzasAmount, int deliveryType, double totalPrice);

int getPaymentInCashFromInput();
int calculatePaymentChange(int customerPaymentAmountInNIS, double totalPriceIncludingVAT);
int askForPaymentUntilNonNegativeChange(int paymentChange);
int calculateRemainingChangeInCoinValue(int remainingChange, int coinValue);
void printPaymentChangeSummary(struct PaymentChange paymentChange);
void handlePayment(double totalPriceIncludingVAT);

struct Quarters getToppingRepresentationByQuarters(struct Pizza pizza);
struct Quarters placeToppingOnQuarter(struct Quarters quarters, int quarterPlacement, char topping);
struct Quarters addToppingToQuarter(double toppingPortion, char toppingChar, struct Quarters quarters);
int findNextAvailableQuarter(struct Quarters quarters);
double sumTotalQuarterToppings(struct Quarters quarters);

bool isEven(int number);
void printSeparator();

const int basicPizzaPrice = 70;
const int basicPizzaLength = 40, basicPizzaWidth = 50;
const int toppingOlivesPrice = 10, toppingMushroomsPrice = 12, toppingTomatoesPrice = 9, toppingPineapplePrice = 14;
const int doughTypeRegularPrice = 0, doughTypeVeganPrice = 5, doughTypeWholeWheatPrice = 3,
          doughTypeGlutenFreePrice = 4;
const int basicDeliveryPrice = 15;

int main() {
  int customerId;
  int pizzasAmount;
  int deliveryType;

  int deliveryPrice;
  double totalPriceIncludingVAT;
  double totalPrice = 0;

  printWelcomeMessage();

  customerId = getCustomerIdFromInput();

  printMenu();

  pizzasAmount = getPizzasAmountFromInput();

  // Build pizzas
  for (int i = 0; i < pizzasAmount; i++) {
    struct Pizza pizza;
    int pizzaNumber = i + 1;

    pizza = buildPizza(pizzaNumber);
    totalPrice += pizza.totalPrice;
  }

  printSeparator();

  deliveryType = chooseDeliveryType();

  deliveryPrice = calculateDeliveryPriceByDeliveryType(deliveryType);
  totalPrice += deliveryPrice;
  totalPriceIncludingVAT = totalPrice * 1.17;

  printOrderSummaryForCustomerId(customerId, pizzasAmount, deliveryType, totalPrice);

  handlePayment(totalPriceIncludingVAT);

  printf("Thank you for your order!");

  return EXIT_SUCCESS;
};

void printWelcomeMessage() {
  printf(" Welcome to MTA-Pizza!\n\n"
         "*****\n"
         " *** \n"
         "  *  \n\n");
}

int getCustomerIdFromInput() {
  int customerId;

  printf("Please enter your ID number:\n");
  scanf("%d", &customerId);

  while (!isValidCustomerId(customerId)) {
    if (!isValidCustomerIdLength(customerId)) {
      printf("Invalid ID number! Try again.\n");
    } else if (!isValidCustomerIdCheckDigit(customerId)) {
      printf("Invalid check digit! Try again.\n");
    }

    printf("Please enter your ID number:\n");
    scanf("%d", &customerId);
  }

  return customerId;
};

bool isValidCustomerId(int customerId) {
  return isValidCustomerIdLength(customerId) && isValidCustomerIdCheckDigit(customerId);
}

bool isValidCustomerIdLength(int customerId) {
  return customerId > 0 && customerId < 1000000000;
}

int hashLastDigit(int i, int customerIdLastDigit) {
  int hashResult;
  bool isMultiplyByTwo = (i % 2) == 0;

  hashResult = isMultiplyByTwo ? customerIdLastDigit * 2 : customerIdLastDigit;

  if (hashResult > 9) {
    int hashResultFirstDigit, hashResultLastDigit;

    hashResultFirstDigit = hashResult / 10;
    hashResultLastDigit = hashResult % 10;
    return (hashResultFirstDigit + hashResultLastDigit);
  }

  return hashResult;
}

int calculateCheckDigit(int hashResultSum) {
  return (hashResultSum % 10) == 0 ? 0 : (-1) * ((hashResultSum % 10) - 10);
}

bool isValidCustomerIdCheckDigit(int customerId) {
  int customerIdWithoutCheckDigit = customerId / 10;
  int calculatedCheckDigit, checkDigit = customerId % 10;
  int customerIdRemainingDigits = customerIdWithoutCheckDigit;
  int customerIdLastDigit;
  int hashResultSum = 0;
  int i = 0;

  while (customerIdRemainingDigits > 0) {
    int hashResult;

    customerIdLastDigit = customerIdRemainingDigits % 10;

    hashResult = hashLastDigit(i, customerIdLastDigit);
    hashResultSum += hashResult;

    customerIdRemainingDigits /= 10;
    i++;
  }

  calculatedCheckDigit = calculateCheckDigit(hashResultSum);

  return (calculatedCheckDigit == checkDigit);
}

void printMenu() {
  // TODO: Hope who reads this will make sure they will remove the newline char from the beggining.
  printf("Our menu:\n"
         "*********\n"
         "Basic pizza: %.2f NIS for %dx%d size pizza\n\n",
         (float)basicPizzaPrice, basicPizzaLength, basicPizzaWidth);

  printf("Toppings for basic size pizza:\n"
         "Olives: %d NIS\n"
         "Mushrooms: %d NIS\n"
         "Tomatoes: %d NIS\n"
         "Pineapple: %d NIS\n\n",
         toppingOlivesPrice, toppingMushroomsPrice, toppingTomatoesPrice, toppingPineapplePrice);

  printf("Dough type for basic size pizza:\n"
         "Regular: %d NIS\n"
         "Vegan: %d NIS\n"
         "Whole wheat: %d NIS\n"
         "Gluten free: %d NIS\n\n",
         doughTypeRegularPrice, doughTypeVeganPrice, doughTypeWholeWheatPrice, doughTypeGlutenFreePrice);
};

int getPizzasAmountFromInput() {
  int pizzasAmount;

  printf("How many pizzas would you like to order?\n");
  scanf("%d", &pizzasAmount);

  while (!isValidPizzasAmount(pizzasAmount)) {
    printf("Invalid choice! Try again.\n");

    printf("How many pizzas would you like to order?\n");
    scanf("%d", &pizzasAmount);
  }

  return pizzasAmount;
};

bool isValidPizzasAmount(int pizzasAmount) {
  return pizzasAmount > 0;
};

void printHeaderForPizzaNumber(int pizzaNumber) {
  printf("*************************************************\n"
         "Pizza #%d:\n\n",
         pizzaNumber);
}

int getPizzaLengthFromInput() {
  int pizzaLength;

  // TODO: Hope who reads this will make sure they will add the newline char back.
  printf("Please enter your pizza's length (cm): ");
  scanf("%d", &pizzaLength);

  while (!isValidPizzaLength(pizzaLength)) {
    printf("Invalid length! Try again.\n");

    // TODO: Hope who reads this will make sure they will add the newline char back.
    printf("Please enter your pizza's length (cm): ");
    scanf("%d", &pizzaLength);
  }

  return pizzaLength;
};

int getPizzaWidthFromInput() {
  int pizzaWidth;

  printf("Please enter your pizza's width (cm): ");
  scanf("%d", &pizzaWidth);

  while (!isValidPizzaWidth(pizzaWidth)) {
    printf("Invalid width! Try again.\n");

    printf("Please enter your pizza's width (cm):\n");
    scanf("%d", &pizzaWidth);
  }

  return pizzaWidth;
};

bool isValidPizzaLength(int pizzaLength) {
  return (pizzaLength >= MIN_PIZZA_LENGTH && pizzaLength <= MAX_PIZZA_LENGTH) && isEven(pizzaLength);
};

bool isValidPizzaWidth(int pizzaWidth) {
  return (pizzaWidth >= MIN_PIZZA_WIDTH && pizzaWidth <= MAX_PIZZA_WIDTH) && isEven(pizzaWidth);
};

char getPizzaDoughType() {
  char pizzaDoughType;
  // TODO: Hope who reads this will make sure they will remove the newline char from the beggining.
  printf("\nPlease enter the pizza's dough type:\n"
         "r - for regular\n"
         "v - for vegan\n"
         "w - for whole wheat\n"
         "f - for gluten-free\n");
  scanf(" %c", &pizzaDoughType);

  while (!isValidDoughType(pizzaDoughType)) {
    printf("Invalid choice! Try again.\n");

    // TODO: Hope who reads this will make sure they will remove the newline char from the beggining.
    printf("\nPlease enter the pizza's dough type:\n"
           "r - for regular\n"
           "v - for vegan\n"
           "w - for whole wheat\n"
           "f - for gluten-free\n");
    scanf(" %c", &pizzaDoughType);
  }

  return pizzaDoughType;
};

bool isValidDoughType(char pizzaDoughType) {
  return (pizzaDoughType == DOUGH_REGULAR || pizzaDoughType == DOUGH_VEGAN || pizzaDoughType == DOUGH_WHOLE_WHEAT ||
          pizzaDoughType == DOUGH_GLUTEN_FREE);
}

double calculateRelativePizzaSize(int pizzaLength, int pizzaWidth) {
  return ((double)pizzaLength * pizzaWidth) / (basicPizzaLength * basicPizzaWidth);
};

void printToppingSelectionMenu(char toppingName[], bool isIgnoreToppingName) {
  if (isIgnoreToppingName) {
    printf("0. None\n"
           "1. Whole pizza\n"
           "2. Half pizza\n"
           "3. Quarter pizza\n\n");
  } else {
    printf("%s (choose 0-3):\n"
           "0. None\n"
           "1. Whole pizza\n"
           "2. Half pizza\n"
           "3. Quarter pizza\n\n",
           toppingName);
  }
};

float selectToppingForPizza(char toppingName[]) {
  float pizzaToppingPortion;

  printToppingSelectionMenu(toppingName, false);
  scanf("%f", &pizzaToppingPortion);

  while (!isValidToppingPortion(pizzaToppingPortion)) {
    printf("Invalid choice! Try again.\n");

    printToppingSelectionMenu(toppingName, true);
    scanf("%f", &pizzaToppingPortion);
  }

  return pizzaToppingPortion;
}

// TODO: Remove this when they will fix the wrong identation -_-
float selectToppingForPizzaOnOverflow(char toppingName[]) {
  float pizzaToppingPortion;

  printToppingSelectionMenu(toppingName, true);
  scanf("%f", &pizzaToppingPortion);

  while (!isValidToppingPortion(pizzaToppingPortion)) {
    printf("Invalid choice! Try again.\n");

    printToppingSelectionMenu(toppingName, true);
    scanf("%f", &pizzaToppingPortion);
  }

  return pizzaToppingPortion;
}

bool isValidToppingPortion(float toppingPortion) {
  return toppingPortion >= 0 && toppingPortion <= 3;
}

float mapToppingPortionsToValues(float toppingPortion) {
  int tempToppingPortion = toppingPortion;

  switch (tempToppingPortion) {
    case 1:
      toppingPortion = 1;
      break;
    case 2:
      toppingPortion = 0.5;
      break;
    case 3:
      toppingPortion = 0.25;
      break;
    default:
      toppingPortion = 0;
      break;
  }

  return toppingPortion;
}

bool isValidToppingSum(float sumOfToppingsPortions) {
  return sumOfToppingsPortions <= 1;
}

bool isToppingsCoverAllPizza(float sumOfToppingsPortions) {
  return sumOfToppingsPortions == 1;
}

float mapToppingPortionToValidSize(float currentSumOfToppingsPortions, char lastAddedToppingName[],
                                   float lastAddedToppingPortion) {
  currentSumOfToppingsPortions += lastAddedToppingPortion;
  while (!isValidToppingSum(currentSumOfToppingsPortions)) {
    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
    currentSumOfToppingsPortions -= lastAddedToppingPortion;

    lastAddedToppingPortion = selectToppingForPizza(lastAddedToppingName);
    lastAddedToppingPortion = mapToppingPortionsToValues(lastAddedToppingPortion);
    currentSumOfToppingsPortions += lastAddedToppingPortion;
  }

  return lastAddedToppingPortion;
}

float getValidToppingPortionByPortionsSum(float sumOfToppingsPortions, char toppingName[], float toppingPortion) {
  while (!isValidToppingSum(sumOfToppingsPortions + toppingPortion)) {
    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");

    // TODO: Use the previous function, 'selectToppingForPizza' when they fix identation problems
    toppingPortion = selectToppingForPizzaOnOverflow(toppingName);
    toppingPortion = mapToppingPortionsToValues(toppingPortion);
  }

  return toppingPortion;
}

struct Pizza addToppingsToPizza(struct Pizza pizza) {
  float sumOfToppingsPortions = 0;
  printf("Please choose the toppings:\n\n");

  // Add toppings untill full
  while (true) {
    // Olives
    pizza.toppings.olives = selectToppingForPizza(TOPPING_OLIVES);
    pizza.toppings.olives = mapToppingPortionsToValues(pizza.toppings.olives);
    sumOfToppingsPortions += pizza.toppings.olives;
    if (isToppingsCoverAllPizza(sumOfToppingsPortions)) {
      break;
    }

    // Mushrooms
    pizza.toppings.mushrooms = selectToppingForPizza(TOPPING_MUSHROOMS);
    pizza.toppings.mushrooms = mapToppingPortionsToValues(pizza.toppings.mushrooms);
    // Validate Topping Overflow
    pizza.toppings.mushrooms =
        getValidToppingPortionByPortionsSum(sumOfToppingsPortions, TOPPING_MUSHROOMS, pizza.toppings.mushrooms);
    sumOfToppingsPortions += pizza.toppings.mushrooms;
    if (isToppingsCoverAllPizza(sumOfToppingsPortions)) {
      break;
    }

    // Tomatoes
    pizza.toppings.tomatoes = selectToppingForPizza(TOPPING_TOMATOES);
    pizza.toppings.tomatoes = mapToppingPortionsToValues(pizza.toppings.tomatoes);
    // Validate Topping Overflow
    pizza.toppings.tomatoes =
        getValidToppingPortionByPortionsSum(sumOfToppingsPortions, TOPPING_TOMATOES, pizza.toppings.tomatoes);
    sumOfToppingsPortions += pizza.toppings.tomatoes;
    if (isToppingsCoverAllPizza(sumOfToppingsPortions)) {
      break;
    }

    // Pineapple
    pizza.toppings.pineapple = selectToppingForPizza(TOPPING_PINEAPPLE);
    pizza.toppings.pineapple = mapToppingPortionsToValues(pizza.toppings.pineapple);
    // Validate Topping Overflow
    pizza.toppings.pineapple =
        getValidToppingPortionByPortionsSum(sumOfToppingsPortions, TOPPING_PINEAPPLE, pizza.toppings.pineapple);
    sumOfToppingsPortions += pizza.toppings.pineapple;

    // End of available toppings
    break;
  }

  return pizza;
}

double calculatePizzaPriceByRelativeSize(double pizzaRelativeSize) {
  return pizzaRelativeSize * basicPizzaPrice;
}

double calculateDoughPriceByRelativeSize(double pizzaRelativeSize, char pizzaDoughType) {
  double doughPrice;

  switch (pizzaDoughType) {
    case DOUGH_REGULAR:
      doughPrice = pizzaRelativeSize * doughTypeRegularPrice;
      break;
    case DOUGH_VEGAN:
      doughPrice = pizzaRelativeSize * doughTypeVeganPrice;
      break;
    case DOUGH_WHOLE_WHEAT:
      doughPrice = pizzaRelativeSize * doughTypeWholeWheatPrice;
      break;
    case DOUGH_GLUTEN_FREE:
      doughPrice = pizzaRelativeSize * doughTypeGlutenFreePrice;
      break;
    default:
      printf("Error. Input doesn't match any available dough types. Please try again.");
      exit(EXIT_FAILURE);
  }

  return doughPrice;
}

double calculateToppingsPriceByRelativeSize(double pizzaRelativeSize, float olivesPortion, float mushroomsPortion,
                                            float tomatoesPortion, float pineapplePortion) {
  return pizzaRelativeSize * ((toppingOlivesPrice * olivesPortion) + (toppingMushroomsPrice * mushroomsPortion) +
                              (toppingTomatoesPrice * tomatoesPortion) + (toppingPineapplePrice * pineapplePortion));
};

double calculatePizzaPrice(struct Pizza pizza) {
  double pizzaPriceByPizzaSize, doughPrice, toppingsPrice, totalPizzaPrice = 0;

  pizzaPriceByPizzaSize = calculatePizzaPriceByRelativeSize(pizza.relativeSize);
  doughPrice = calculateDoughPriceByRelativeSize(pizza.relativeSize, pizza.doughType);
  toppingsPrice =
      calculateToppingsPriceByRelativeSize(pizza.relativeSize, pizza.toppings.olives, pizza.toppings.mushrooms,
                                           pizza.toppings.tomatoes, pizza.toppings.pineapple);

  totalPizzaPrice = pizzaPriceByPizzaSize + doughPrice + toppingsPrice;

  return totalPizzaPrice;
}

void printPizzaSummary(struct Pizza pizza) {
  printf("Pizza #%d details:\n"
         "*******************\n",
         pizza.number);
  printf("Pizza size: %dx%d\n", pizza.length, pizza.width);
  printf("Pizza price (without tax): %.2f\n", pizza.totalPrice);
  printPizzaPreview(pizza);
}

void printPizzaPreview(struct Pizza pizza) {
  int i, j;
  struct Quarters toppingsByQuarters;

  toppingsByQuarters = getToppingRepresentationByQuarters(pizza);

  // Print first half of pizza
  for (i = 0; i < (pizza.length / 2); i++) {
    // Print first row (dough only)
    if (i == 0) {
      for (j = 0; j < pizza.width; j++) {
        printf("%c", pizza.doughType);
      }
      printf("\n");
    } else {
      // Print dough on margins (left)
      printf("%c", pizza.doughType);

      // Print 4th quarter topping
      for (j = 0; j < (pizza.width - 2) / 2; j++) {
        printf("%c", toppingsByQuarters.fourth);
      }

      // Print 1st quarter topping
      for (j = 0; j < (pizza.width - 2) / 2; j++) {
        printf("%c", toppingsByQuarters.first);
      }

      // Print dough on margins (right)
      printf("%c", pizza.doughType);

      // Print newline
      printf("\n");
    }
  }

  // Print second half of pizza
  for (i = 0; i < (pizza.length / 2); i++) {
    // Print last row (dough only)
    if (i == (pizza.length / 2) - 1) {
      for (j = 0; j < pizza.width; j++) {
        printf("%c", pizza.doughType);
      }
      printf("\n");
    } else {
      // Print dough on margins (left)
      printf("%c", pizza.doughType);

      // Print 3rd quarter topping
      for (j = 0; j < (pizza.width - 2) / 2; j++) {
        printf("%c", toppingsByQuarters.third);
      }

      // Print 2nd quarter topping
      for (j = 0; j < (pizza.width - 2) / 2; j++) {
        printf("%c", toppingsByQuarters.second);
      }

      // Print dough on margins (right)
      printf("%c", pizza.doughType);

      // Print newline
      printf("\n");
    }
  }
  printf("\n");
}

struct Pizza buildPizza(int pizzaNumber) {
  struct Pizza pizza;
  struct Toppings pizzaToppings = {.olives = 0, .mushrooms = 0, .tomatoes = 0, .pineapple = 0};

  // Init empty toppings
  pizza.toppings = pizzaToppings;

  pizza.number = pizzaNumber;

  printHeaderForPizzaNumber(pizza.number);

  pizza.length = getPizzaLengthFromInput();
  pizza.width = getPizzaWidthFromInput();

  pizza.doughType = getPizzaDoughType();

  // calculateRelativePizzaSize
  pizza.relativeSize = calculateRelativePizzaSize(pizza.length, pizza.width);

  // addToppingsToPizza
  pizza = addToppingsToPizza(pizza);

  // calculatePizzaPrice
  pizza.totalPrice = calculatePizzaPrice(pizza);

  printPizzaSummary(pizza);

  return pizza;
};

int chooseDeliveryType() {
  int deliveryType;

  printf("Do you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up:\n");
  scanf("%d", &deliveryType);

  while (!isValidDeliveryType(deliveryType)) {
    printf("Invalid choice! Try again.\n");

    printf("Do you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up:\n");
    scanf("%d", &deliveryType);
  }

  return deliveryType;
};

bool isValidDeliveryType(int deliveryType) {
  return (deliveryType == PICKUP || deliveryType == DELIVERY);
};

int calculateDeliveryPriceByDeliveryType(int deliveryType) {
  return deliveryType == DELIVERY ? basicDeliveryPrice : 0;
};

void printOrderSummaryForCustomerId(int customerId, int pizzasAmount, int deliveryType, double totalPrice) {
  double totalPriceIncludingVAT = totalPrice * 1.17;

  printf("Your order details:\n"
         "*******************\n");
  printf("ID number: %09d\n", customerId);
  printf("Number of pizzas: %d\n", pizzasAmount);
  printf(deliveryType == DELIVERY ? "Delivery\n" : "Pick-up\n");
  printf("Total price: %.2f\n"
         "Total price with tax (rounded down): %d\n",
         totalPrice, (int)(totalPriceIncludingVAT));
};

int getPaymentInCashFromInput() {
  int customerPaymentAmountInNIS;

  // TODO: Hope who reads this will make sure they will remove the newline char from the beggining.
  printf("Please enter your payment: ");
  scanf("%d", &customerPaymentAmountInNIS);

  return customerPaymentAmountInNIS;
}

int calculatePaymentChange(int customerPaymentAmountInNIS, double totalPriceIncludingVAT) {
  return customerPaymentAmountInNIS - (int)totalPriceIncludingVAT;
}

/**
 * Asks customer for payment until the payment change is non-negative.
 * returns paymentChange as an output
 */
int askForPaymentUntilNonNegativeChange(int paymentChange) {
  int customerPaymentAmountInNIS;

  while (paymentChange < 0) {
    printf("Your remaining balance is: %d\n", -1 * paymentChange);
    printf("Please enter your payment:\n");
    scanf("%d", &customerPaymentAmountInNIS);

    paymentChange += customerPaymentAmountInNIS;
  }

  return paymentChange;
}

int calculateRemainingChangeInCoinValue(int remainingChange, int coinValue) {
  return remainingChange / coinValue;
}

void printPaymentChangeSummary(struct PaymentChange paymentChange) {
  if (paymentChange.amount > 0) {
    printf("Your change is %d NIS using:\n", paymentChange.amount);
    if (paymentChange.inTens > 0) {
      printf("%d coin(s) of ten\n", paymentChange.inTens);
    }
    if (paymentChange.inFives > 0) {
      printf("%d coin(s) of five\n", paymentChange.inFives);
    }
    if (paymentChange.inTwos > 0) {
      printf("%d coin(s) of two\n", paymentChange.inTwos);
    }
    if (paymentChange.inOnes > 0) {
      printf("%d coin(s) of one\n", paymentChange.inOnes);
    }
  }
}

void handlePayment(double totalPriceIncludingVAT) {
  struct PaymentChange paymentChange;
  int customerPaymentAmountInNIS;
  int remainingChange;

  customerPaymentAmountInNIS = getPaymentInCashFromInput();
  paymentChange.amount = calculatePaymentChange(customerPaymentAmountInNIS, totalPriceIncludingVAT);
  paymentChange.amount = askForPaymentUntilNonNegativeChange(paymentChange.amount);

  remainingChange = paymentChange.amount;

  // calculateRemainingChangeInTens
  paymentChange.inTens = calculateRemainingChangeInCoinValue(remainingChange, 10);
  remainingChange -= paymentChange.inTens * 10;

  // calculateRemainingChangeInFives
  paymentChange.inFives = calculateRemainingChangeInCoinValue(remainingChange, 5);
  remainingChange -= paymentChange.inFives * 5;

  // calculateRemainingChangeInTwos
  paymentChange.inTwos = calculateRemainingChangeInCoinValue(remainingChange, 2);
  remainingChange -= paymentChange.inTwos * 2;

  // calculateRemainingChangeInOnes
  paymentChange.inOnes = calculateRemainingChangeInCoinValue(remainingChange, 1);
  remainingChange -= paymentChange.inOnes * 1;

  printPaymentChangeSummary(paymentChange);
}

/**
 * Helper functions
 */
bool isEven(int number) {
  return number % 2 == 0;
};

void printSeparator() {
  printf("*************************************************\n");
}

struct Quarters getToppingRepresentationByQuarters(struct Pizza pizza) {
  struct Quarters quarters = {.first = EMPTY_CHAR, .second = EMPTY_CHAR, .third = EMPTY_CHAR, .fourth = EMPTY_CHAR};
  double sumOfQuartersOnToppings = 0;

  // TODO: Improve with for loop when arrays are available
  quarters = addToppingToQuarter(pizza.toppings.olives, OLIVES_CHAR, quarters);
  sumOfQuartersOnToppings += sumTotalQuarterToppings(quarters);

  if (sumOfQuartersOnToppings >= 1) {
    return quarters;
  }

  quarters = addToppingToQuarter(pizza.toppings.mushrooms, MUSHROOMS_CHAR, quarters);
  sumOfQuartersOnToppings += sumTotalQuarterToppings(quarters);

  if (sumOfQuartersOnToppings >= 1) {
    return quarters;
  }

  quarters = addToppingToQuarter(pizza.toppings.tomatoes, TOMATOES_CHAR, quarters);
  sumOfQuartersOnToppings += sumTotalQuarterToppings(quarters);

  if (sumOfQuartersOnToppings >= 1) {
    return quarters;
  }

  quarters = addToppingToQuarter(pizza.toppings.pineapple, PINEAPPLE_CHAR, quarters);
  sumOfQuartersOnToppings += sumTotalQuarterToppings(quarters);

  if (sumOfQuartersOnToppings >= 1) {
    return quarters;
  }

  return quarters;
}

struct Quarters addToppingToQuarter(double toppingPortion, char toppingChar, struct Quarters quarters) {
  int i;
  int nextAvailableQuarter, numOfSequentQuarters;

  if (toppingPortion == 0.25) {
    numOfSequentQuarters = 1;
    nextAvailableQuarter = findNextAvailableQuarter(quarters);
  } else if (toppingPortion == 0.5) {
    numOfSequentQuarters = 2;
    nextAvailableQuarter = findNextAvailableQuarter(quarters);
  } else if (toppingPortion == 1) {
    numOfSequentQuarters = 4;
    nextAvailableQuarter = 1;
  } else {
    return quarters;
  }

  // Add topping X to the next available quarter, for Y sequent quarters.
  for (i = 0; i < numOfSequentQuarters; i++) {
    quarters = placeToppingOnQuarter(quarters, nextAvailableQuarter, toppingChar);
    nextAvailableQuarter += 1;
  }

  return quarters;
}

struct Quarters placeToppingOnQuarter(struct Quarters quarters, int quarterPlacement, char topping) {
  switch (quarterPlacement) {
    case 1:
      quarters.first = topping;
      break;
    case 2:
      quarters.second = topping;
      break;
    case 3:
      quarters.third = topping;
      break;
    case 4:
      quarters.fourth = topping;
      break;
    default:
      printf("This is not an available quarter. Exiting due to failure.");
      exit(EXIT_FAILURE);
  }

  return quarters;
}

int findNextAvailableQuarter(struct Quarters quarters) {
  if (quarters.first == EMPTY_CHAR) {
    return 1;
  } else if (quarters.second == EMPTY_CHAR) {
    return 2;
  } else if (quarters.third == EMPTY_CHAR) {
    return 3;
  } else if (quarters.fourth == EMPTY_CHAR) {
    return 4;
  }

  return -1;
}

double sumTotalQuarterToppings(struct Quarters quarters) {
  double sum = 0;
  sum += quarters.first != EMPTY_CHAR ? 0.25 : 0;
  sum += quarters.second != EMPTY_CHAR ? 0.25 : 0;
  sum += quarters.third != EMPTY_CHAR ? 0.25 : 0;
  sum += quarters.fourth != EMPTY_CHAR ? 0.25 : 0;

  return sum;
}