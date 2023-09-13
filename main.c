#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// I implement a linked list to read in my file based on the number of letters. Here is the struct
struct Node {
    char data[81];
    struct Node* next;
};

//first thing called in main and is only called once to signal that this is the beggining of the game
void displayBeggining(){
    printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
    printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
    printf("Enjoy!\n\n");
}

void linkedListMaker(struct Node** head, struct Node** tail, char* word) {
    struct Node* newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Out of memory\n");
        exit(1);
    }
    strncpy(newNode->data, word, sizeof(newNode->data));
    newNode->next = NULL;

    if (*head == NULL) {
        // the list is currently empty
        *head = newNode;
        *tail = newNode;
    } else {
        // append the new node to the end of the list
        (*tail)->next = newNode;
        *tail = newNode;

    }
}

//used for random words as it retrieves a random word from the linked list using simple iteration
char* playRandoms(struct Node* head, char* word[81], int linksize){
    int rando = rand()%linksize;
    int counter = 0;
    struct Node *ptemp = head;
    while(counter != rando){
        ptemp = ptemp->next;
        counter++;
    }
    return ptemp->data;
}

//checks to see if the input word is equal in letters as the beggining input of number of letters
int quantity(char* word[81],int numletters){
    if(strlen(word) == numletters){
        return 1;
    }
    else{
        return 0;
    }
}

//checks to see that there is only one difference in sequential words during actual gameplay
int  oneDifference(char word[81], char other[81]){
    int differences = 0;
    for(int i = 0;i<strlen(word);i++){
        if(word[i] != other[i]){
            differences++;
        }
    }
    if(differences == 1){
        return 1;
    }
    else{
        return 0;
    } 

}

//checks to see if inputted word is actually in the linked list, deeming it a valid dictionary word
int inList(struct Node* head, char* word, int listsize) {
    struct Node* ptemp = head;
    while (ptemp != NULL) {
        if (strcmp(ptemp->data, word) == 0) {
            return 1;
        }
        ptemp = ptemp->next;
    }
    return 0;
}

/* this is the main body and gameplay of the program. It inputs two words and deciphers all
valid conditions by calling previous functions. After words are deemed valid, I have a while loop
that checks to see further conditions and exits once the inputted word equals the second word*/
void playGame(struct Node* head,int listsize, int numletters){
    char input[81];
    char input2[81];
    printf("Enter starting and ending words, or 'r' for either for a random word: ");
    scanf("%s", input);
    scanf("%s", input2);
    char *firstword;
    char *secondword;
    if(strlen(input) == 1 && input[0] == 'r'){
       firstword = playRandoms(head, &input,listsize);
    }
    else{
        firstword = input;
    }
    if(strlen(input2) == 1 && input2[0] == 'r'){
        secondword = playRandoms(head, &input2,listsize);
    }
    else{
        secondword = input2;
    }
    if(quantity(firstword,numletters) == 0 && strlen(firstword) != 1){
        //printf("%d \n",quantity(firstword,numletters));
        printf("Your word, '%s', is not a %d-letter word. Try again.\n",firstword,numletters);
        playGame(head,listsize,numletters);
        return;
    }
    if(quantity(secondword,numletters) == 0 && strlen(secondword) != 1){
        //printf("%d \n",quantity(secondword,numletters));
        printf("Your word, '%s', is not a %d-letter word. Try again.\n",secondword,numletters);
        playGame(head,listsize,numletters);
        return;
    }
    if(inList(head,firstword,listsize) != 1){
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n",firstword);
        playGame(head,listsize,numletters);
        return;
    }
    if(inList(head,secondword,listsize) != 1){
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n",secondword);
        playGame(head,listsize,numletters);
        return;
    }
    //preliminary checks of start and finish words are done

    printf("Your starting word is: %s.\n", firstword);
    printf("Your ending word is: %s.\n\n", secondword);
    printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
    printf("You may also type in 'q' to quit guessing.\n");
    int num = 1;
char tries[81];
char current[81] = ""; // used to call one difference and is meant to keep track of previous, or 'current' word comparer
while(1) {
    printf("\n");
    if(num == 1){   // current is empty
        printf("%d. previous word is '%s'. Goal word is '%s'. Next word: ",num,firstword,secondword);
    }
    else{
        printf("%d. previous word is '%s'. Goal word is '%s'. Next word: ",num,current,secondword);
    }
    scanf("%s", tries);
    if(strlen(tries) == 1 && tries[0] == 'q'){return;}
    if(quantity(tries,numletters) == 1){
        if(inList(head,tries,listsize) == 1){
            if(strlen(current) == 0){ 
                if(oneDifference(firstword,tries) == 1){
                    if(strcmp(tries,secondword) == 0){   // all conditions are met and the word is finally reached
                        printf("Congratulations! You changed '%s' into '%s' in %d moves.\n\n",firstword,secondword,num);
                        break;
                    }
                    else{
                        num++;
                        strcpy(current,tries);
                        continue;
                    }
                }
                else{
                    printf("Your word, '%s', is not exactly 1 character different. Try again.\n\n",tries);
                    continue;
                }
            }           //these two big branches indicate the difference between first input and sequential ones as current will be empty
            else{
                if(oneDifference(tries,current) == 1){
                    if(strcmp(tries,secondword) == 0){  // all conditions are met and the word is finally reached
                        printf("Congratulations! You changed '%s' into '%s' in %d moves.\n\n",firstword,secondword,num);
                        break;
                    }
                    else{
                        num++;
                        strcpy(current,tries);
                        continue;
                    }
                }
                else{
                    printf("Your word, '%s', is not exactly 1 character different. Try again.\n\n",tries);
                    continue;
                }
            }
        }
        else{
            printf("Your word, '%s', is not a valid dictionary word. Try again.\n\n",tries);
        }
    }
    else{
        printf("Your word, '%s', is not a %d-letter word. Try again.\n\n",tries,numletters);
    }
}

}

/* this is how the program starts. It initiallizes a linked list based on the number of letters inputted as well as the list size*/
void displayFromNumWords(int *listsize, int *numletters, struct Node** head, struct Node** tail) {
    *listsize = 0; // dereference the pointer to listsize
    printf("How many letters do you want to have in the words? ");
    scanf("%d", numletters); // don't use & since numletters is already a pointer

    char filename[] = "words.txt";
    FILE *filePtr = fopen(filename, "r");
    if(filePtr == NULL) {
        printf("Error: could not open %s for reading\n", filename);
        exit(-1);
    }

    char inputString[81];
    while(fscanf(filePtr, "%s", inputString) != EOF) {
        if (strlen(inputString) == *numletters) {
            linkedListMaker(head, tail, inputString); // dereference the pointers to head and tail
            (*listsize)++; // dereference the pointer to listsize
        }
    }

    fclose(filePtr);
    printf("Number of %d-letter words found: %d.\n\n", *numletters, *listsize);
}

//empties list if quitmenu 2 is chosen and at the end of the program. Makes memory leaks go away
void emptyList(struct Node** head) {
    struct Node* current = *head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

//returns the number based on what option is chosen
int quitMenu(){
    printf("\nEnter: \t1 to play again,\n");
    printf("\t2 to change the number of letters in the words and then play again, or\n");
    printf("\t3 to exit the program.\n");
    printf("Your choice --> ");
    int option;
    scanf("%d", &option);
    if(option == 1){
        return 1;
    }
    else if(option == 2){
        return 2;
    }
    else if(option == 3){
        printf("\nThanks for playing!\n");
        printf("Exiting...");
        return 3;
    }
}

int main() {
    srand(1);
    displayBeggining();
    int listsize;
    int numletters;
    struct Node *head = NULL;
    struct Node *tail = NULL;
    displayFromNumWords(&listsize, &numletters, &head, &tail); // first iteration happens outside of for loop, since I do not want to use quitMenu before first game
    playGame(head,listsize,numletters);
    int x = quitMenu();
    while(x != 3){     // while quitmenu does not equal 3, start program again from appropriate function and then run quitMenu again
        if(x==1){
            playGame(head,listsize,numletters);
            x = quitMenu();
            if(x == 3){break;}
            else{
            continue;
            }
        }
        else if(x == 2){
            emptyList(&head);
            displayFromNumWords(&listsize, &numletters, &head, &tail);
            playGame(head,listsize,numletters);
            x = quitMenu();
            if(x==3){break;}
            else{
            continue;
            }


        }
    }
    emptyList(&head);  //terminal emptying of list

        

    }
    