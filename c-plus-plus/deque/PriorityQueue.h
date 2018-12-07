#ifndef PRIORITY_QUEUE_H_

#define PRIORITY_QUEUE_H_

#include <iostream>

using namespace std;

#include <iostream>

#include <cstdlib>

enum{

	FALSE = 0,

	TRUE = -1

};

/////////////////////////////////

///// Implements Priority Queue

/////////////////////////////////

// Class Prioriry Queue

class PriorityQueue{

	private:

		// Node of Priority Queue

		struct Node{

        struct Node *Previous;

        int Data;

        struct Node *Next;

		}Current;

		struct Node *head;  // Pointer to Head

		struct Node *ptr;   

        // Pointer for travelling through Queue

		static int NumOfNodes;

        // Keeps track of Number of nodes

	public:

		PriorityQueue(void);

		int Maximum(void);

		int Minimum(void);

		void Insert(int);

		int Delete(int);

		void Display(void);

		int Search (int);

		~PriorityQueue(void);

};

/*

//Main Function

void main()

{

    PriorityQueue PQ;

    int choice;

    int DT;

    while(1)

    {

        cout << "Enter your choice"
             << endl;

        cout << "1. Insert an element"
             << endl;

        cout << "2. Display a priorty Queue"
             << endl;

        cout << "3. Delete an element"
             << endl;

        cout << "4. Search an element"
             << endl;

        cout << "5. Exit"
             << endl;

        cin >> choice;

        switch(choice)

        {

        case 1:

            cout << "Enter a Data to enter Queue"
                 << endl;

            cin >> DT;

            PQ.Insert(DT);

            break;

        case 2:

            PQ.Display();

            break;

        case 3:

            {

                int choice;

                cout << "Enter your choice"
                     << endl;

                cout << "1. Maximum Priority Queue"
                     << endl;

                cout << "2. Minimum Priority Queue"
                     << endl;

                cin >> choice;

                switch(choice)

                {

                case 1:

                    PQ.Delete(PQ.Maximum());

                    break;

                case 2:

                    PQ.Delete(PQ.Minimum());

                    break;

                default:

                    cout << "Sorry Not a correct choice"
                         << endl;

                }

            }

            break;

        case 4:

            cout << "Enter a Data to Search in Queue"
                 << endl;

            cin >> DT;

            if(PQ.Search(DT) != FALSE){

                cout << DT
                     << " Is present in Queue" 
                     << endl;

            }else{

                cout << DT
                     << " is Not present in Queue"
                     << endl;

            }
            break;

        case 5:

            exit(0);

        default:

            cout << "Cannot process your choice"
                 << endl;

        }

    }

}

*/
#endif

