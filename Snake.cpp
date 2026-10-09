#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

int main()
{
    //init the time from epoch and random seed gen by math through srand
    srand(time(0));

    //ini the variables
    int N;
    unsigned short userChoice;
    int boardSize, appleSpawnRate, apples;
    unsigned short option;
    unsigned short isDead = 0;

    //init the character variables
    char worldBorder = '#';
    char playerCharUp = '^';
    char playerCharLeft = '<';
    char playerCharDown = 'v';
    char playerCharRight = '>';
    char appleItem = 'A';
    char playerTail = 'O';
    char placeholder = ' ';

    // init the color variables
    string redColor = "\033[31m";
    string resetColor = "\033[0m";
    string greenColor = "\033[32m";
    string yellowColor = "\033[33m";

    //make the start screen
    cout << "Arcade &*^SnAkE&*%\n";
    cout << "   1. PLAY\n";
    cout << "   2. QUIT\n";
    cout << "    Enter: ";
    cin >> userChoice;

    //make the loop if the user pick not 1
    while(userChoice != 1){
        system("cls");
        cout << "Arcade " << yellowColor << "#@$SnAkE#*@" << resetColor << "\n";
        cout << " 1. >>> " << redColor << "PLAY" << resetColor << " <<<\n";
        cout << " 2.  &*%#^%$#&\n";
        cout << "      Enter: ";
        cin >> userChoice;
    }

    //get user inout for how large the board is
    system("cls");
    cout << "How big would your board be (5 <= odd numbers <= 21): ";
    cin >> N;

    //loop it if the user picks below 3 or even numbers
    while (N < 5 || N > 21  || N % 2 == 0)
    {
        cout << "Range is 5 or 21  or 5 -> 21: ";
        cin >> N;
    }

    //init the board size via quadratic and +2 to accomodate the border
    boardSize = (N + 2) * (N + 2);

    //init the array with boarsize size and fill it with space for every index
    vector<char> mainArray(boardSize, ' ');

    //get user input to difficulty
    cout << "1. One life\n";
    cout << "2. Story mode\n";
    cout << "Your choice(1 or 2): ";
    cin >> option;

    //loop if user does not pick 1 
    while (option < 1 || option > 2)
    {
        cout << "Your choice(1 or 2): ";
        cin >> option;
    }

    //story when option 2 is chosen/triggered
    if(option == 2){
        cout << yellowColor << "2GETHER:" << resetColor << " Doomed\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " This world is doomed\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " Firearms has ceased from its effectiveness when 'magic' decended to this world through the same tests\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " It gave humans powers to bend elements and get super human abilities\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " Mutated humans have invaded this 'world' from advanced humanity technology tests to achieve those abilities\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " Its ironic what they thought to help turns to be their own enemies\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " Though there is a person who stood out the most\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " People recite his name when needed\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " 'Kang Hamdan' they say or his title as 'The GIM Master'\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " A title bestowed by the king of this land from his countless achievements\n";
        Sleep(2500);
        cout << yellowColor << "2GETHER:" << resetColor << " People call him as the hero\n";

        system("cls");
        //give tutorials
        cout << "Use W,A,S,D to move your character";
        Sleep(2500);
    }

    // Insert world border
    for (int i = 0; i < boardSize; i++)
    {
        //(i % (N + 2) == 0 for index all left vertically
        //(i + 1) % (N + 2) == 0 for index all right vertically
        //i < (N + 2) for index all top horizontally
        //i >= boardSize - (N + 2) for index all bottom horizontally
        if (i % (N + 2) == 0 || (i + 1) % (N + 2) == 0 || i < (N + 2) || i >= boardSize - (N + 2))
        {
            mainArray[i] = worldBorder;
        }
    }

    //add apples based on input
    appleSpawnRate = N >= 5 ? N : N - 2;

    //apple spawn mechanism based on appleSpawnRate 
    for (int i = 0; i < appleSpawnRate; i++)
    {
        do
        {
            apples = rand() % boardSize;
        } while (mainArray[apples] != placeholder);

        mainArray[apples] = appleItem;
    }

    //insert player at middle
    int playerPositionStorage = (boardSize - 1) / 2;
    //set the player default character 
    mainArray[playerPositionStorage] = playerCharUp;
    //set the default keyboard character input
    char keyboardCharacter = 'w';

    //stores the positions of the snake's body/tail
    vector<int> bodyArray; 

    //Init the playernewposition at the middle of the array
    int playerNewPosition = playerPositionStorage - (N + 2);

    //init the directionnal bool
    bool isup = false;
    bool isleft = false;
    bool isdown = false;
    bool isright = false;
    //init the player points
    unsigned int points = 0;

    //main loop
    do
    {
        //Clear the screen
        system("cls");

        //Cout the points
        cout << "Points: " << points << "\n";

        //Print board
        for (int i = 0; i < boardSize; i++)
        {
            //check if it is not a world border and not an apple
            if (mainArray[i] != '#' && mainArray[i] != 'A')
            {
                //make player character and bodya red
                cout << redColor << mainArray[i] << resetColor << " ";
            }
            //check if it is not a world border, player, and body
            else if (mainArray[i] != '#' && mainArray[i] != '^' && mainArray[i] != 'v' && mainArray[i] != '<' && mainArray[i] != '>' && mainArray[i] != 'O')
            {
                //make apple character green
                cout << greenColor << mainArray[i] << resetColor << " ";
            }
            //none of the above
            else
            {
                //fill the rest with blank character
                cout << mainArray[i] << " ";
                //make a new line everytime at the end of multiply (N + 2)
                if ((i + 1) % (N + 2) == 0)
                {
                    cout << "\n";
                }
            }
        }

        //save keyboard character in current direction
        char currentDirection = keyboardCharacter;

        //loop this continuously while user is mashing the buttons
        while (_kbhit())
        {
            //get the character from keyboard and turn it to undercase
            char tempKey = tolower(_getch());
            // Validate against currentDirection (the actual physical movement), NOT keyboardCharacter
            if (tempKey == 'w' && currentDirection != 's')
                keyboardCharacter = tempKey;
            else if (tempKey == 'a' && currentDirection != 'd')
                keyboardCharacter = tempKey;
            else if (tempKey == 's' && currentDirection != 'w')
                keyboardCharacter = tempKey;
            else if (tempKey == 'd' && currentDirection != 'a')
                keyboardCharacter = tempKey;
            //keyboard character can only be changed after the conditions are met, therefore its impossible to eat itself from 180 degree
        }

        //when the keyboard character is the same as current direction(guaranteed), this program will sleeep to avoid intense terminal flickering from the while loop
        if (keyboardCharacter == currentDirection)Sleep(200);

        // Player movement mechanics
        //the bool is to validate the direction and trigger condition met to change player character model based on keyboard character
        switch (keyboardCharacter)
        {
        case 'w':
            playerNewPosition = playerPositionStorage - (N + 2);
            isup = true;
            isleft = false;
            isdown = false;
            isright = false;
            break;
        case 'a':
            playerNewPosition = playerPositionStorage - 1;
            isup = false;
            isleft = true;
            isdown = false;
            isright = false;
            break;
        case 's':
            playerNewPosition = playerPositionStorage + (N + 2);
            isup = false;
            isleft = false;
            isdown = true;
            isright = false;
            break;
        case 'd':
            playerNewPosition = playerPositionStorage + 1;
            isup = false;
            isleft = false;
            isdown = false;
            isright = true;
            break;
        }

        //check if player new position hits a world border
        if (mainArray[playerNewPosition] != worldBorder)
        {
            //change bool state when the player eats an apple at its new position
            bool ateApple = (mainArray[playerNewPosition] == appleItem);

            //check if player new position eats its own body
            if (mainArray[playerNewPosition] == 'O')
            {
                //check if the gamemode is option 1(one life)
                if (option == 1)
                {
                    system("cls");
                    //uses R"()" because entering in a cout is not valid and this(R"()") translates all this as a litteral string to avoid errors
                    cout << redColor << R"(
                    ##      ##    ######    ##      ##        ########    ######  ##########  ########    
                    ##      ##    ######    ##      ##        ########    ######  ##########  ########    
                      ##  ##    ##      ##  ##      ##        ##      ##    ##    ##          ##      ##  
                      ##  ##    ##      ##  ##      ##        ##      ##    ##    ##          ##      ##  
                        ##      ##      ##  ##      ##        ##      ##    ##    ########    ##      ##  
                        ##      ##      ##  ##      ##        ##      ##    ##    ########    ##      ##  
                        ##      ##      ##  ##      ##        ##      ##    ##    ##          ##      ##  
                        ##      ##      ##  ##      ##        ##      ##    ##    ##          ##      ##  
                        ##        ######      ######          ########    ######  ##########  ########    
                        ##        ######      ######          ########    ######  ##########  ########    )"
                         << resetColor;
                    cout << "\n\n\t\t\t\t\tYOU ATE YOURSELF, BETTER LUCK NEXT TIME!";
                    cout << "\n\n\t\t\t\t\t\tYOUR HIGH SCORE: " << points;
                    return 0;
                }

                //if the game options was 2(story mode)
                else
                {
                    //counter how many times died
                    isDead++;
                    //clear screen
                    system("cls");
                    if (isDead == 1) {
                        cout << redColor << "???: " << resetColor << "Youre Back\n";
                        cout << " ";
                        Sleep(1000);
                        cout << greenColor << "Kang Hamdan: " << resetColor << "What?\n";
                        system("pause"); //pauses so you can actually read it before respawning
                    }
                    else if (isDead == 2) {
                        cout << redColor << "???: " << resetColor << "Again\n";
                        Sleep(1000);
                        cout << greenColor << "Kang Hamdan: " << resetColor << "What's happening? why didnt i die?\n";
                        cout << " ";
                        system("pause");
                    }
                    else if (isDead == 3) {
                        cout << redColor << "???: " << resetColor << "And again\n";
                        Sleep(1000);
                        cout << greenColor << "Kang Hamdan: " << resetColor << "Stop it!\n";
                        cout << " ";
                        system("pause");
                    }

                    //eliminate all compounded body from a single game to force restart from just the head
                    for (unsigned int i = 0; i < bodyArray.size(); i++)
                    {
                        mainArray[bodyArray[i]] = placeholder;
                    }

                    //erase the index memory from the body array
                    bodyArray.clear();
                    //replace the old head to placeholder or it will linger in the array because it is not part of body array's indexing so it needs to be deleted manually
                    mainArray[playerPositionStorage] = placeholder;
                    //reset the player position storage at center of grid
                    playerPositionStorage = (boardSize - 1) / 2;
                    //reset the player new position
                    playerNewPosition = 0;
                    //reset the player position by player char
                    mainArray[playerPositionStorage] = playerCharUp;
                    //reset keyboard character so the player does not auto move(to emphasize return by death(art of surprise))
                    keyboardCharacter = ' ';
                    //reset the bool to match when going to north direction/'w'
                    isup = true;
                    isleft = false;
                    isdown = false;
                    isright = false;

                    //continues to the next program if this else block is unused anymore
                    continue;

                }
            }

            // 1. MASUKKAN koordinat kepala saat ini ke memori ekor
            bodyArray.push_back(playerPositionStorage);

            // 2. UBAH kepala lama langsung menjadi karakter ekor ('O') saat ini juga!
            mainArray[playerPositionStorage] = playerTail;

            // 3. CETAK kepala baru di posisi yang dituju
            if (isup)
            {
                mainArray[playerNewPosition] = playerCharUp;
            }
            else if (isleft)
            {
                mainArray[playerNewPosition] = playerCharLeft;
            }
            else if (isdown)
            {
                mainArray[playerNewPosition] = playerCharDown;
            }
            else if (isright)
            {
                mainArray[playerNewPosition] = playerCharRight;
            }
            playerPositionStorage = playerNewPosition;

            if (ateApple)
            {
                // Jika makan apel, ular memanjang. Jangan hapus ekor paling belakang.
                // Cukup spawn apel baru di tempat kosong.
                do
                {
                    apples = rand() % boardSize;
                } while (mainArray[apples] != placeholder);
                mainArray[apples] = appleItem;
                points++;
            }

            else
            {
                // Jika jalan biasa, hapus ekor paling lama di peta agar ular terlihat bergerak maju
                //check the body array is not empty(which is never empty with atleast one index(0) is filled)
                if (!bodyArray.empty())
                {
                    //replace anything in the main array pointed via bodyArray with .front()(tells the value from the most front index in the body array) with a placeholder character
                    mainArray[bodyArray.front()] = placeholder;
                    //erase the value at the most front index(0) at the body array with .erase() function via pointer from bodyarray with .begin()(points at the first index from the body array)
                    bodyArray.erase(bodyArray.begin());
                }
            }
        }

    } while (isDead < 4);

        //triggers when isDead = 4
        //clears screen
        system("cls");

        //start story
        cout << greenColor << "Kang Hamdan: " << resetColor << "Who is speaking and what is happening?\n";
        Sleep(2500);
        cout << redColor << "???: " << resetColor << "Are you really going to waste your time with such trivial question?\n";
        Sleep(2500);
        cout << redColor << "???: " << resetColor << "You, a mortal being cannot comprehend my existence in this so called 'world' and you are stuck in a 'timeloop'\n";
        Sleep(2500);
        cout << redColor << "???: " << resetColor << "I'll spare you a little of the great me, i am the architect of this bubble you are in and you are a prisoner of mine\n";
        Sleep(2500);
        cout << redColor << "???: " << resetColor << "It seems my words are too great, you can just percieve me as 'GOD'\n";
        Sleep(2500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "GOD?\n";
        Sleep(2500);
        cout << redColor << "GOD?: " << resetColor << "Yes, and i have had enough having you stepping in my 'world'. You know what this means dont you?\n";
        Sleep(2500);
        cout << redColor << "GOD?: " << resetColor << "You who had ate countless 'god apples' and slained dragons upon your ways and in the verge of death....is entertaining to watch from a mere mortal\n";
        Sleep(2500);
        cout << redColor << "GOD?: " << resetColor << "Though you had displeased me by dying three times in a row and you have not fullfilled my interest\n";
        Sleep(2500);
        cout << redColor << "GOD?: " << resetColor << "You have no worth anymore, so..\n";
        Sleep(2500);
        cout << redColor << "GOD?: " << resetColor << "DIE like how all the things you have killed\n";
        Sleep(2500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "Die? thats the last thing you could ever imagined\n";
        Sleep(2500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "My friends has entrusted me with this weight\n";
        Sleep(2500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "Countless obstacles have I passed to this point\n";
        Sleep(2500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "And if this is all worthless in your 'eyes'\n";
        Sleep(2500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "Then your absence would improve the 'world' considerably\n";
        Sleep(2500);
        cout << redColor << "GOD?: " << resetColor << "Well its always a losing game afterall\n";
        Sleep(2500);
        cout << redColor << "GOD?: " << resetColor << "so you would never win\n";
        Sleep(2500);
        cout << redColor << "GOD?: " << resetColor << "Its nice knowing you Kang Hamdan 'the legendary GIM master' but your journey ends here\n";
        Sleep(2500);

        //init variables
        unsigned short spaceClick;
        //init count down from where
        unsigned short countDown = 3;
        //print the title
        cout << "Press Space quickly or you will die!\n";

        //while countdown is not zero, do this
        while (countDown != 0)
        {
            cout << countDown << " Seconds Left\n";

            //this will run 3 times because while != 0
            //loop sleeping + get character twenty times
            for (int i = 0; i < 20; i++)
            {
                //check if a keyboard key is being clicked
                if (_kbhit())
                {                       
                    char click = _getch(); // Mengambil tombol tersebut
                    if (click == ' ')
                    { // Jika tombol tersebut adalah Space
                        spaceClick++;
                    }
                }
                Sleep(50); // Jeda kecil 50ms x 20 = 1000ms (1 detik)
            }
            //decrease one time for the countDown var;
            countDown--;
        }

        //lose situation
        if (spaceClick < 10)
        {
            cout << "You Died\n";
            cout << "Your journey would be remembered, Kang Hamdan the GIM master";
            return 0;
        }

        //win situation
        if (spaceClick >= 15)
        {
            system("cls");
            cout << "You won against" << redColor << " GOD\n" << resetColor;
            Sleep(2500);
            cout << "Now recieve the" << yellowColor << " GRAND PRIZE!\n" << resetColor;
            Sleep(2500);
            cout << greenColor << "You recieved the power of" << resetColor << redColor << " GOD " << resetColor << greenColor << "and you have trancended from the timeline" << resetColor;
            return 0;
        }

    return 0;
}