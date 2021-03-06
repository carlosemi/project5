/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataBST.cpp
 * Author: dms147
 *
 * Created on March 27, 2020, 5:48 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


// The following two function implement the quicksort algorithm.
// They are from some web site on the internet. The link of the
// web page unavailable at this time
int partition(vector<int> &values, int left, int right) {
    if (left>=right)
        return -1;
    int pivotIndex = left + rand()%(right - left+1)-1;
    int pivotValue = values[pivotIndex];
    int i = left, j = right;
    int temp;
    while(i <= j) {
        while(values[i] < pivotValue) {
            i++;
        }
        while(values[j] > pivotValue) {
            j--;
        }
        if(i <= j) {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void qSortVec(vector<int> &values, int left, int right) {
    if(left < right) {
        int pivotIndex = partition(values, left, right);
        qSortVec(values, left, pivotIndex - 1);
        qSortVec(values, pivotIndex, right);
    }
}

// Class DATABSTNode represents a single node in a binary search tree (BST).
class DataBSTNode{
    public: 
        
        // The following attributes are declared public
        // for the convenience of accessing them.        
        int val;
        DataBSTNode *left;
        DataBSTNode *right;
        DataBSTNode *parent;
        
        // Constructor Function for creating a node in a BST
        // with initial value of aVal
        DataBSTNode(int aVal){
            val = aVal;
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        
        // Destructor function, optional
        ~DataBSTNode(){
            //delete left;
            //delete right;
        }

        // This function returns the sequence of key values
        // of nodes in the BST in the order the nodes appear
        // in the inorder tree traversal.
        string getInOrder(){
            string inOrder = "";
            if(left!=NULL)
                inOrder += left->getInOrder() +", ";
            inOrder += to_string(val);
            if(right!=NULL)
                inOrder += ", " + right->getInOrder();
            
            return inOrder;
        }
        
        // This function returns the sequence of key values
        // of nodes in the BST in the order the nodes appear
        // in the inorder tree traversal.
        string getPreOrder(){
            string preOrder = to_string(val);
            
            if(left!=NULL)
                preOrder += ", "+left->getPreOrder();
            if(right!=NULL)
                preOrder += ", " + right->getPreOrder();
            
            return preOrder;
        }

        // This function returns the height of the BST.
        int getHeight(){
            int hl = -1, hr = -1;
            
            if(left!=NULL)
                hl = left->getHeight();
            if(right!=NULL)
                hr = right->getHeight();
            
            return max(hl, hr) + 1;
            
        }
        
        // This function returns a set of strings that displays 
        // the BST rotated 45 degree counterclockwise in a text based environment
        void toStrings(int line, int offset, int width, vector<string> &bstStrings){
            for(int i=0; i<offset; i++)
                bstStrings[line] += "    ";
            bstStrings[line] += to_string(this->val);

            if(left!=NULL)
                left->toStrings(line+width+1, offset+1, (width-1)/2, bstStrings);
            if(right!=NULL)
                right->toStrings(line-width-1, offset+1, (width-1)/2, bstStrings);
            
            return;
        }
};

class DataBST{
    public:
        
        // Default Constructor for 
        // creating an empty BST
        DataBST(){
            // The pointers to root of the BST
            mRoot = NULL;
        }
        
        // An alternate constructor function allowing the 
        // initialization of a BST with a vector of given values.
        DataBST(vector<int> &vals){

            buildFromArray(vals);
        }
        
        // initialize/reload the BST with values
        // in the vector parameter vals
        void buildFromArray(vector<int> vals){
            qSortVec(vals, 0, vals.size()-1);
                        
            mRoot = buildFromSortedArray(vals,0,vals.size()-1);
        
        }
        
        // This function searches a node with the value theVal and
        // returns a pointer to a BST node with the value theVal if 
        // such a node exists, or a null pointer otherwise.
        // The function, however, returns a pointer to a node that
        // a new node with value theVal will be linked to if the
        // new node is inserted into the BST.
        DataBSTNode *search(int theVal, bool forInsert=false){
            if (mRoot==NULL)
                return NULL;
            
            DataBSTNode *p = mRoot;
            DataBSTNode *q = NULL;
            while(p!=NULL){
                if (p->val==theVal && !forInsert)
                    return p;
                q = p;
                if(p->val>=theVal)
                    p = p->left;
                else
                    p = p->right;
            }
            
            if(forInsert)
                return q;
            else
                return p;
        }
        
        // This function returns the sequence of key values of nodes 
        // in the BST as they appear in the inorder tree trversal.
        string getInOrder(){
            
            if(mRoot==NULL)
                return "";

            return mRoot->getInOrder();
        }
        
        // This function returns the sequence of key values of nodes 
        // in the BST as they appear in the preorder tree trversal.
        string getPreOrder(){
            
            if(mRoot==NULL)
                return "";

            return mRoot->getPreOrder();
        }
        
        // This function returns the height of the BST
        int getHeight(){
            
            if(mRoot==NULL)
                return -1;
            
            return mRoot->getHeight();
        }
        
        // This function inserts a node into a BST
        void insert(DataBSTNode *dbstNode) {
            
            if (dbstNode==NULL)
                return;
            
            DataBSTNode *p = search(dbstNode->val, true);
            if(p==NULL)
                mRoot = dbstNode;
            else 
                if (p->val>=dbstNode->val)
                    p->left = dbstNode;
                else
                    p->right = dbstNode;
            
            dbstNode->parent = p;
            dbstNode->left = NULL;
            dbstNode->right = NULL;
            
        }
        
        // This function inserts a new node with
        // key value aVal into the BST.
        void insert(int aVal) {
            insert(new DataBSTNode(aVal));
        }

        //This function returns the predecessor of a given node if found in the BST
        int Predecessor(int theVal){

            DataBSTNode *p = mRoot;
            bool end = false;

            //This loops searches for the node, after it finds it
            while(!end){
                
                int z = p->val;

                
                if (z == theVal){   //We found the node
                
                    if(p->left == NULL){    //If the node to the left is empty then the parent is the predecessor
                        p = p->parent;
                        break;
                    }
                    else{   //If the can move to the left it does, then tries moving as far right as possible if there are nodes to the right
                        p = p->left;                      
                        while(p->right != NULL){
                            p = p->right;
                        }
                        break;
                    }
                    
                }

                if(z >= theVal){    //If the current node value is greater than the node value we looking for, move left
                    p = p->left;
                    
                }
                else{   //Else move right
                    p = p->right;
                }

            }

            return p->val;
        }


    


    // This function returns a text-based display of the BST. 
    // This function does not seem to work well for BSTs of 
    // heights more than 5.    
    vector<string> toStrings(){
        
        vector<string> errBSTStrings{"maximal tree height exceeded."};
        vector<string> &bstStrings = errBSTStrings;
        
        int h = getHeight();
        if (h>10){
            return bstStrings;
        }
        
        int numLines = pow(2,h+1)-1;
        bstStrings.clear();
        bstStrings.resize(numLines);
        
        int rootLine = (numLines-1)/2;
        int rootWidth = (rootLine-1)/2;
        
        mRoot->toStrings(rootLine, 0, rootWidth, bstStrings);
        
        return bstStrings;
    }
    
    // This function displays the BST and the inorder and preorder
    // traversals of the BST
    void showBST(){
        
        cout << "*************************************************************************************" << endl;
        cout << "Binary Search Constructed." << endl;
        cout << "InOrder Traversal: " << getInOrder() << endl;
        cout << "PreOrder Traversal: " << getPreOrder() << endl;
        vector<string> dBSTStrings = toStrings();
        for(int i=0; i<dBSTStrings.size(); i++)
        cout << dBSTStrings[i] << endl;        
    }
    

private:

    // Pointer defined that points to the root node of the BST.
    DataBSTNode *mRoot;

    // This helper function recursively builds a BST from an
    // integer array.
    DataBSTNode *buildFromSortedArray(vector<int> vals, int s, int e){
            if (s>e)
                return NULL;
            
            int mid = (s + e)/2;
            DataBSTNode *bstNode = new DataBSTNode(vals[mid]);
            DataBSTNode *leftBSTNode = buildFromSortedArray(vals, s, mid-1);
            DataBSTNode *rightBSTNode = buildFromSortedArray(vals, mid+1, e);
            
            if(leftBSTNode!=NULL){
                bstNode->left = leftBSTNode;
                leftBSTNode->parent = bstNode;
            }
            
            if(rightBSTNode!=NULL){
                bstNode->right = rightBSTNode;
                rightBSTNode->parent = bstNode;
            }
            
            return bstNode;
        }
        
};  



//This functions returns the address if a particular node value is found
void checkForValue(DataBST dBST, int value){
    DataBSTNode *x;
    
    x = dBST.search(value);
    if(x == NULL){
        cout << value << " was NOT found" << endl;
    }
    else{
        cout << value << " was found in address: " << x << endl;
    }
}

//This function will test the insert() function
DataBST checkInsert(DataBST dBST, int x ){
    //The variable value will be the one inserted into each tree so the trees will end up with 3 new values
    //Which will be outputed

    DataBSTNode *value = new DataBSTNode(x); //create new node with value 'x'

    dBST.insert(value);

    return dBST;

}

//This function will test the required functions in the project for each new case of BST
DataBST Testing(DataBST dBST){

    //Testing search function
    cout << "Testing the search function with values 17, 2, and 61" << endl;
    checkForValue(dBST, 17); 
    checkForValue(dBST, 2); 
    checkForValue(dBST, 61); 

    //Checking the height of tree
    int height;

    height = dBST.getHeight();
    cout << "The height of the tree is: " << height << endl;

    //Testing inserting functions
    dBST = checkInsert(dBST, 3);
    return dBST;

   
}

// The main function below provides some sample testing code.
int main(){

    //3 Different vector lists are created and each one is tested using the Testing(dBST) function

    //Vector 1
    // create a BST using an integer array
    vector<int> vals{3, 5, 9, 1, -5, 0, 7, 2,-2,8, 12, 13, -9, 67, 89};
    DataBST dBST(vals);
    dBST.showBST();

    //Test the BST
    int x = dBST.Predecessor(12); //Tests the predecessor function
    cout << "Predecessor of 12: " << x << endl;   
    dBST = Testing(dBST); //Tests the rest of the functions
    string z = dBST.getInOrder(); //Display again after adding the values with the Insert function
    cout << "New list with value 3 added: " << z << endl;

    //Vector 2
    // create a BST with random values.
    vals.clear();
    vals.resize(50);
    for(int i=0; i<vals.size(); i++)
        vals[i] = 2*i+1;
    dBST.buildFromArray(vals);
    dBST.showBST();

    //Test the BST
    x = dBST.Predecessor(3); //Tests the predecessor function
    cout << "Predecessor of 3: " << x << endl;
    dBST = Testing(dBST); //Tests the rest of the functions
    z = dBST.getInOrder(); //Display again after adding the values with the Insert function
    cout << "New list with value 3 added: " << z << endl;

    //Vector 3
    // create a new BST with new and more pseudo random values.
    vals.clear();
    vals.resize(100);
    for(int i=0; i<vals.size(); i++)
        vals[i] = 3*i+1;
    dBST.buildFromArray(vals);
    dBST.showBST();

    //Test the BST
    x = dBST.Predecessor(241); //Tests the predecessor function
    cout << "Predecessor of 241: " << x << endl; 
    Testing(dBST);//Tests the rest of the functions
    z = dBST.getInOrder(); //Display again after adding the values with the Insert function
    cout << "New list with value 3 added: " << z << endl;

    return 0;
}


