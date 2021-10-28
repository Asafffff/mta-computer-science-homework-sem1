#include <stdio.h>

int main() {
  const int basicPizzaPrice = 60;
  const int basicPizzaLength = 40, basicPizzaWidth = 40;
  const int toppingOlivesPrice = 10, toppingMushroomsPrice = 12;
  const int basicDeliveryPrice = 15;

  int customerId;
  int pizzaLength, pizzaWidth;
  float relativePizzaSize;
  float toppingOlivesPortion, toppingMushroomsPortion;
  int isDelivery;

  float pizzaPriceByPizzaSize, toppingsPrice;
  int deliveryPrice;
  float totalPrice = 0, totalPriceIncludingVAT;

  // printWelcomeMessage
  printf("Welcome to MTA-Pizza!\n"
         "*****\n"
         " *** \n"
         "  *  \n");

  // getCustomerIdFromInput
  printf("Please enter your ID number:\n");
  scanf("%d", &customerId);

  // printMenu
  printf("Our menu:\n"
         "*********\n"
         "Basic pizza: %.2f NIS for %dx%d size pizza\n",
         (float)basicPizzaPrice, basicPizzaLength, basicPizzaWidth);

  printf("Toppings for basic size pizza:\n"
         "Olives: %d NIS\n"
         "Mushrooms: %d NIS\n",
         toppingOlivesPrice, toppingMushroomsPrice);

  printf("Dough type for basic size pizza:\n"
         "Regular: \n"
         "Vegan: \n"
         "Whole wheat: \n"
         "Gluten free: \n");

  // getPizzaLengthFromInput
  printf("Please enter your pizza's length (cm): ");
  scanf("%d", &pizzaLength);

  // getPizzaWidthFromInput
  printf("Please enter your pizza's width (cm): ");
  scanf("%d", &pizzaWidth);

  // calculateRelativePizzaSize
  relativePizzaSize = ((float)pizzaLength * pizzaWidth) / (basicPizzaLength * basicPizzaWidth);

  // chooseTopings
  printf("Please choose the toppings:\n\n");

  // chooseTopings - addOlivesToppingToPizza
  printf("Olives - Enter 1 for the whole pizza\n"
         "0.5 for half\n"
         "0.25 for quarter\n"
         "or 0 for none: ");
  scanf("%f", &toppingOlivesPortion);

  // chooseTopings - addMushroomsToppingToPizza
  printf("Mushrooms - Enter 1 for the whole pizza\n"
         "0.5 for half\n"
         "0.25 for quarter\n"
         "or 0 for none: ");
  scanf("%f", &toppingMushroomsPortion);

  // chooseDeliveryType
  printf("Do you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
  scanf("%d", &isDelivery);

  // calculateTotalPrice
  // calculateTotalPrice - calculatePizzaPriceByPizzaSize
  pizzaPriceByPizzaSize = relativePizzaSize * basicPizzaPrice;

  // calculateTotalPrice - calculateToppingsPrice
  toppingsPrice = relativePizzaSize *
                  ((toppingOlivesPrice * toppingOlivesPortion) + (toppingMushroomsPrice * toppingMushroomsPortion));

  // calculateTotalPrice - calculateDeliveryPrice
  deliveryPrice = isDelivery * basicDeliveryPrice;

  // calculateTotalPrice - calculateTotalPrice
  totalPrice = pizzaPriceByPizzaSize + toppingsPrice + isDelivery * deliveryPrice;
  totalPriceIncludingVAT = totalPrice * 1.17;

  // printOrderSummaryForId
  printf("Your order details:\n"
         "*******************\n"
         "ID number: %09d\n"
         "Pizza size: %dx%d\n"
         "Total price: %.2f\n"
         "Total price with tax (rounded down): %d\n"
         "Thank you for your order!",
         customerId, pizzaLength, pizzaWidth, totalPrice, (int)totalPriceIncludingVAT);

  return 0;
}