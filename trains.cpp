#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

//Creates a structure for a node that points to the next and previous nodes
struct node {
	int data;
	struct node *next;
	struct node *previous;
	static node* makeNewNode(int data) {
		node* Node = (node*)malloc(sizeof(node));
		Node->data = data;
		Node->previous = NULL;
		Node->next = NULL;
		return Node;
	}
};

//Creates a class named Dequeue (which is a train) that uses nodes (which are the cars)
class Dequeue
{
	node* front;
	node* rear;
	public:
		Dequeue();
		bool isEmptyDequeue();
		void insertFrontDequeue(int data);
		int deleteFrontDequeue();
		int deleteRearDequeue();
		int getDequeueVal(Dequeue myDequeue);


};

//Constructor that sets the front and read nodes to NULL
Dequeue::Dequeue() {
	front = NULL;
	rear = NULL;
}

//Member function that returns a boolean value based if a train is empty
bool Dequeue::isEmptyDequeue() {
	if (front == NULL)
		return 1;
	else
		return 0;
}

//Member function that inserts a new car to the front of the train
void Dequeue::insertFrontDequeue(int data) {
	node* newNode = node::makeNewNode(data);
		if (front == NULL) {
			front = newNode;
			rear = newNode;
		}
		else {
		newNode->next = front;
		front->previous = newNode;
		front = newNode;
		}
}

//Member function that deletes the last car of a train and returns the value of that car so it can be added to another train
int Dequeue::deleteRearDequeue() {
	if (front == NULL) {
		cout << "Dequeue is empty" << endl;
		return 0;
	}
	else {
		int nodeVal = rear->data;
		rear = rear->previous;
		rear->next = NULL;
		return nodeVal;
	}
}

//Member function that deletes the first car of a train and returns the value of that car so it can be added to another train
int Dequeue::deleteFrontDequeue() {
	if (front == NULL) {
		cout << "Dequeue is empty" << endl;
		return 0;
	}
	else {
		int nodeVal = front->data; 
		front = front->next;
		return nodeVal;
	}
}

//Member function that returns the value of a train
int Dequeue::getDequeueVal(Dequeue myDequeue) {
	if (front == NULL)
		return 0;
	else {
		node* myNode = front;
		int val = 0;
		int pos = 1;
		while (myNode->next != NULL) {
			val = val + (pos * myNode->data);
			myNode = myNode->next;
			pos = pos + 1;
		}
	
		val = val + (pos * myNode->data);
		return val;
	}
}

int main(int argc, char *argv[]) {

	int n; //Creates an integer to hold the amount of trains
	int c; //Creates an integer to hold the amount of cars per train
	int t; //Creates an integer to hold the amount turns the simulation can go
	int isTrainEmpty; //Creates an integer that holds the boolean value if a train is empty
	int randDonor; //Creates an integer that holds which train will donate a car
	int randAcceptingTrain; //Creates an integer that holds which train will receive a car
	int randTwoSidedDie; //Creates an integers that holds a value, either 1 or 2 that determines if a car is taken from the front or back
	int x = 0; //Creates a local variable that helps to stop the simulation at the right amount of steps

	//Sets n, c, and t to the command line parameters that were entered;
	if (argc == 4) {
		n = stoi(argv[1]);
		c = stoi(argv[2]);
		t = stoi(argv[3]);
	}

	if ((n > 0) && (c > 0) && (t > 0)) {

	//Creates an array of trains
	Dequeue dequeues[n];
	for (int i = 0; i < n; i++)
		for (int j = c; j > 0; j--)
			dequeues[i].insertFrontDequeue(j);
	
	//The Simulation runs while the amount of steps has not exceeded t and if there is not an empty train
	while ((x < t) && (isTrainEmpty != 1)) {
		
		//Inserts which train is the donor
		cin >> randDonor;
		randDonor = (randDonor % n) + 1;

		//Inserts a 1 or 2 to determine if the car will be taken from the front or back
		cin >> randTwoSidedDie;
		randTwoSidedDie = (randTwoSidedDie % 2) + 1;
		
		//Inserts which train will recieve the car
		cin >> randAcceptingTrain;
		randAcceptingTrain = (randAcceptingTrain % n) + 1;
		
		//Deletes a car from the front of the Donor and inserts that car to the front of the Accepting train
		if (randTwoSidedDie == 1) {
			int transferNode = dequeues[randDonor - 1].deleteFrontDequeue();
			dequeues[randAcceptingTrain - 1].insertFrontDequeue(transferNode);
			cout << "Turn " << x + 1 << ": Train " << randDonor << " sends a car to Train " << randAcceptingTrain << " from front" << endl;
		}

		//Deletes a car from the back of the Donor and inserts the car to the front of the Accepting train
		else  {
			int transferNode = dequeues[randDonor - 1].deleteRearDequeue();
			dequeues[randAcceptingTrain - 1].insertFrontDequeue(transferNode);
			cout << "Turn " << x + 1 << ": Train " << randDonor << " sends a car to Train " << randAcceptingTrain << " from back" << endl;
		}
		
		//Prints the value of each train
		for (int i = 1; i <= n; i++) {
			cout <<  '\t' << "Train " << i << " has value " << dequeues[i-1].getDequeueVal(dequeues[i-1]) << endl;
		}
		cout << endl;

		//Checks to see if the train is empty and prints a message if it is empty
		isTrainEmpty = dequeues[randDonor - 1].isEmptyDequeue();
		if (isTrainEmpty == 1)
			cout << "Simulation is over, Train " << randDonor << " has no cars left" << endl;

		//Increases to keep the simulation from running forever
		x++;
		
		//Prints a message that the simulation is over if the maximum amount of steps were reached
		if (x == t)
			cout << "Simulation is over, MAX steps were reached" << endl;
	
	}

		//Creates variable to hold the largest train and its value
		int greatestVal = dequeues[0].getDequeueVal(dequeues[0]);
		int greatestTrain = 1; 

		//Finds the largest train and its value
		for (int i = 1; i < n; i++) {
			if (dequeues[i].getDequeueVal(dequeues[i]) > greatestVal) {
					greatestVal = dequeues[i].getDequeueVal(dequeues[i]);
					greatestTrain = i + 1;
					}
			}

		//Prints which train had the largest value at the end of the simulation
		cout << "Train " << greatestTrain << " had the highest value" << endl;
	}

	else {
		//Prints an error message if the user puts in the wrong parameters
		cout << "Invalid command line parameters" << endl;
	}

	return 0;
}
