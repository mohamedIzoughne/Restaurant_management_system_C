#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>cmd
char MANAGER_PASSWORD[] = "12345";

typedef struct foodItem{
    char name[30];
    float price;
    char category[30];
    struct foodItem *next;
} foodItem;

typedef struct orderItem{
    foodItem* food;
    int quantity;
    struct orderItem* next;
} orderItem;

typedef struct {
    char fullName[30];
    char phoneNumber[30];
    struct client* next;
    orderItem* order;
} client;


foodItem* createFoodItem(char name[], float price, char category[]) {
    foodItem *item = (foodItem*)malloc(sizeof(foodItem));
    item->price = price;
    strcpy(item->name, name);
    strcpy(item->category, category);
    item->next = NULL;
    return item;
}

void showFoodList(foodItem *first) {
    system("cls");
    printHeader("FOOD LIST");
    foodItem *temp = first;

    if(temp == NULL) {
        printInMiddle("The Food list is empty");
        return;
    }
    int i= 1;
    while(temp != NULL) {
        printf("\t\t\t\t\t\t%d. name: %s, price: %.2f, category: %s\n", i, temp->name, temp->price, temp->category);
        temp = temp->next;
        i++;
    }
}

foodItem* addFoodItem(foodItem *first, char name[], char category[], float price) {
    foodItem *newItem = createFoodItem(name, price, category);
    foodItem *temp = first;

    if(first == NULL) {
        first = newItem;
        return first;
    }

    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newItem;
    return first;
}

foodItem* removeItem(foodItem *first, int index) {
    foodItem *temp = first;
    if(first == NULL) {
        printInMiddle("The food List is empty");
        return first;
    } else if(index == 0) {
        first = first->next;
        free(temp);
        temp = NULL;
        return first;
    }

    for (int i = 0; temp->next != NULL && i < index  - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("please enter a correct number.\n");
    } else {
        foodItem *nextItem = temp->next->next;
        free(temp->next);
        temp->next = nextItem;
        showFoodList(first);
    }

    return first;
}

void editFoodItemPrice(foodItem *first, int index, float newPrice) {
    if (first == NULL) {
        printf("List is empty.\n");
        return;
    }

    foodItem *temp = first;
    int i = 0;

    while (temp != NULL && i < index) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printInMiddle("food item not found\n");
        return;
    }

    temp->price = newPrice;
    printInMiddle("the food item is edited successfully");
}

// ---------

client* createClient(char name[], char phoneNumber[]) {
    client *clientInstance = (client*)malloc(sizeof(client));
    strcpy(clientInstance->fullName, name);
    strcpy(clientInstance->phoneNumber, phoneNumber);
    clientInstance->order = NULL;
    clientInstance->next = NULL;
    return clientInstance;
}

foodItem* getFoodIndex(foodItem* first, int index) {
    if (first == NULL) {
        printf("Food list is empty.\n");
        return NULL;
    }

    foodItem *temp = first;
    int i = 0;

    while (temp != NULL && i < index) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Please Enter a correct number.\n");
        return NULL;
    }

    // Return the pointer to the food item at the given index
    return temp;
}

client* orderMeal(foodItem* firstFood, client* orderingClient, int order, int quantity) {
    foodItem* food = getFoodIndex(firstFood, order - 1);
    orderItem *temp = orderingClient->order;
    orderItem *newOrder = (orderItem*)malloc(sizeof(orderItem));
    newOrder->food = food;
    newOrder->quantity = quantity;
    newOrder->next = NULL;

    if(temp == NULL) {
        orderingClient->order = newOrder;

        return orderingClient;
    }

    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newOrder;

    return orderingClient;
}

orderItem* removeOrder(orderItem* first, int index) {
    orderItem *temp = first;
    if(first == NULL) {
        printInMiddle("The order List is empty");
        return NULL;
    } else if(index == 0) {
        free(temp);
        temp = NULL;
        return first->next;
    }

    for (int i = 0; temp->next != NULL && i < index  - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printInMiddle("please enter a correct number.\n");
    } else {
        orderItem *nextItem = temp->next->next;
        free(temp->next);
        temp->next = nextItem;
        showOrderList(first);
    }

    return first;
}

void showOrderList(orderItem *first) {
    system("cls");
    printHeader("ORDER LIST");
    orderItem *temp = first;

    if(temp == NULL) {
        printInMiddle("The Order list is empty");
        return;
    }
    int i = 1;
    while(temp != NULL) {
        printf("\t\t\t\t\t\t%d. name: %s, price: %.2f, category: %s, x%d\n", i, temp->food->name, temp->food->price, temp->food->category, temp->quantity);
        temp = temp->next;
        i++;
    }
}

void showBill(orderItem *first) {
    system("cls");
    printHeader("FINAL BILL");
    orderItem *temp = first;
    float bill = 0;

    if(temp == NULL) {
        printInMiddle("The Order list is empty");
        return;
    }
    int i = 1;
    while(temp != NULL) {
        float subTotal = temp->food->price * temp->quantity;
        bill += subTotal;
        printf("\t\t\t\t\t\t%d. name: %s, price: %.2f, x%d, sub total: %.2f\n", i, temp->food->name,temp->food->price, temp->quantity, subTotal);
        temp = temp->next;
        i++;
    }
    printf("\n\t\t\t\t\t\t---------------------");
    printf("\n\t\t\t\t\t\Total price: %.2f", bill);

}

void showClients(client *first) {
        client *temp = first;
        system("cls");
        printHeader("CLIENTS");

        if(first == NULL) {
            printInMiddle("There are no clients");
            return;
        }

        while(temp != NULL) {
            printf("\t\t\t\t\t\t\tname: %s, phoneNumber: %s\n", temp->fullName, temp->phoneNumber);
            temp = temp->next;
        }
        printInMiddle("Press any key to continue.");
        getch();
}

client* addClient(client *first, char name[], char phoneNumber[]) {
    client *newItem = createClient(name, phoneNumber);
    client *temp = first;

    if(first == NULL) {
        return newItem;
    }

    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newItem;
    return newItem;
}

void admin(foodItem *first, client* firstClient) {
    system("cls");
    char password[30];
    printHeader("MANAGER SECTION");
    printInMiddle("Please Enter your password :");
    scanf("%s", password);

    if(strcmp(password, MANAGER_PASSWORD) != 0) {
        printInMiddle("Your password is incorrect, please try again");
        printInMiddle("1. Try again");
        printInMiddle("2. Go back");
        int choice = choiceSelection();

        if(choice == 1) {
            admin(first, firstClient);
        };
    } else {
        adminMenu(first, firstClient);
    }
}

void adminMenu(foodItem* first, client* firstClient)
{
    while(1) {
        system("cls");
        printHeader("ADMIN SECTION");
        printInMiddle("1. Show Food List");
        printInMiddle("2. Add new items in the food list");
        printInMiddle("3. Delete items from the food list");
        printInMiddle("4. edit food price");
        printInMiddle("5. show clients");
        printInMiddle("6. Back To Main Menu");
        int choice = choiceSelection();
        char name[50];
        char category[50];
        int price;

        switch(choice) {
        case 1:
            showFoodList(first);
            printInMiddle("Press any key to go back");
            getch();
            break;
        case 2:
            printInMiddle("Food name: ");
            scanf("%s", name);
            printInMiddle("Food category: ");
            scanf("%s", category);
            printInMiddle("Food price: ");
            scanf("%d", &price);

            addFoodItem(first, name, category, price);
            printInMiddle("Done");
            showFoodList(first);
            sleep(0.7);
            break;
        case 3:
            showFoodList(first);
            printInMiddle("Choose the number of food item to remove: ");
            scanf("%d", &choice);
            first = removeItem(first, choice - 1);

            sleep(1);

            break;
        case 4:
            showFoodList(first);
            if(first != NULL) {
                choice = choiceSelection();
                printInMiddle("Please enter a new price: ");
                scanf("%d", &price);
                editFoodItemPrice(first, choice - 1, price);
                showFoodList(first);
                printInMiddle("press any key to go back: ");
                getch();

            } else {
                printInMiddle("There are no items to edit");
            }
            break;
        case 5:
            showClients(firstClient);
            break;
        case 6:
            return;
        }
    }

}

void customerMenu(foodItem *firstFood, client* connectedClient)
{
    while(1) {
    system("cls");
    printHeader("CUSTOMER SECTION");

    printInMiddle("1. Choose a meal");
    printInMiddle("2. View your ordered foods");
    printInMiddle("3. Delete a food from order");
    printInMiddle("4. Display final bill");
    printInMiddle("5. Back To Main Menu");
    int choice = choiceSelection();
    int foodChoice;
    int quantity;

    switch(choice) {
    case 1:
        showFoodList(firstFood);
        printInMiddle("Choose your meal: ");
        scanf("%d", &foodChoice);
        printInMiddle("Please enter the quantity: ");
        scanf("%d", &quantity);
        connectedClient = orderMeal(firstFood, connectedClient, foodChoice, quantity);
        printInMiddle("Order Added");
        break;
    case 2:
        showOrderList(connectedClient->order);
        printInMiddle("Please Press any key to go back.");
        getch();
        break;
    case 3:
        showOrderList(connectedClient->order);
        printInMiddle("Choose the meal you want to remove: ");
        scanf("%d", &choice);
        connectedClient->order = removeOrder(connectedClient->order, choice - 1);
        break;
    case 4:
        showBill(connectedClient->order);
        printInMiddle("Press any key to go back");
        getch();
        break;
    default:
        return;
    }
}
}

void mainMenu()
{
    system("cls");
    printHeader("WELCOME TO RESTAURANT MANAGEMENT SYSTEM");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t\t\t3. Exit--> \n\n");
}

void printInMiddle(char text[]) {
    printf("\n\t\t\t\t\t\t\t%s\n", text);
}

void printHeader(char text[]) {
    printf("\n                                 **************************************************************************\n");
    printf("                                                     %s\n", text);
    printf("                                 **************************************************************************\n\n\n");
}

int choiceSelection() {
    int choice;
    printf("\t\t\t\t\t\t\t   Enter Your Choice =>>>>>: ");
    scanf("%d", &choice);
    return choice;
}

int main()
{
    foodItem* firstFoodItem = createFoodItem("Couscous", 15, "Moroccan food");
    addFoodItem(firstFoodItem, "tajine", "moroccan", 34);
    client* firstClient = addClient(NULL, "Mohamed izourne", "0638742234");
    addClient(firstClient, "Abdelmoula Ougouzal", "0634235234");

    char name[30];
    char phoneNumber[30];
    int choice;

    while(1) {
        mainMenu();
        choice = choiceSelection();
        switch(choice) {
        case 1:
            admin(firstFoodItem, firstClient);
            break;
        case 2:
            system("cls");
            printHeader("CUSTOMER SECTION");

            printInMiddle("Please enter your full name: ");
            scanf("%s", &name);
            printInMiddle("Please enter your phone number: ");
            scanf("%s", &phoneNumber);

            client* newClient = addClient(firstClient, name, phoneNumber);
            customerMenu(firstFoodItem, newClient);
            break;
        default:
            printInMiddle("You exited");
            exit(33);
        }
    }

    return 0;
}
