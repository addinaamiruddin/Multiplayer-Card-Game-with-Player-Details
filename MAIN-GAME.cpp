#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct node{
    int index, score, rank;
    string name;
    struct node *previous;
    struct node *next;
};
struct node *head, *tail = NULL;

class ADTqueue
{
	public :
	node *head, *tail, *temp, *prev;

	ADTqueue() //constructor (index, name, ranking)
	{
		head = NULL;
		tail = NULL;
	}
    friend class memoryGame;
};

class memoryGame
{
private:
    int level;
    int cards[4][4];
    char face[4][4];
    int pairs[16] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8};

public:
    memoryGame(int l) //constructor
    {
        level=l;
        // Initialization of array with through constructor
        for(int i = 0; i < l; i++)
        {
            for(int j = 0; j < l; j++)
            {
                cards[i][j] = 0;
                face[i][j] = '*';
            }
        }
        //cout<<"constructor working"<<endl;
    }

    int getLevel()
    {
        return level;
    }

    // Function to play game
    void play(int qty)
    {
        shuffle();
        node *head;

        int *score=new int[qty];
        //cout<<"test play function"<<endl;
        while(1)
        {
            // Game terminating after completing the game successfully
            if(win())
            {
                table();
                //cout<<"we won"<<endl;
                return;
            }
            // Keep playing
            else
            {
                int i=0;
    			do {
					table();
                	pick(i, qty, head); //sending index ONE BY ONE
                	i++;
				} while (i<qty && !win());
            }
        }
    }

    // For displaying shuffled cards (faced up and faced down)
    void table()
    {
        cout << endl;
        for(int i = 0; i < getLevel(); i++)
        {
            cout << "   ";
            for(int j = 0; j < getLevel(); j++)
            {
                cout << face[i][j] << " ";
            }
            cout << endl;
        }
        //cout <<"table function "<< endl;
    }

    // Function for random shuffle of cards
    void shuffle()
    {
        int x = -1;
        int y = -1;
        int z = 0;
        srand(time(0));
        int N=getLevel();

        //cout<<"N is "<<N<<endl;

        fflush(stdin);
        // Run until all cards are shuffle
        if (N==2)
        {
            while((cards[0][0] == 0) || (cards[0][1] == 0) ||
                  (cards[1][0] == 0) || (cards[1][1] == 0))
            {
                // Random pick of array index
                x = (rand() % getLevel());
                y = (rand() % getLevel());

                // Checking if array index is empty or not
                if(cards[x][y] == 0)
                {
                    cards[x][y] = pairs[z];
                    z++;
                }
            }
        }
        else if (N==4)
        {
            while((cards[0][0] == 0) || (cards[0][1] == 0) || (cards[0][2] == 0) || (cards[0][3] == 0) ||
              (cards[1][0] == 0) || (cards[1][1] == 0) || (cards[1][2] == 0) || (cards[1][3] == 0) ||
              (cards[2][0] == 0) || (cards[2][1] == 0) || (cards[2][2] == 0) || (cards[2][3] == 0) ||
              (cards[3][0] == 0) || (cards[3][1] == 0) || (cards[3][2] == 0) || (cards[3][3] == 0))
            {
                // Random pick of array index
                x = (rand() % getLevel());
                y = (rand() % getLevel());

                // Checking if array index is empty or not
                if(cards[x][y] == 0)
                {
                    cards[x][y] = pairs[z];
                    z++;
                }
            }
        }

        //cout<<"shuffle function"<<endl;
    }

    // Function to let player pick cards through index position
    void pick(int index, int qty, struct node *head)
    {
        node *temp;
        bool picked1, picked2;
        int x1, x2, y1, y2, level=getLevel();
        ADTqueue q;

        head=temp;
        int j;
        int a;


			picked1 = picked2 = false;
            x1 = x2 = y1 = y2 = -1;

            //cout<<"early pick function"<<endl;

            do
            {
                // First Pick
                if(picked1 == false)
                {
                    cout <<"picking out card 1 "<< endl;
                    fflush(stdin);
                    cout << "\nPlayer "<<index+1<<", "<<" : \nEnter the row (1 to "<<getLevel()<<") and col (1 to "<<getLevel()<<") position of the pair: \n";
                    cin >> x1 >> y1;

                    // Changing input from 1-4 to 0-3 for array
                    x1--;
                    y1--;

                    // Checking invalid position
                    if( (x1 < 0 || x1 > level-1) || (y1 < 0 || y1 > level-1))
                    {
                        cout << "\nInvalid position.\n";
                        continue;
                    }

                    // Checking if already face up or not
                    else if (face[x1][y1] != '*')
                    {
                        cout << "\nCard at this position already faced up. Select option again.\n";
                        continue;
                    }
                    // Turning picked card face up
                    else
                    {
                        face[x1][y1] = cards[x1][y1] + '0';
                        picked1 = true;
                        table();
                    }
                }
                // Second Pick
                else
                {
                    //cout <<"picking out card 2 "<< endl;
                    cout << "\nPlayer "<<index+1<<", "<<" : \nEnter the row (1 to 4) and col (1 to 4) position of the pair: \n" ;
                    cin >> x2 >> y2;

                    // Changing input from 1-4 to 0-3 for array
                    x2--;
                    y2--;

                    // User input error
                    if(x2 == -1 || y2 == -1)
                    {
                        cout << "\nBoth number must be entered.\nPlease try again.\n";
                        continue;
                    }

                    // Checking invalid position
                    else if( (x2 < 0 || x2 > level-1) || (y2 < 0 || y2 > level-1))
                    {
                        cout << "\nInvalid position.\n";
                        continue;
                    }

                    // Checking if already face up or not
                    else if (face[x2][y2] != '*')
                    {
                        cout << "\nCard at this position already faced up. Select option again.\n";
                        continue;
                    }
                    // Turning picked card face up
                    else
                    {
                        face[x2][y2] = cards[x2][y2] + '0';
                        picked2 = true;
                        table();
                    }
                }
            } while((picked1 == false) || (picked2 == false));

            // Checking either pair matched or not
            //if matched, then add +2 to score
            if(face[x1][y1] == face[x2][y2])
            {
                cout << "\nPair matched!\n";
                face[x1][y1]='  ';
                face[x2][y2]='  ';

                cout<<"Your score : "<<endl;

                if (!win())
                {
                    cout<<"You get 2 points! It is still your turn :)\n";
                    pick(index, qty, head); //recursive index -> calling the function again
                }
            }

            else
            {
                cout << "\nPair do not match. Next player!\n\n";
                face[x1][y1] = face[x2][y2] = '*';
            }
        //cout<<"end pick function"<<endl;
    }

    // Checking either all cards are shuffled or not
    bool win()
    {
        if((face[0][0] == '*') || (face[0][1] == '*') || (face[0][2] == '*') || (face[0][3] == '*') ||
           (face[1][0] == '*') || (face[1][1] == '*') || (face[1][2] == '*') || (face[1][3] == '*') ||
           (face[2][0] == '*') || (face[2][1] == '*') || (face[2][2] == '*') || (face[2][3] == '*') ||
           (face[3][0] == '*') || (face[3][1] == '*') || (face[3][2] == '*') || (face[3][3] == '*'))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
	friend class ADTqueue;
};

void addNode(int index, string n, int score)
	{
        //Create a new node
        //struct node *newNode = (struct node*)malloc(sizeof(struct node));
        struct node* newNode = new node;
        newNode->index = index;
        newNode->name = n;
        newNode->score = score;

        //If list is empty
        if(head == NULL) {
            //Both head and tail will point to newNode
            head = tail = newNode;
            //head's previous will point to NULL
            head->previous = NULL;
            //tail's next will point to NULL, as it is the last node of the list
            tail->next = NULL;
        }
        else {
            //newNode will be added after tail such that tail's next will point to newNode
            tail->next = newNode;
            //newNode's previous will point to tail
            newNode->previous = tail;
            //newNode will become new tail
            tail = newNode;
            //As it is last node, tail's next will point to NULL
            tail->next = NULL;
        }
    }

    //sortList() will sort the given list in ascending order
    void sortList()
    {
        struct node *current = NULL, *index = NULL;
        int temp;
        //Check whether list is empty
        if(head == NULL) {
            return;
        }
        else {
            //Current will point to head
            for(current = head; current->next != NULL; current = current->next) {
                //Index will point to node next to current
                for(index = current->next; index != NULL; index = index->next) {
                    //If current's score is greater than index's score, swap the score of current and index
                    if(current->score > index->score) {
                        temp = current->score;
                        current->score = index->score;
                        index->score = temp;
                    }
                }
            }
        }
    }

    //display() will print out the nodes of the list
    void display()
    {
        //Node current will point to head
        struct node *current = head;
        if(head == NULL) {
            cout<<"List is empty\n";
            return;
        }
        while(current != NULL) {
            //Prints each node by incrementing pointer.
            cout<<"Ranking : "<<current->index<<endl;
            cout<<"Name : "<<current->name<<endl;
            cout<<"Score : "<<current->score<<"\n\n";
            current = current->next;
        }
        cout<<"\n";
    }

int numOfPlayers()
    {
        int qty;
        node *head, *temp, *tail;
        int score, rank;
        ADTqueue q;

        cout << "\nNumber of players : " << endl;
        cin>>qty;

        string *name=new string[qty];
        fflush(stdin);

        //WHERE THE NODES ARE CREATED
        for (int i=0; i<qty; i++)
        {
            cout << "\nPlayer "<<i+1<<" name : ";
            getline(cin, name[i]);
            fflush(stdin);

            addNode(i+1, name[i], 0);
        }

        cout<<"\nDetails of player :\n\n";
        display();

        return qty;
    };

int displayMenu()
{
    //Select game
    //SetConsoleTextAttribute(color, 7);
    int menu, again;

    cout << "\tGame Menu" << endl;
    cout << "********************" << endl;
    cout << "Select 1 for a New Game and 2 to Exit Game" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Exit Game" << endl;
    cout << "********************" << endl;
    cin >> menu;

    // Option to start game and difficulty selection
    if (menu == 1) //NEW GAME
    {
        return 1;
    } else if (menu == 2)
    {
        exit(1); //terminate the program completely
    }
};


int difficulty()
{
    int level;
    // Game grid selection
    cout << endl << "\tSELECT A LEVEL" << endl;
    cout << "*******************************" << endl;
    cout << "For an Easy Game enter '1' ( 2x2 grid )" << endl;
    cout << "For an Intermediate Game enter '2' ( 4x4 grid )" << endl;
    cout << "*******************************" << endl;
    cin >> level;

    if (level==1)
        return 2;
    else if (level==2)
        return 4;
};


int main()
{
    int level, cont=1, qty, j=0;
    ADTqueue q;

    while(1) //continuous list so the only way to terminate is to use exit(1)
    {
        cont=displayMenu();
        //if cont==1, then continue
        //if cont==0, then break the loop

        level=difficulty(); //prompt for level
        //cout<<"level is "<<level<<endl;

        //creating the object of class memoryGame -> invoking the memoryGame constructor (* and 0s depending on 4/6)
        //sending int level as parameter so can be initialized in constructor
        memoryGame game(level);

        qty=numOfPlayers(); //prompt for number of players and their names (into struct)

        fflush(stdin);
        //call game.play() to start game
        //sending qty as parameter (so can loop)
        game.play(qty);
        sortList();
        display();
    }
    return 0;
}
