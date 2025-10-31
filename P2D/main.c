#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct nodeI *PtrToNodeI;
typedef PtrToNodeI IntStack;// we need it for the evaluation of the prefix notation
struct nodeI {
    int element;
    PtrToNodeI next;
};

int isEmptyIntStack(IntStack s) {
    return s->next == NULL;
}

void PopInt(IntStack s) {
    PtrToNodeI firstCell;
    if (isEmptyIntStack(s))
        printf("the Stack is empty");
    else {
        firstCell = s->next;
        s->next = firstCell->next;
        free(firstCell);
    }
}

int TopInt(IntStack s) {
    if (!isEmptyIntStack(s))
        return s->next->element;
    printf("Empty Stack");
    return 0;
}

void PushInt(int x, IntStack s) {
    PtrToNodeI temp;
    temp = (PtrToNodeI) malloc(sizeof(struct nodeI));// reserving memory for the new node
    if (temp == NULL)
        printf("out of space! ");
    else {
        temp->element = x;
        temp->next = s->next;
        s->next = temp;
    }
}

void makeEmptyIntStack(IntStack s) {
    if (s == NULL)
        printf("out of Space");
    else
        while (!isEmptyIntStack(s))
            PopInt(s);
}

IntStack createIntStack() {
    IntStack s;
    s = (struct nodeI *) malloc(sizeof(struct nodeI));
    if (s == NULL)
        printf("out of Space!!");
    s->next = NULL;
    makeEmptyIntStack(s);
    return s;
}

void disposeIntStack(IntStack s) {
    makeEmptyIntStack(s);
    free(s);
}


struct node {
    char *str;   // node for linked list that takes string
    struct node *Next;
    int val;
};
typedef struct node *list;

void deleteList(list l) { /// return to it
    struct node *p;
    struct node *temp;
    p = l->Next;
    l->Next = NULL;
    while (p != NULL) {
        temp = p->Next;
        free(p);
        p = temp;
    }
}

list makeEmpty(list l) { // to empty a list
    if (l != NULL)
        deleteList(l);
    l = (list) malloc(sizeof(struct node));
    if (l == NULL)
        printf("out of memory");
    l->Next = NULL;
    return l;
}

int isEmpty(list l) {
    return (l->Next == NULL); // to check if list is empty

}

void insert(char *s, struct node *p, list l) { // to insert in a linked list after a certain position
    struct node *temp;
    temp = malloc(sizeof(struct node));// reserving space for the new node
    temp->str = s;
    temp->Next = p->Next; // inserting it in the right place in the linked list
    p->Next = temp;
}

void insertLastLOS(char *s, list l) { // to insert the node last in the linked list
    struct node *p = l;
    struct node *temp;
    temp = malloc(sizeof(struct node));
    while (p->Next != NULL)// to find last node
        p = p->Next;
    temp->str = strdup(s);// to take the string
    temp->Next = NULL;
    p->Next = temp;

}

int isLast(struct node *p, list l) {
    return p->Next == NULL;
}

int size(list l) { // to know the size of the linked list
    int counter = 0;
    struct node *p = l->Next;
    while (p != NULL) {
        counter++;
        p = p->Next;
    }
    return counter;
}

typedef struct Snode *PtrToNode;
typedef PtrToNode Stack;
struct Snode {
    char element; // node for stack that take characters as the input
    PtrToNode next;
};

int isEmptyStack(Stack s) {
    return s->next == NULL;
}

void Pop(Stack s) {
    PtrToNode firstCell; // this   function will delete the last / top node from the stack
    if (isEmpty(s))
        printf("the Stack is empty");
    else {
        firstCell = s->next;
        s->next = firstCell->next;
        free(firstCell);
    }
}

char Top(Stack s) { // return the last / top element
    if (!isEmpty(s))
        return s->next->element;
    // printf("Empty Stack");
    return 0;
}

void Push(char x, Stack s) {
    PtrToNode temp;
    temp = (PtrToNode) malloc(sizeof(struct Snode));// reserving space
    if (temp == NULL)
        printf("out of space! ");
    else {
        temp->element = x;
        temp->next = s->next;
        s->next = temp;
    }
}

void makeEmptyStack(Stack s) {
    if (s == NULL)
        printf("out of Space");
    else
        while (!isEmpty(s))
            Pop(s);
}

Stack createStack() {
    Stack s;
    s = (struct node *) malloc(sizeof(struct node));// creating an empty stack
    if (s == NULL)
        printf("out of Space!!");
    s->next = NULL;
    makeEmpty(s);
    return s;
}

void disposeStack(Stack s) {
    makeEmpty(s);
    free(s);
}

list readFile(
        char *str) {// this function will take string from file line by line and will store every string that represent an equation in
    FILE *fp = NULL;        // a node in the linked list and will return the list
    list memory = makeEmpty(NULL);
    fp = fopen(str, "r");// the user will enter the name of the file
    if (fp == NULL) {// in case of an empty file
        printf("empty file");
        return memory;
    } else {
        char eqq[50];// to take string from files
        while (fgets(eqq, sizeof(eqq), fp) != NULL) {
            insertLastLOS(eqq, memory);
        }
        fclose(fp);
        return memory;
    }
}

void whyInvalid(list l) {// this function to print the reason of invalidity
    list V = makeEmpty(NULL);

    struct node *p = l->Next;
    int counter = 1;// to number the equation
    while (p != NULL) {// this loop form the equations in the linked list
        int valid = 1;// flag to determine if valid or not

        Stack order = createStack(); // to test validity of brackets and parentheses
        int SLenght = strlen(p->str);
        for (int i = 0; i < SLenght; i++) {
            if ((i == 0 && p->str[i] == '/') || (i == 0 && p->str[i] == '*') ||
                (i == 0 && p->str[i] == '^')) {//sign in beginning case
                printf("Equation NO %d -> invalid you cant have %c at the begging \n", counter, p->str[i]);
                valid = 0;
                break;
            } else if ((i == (SLenght - 1) && p->str[i] == '+') || (i == (SLenght - 1) && p->str[i] == '/') ||
                       // sign  in last case
                       (i == (SLenght - 1) && p->str[i] == '-')
                       || (i == (SLenght - 1) && p->str[i] == '^') || (i == (SLenght - 1) && p->str[i] == '*')) {
                printf("Equation NO %d -> invalid you cant have %c at the end\n", counter, p->str[i]);
                valid = 0;
                break;
            } else if ((p->str[i] == '^' && p->str[i + 1] == '^') || (p->str[i] == '-' && p->str[i + 1] == '^') ||
                       (p->str[i] == '+' && p->str[i + 1] == '^') ||
                       // multiple cases for signs after each others
                       (p->str[i] == '^' && p->str[i + 1] == '+') ||
                       (p->str[i] == '*' && p->str[i + 1] == '^') || (p->str[i] == '^' && p->str[i + 1] == '*') ||
                       (p->str[i] == '/' && p->str[i + 1] == '^') || (p->str[i] == '^' && p->str[i + 1] == '/') ||
                       (p->str[i] == '*' && p->str[i + 1] == '/') || (p->str[i] == '/' && p->str[i + 1] == '*') ||
                       (p->str[i] == '+' && p->str[i + 1] == '+') || (p->str[i] == '+' && p->str[i + 1] == '*') ||
                       (p->str[i] == '-' && p->str[i + 1] == '*') ||
                       (p->str[i] == '+' && p->str[i + 1] == '/') || (p->str[i] == '-' && p->str[i + 1] == '/')
                       || (p->str[i] == '*' && p->str[i + 1] == '*') || (p->str[i] == '/' && p->str[i + 1] == '/')) {
                printf("Equation NO %d -> invalid you cant have %c after %c \n", counter, p->str[i + 1], p->str[i]);
                valid = 0;
                break;
            } else if ((p->str[i] >= 48 && p->str[i] <= 57 && p->str[i + 1] == '[') ||
                       // no operator between a bracket and a number
                       (p->str[i] >= 48 && p->str[i] <= 57 && p->str[i + 1] == '(')) {
                printf("Equation NO %d -> Invalid there is no operator between %c and %c\n", counter, p->str[i],
                       p->str[i + 1]);
                valid = 0;
                break;
            } else if ((p->str[i + 1] >= 48 && p->str[i + 1] <= 57 && p->str[i] == ']') ||
                       (p->str[i + 1] >= 48 && p->str[i + 1] <= 57 && p->str[i] == ')')) {
                printf("Equation NO %d -> invalid there is no operator between %c and %c\n", counter, p->str[i],
                       p->str[i + 1]);
                valid = 0;
                break;
            } else if(p->str[i+1]=='0' && p->str[i]=='/'){
                printf("invalid division by zero!!\n");
                valid=0;
            }
            else if (isEmptyStack(order) && p->str[i] == ')' ||
                       isEmptyStack(order) && p->str[i] == ']') {// when there is a closing without an opening
                printf("Equation NO %d -> invalid %c does not have an opening bracket \n", counter, p->str[i]);
                valid = 0;
                break;
            } else if (Top(order) == '(' && p->str[i] == ']') { // the case when the brackets are not matching
                printf("Equation NO %d -> invalid ( is not closed properly\n", counter);
                makeEmptyStack(order);
                valid = 0;
                break;
            }
            else if (Top(order) == '[' && p->str[i] == ')') {
                printf("Equation NO %d -> invalid [ is not closed properly\n", counter);
                makeEmptyStack(order);
                valid = 0;
                break;
            } else if (Top(order) == '(' && p->str[i] == ')') {// popping when brackets match
                Pop(order);
            } else if (Top(order) == '[' && p->str[i] == ']') {
                Pop(order);
            } else if ((p->str[i] == '(') || (p->str[i] == '[')) {
                Push(p->str[i], order);
            }



        }
        if (!isEmptyStack(order) && valid == 1) {// when there are only one opening bracket case
            printf("Equation NO %d -> invalid  %c is not closed !\n", counter, Top(order));

            valid = 0;
        }
        if (valid) {
            printf("Equation NO %d -> valid\n", counter);
            insertLastLOS(p->str, V);
        }
        p = p->Next;
        counter++;
    }
    //   return V;
}

void printInvalid(list l) {
    struct node *p = l->Next;
    int counter = 1;
    int valCounter=0;
    while (p != NULL) {
        if (!p->val) {
            printf("equation #%d is invalid:%s", counter, p->str);
        } else valCounter++;
        p = p->Next;
        counter++;
    }
    if(valCounter== size(l)){
        printf("there are no invalid equations\n");
    }
}

void isItValid(
        list l) {// this function will only give value to the atribute val so we can decide which equation is valid or not
    struct node *p = l->Next;
    int counter = 1;
    while (p != NULL) {// this loop form the equations in the linked list

        int valid = 1;// flag to determine if valid or not

        Stack order = createStack(); // to test validity of brackets and parentheses
        int SLenght = strlen(p->str);
        for (int i = 0; i < SLenght; i++) {
            if ((i == 0 && p->str[i] == '/') || (i == 0 && p->str[i] == '*') ||
                (i == 0 && p->str[i] == '^')) {//sign in beginning case
                valid = 0;
                break;
            } else if ((i == (SLenght - 1) && p->str[i] == '+') || (i == (SLenght - 1) && p->str[i] == '/') ||
                       // sign  in last case
                       (i == (SLenght - 1) && p->str[i] == '-')
                       || (i == (SLenght - 1) && p->str[i] == '^') || (i == (SLenght - 1) && p->str[i] == '*')) {
                valid = 0;
                break;
            } else if ((p->str[i] == '^' && p->str[i + 1] == '^') || (p->str[i] == '-' && p->str[i + 1] == '^') ||
                       (p->str[i] == '+' && p->str[i + 1] == '^') ||
                       // multiple cases for signs after each others
                       (p->str[i] == '^' && p->str[i + 1] == '+') ||
                       (p->str[i] == '*' && p->str[i + 1] == '^') || (p->str[i] == '^' && p->str[i + 1] == '*') ||
                       (p->str[i] == '/' && p->str[i + 1] == '^') || (p->str[i] == '^' && p->str[i + 1] == '/') ||
                       (p->str[i] == '*' && p->str[i + 1] == '/') || (p->str[i] == '/' && p->str[i + 1] == '*') ||
                       (p->str[i] == '+' && p->str[i + 1] == '+') || (p->str[i] == '+' && p->str[i + 1] == '*') ||
                       (p->str[i] == '-' && p->str[i + 1] == '*') ||
                       (p->str[i] == '+' && p->str[i + 1] == '/') || (p->str[i] == '-' && p->str[i + 1] == '/')
                       || (p->str[i] == '*' && p->str[i + 1] == '*') || (p->str[i] == '/' && p->str[i + 1] == '/')) {
                valid = 0;
                break;
            } else if ((p->str[i] >= 48 && p->str[i] <= 57 && p->str[i + 1] == '[') ||
                       // no operator between a bracket and a number
                       (p->str[i] >= 48 && p->str[i] <= 57 && p->str[i + 1] == '(')) {
                valid = 0;
                break;
            } else if ((p->str[i + 1] >= 48 && p->str[i + 1] <= 57 && p->str[i] == ']') ||
                       (p->str[i + 1] >= 48 && p->str[i + 1] <= 57 && p->str[i] == ')')) {
                valid = 0;
                break;
            }else if(p->str[i+1]=='0' && p->str[i]=='/'){
                printf("invalid division by zero!!\n");
                valid=0;
            } else if (isEmptyStack(order) && p->str[i] == ')' ||
                       isEmptyStack(order) && p->str[i] == ']') {// when there is an closing without an opening
                valid = 0;
                break;
            } else if (Top(order) == '(' && p->str[i] == ']') { // the case when the brackets are not matching
                makeEmptyStack(order);
                valid = 0;
                break;
            } else if (Top(order) == '[' && p->str[i] == ')') {
                makeEmptyStack(order);
                valid = 0;
                break;
            } else if (Top(order) == '(' && p->str[i] == ')') {// popping when brackets match
                Pop(order);
            } else if (Top(order) == '[' && p->str[i] == ']') {
                Pop(order);
            } else if ((p->str[i] == '(') || (p->str[i] == '[')) {
                Push(p->str[i], order);
            }


        }
        if (!isEmptyStack(order) && valid == 1) {// when there are only one opening bracket case
            valid = 0;
        }
        if (!valid) {
            p->val = 0;
        } else p->val = 1;
        p = p->Next;
    }
}

void reverseString(char *str) { //didnt know strrec existed :(
    int length = strlen(str);
    int i, j;
    char temp;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

list inToPre(list l) {
    list answers = makeEmpty(NULL);
    struct node *p = l->Next;
    int num = 1;// number of equations
    while (p != NULL) {
        if (p->val == 0) {//to skip invalid cases
            p = p->Next;
            continue;
        }
        char stemp[50]; // to store value of each equation
        strcpy(stemp, p->str);
        char pre[50];
        Stack order = createStack();/// we will use it in out conversion method
        reverseString(stemp);// we need to reverse the string to convert it
        int counter = 0;//for the new prefix equation
        for (int i = 0; i < strlen(stemp); ++i) {
            if (stemp[i] >= 48 && stemp[i] <= 57 &&
                i == (strlen(stemp) - 1)) { // when we reach to the end we will empty the stack
                pre[counter] = stemp[i];
                counter++;
                ////////////
                pre[counter] = ' ';// we want space between integers
                counter++;
                ///////
                while (!isEmptyStack(order)) {
                    if (stemp[i] != ')' && stemp[i] != ']') {
                        pre[counter] = Top(order);
                        Pop(order);
                        counter++;
                    } else Pop(order);// because we dont want to print the brackets in the prefix equation
                }
            } else if (stemp[i] >= 48 && stemp[i] <= 57) {// we will put numbers directly in the strings
                pre[counter] = stemp[i];
                counter++;
            } else if (stemp[i] == '+' || stemp[i] == '-') {

                if (isEmptyStack(order) || Top(order) == ']' || Top(order) == ')' || Top(order) == '+' ||
                    Top(order) == '-') {// check the piramade of presidency
                    pre[counter] = ' ';// we want space between integers
                    counter++;
                    ///////////////////////////// return here
                    if (i == (strlen(stemp) -
                              1)) {// in case there were a negative int in teh beging we treat it as it was subtracted from zero

                        pre[counter] = '0';// we want space between integers
                        counter++;
                        pre[counter] = ' ';// we want space between integers
                        counter++;
                        /*pre[counter] = '-';// we want space between integers
                        counter++;
                        pre[counter] = ' ';// we want space between integers
                        counter++;*/
                    }
                    Push(stemp[i], order);
                } else {
                    while ((!isEmptyStack(order) && Top(order) != ')' && Top(order) != ']') && Top(order) != '+' &&
                           // checking allowed presidency
                           Top(order) != '-') { // same for different operations

                        if (Top(order) == ')' || Top(order) == ']') {
                            Pop(order);
                            continue;
                        }
                        ////////////
                        pre[counter] = ' ';// we want space between integers
                        counter++;
                        ///////
                        pre[counter] = Top(order);
                        counter++;
                        Pop(order);
                    }
                    Push(stemp[i], order);
                }
            } else if (stemp[i] == '*' || stemp[i] == '/') {
                if (isEmptyStack(order) || Top(order) == ')' || Top(order) == ']' || Top(order) == '+' ||
                    Top(order) == '-' || Top(order) == '*' || Top(order) == '/') {
                    pre[counter] = ' ';
                    counter++;
                    Push(stemp[i], order);
                } else {
                    while ((!isEmptyStack(order) && Top(order) != ']') && Top(order) != ')' && Top(order) != '+' &&
                           Top(order) != '-' && Top(order) != '*' && Top(order) != '/') {
                        if (Top(order) == ')' || Top(order) == ']') {
                            Pop(order);
                            continue;
                        }
                        ////////////
                        pre[counter] = ' ';// we want space between integers
                        counter++;
                        ///////
                        pre[counter] = Top(order);
                        counter++;
                        Pop(order);
                    }
                    Push(stemp[i], order);
                }
            } else if (stemp[i] == '^') {

                pre[counter] = ' ';
                counter++;
                Push(stemp[i], order);
            } else if (stemp[i] == ']' || stemp[i] == ')') {//opennigs goes to the stack
                Push(stemp[i], order);
            } else if (stemp[i] == '[' || stemp[i] == '(') {
                while (Top(order) != ')' && Top(order) != ']') {// when closing we pop every element between brackets
                    ////////////
                    pre[counter] = ' ';// we want space between integers
                    counter++;
                    ///////
                    pre[counter] = Top(order);
                    counter++;
                    Pop(order);
                }
                Pop(order);
            }

        }
        while (!isEmptyStack(order)) {
            if (Top(order) != ')' && Top(order) != ']') {
                pre[counter] = Top(order);
                Pop(order);
                counter++;
            } else Pop(order);
        }
        pre[counter] = '\0';//to close the string
        reverseString(pre);
        insertLastLOS(pre, answers);// prefix string
        p = p->Next;
        num++;
    }
    return answers;
}

void printPrefix(list l) { // to print the prefix notation stored in the list
    struct node *p = l->Next;
    int count = 1;
    while (p != NULL) {
        printf("Valid equation number #%d in prefix:%s\n", count, p->str);
        p = p->Next;
        count++;
    }
}

int stringToInt(char *str) {// to convert a number from an string form to an integer
    int sum = 0;
    for (int i = 0; i < strlen(str); i++) {
        int val = str[i] - '0';
        sum += val * pow(10, i);
    }
    return sum;
}

int *Evaluate(list l) {// by using stack that will push the last 2 numbers to do every operation on its way
    int lenght = size(l);
    int *answers = malloc(lenght * sizeof(int)); // Create an array dynamically
    struct node *p = l->Next;
    int eqqNum = 0;//numbers of equation

    while (p != NULL) {

        char rev[50];
        strcpy(rev, p->str);
        reverseString(rev);// we need to work from the end to beginning
        int size = strlen(rev);
        IntStack flow = createIntStack();//to track the flow of operations
        int counter = 0;
        char sInt[100];// we will save integers that have more than one digit in it then i will convert it to an integer
        sInt[0] = '\0';

        for (int i = 0; i < size; i++) {
            if (rev[i] == ' ') {
                sInt[counter] = '\0';//to end the string
                if (sInt[0] != '\0') {// if the string is empty it will cause an error
                    int num = stringToInt(sInt); // we turn the string to an int and push it in the stack
                    counter = 0;
                    PushInt(num, flow);
                }
            } else if (rev[i] >= 48 && rev[i] <= 57) {
                sInt[counter] = rev[i];// we take numbers in the string
                counter++;
            } else if (rev[i] ==
                       '+') {// for every operation we will push the top 2 int and preform the operation on them and store the resault in the top of the stack

                int firstOp = TopInt(flow);
                PopInt(flow);

                int secondOp = TopInt(flow);
                PopInt(flow);
                PushInt((firstOp + secondOp), flow);
            } else if (rev[i] == '*') {// the same as above

                int firstOp = TopInt(flow);
                PopInt(flow);
                int secondOp = TopInt(flow);
                PopInt(flow);
                PushInt((firstOp * secondOp), flow);
            } else if (rev[i] == '-') {

                int firstOp = TopInt(flow);
                PopInt(flow);
                if (isEmptyIntStack(flow)) {
                    PushInt(firstOp * -1, flow);// in case of negative integers
                } else {
                    int secondOp = TopInt(flow);
                    PopInt(flow);
                    PushInt((firstOp - secondOp), flow);
                }
            } else if (rev[i] == '/') {
                int firstOp = TopInt(flow);
                PopInt(flow);
                int secondOp = TopInt(flow);
                PopInt(flow);
                PushInt((firstOp / secondOp), flow);
            } else if (rev[i] == '^') {
                int firstOp = TopInt(flow);
                PopInt(flow);
                int secondOp = TopInt(flow);
                PopInt(flow);
                PushInt(((int) pow(firstOp, secondOp)), flow);
            }
        }

        //printf("Equation number %d-> %d\n", eqqNum, TopInt(flow));
        answers[eqqNum] = TopInt(flow);
        p = p->Next;
        eqqNum++;
    }
    return answers;
}

void writeFile(list eqqs) {
    FILE *fp = fopen("output.txt", "w");// opening output file
    struct node *p = eqqs->Next;
    int eqqCounter = 1;
    isItValid(eqqs);
    while (p != NULL) {
        if (p->val == 1)// to check which are valid equations and will print the valid ones
            fprintf(fp, "Equation #%d is valid:%s\n", eqqCounter, p->str);
        else fprintf(fp, "Equation #%d is not valid:%s\n", eqqCounter, p->str);

        p = p->Next;
        eqqCounter++;
    }
    list pre = inToPre(eqqs);
    p = pre->Next;
    eqqCounter = 1;
    while (p != NULL) {// just printing you know
        fprintf(fp, "\nValid equation number #%d in prefix:%s\n", eqqCounter, p->str);
        p = p->Next;
        eqqCounter++;
    }
    int *values = Evaluate(pre);
    for (int i = 0; i < size(pre); i++) {
        fprintf(fp, "\nvalid Equation result #%d->%d\n", (i + 1), values[i]);
    }
    fclose(fp);


}

int main() {

    list eqq = makeEmpty(NULL);
    list valid = makeEmpty(NULL);
    list pre = makeEmpty(NULL);
    int choose = 0;// to make tghe user choose which option he wants to preform from the options
    while (choose != 7) {
        printf("\nTo read file containing equations enter 1\n");
        printf("To check the validity of the equations enter 2\n");
        printf("To convert equations from infix to prefix enter 3\n");
        printf("To evaluate the prefix equations enter 4\n");
        printf("To print invalid equations enter 5\n");
        printf("To print in output file enter 6\n");
        printf("To exit press 7\n");
        scanf("%d", &choose);
        if (choose > 7 || choose < 1)
            printf("please enter valid number!!!\n");
        if (choose == 1) {
            printf("Enter file name\n");
            char Fname[20];
            scanf("%s", Fname);
            eqq = readFile(Fname);
            isItValid(eqq);
            printf("File was read \n");
        } else if (choose == 2) {
            if (isEmpty(eqq))
                printf("you need to read the file first!!\n");
            else whyInvalid(eqq);
        } else if (choose == 3) {
            if (isEmpty(eqq))
                printf("you need to read the file first!!\n");
            else {
                pre = inToPre(eqq);
                printPrefix(pre);
            }

        } else if (choose == 4) {
            if (isEmpty(pre))
                printf("you need to convert equations to prefix form first!!\n");
            else {
                int *values = Evaluate(pre);
                for (int i = 0; i < size(pre); i++) {
                    printf("valid Equation #%d->%d\n", (i + 1), values[i]);
                }
            };
        } else if (choose == 5) {
            if (isEmpty(eqq))
                printf("you need to read the file first!!\n");
            else printInvalid(eqq);
        } else if (choose == 6) {
            if (isEmpty(eqq))
                printf("you need to read input file first!!\n");
            else {
                writeFile(eqq);
                printf("output file has been updated\n");
            }
        }
    }
    printf("THANKS FOR USING MY PROGRAM :)\n");
    return 1211756;
}