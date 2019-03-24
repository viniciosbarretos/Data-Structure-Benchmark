//
//  Vinicios Barretos Batista
//  macOS High Sierra
//  xCode 9.4
//
//  Laboratory of Data Structure I
//  Anderson Rici Amorim
//  UNESP / IBILCE
//  1 June 2018
//

/*
 * 1) Header
 *   1.1) Initialization of Structures
 *   1.2) Global Variables
 *   1.3) Function Prototypes
 *   1.4) Table Parameters
 *
 * 2) Main
 *
 * 3) AVL Tree Manipulation
 *   3.1) Left Rotation
 *   3.2) Right Rotation
 *   3.3) Balance
 *   3.4) Add Element AVL Tree
 *   3.5) Add Element Binary Tree
 *   3.6) Search Element Tree
 *   3.7) Delete Tree
 *
 * 4) Array Manipulation
 *   4.1) Sequential Search
 *   4.2) Binary Search
 *   4.3) Quicksort
 *
 * 5) Experiments
 *   5.1) Get Time
 *   5.2) Create Data and Structures
 *   5.3) Search Data
 *
 *  6) Visual Elements
 *    6.1) Print Rows
 *    6.2) Generate Table
 *    6.3) Pre Head Table
 *    6.4) Head Table
 *    6.5) Separator Line
 *    6.6) Found to String
 *    6.7) Clear Screen
 */

#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

struct node {
    int number;
    int leftHeight;
    int rightHeight;
    struct node *left;
    struct node *right;
};

// Initialization of Structures --------------------------------------------------  [1.1]
#define ArraySize 4000000                            // Max numbers to be added !IMPORTANT
int Array[ArraySize];
node *AVL = NULL;
node *Tree = NULL;


// Global Variables --------------------------------------------------------------  [1.2]
long int iterationNumber;
long int creationIteration[4]; // 0 -> AVL | 1 -> Tree | 2 -> Array Sequential Search | 3 -> Array Binary Search
double creationTime[4];        // 0 -> AVL | 1 -> Tree | 2 -> Array Sequential Search | 3 -> Array Binary Search
long int searchIteration[4];   // 0 -> AVL | 1 -> Tree | 2 -> Array Sequential Search | 3 -> Array Binary Search
double searchTime[4];          // 0 -> AVL | 1 -> Tree | 2 -> Array Sequential Search | 3 -> Array Binary Search
int searchFound[4];            // 0 -> AVL | 1 -> Tree | 2 -> Array Sequential Search | 3 -> Array Binary Search
string identifiers[4] = {"Balanced AVL Tree", "Binary Tree", "Sorted Array", "Sorted Array [BINARY]"};


// Function Prototypes -----------------------------------------------------------  [1.3]
void quickSort (int array[], int left, int right);
node* leftRotation(node *aux);
node* rightRotation(node *aux);
node* balance(node *aux, int height);
node* addAVL(node *aux, int number);
node* addTree(node *tree, int number);
node* deleteTree(node *tree);
int searchTree(node *aux, int number, int found);
int searchSequential (int v[], int size, int number);
int searchBinary (int *v, int size, int number);
double getTime ();
int createData(int elements, long int randNumber);
void searchData(int number, int size);
void printSeparatorLine(int quant);
void printHeadTable();
void printQuantityTable(int quant);
string foundToString(int found);
void printRows();
void generateTable(int numbers, long int range);
void clearScreen();


// Table Parameters --------------------------------------------------------------  [1.4]
const char separator = ' ';
const int nameWidth = 24;
const int creationTimeWidth = 20;
const int creationIterationWidth = 20;
const int searchTimeWidth = 16;
const int searchIterationWidth = 18;
const int foundWidth = 6;
int line = nameWidth + creationTimeWidth + creationIterationWidth + searchTimeWidth + searchIterationWidth + foundWidth;




// Main Section ------------------------------------------------------------------  [2]
int main(int argc, const char * argv[]) {
    
    clearScreen();
    cout << "\n\n[If the table view is wrong increase the width of the window]\n\n";
    
    // Remember to set max array size
    
    generateTable(100000, 200000);
    generateTable(500000, 1000000);
    
    //these tests may take a little longer than expected
    //generateTable(2000000, 2000000);
    //generateTable(4000000, 8000000);
    
    return 0;
}



// AVL Tree Manipulation Section ------------------------------------------------  [3]

// Left Rotation ----------------------------------------------------------------  [3.1]
node* leftRotation(node *aux) {
    iterationNumber++;
    node *aux1, *aux2;
    
    aux1 = aux->right;
    aux2 = aux1->left;
    aux->right = aux2;
    aux1->left = aux;
    
    //count the right height of the original root
    if(aux->right == NULL)
        aux->rightHeight = 0;
    //set the current side height as the highest height (or height) summed up of 1
    else if(aux->right->leftHeight > aux->right->rightHeight)
        aux->rightHeight = aux->right->leftHeight + 1;
    else
        aux->rightHeight = aux->right->rightHeight + 1;
    
    //count the left height of the new root
    if(aux1->left->leftHeight > aux1->left->rightHeight)
        aux1->leftHeight = aux1->left->leftHeight + 1;
    else
        aux1->leftHeight = aux1->left->rightHeight + 1;
    
    return aux1;
}

// Right Rotation ----------------------------------------------------------------  [3.2]
node* rightRotation(node *aux) {
    iterationNumber++;
    node *aux1, *aux2;
    
    aux1 = aux->left;
    aux2 = aux1->right;
    aux->left = aux2;
    aux1->right = aux;
    
    //count the left height of the original root
    if(aux->left == NULL)
        aux->leftHeight = 0;
    else if(aux->left->leftHeight > aux->left->rightHeight)
        aux->leftHeight = aux->left->leftHeight + 1;
    else
        aux->leftHeight = aux->left->rightHeight + 1;
    
    //count the right height of the new root
    if(aux1->right->leftHeight > aux1->right->rightHeight)
        aux1->rightHeight = aux1->right->leftHeight + 1;
    else
        aux1->rightHeight = aux1->right->rightHeight + 1;
    
    return aux1;
}

// Balance ------------------------------------------------------------------------  [3.3]
node* balance(node *aux, int height) {
    iterationNumber++;
    int childheight;
    
    if(height == 2) {
        //height of the right child
        childheight = aux->right->rightHeight - aux->right->leftHeight;
        
        if(childheight >= 0)
            aux = leftRotation(aux);
        else {
            aux->right = rightRotation(aux->right);
            aux = leftRotation(aux);
        }
    }
    else if(height == -2) {
        //height of the left child
        childheight = aux->left->rightHeight - aux->left->leftHeight;
        
        if(childheight <= 0)
            aux = rightRotation(aux);
        else {
            aux->left = leftRotation(aux->left);
            aux = rightRotation(aux);
        }
    }
    
    //return the balanced node
    return aux;
}

// Add Element AVL Tree -----------------------------------------------------------  [3.4]
node* addAVL(node *aux, int number) {
    iterationNumber++;
    int height;
    node *newNode;
    
    if(aux == NULL) {
        newNode = new node();
        newNode->number = number;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->leftHeight = 0;
        newNode->rightHeight = 0;
        aux = newNode;
    }
    else if(number < aux->number) {
        aux->left = addAVL(aux->left, number);
        
        //set height
        if(aux->left->leftHeight > aux->left->rightHeight)
            aux->leftHeight = aux->left->leftHeight + 1;
        else
            aux->leftHeight = aux->left->rightHeight + 1;
        
        //balance
        height = (aux->rightHeight - aux->leftHeight);
        if(height == 2 || height == -2)
            aux = balance(aux, height);
    }
    else {
        aux->right = addAVL(aux->right, number);
        
        if(aux->right->leftHeight > aux->right->rightHeight)
            aux->rightHeight = aux->right->leftHeight + 1;
        else
            aux->rightHeight = aux->right->rightHeight + 1;
        
        height = (aux->rightHeight - aux->leftHeight);
        if(height == 2 || height == -2)
            aux = balance(aux, height);
    }
    
    return aux;
}

// Add Element Binary Tree ------------------------------------------------------  [3.5]
node* addTree(node *tree, int number) { // Add Elements
    iterationNumber++;
    if(tree == NULL) {
        tree = new node();
        tree->number = number;
        tree->left = NULL;
        tree->right = NULL;
    }
    else {
        if(number < tree->number) //Smallest elements go to the left side
            tree->left = addTree(tree->left, number);
        else //Biggest elements go to the right side
            tree->right = addTree(tree->right, number);
    }
    return tree;
}

// Search Element Tree -----------------------------------------------------------  [3.6]
int searchTree(node *aux, int number, int found) {
    iterationNumber++;
    if(aux!=NULL && !found) {
        if(aux->number == number)
            found = 1;
        else {
            if(number < aux->number)
                found = searchTree(aux->left, number, found);
            else
                found = searchTree(aux->right, number, found);
        }
    }
    return found;
}

// Delete Tree --------------------------------------------------------------------  [3.7]
node* deleteTree(node *tree) {
    if(tree!=NULL) {
        deleteTree(tree->left);
        deleteTree(tree->right);
        delete(tree);
    }
    return NULL;
}



// Array Section -----------------------------------------------------------------  [4]

// Search Array Sequential -------------------------------------------------------  [4.1]
int searchSequential (int array[], int size, int number) {
    int m;
    for(m=0; m<size && array[m]<number; m++)
        iterationNumber++;
    if(m == size)
        return 0;
    else
        if(array[m] == number)
            return 1;
        else
            return 0;
}

// Search Array Binary ----------------------------------------------------------  [4.2]
int searchBinary (int *array, int size, int number) { // Array should be sorted
    int m, left, right;
    left = 0;
    right = size - 1;
    while(left <= right) {
        iterationNumber++;
        m = (left+right) / 2;
        if(array[m] == number)
            return 1;
        else
            if(array[m] < number)
                left = m+1;
            else
                right = m-1;
    }
    return 0;
}

// Quicksort ----------------------------------------------------------------------  [4.3]
void quickSort (int array[], int left, int right) {
    int i = left, j = right, aux, x;
    x = array[(i+j) / 2];
    do {
        iterationNumber++;
        while(array[i] < x){
            i++;
            iterationNumber++;
        }
        while(array[j] > x) {
            j--;
            iterationNumber++;
        }
        if(i <= j) {
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
            i++;
            j--;
        }
        
    } while(i < j);
    if(left < j) quickSort(array, left, j);
    if(i < right) quickSort(array, i, right);
}



// Experiments Section ------------------------------------------------------------  [5]

// Get Time -----------------------------------------------------------------------  [5.1]
double getTime () {
    return (double) clock()/CLOCKS_PER_SEC;
}

// Create Data and Structures -----------------------------------------------------  [5.2]
int createData(int elements, long int randNumber) {
    srand((unsigned int)time(NULL));
    int i, number, elementsCount = 0, found;
    double startTime, endTime;
    
    // Delete All Tree Elements
    AVL = deleteTree(AVL);
    Tree = deleteTree(Tree);
    
    // Set to 0 Time and iterations to create the structures
    for(i=0; i<3; i++) {
        creationIteration[i] = 0;
        creationTime[i] = 0;
    }
    
    // Add Elements in array, binary tree and avl tree
    for(i=0; i<elements; i++) {
        
        // Add no repeated numbers
        do {
            found = 0;
            // Generate a random number
            number = rand() % randNumber;
            // Checks if element already was added
            found = searchTree(AVL, number, 0);
        } while(found);
        
        // Count Elapsed Time to add all elements in the Array
        startTime = getTime();
        Array[elementsCount] = number;
        endTime = getTime();
        elementsCount++;
        creationTime[2] += endTime - startTime;
        // Each insertion is a iteration
        creationIteration[2]++;
        
        // Count Iterations and Elapsed Time to add all elements in the AVL Tree
        iterationNumber = 0;
        startTime = getTime();
        AVL = addAVL(AVL, number);
        endTime = getTime();
        creationTime[0] += endTime - startTime;
        creationIteration[0] += iterationNumber;
        
        // Count Iterations and Elapsed Time to add all elements in the Binary Tree
        iterationNumber = 0;
        startTime = getTime();
        Tree = addTree(Tree, number);
        endTime = getTime();
        creationTime[1] += endTime - startTime;
        creationIteration[1] += iterationNumber;
    }
    
    // Sort the array using Quicksort
    elementsCount--;
    iterationNumber = 0;
    startTime = getTime();
    quickSort(Array, 0, elementsCount);
    endTime = getTime();
    creationTime[2] += endTime - startTime;
    creationIteration[2] += iterationNumber;
    
    // Array to Binary Search and Sequential Search is the same
    creationTime[3] = creationTime[2];
    creationIteration[3] = creationIteration[2];
    
    // Generate the number that will be searched
    number = rand() % randNumber;
    return number;
}

// Search Data -------------------------------------------------------------------  [5.3]
void searchData(int number, int size) {
    int i;
    double startTime, endTime;
    
    // Set to 0 time and iterations to search a number
    for(i=0; i<4; i++) {
        searchTime[i] = 0;
        searchIteration[i] = 0;
        searchFound[i] = 0;
    }
    
    // Search in the AVL Tree
    iterationNumber = 0;
    startTime = getTime();
    searchFound[0] = searchTree(AVL, number, 0);
    endTime = getTime();
    searchTime[0] = endTime - startTime;
    searchIteration[0] += iterationNumber;
    
    // Search in the Binary Tree
    iterationNumber = 0;
    startTime = getTime();
    searchFound[1] = searchTree(Tree, number, 0);
    endTime = getTime();
    searchTime[1] = endTime - startTime;
    searchIteration[1] += iterationNumber;
    
    // Sequential Search in the Array
    iterationNumber = 0;
    startTime = getTime();
    searchFound[2] = searchSequential(Array, size, number);
    endTime = getTime();
    searchTime[2] = endTime - startTime;
    searchIteration[2] += iterationNumber;
    
    // Binary Search in the Array
    iterationNumber = 0;
    startTime = getTime();
    searchFound[3] = searchBinary(Array, size, number);
    endTime = getTime();
    searchTime[3] = endTime - startTime;
    searchIteration[3] += iterationNumber;
}


// Visual Elements Section -----------------------------------------------------------------  [6]

// Print Rows ------------------------------------------------------------------------------  [6.1]
void printRows() {
    int i;
    for(i=0; i<4; i++) {
        cout << left << setw(nameWidth) << setfill(separator) << "| " + identifiers[i] << "| ";
        cout << left << setw(creationTimeWidth) << setfill(separator) << to_string(creationTime[i]) + 's' << "| ";
        cout << left << setw(creationIterationWidth) << setfill(separator) << to_string(creationIteration[i]) << "| ";
        cout << left << setw(searchTimeWidth) << setfill(separator) << to_string(searchTime[i]) + 's' << "| ";
        cout << left << setw(searchIterationWidth) << setfill(separator) << searchIteration[i] << "| ";
        cout << left << setw(foundWidth) << setfill(separator) << foundToString(searchFound[i]) << "| ";
        cout << "\n";
    }
}

// Generate Table ---------------------------------------------------------------------------  [6.2]
void generateTable(int numbers, long int range) {
    int search;
    search = createData(numbers, range);
    searchData(search, numbers);
    printQuantityTable(numbers);
    printHeadTable();
    printRows();
    printSeparatorLine(line);
    cout << "\n";
}

// Pre Head Table ------------------------------------------------------------------------------  [6.3]
void printQuantityTable(int quant) {
    //printSeparatorLine(line);
    cout << "\n";
    cout << left << setw(nameWidth-1) << setfill(separator) << "" << "  ";
    cout << left << setw(creationTimeWidth) << setfill(separator) << "" << "  ";
    cout << left << setw(creationIterationWidth) << setfill(separator) << to_string(quant) + " Numbers" << " ";
    cout << "\n";
}

// Head Table ----------------------------------------------------------------------------------  [6.4]
void printHeadTable() {
    printSeparatorLine(line);
    cout << left << setw(nameWidth) << setfill(separator) << "| Name" << "| ";
    cout << left << setw(creationTimeWidth) << setfill(separator) << "Creation time" << "| ";
    cout << left << setw(creationIterationWidth) << setfill(separator) << "Creation iterations" << "| ";
    cout << left << setw(searchTimeWidth) << setfill(separator) << "Search time" << "| ";
    cout << left << setw(searchIterationWidth) << setfill(separator) << "Search iterations" << "| ";
    cout << left << setw(foundWidth) << setfill(separator) << "Found" << "| ";
    cout << "\n";
    printSeparatorLine(line);
}

// Separator Line -----------------------------------------------------------------------------  [6.5]
void printSeparatorLine(int quant) {
    quant += 9;
    int i;
    cout << " ";
    for(i=0; i<quant; i++)
        cout << '-';
    cout << "\n";
}

// Found to String ----------------------------------------------------------------------------  [6.6]
string foundToString(int found) {
    if(found)
        return "Yes";
    else
        return "No";
}

// Clear Screen --------------------------------------------------------------------------------  [6.7]
// This function is to clear terminal both Windows and UNIX
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
