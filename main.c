#include <stdbool.h>
#include <stdio.h>

struct Pizza {
  int length;
  int width;
  char doughType;
  float relativeSize;
  float toppingOlivesPortion;
  float toppingMushroomsPortion;
};

int main() {
  const int basicPizzaPrice = 60;
  const int basicPizzaLength = 40, basicPizzaWidth = 40;
  const int toppingOlivesPrice = 10, toppingMushroomsPrice = 12;
  const int doughTypeRegularPrice = 0, doughTypeVeganPrice = 5, doughTypeWholeWheatPrice = 3,
            doughTypeGlutenFreePrice = 4;
  const int basicDeliveryPrice = 15;

  int customerId;
  int pizzasAmount;
  int isDelivery;

  int deliveryPrice;
  float totalPriceIncludingVAT;
  float totalPrice = 0;

  int customerPaymentAmountInNIS;
  int paymentChange, remainingChange, remainingChangeInTens, remainingChangeInFives, remainingChangeInTwos,
      remainingChangeInOnes;

  // printWelcomeMessage
  printf(" Welcome to MTA-Pizza!\n"
         "*****\n"
         " *** \n"
         "  *  \n");

  // getCustomerIdFromInput
  printf("Please enter your ID number:\n");
  scanf("%d", &customerId);

  // printMenu
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

  // getPizzasAmountFromInput
  printf("How many pizzas would you like to order?\n");
  scanf("%d", &pizzasAmount);

  // ValidatePizzasAmount
  if (pizzasAmount <= 0) {
    printf("Thank you and goodbye.");
    return 0;
  }

  // buildPizzas
  for (int i = 0; i < pizzasAmount; i++) {
    int pizzaNumber = i + 1;
    struct Pizza pizza;
    int tempToppingOlivesPortion, tempToppingMushroomsPortion;

    bool oneOfToppingsIsNone;
    float sumOfToppingsPortions;

    float pizzaPriceByPizzaSize, doughPrice, toppingsPrice, totalPizzaPrice = 0;

    // printHeader
    printf("*************************************************\n"
           "Pizza #%d:\n\n",
           pizzaNumber);

    // getPizzaLengthFromInput
    printf("Please enter your pizza's length (cm):\n");
    scanf("%d", &pizza.length);

    // TODO Validation to be done by functions with better names when allowed
    // validatePizzaLength - Validate allowed range in 'cm', validate if even
    if (!(pizza.length >= 10 && pizza.length <= 40) || pizza.length % 2 != 0) {
      printf("Invalid length! Basic length was chosen as a default.\n");
      pizza.length = basicPizzaLength;
    }

    // getPizzaWidthFromInput
    printf("Please enter your pizza's width (cm):\n");
    scanf("%d", &pizza.width);

    // TODO Validation to be done by functions with better names when allowed
    // validatePizzaWidth - Validate allowed range in 'cm', validate if even
    if (!(pizza.width >= 10 && pizza.width <= 80) || pizza.width % 2 != 0) {
      printf("Invalid width! Basic width was chosen as a default.\n");
      pizza.width = basicPizzaWidth;
    }

    // getPizzaDoughType
    printf("Please enter the pizza's dough type:\n"
           "r - for regular\n"
           "v - for vegan\n"
           "w - for whole wheat\n"
           "f - for gluten-free\n");
    scanf(" %c", &pizza.doughType);

    // validateDoughType
    if (!(pizza.doughType == 'r' || pizza.doughType == 'v' || pizza.doughType == 'w' || pizza.doughType == 'f')) {
      printf("Invalid choice! Regular dough was chosen as a default.\n");
      pizza.doughType = 'r';
    }

    // calculateRelativePizzaSize
    pizza.relativeSize = ((float)pizza.length * pizza.width) / (basicPizzaLength * basicPizzaWidth);

    // chooseToppings
    printf("Please choose the toppings:\n\n");

    // chooseToppings - addOlivesToppingToPizza
    printf("Olives (choose 0-3):\n"
           "0. None\n"
           "1. Whole pizza\n"
           "2. Half pizza\n"
           "3. Quarter pizza\n");
    scanf("%f", &pizza.toppingOlivesPortion);
    tempToppingOlivesPortion = pizza.toppingOlivesPortion;

    // chooseToppings - validateToppings
    if (!(pizza.toppingOlivesPortion >= 0 && pizza.toppingOlivesPortion <= 3)) {
      printf("Invalid choice! Current topping not added.\n");
      pizza.toppingOlivesPortion = 0;
    }

    // chooseToppings - addMushroomsToppingToPizza
    printf("Mushrooms (choose 0-3):\n"
           "0. None\n"
           "1. Whole pizza\n"
           "2. Half pizza\n"
           "3. Quarter pizza\n");
    scanf("%f", &pizza.toppingMushroomsPortion);
    tempToppingMushroomsPortion = pizza.toppingMushroomsPortion;

    // chooseToppings - validateToppings
    if (!(pizza.toppingMushroomsPortion >= 0 && pizza.toppingMushroomsPortion <= 3)) {
      printf("Invalid choice! Current topping not added.\n");
      pizza.toppingMushroomsPortion = 0;
    }

    // mapToppingsToValues
    switch (tempToppingOlivesPortion) {
      case 0:
        pizza.toppingOlivesPortion = 0;
        break;
      case 1:
        pizza.toppingOlivesPortion = 1;
        break;
      case 2:
        pizza.toppingOlivesPortion = 0.5;
        break;
      case 3:
        pizza.toppingOlivesPortion = 0.25;
        break;
      default:
        return -1;
    }

    // mapToppingsToValues
    switch (tempToppingMushroomsPortion) {
      case 0:
        pizza.toppingMushroomsPortion = 0;
        break;
      case 1:
        pizza.toppingMushroomsPortion = 1;
        break;
      case 2:
        pizza.toppingMushroomsPortion = 0.5;
        break;
      case 3:
        pizza.toppingMushroomsPortion = 0.25;
        break;
      default:
        return -1;
    }

    // validateToppingOverflow
    oneOfToppingsIsNone = (pizza.toppingOlivesPortion == 0 || pizza.toppingMushroomsPortion == 0);
    sumOfToppingsPortions = (pizza.toppingOlivesPortion + pizza.toppingMushroomsPortion);

    if (!oneOfToppingsIsNone) {
      if (sumOfToppingsPortions > 1) {
        printf("You have exceeded the maximum amount of toppings allowed on one pizza! Current topping not added.\n");
        pizza.toppingMushroomsPortion = 0;
      }
    }

    // calculatePizzaPrice
    // calculatePizzaPrice - calculatePizzaPriceByPizzaSize
    pizzaPriceByPizzaSize = pizza.relativeSize * basicPizzaPrice;

    // calculateDoughPrice
    switch (pizza.doughType) {
      case 'r':
        doughPrice = pizza.relativeSize * doughTypeRegularPrice;
        break;
      case 'v':
        doughPrice = pizza.relativeSize * doughTypeVeganPrice;
        break;
      case 'w':
        doughPrice = pizza.relativeSize * doughTypeWholeWheatPrice;
        break;
      case 'f':
        doughPrice = pizza.relativeSize * doughTypeGlutenFreePrice;
        break;
      default:
        printf("Error. Input doesn't match any available dough types. Please try again.");
        return 1;
    }

    // calculatePizzaPrice - calculateToppingsPrice
    toppingsPrice = pizza.relativeSize * ((toppingOlivesPrice * pizza.toppingOlivesPortion) +
                                          (toppingMushroomsPrice * pizza.toppingMushroomsPortion));

    // calculatePizzaPrice - calculateTotalPizzaPrice
    totalPizzaPrice = pizzaPriceByPizzaSize + doughPrice + toppingsPrice;
    totalPrice += totalPizzaPrice;

    // printPizzaSummary
    printf("Pizza #%d details:\n"
           "*******************\n",
           pizzaNumber);
    printf("Pizza size: %dx%d\n", pizza.length, pizza.width);
    printf("Pizza price (without tax): %.2f\n", totalPizzaPrice);
  }

  // printSeparator
  printf("*************************************************\n");

  // chooseDeliveryType
  printf("Do you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up:\n");
  scanf("%d", &isDelivery);

  // validateDeliveryType
  if (!(isDelivery == 0 || isDelivery == 1)) {
    printf("Invalid choice! Pick-up was chosen as a default.\n");
    isDelivery = 0;
  }

  // calculateTotalPrice - calculateDeliveryPrice
  deliveryPrice = isDelivery * basicDeliveryPrice;

  // calculateTotalPrice - calculateTotalPrice
  totalPrice += deliveryPrice;
  totalPriceIncludingVAT = totalPrice * 1.17;

  // printOrderSummaryForId
  printf("Your order details:\n"
         "*******************\n");
  printf("ID number: %09d\n", customerId);
  printf("Number of pizzas: %d\n", pizzasAmount);
  printf("Total price: %.2f\n"
         "Total price with tax (rounded down): %d\n",
         totalPrice, (int)totalPriceIncludingVAT);

  // getPaymentInCashFromInput
  printf("Please enter your payment:\n");
  scanf("%d", &customerPaymentAmountInNIS);

  // calculatePaymentChange
  paymentChange = customerPaymentAmountInNIS - (int)totalPriceIncludingVAT;

  while (paymentChange < 0) {
    printf("Your remaining balance is: %d\n", -1 * paymentChange);
    printf("Please enter your payment:\n");
    scanf("%d", &customerPaymentAmountInNIS);

    paymentChange += customerPaymentAmountInNIS;
  }

  remainingChange = paymentChange;

  // calculatePaymentChange - calculateRemainingChangeInTens
  remainingChangeInTens = remainingChange / 10;
  remainingChange -= remainingChangeInTens * 10;

  // calculatePaymentChange - calculateRemainingChangeInFives
  remainingChangeInFives = remainingChange / 5;
  remainingChange -= remainingChangeInFives * 5;

  // calculatePaymentChange - calculateRemainingChangeInTwos
  remainingChangeInTwos = remainingChange / 2;
  remainingChange -= remainingChangeInTwos * 2;

  // calculatePaymentChange - calculateRemainingChangeInOnes
  remainingChangeInOnes = remainingChange / 1;
  remainingChange -= remainingChangeInOnes * 1;

  // printPaymentChange
  if (paymentChange > 0) {
    printf("Your change is %d NIS using:\n", paymentChange);
    if (remainingChangeInTens > 0) {
      printf("%d coin(s) of ten\n", remainingChangeInTens);
    }
    if (remainingChangeInFives > 0) {
      printf("%d coin(s) of five\n", remainingChangeInFives);
    }
    if (remainingChangeInTwos > 0) {
      printf("%d coin(s) of two\n", remainingChangeInTwos);
    }
    if (remainingChangeInOnes > 0) {
      printf("%d coin(s) of one\n", remainingChangeInOnes);
    }
  }

  printf("Thank you for your order!");

  return 0;
}