#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MIN_PIZZA_WIDTH 10
#define MIN_PIZZA_LENGTH 10
#define MAX_PIZZA_WIDTH 80
#define MAX_PIZZA_LENGTH 40
#define DELIVERY 1
#define PICKUP 0

struct Pizza {
  int number;
  int length;
  int width;
  char doughType;
  double relativeSize;
  float toppingOlivesPortion;
  float toppingMushroomsPortion;
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
bool isValidCustomerId();
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
float selectOlivesToppingForPizza();
float selectMushroomToppingForPizza();
bool isValidToppingPortion(float toppingPortion);
float mapToppingPortionsToValues(float toppingPortion);
bool isValidToppingSum(float pizzaToppingOlivesPortion, float pizzaToppingMushroomsPortion);
double calculatePizzaPriceByRelativeSize(double pizzaRelativeSize);
double calculateDoughPriceByRelativeSize(double pizzaRelativeSize, char pizzaDoughType);
double calculateToppingsPriceByRelativeSize(double pizzaRelativeSize, float pizzaToppingOlivesPortion,
                                            float pizzaToppingMushroomsPortion);
double calculatePizzaPrice(struct Pizza pizza);
void printPizzaSummary(struct Pizza pizza);
int chooseDeliveryType();
bool isValidDeliveryType(int deliveryType);
int calculateDeliveryPriceByDeliveryType(int deliveryType);
void printOrderSummaryForCustomerId(int customerId, int pizzasAmount, double totalPrice);

int getPaymentInCashFromInput();
int calculatePaymentChange(int customerPaymentAmountInNIS, double totalPriceIncludingVAT);
int askForPaymentUntilNonNegativeChange(int paymentChange);
int calculateRemainingChangeInCoinValue(int remainingChange, int coinValue);
void printPaymentChangeSummary(struct PaymentChange paymentChange);
void handlePayment(double totalPriceIncludingVAT);

bool isEven(int number);
void printSeparator();

const int basicPizzaPrice = 60;
const int basicPizzaLength = 40, basicPizzaWidth = 40;
const int toppingOlivesPrice = 10, toppingMushroomsPrice = 12;
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

  printOrderSummaryForCustomerId(customerId, pizzasAmount, totalPrice);

  handlePayment(totalPriceIncludingVAT);

  printf("Thank you for your order!");

  return EXIT_SUCCESS;
};

void printWelcomeMessage() {
  printf(" Welcome to MTA-Pizza!\n"
         "*****\n"
         " *** \n"
         "  *  \n");
}

int getCustomerIdFromInput() {
  int customerId;

  printf("Please enter your ID number:\n");
  scanf("%d", &customerId);

  while (!isValidCustomerId(customerId)) {
    printf("Invalid ID number! Try again.\n");

    printf("Please enter your ID number:\n");
    scanf("%d", &customerId);
  }

  return customerId;
};

void printMenu() {
  printf("Our menu:\n"
         "*********\n"
         "Basic pizza: %.2f NIS for %dx%d size pizza\n\n",
         (float)basicPizzaPrice, basicPizzaLength, basicPizzaWidth);

  printf("Toppings for basic size pizza:\n"
         "Olives: %d NIS\n"
         "Mushrooms: %d NIS\n\n",
         toppingOlivesPrice, toppingMushroomsPrice);

  printf("Dough type for basic size pizza:\n"
         "Regular: %d NIS\n"
         "Vegan: %d NIS\n"
         "Whole wheat: %d NIS\n"
         "Gluten free: %d NIS\n",
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

  printf("Please enter your pizza's length (cm):\n");
  scanf("%d", &pizzaLength);

  while (!isValidPizzaLength(pizzaLength)) {
    printf("Invalid length! Try again.\n");

    printf("Please enter your pizza's length (cm):\n");
    scanf("%d", &pizzaLength);
  }

  return pizzaLength;
};

int getPizzaWidthFromInput() {
  int pizzaWidth;

  printf("Please enter your pizza's width (cm):\n");
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

  printf("Please enter the pizza's dough type:\n"
         "r - for regular\n"
         "v - for vegan\n"
         "w - for whole wheat\n"
         "f - for gluten-free\n");
  scanf(" %c", &pizzaDoughType);

  while (!isValidDoughType(pizzaDoughType)) {
    printf("Invalid choice! Try again.\n");

    printf("Please enter the pizza's dough type:\n"
           "r - for regular\n"
           "v - for vegan\n"
           "w - for whole wheat\n"
           "f - for gluten-free\n");
    scanf(" %c", &pizzaDoughType);
  }

  return pizzaDoughType;
};

bool isValidDoughType(char pizzaDoughType) {
  return (pizzaDoughType == 'r' || pizzaDoughType == 'v' || pizzaDoughType == 'w' || pizzaDoughType == 'f');
}

double calculateRelativePizzaSize(int pizzaLength, int pizzaWidth) {
  return ((double)pizzaLength * pizzaWidth) / (basicPizzaLength * basicPizzaWidth);
};

float selectOlivesToppingForPizza() {
  float pizzaToppingOlivesPortion;

  printf("Olives (choose 0-3):\n"
         "0. None\n"
         "1. Whole pizza\n"
         "2. Half pizza\n"
         "3. Quarter pizza\n");
  scanf("%f", &pizzaToppingOlivesPortion);

  return pizzaToppingOlivesPortion;
}

float selectMushroomToppingForPizza() {
  float pizzaToppingMushroomPortion;

  printf("Mushrooms (choose 0-3):\n"
         "0. None\n"
         "1. Whole pizza\n"
         "2. Half pizza\n"
         "3. Quarter pizza\n");
  scanf("%f", &pizzaToppingMushroomPortion);

  return pizzaToppingMushroomPortion;
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

bool isValidToppingSum(float pizzaToppingOlivesPortion, float pizzaToppingMushroomsPortion) {
  float sumOfToppingsPortions = (pizzaToppingOlivesPortion + pizzaToppingMushroomsPortion);

  return sumOfToppingsPortions <= 1;
}

struct Pizza addToppingsToPizza(struct Pizza pizza) {
  printf("Please choose the toppings:\n\n");

  // chooseToppings - Olives
  pizza.toppingOlivesPortion = selectOlivesToppingForPizza();

  if (!isValidToppingPortion(pizza.toppingOlivesPortion)) {
    printf("Invalid choice! Current topping not added.\n");
    pizza.toppingOlivesPortion = 0;
  }

  // chooseToppings - Olives - mapToppingPortionsToValues
  pizza.toppingOlivesPortion = mapToppingPortionsToValues(pizza.toppingOlivesPortion);

  // chooseToppings - Mushroom
  pizza.toppingMushroomsPortion = selectMushroomToppingForPizza();

  if (!isValidToppingPortion(pizza.toppingMushroomsPortion)) {
    printf("Invalid choice! Current topping not added.\n");
    pizza.toppingMushroomsPortion = 0;
  }

  // chooseToppings - Mushroom - mapToppingPortionsToValues
  pizza.toppingMushroomsPortion = mapToppingPortionsToValues(pizza.toppingMushroomsPortion);

  // validateToppingOverflow
  if (!isValidToppingSum(pizza.toppingOlivesPortion, pizza.toppingMushroomsPortion)) {
    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Current topping not added.\n");
    pizza.toppingMushroomsPortion = 0;
  }

  return pizza;
}

double calculatePizzaPriceByRelativeSize(double pizzaRelativeSize) {
  return pizzaRelativeSize * basicPizzaPrice;
}

double calculateDoughPriceByRelativeSize(double pizzaRelativeSize, char pizzaDoughType) {
  double doughPrice;

  switch (pizzaDoughType) {
    case 'r':
      doughPrice = pizzaRelativeSize * doughTypeRegularPrice;
      break;
    case 'v':
      doughPrice = pizzaRelativeSize * doughTypeVeganPrice;
      break;
    case 'w':
      doughPrice = pizzaRelativeSize * doughTypeWholeWheatPrice;
      break;
    case 'f':
      doughPrice = pizzaRelativeSize * doughTypeGlutenFreePrice;
      break;
    default:
      printf("Error. Input doesn't match any available dough types. Please try again.");
      exit(EXIT_FAILURE);
  }

  return doughPrice;
}

double calculateToppingsPriceByRelativeSize(double pizzaRelativeSize, float pizzaToppingOlivesPortion,
                                            float pizzaToppingMushroomsPortion) {
  return pizzaRelativeSize *
         ((toppingOlivesPrice * pizzaToppingOlivesPortion) + (toppingMushroomsPrice * pizzaToppingMushroomsPortion));
};

double calculatePizzaPrice(struct Pizza pizza) {
  double pizzaPriceByPizzaSize, doughPrice, toppingsPrice, totalPizzaPrice = 0;

  pizzaPriceByPizzaSize = calculatePizzaPriceByRelativeSize(pizza.relativeSize);
  doughPrice = calculateDoughPriceByRelativeSize(pizza.relativeSize, pizza.doughType);
  toppingsPrice = calculateToppingsPriceByRelativeSize(pizza.relativeSize, pizza.toppingOlivesPortion,
                                                       pizza.toppingMushroomsPortion);

  totalPizzaPrice = pizzaPriceByPizzaSize + doughPrice + toppingsPrice;

  return totalPizzaPrice;
}

void printPizzaSummary(struct Pizza pizza) {
  printf("Pizza #%d details:\n"
         "*******************\n",
         pizza.number);
  printf("Pizza size: %dx%d\n", pizza.length, pizza.width);
  printf("Pizza price (without tax): %.2f\n", pizza.totalPrice);
}

struct Pizza buildPizza(int pizzaNumber) {
  struct Pizza pizza;
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

void printOrderSummaryForCustomerId(int customerId, int pizzasAmount, double totalPrice) {
  double totalPriceIncludingVAT = totalPrice * 1.17;

  printf("Your order details:\n"
         "*******************\n");
  printf("ID number: %09d\n", customerId);
  printf("Number of pizzas: %d\n", pizzasAmount);
  printf("Total price: %.2f\n"
         "Total price with tax (rounded down): %d\n",
         totalPrice, (int)(totalPriceIncludingVAT));
};

int getPaymentInCashFromInput() {
  int customerPaymentAmountInNIS;

  printf("Please enter your payment:\n");
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