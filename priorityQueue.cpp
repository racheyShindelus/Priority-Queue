#include <iostream>
#include <cmath>
#include <cassert>
#include <limits>

using namespace std;

class PriorityQueueBHA {

  //
  // PRIVATE STUFF
  //

  private:
    int maxSize; // max number of values this heap can hold
    int currentSize=0; // current number of values this heap holds (total pushes + any initial items we started with
    int *arr; // we will dynamically create this array 
    bool doMinHeap = true;

    int compareCount = 0; // used to keep track of number of compares we do

    int compare(int a, int b){
      compareCount++;
      if(a > b) return 1;
      if (a < b) return -1;
      return 0;  // they must be equal
    }

    int swapCount = 0; // used to keep track of # of swaps we do

    // swap i and j and increment counter
    void swap(int a[], int i, int j){
      swapCount++;
      int temp = a[i]; 
      a[i] = a[j];
      a[j] = temp;
    }


  //
  // PUBLIC STUFF
  //

  public:

  //
  // CONSTRUCTOR - no initial values
  //
    PriorityQueueBHA(int n, bool doMin=true, bool debug=false){ // create a heap array that will hold at least N values (default min)
      int treeHeight = ceil(log2(n+1))-1;
      if (debug) cout << "Heap Constructor() Height of new heap will be " << treeHeight << " for " << n << " values" << endl;
      maxSize = pow(2, treeHeight+1 ) - 1;
      if (debug) cout << "Heap Constructor() Creating array of size " << maxSize << " for " << n << " values" << endl;
      doMinHeap = doMin; // true if we want this to be a min heap

      arr = new int[maxSize]; // create a new array of size 
    }


  //
  // IS EMPTY
  //

    bool isEmpty(){
      return(currentSize==0); // true if N is zero
    }

  //
  // GET SIZE
  //

    int getSize(){
      return(currentSize); // N represents the current number of items in the heap
    }

  //
  // push() - insert a value as a new node in the heap
  //

    void push(int val, bool debug = false){
      cout << " N = " << currentSize << endl;
      if (currentSize >= maxSize){
        cout << "push() Error - heap full at " << maxSize << " cannot insert " << val << " at location " << currentSize << endl;
        return;
      }
      //cout << "Inserting node " << val << " into heap array at location " << N << endl;
      arr[currentSize] = val; // make initial insertion at next available spot in the array
      bubbleUp(currentSize, debug); // bubble up from the current insertion point, as necessary
      currentSize++; // increment total values stored so far
      //printHeap();
      
    } // end push()


  //
  // POP
  //
    int pop(){
      return( removePosition(0) ); // pop highest priority item off the heap, which is ALWAYS the item in array position 0
    }

  //
  // PARENT POSITION
  //
    
    // return the binary heap array position of the parent for the given child position
    int parentPosition(int childPosition){


      if (childPosition == 0) return -1; // no parentPosition for root element

      // note that every parent's left child sits at 2*x+1
      // and right child at 2*x+2
      // but because of integer division truncation, we can compute the parent position for both children simply by dividing the child positon minus by 2. 

      //cout << "parentPosition() of child @ position =" << childPosition << " with value " << arr[childPosition] << " = " << (childPosition-1)/2 << endl;
      return((childPosition-1)/2); // LeftPosition = 2p+1, so p = (LeftPosition-1)/2
      
    } // end parentPosition()

  //
  // Bubble Up - swap the child with its parent until the current heap invariant is satisfied 
  // 

    void bubbleUp(int childPosition, bool debug=false) { // c is the position of the child 

      for( int c=childPosition; c>0; ) { // c is for child position of insertion point; stop if it becomes <=  0
          int p = parentPosition(c); // find the parent p of the child c

          if ( (doMinHeap && compare(arr[c], arr[p]) == -1 )  // swap because arr[child] needs to be > arr[parent]
          ||                                    // OR
              (!doMinHeap && compare( arr[p], arr[c]) ==-1  )) // swap because arr[child] needs to be < arr[parent]
          { 
            if (debug) cout << "  bubbleUp(): " << arr[c] << " swaps with parent " << arr[p] << endl;
            
            swap(arr, c, p); // swap value at c with value at p in arr
            c = p; // update child position to be parent for next loop, if needed
          }
          else {
            return; // done because the arr[c] child value is correct relative to heap type
          }
      }

    } // end bubbleUp()

  //
  // Bubble Down - swap the parent with its child until the current heap invariant is satisfied 
  // 

    void bubbleDown(int parentPosition, bool debug=false) { // 

      for( int p=parentPosition; p<currentSize; ) { // p is for child position of insertion point; stop if it exceeds right-most leave of tree


        int l = 2*p+1; // find the left child position; could be out of range
        int r = 2*p+2; // find right child position; could be out of range
        
        if (l > currentSize-1)
          return; // we can no longer swap since child positions for this parent are beyond current N; no left means no right in a complete tree

        // now we know that at least our left child position exists

        int swapPosition = l; // by default we will be swapping with left child

        // now we need to determine if we will swap with left or right child

        if (doMinHeap ){ // min heap and we have right child
          if (r < currentSize && compare(arr[r],  arr[l] ) != 1){
            swapPosition = r; // choose right child because right child is smaller than left child
          }
          
          // else stick with left child as swapPosition
          //if (lessThanEq(arr[p],  arr[swapPosition] ) )  // are we done?
          if (compare(arr[p],  arr[swapPosition] )!= 1 )  // are we done?
            return; // min heap invariant is ok; we are done
          // else we will need to swap
        } // end min heap check

        else if (!doMinHeap ){ // max heap and we have right child{ 
          if (r < currentSize &&  compare(arr[l], arr[r] )==-1 )
            swapPosition = r; // choose right child because right child is larger than left child
          
          // else stick with left child as swapPosition
          //if ( greaterThanEq(arr[p], arr[swapPosition])  )  // are we done? is arr[p] >= arr[swapPosition]?
          if ( compare(arr[p], arr[swapPosition]) != -1 )     // are we done? is arr[p] >= arr[swapPosition]?
            return; // max heap invariant is ok; we are done
          // else we will need to swap
        } // end max heap check

        // else we need to swap with the child at swapPosition

        if (debug) cout << "  bubbleDown(): " << arr[p] << " at position = " << p << " swaps with child " << arr[swapPosition] << " at position = " << swapPosition << endl;

        swap( arr, p, swapPosition);
        p = swapPosition; // update parent position to be child for next loop, if needed

      } // end for
    } // end bubbleDown()



  //
  // REMOVE POSITION 
  // remove node at a given position in the heap array
  // this is valid for "pop", which is to remvoe the node
  //

    int removePosition(int c, bool debug=false){ // remove node at position =  c (child)
      if (debug) cout << "\n** Removing node at " << c << " with value  = " << arr[c] << endl;

      // N-1 = most recently filled position

      int tempNum = arr[c]; // value we are going to remove

      if (debug) cout << "\n** Swapping child value at position " << c << " = " << arr[c] << " with last element = " << arr[currentSize-1] << endl;


      swap(arr, c, currentSize-1); // swap the item at the specified positio with the position at the end of the array

      // int temp = arr[c];
      // arr[c] = arr[N-1];
      // arr[N-1] = temp;

      currentSize--; // decrement heap usage N
      // notice that we have left our swapped value in the array

      bubbleUp(c, debug); // may or may not bubble up
      bubbleDown(c, debug);

      return(tempNum);  // return the value that we removed

    } // end removePosition()

  //
  // Sort - sort the heap by removing the root value until the heap is "empty"
  // leave the removed items in the array in reverse order
  //

    void sort(){ 

      while(currentSize>1){
        pop();
      }
    }


  //
  // PRINT Priority Queue
  //

    void print() {

      cout << "\nPrint Priority Queue" << endl;
      cout << "--------------------------------------" << endl;
      cout << "Print " << (doMinHeap ? "Min " : "Max " ) << "Heap Array (max size=" << maxSize << ", N current =" << currentSize << "): ";

      for(int i=0; i<currentSize; i++){
        cout << arr[i];
        if (i != currentSize-1 )
          cout << ", ";          // don't print the comma on the last item

      }
      cout << endl;
    } // end print()


  //
  // DESTRUCTOR
  //

    ~PriorityQueueBHA(){ // heap destructor
      delete[] arr; // delete the dynamically allocated array
    }

}; // end PriorityQueueBHA class


//
// Get an integer from input (until success)
// (this function does a bit of extra work to avoid input errors)
//

    int getIntegerInput(){
      int num; 
      cin>>num;     // try to get an integer

      while(true) { // keep trying until we get a good integer
        if(cin.fail()) { // that was not an integer
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(),'\n');
          cout<<"That's not an integer - please try again: ";
          cin>>num;
        }

        if(!cin.fail())  // else if we got the integer, break out of the loop
          break;
      }
      return num; // return the input integer

    } // end getIntegerInput()

//
// MAIN
//

  int main() {
    std::cout << "Priority queue (Implemented via Heap Array) \n";

    cout << "\nHow many items would you like your priority queue to hold?  ";

    int N = 0;
    cin >> N;

    bool doMin = true;


    // ask the user if they want (m)in or ma(x) priority queue
    cout << "\nDo you want a Min Priority Queue (m) or a Max Priority Queue (M) ?  ";
    string pqtype; 
    cin >> pqtype;  

    if (pqtype == "m")
      doMin = true;
    else
      doMin = false;

    // create the PQ
  
    PriorityQueueBHA mh(N, doMin); // create a queue that holds AT LEAST N items (maxSize will be next power of 2 -1)

    // loop for input

    while(1){
      int num;

      cout << "\nEnter any positive NUMBER to push it, or any negative value to pop (then hit return): ";
      num = getIntegerInput();
      if (num < 0 ){ // if negative, we want to pop
        if (!mh.isEmpty()){
          if (doMin) cout << "Popped Min value " << mh.pop() << endl;
          else cout << "Poppsed Max value " << mh.pop() << endl;
        }
        else
          cout << "Sorry - queue is empty. Please enqueue strings first" << endl;
      }
      else // if positive we want to push
         mh.push(num);
      mh.print(); // print the current queue in breadth-first order (highest priority first, at left)
    }

  
    cout << "Done" << endl;
  }
