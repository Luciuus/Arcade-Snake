#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

int main()
{

    srand(time(0));
    int N;
    unsigned short userChoice;

    cout << "Arcade &*^SnAkE&*%\n";
    cout << "   1. PLAY\n";
    cout << "   2. QUIT\n";
    cout << "    Enter: ";
    cin >> userChoice;

    while(userChoice != 1){
        system("cls");
        cout << "Arcade #@$SnAkE#*@\n";
        cout << " 1. >>> PLAY <<<\n";
        cout << " 2.  &*%#^%$#&\n";
        cout << "      Enter: ";
        cin >> userChoice;
    }

    system("cls");
    cout << "How big would your board be (use odd numbers): ";
    cin >> N;

    while (N < 2 || N % 2 == 0)
    {
        cout << "Minimum is three or odd numbers: ";
        cin >> N;
    }

    int boardSize, appleSpawnRate, apples;
    unsigned short option;
    unsigned short isDead = 0;
    char worldBorder = '#';
    char playerCharUp = '^';
    char playerCharLeft = '<';
    char playerCharDown = 'v';
    char playerCharRight = '>';
    char appleItem = 'A';
    char playerTail = 'O';
    char placeholder = ' ';
    string redColor = "\033[31m";
    string resetColor = "\033[0m";
    string greenColor = "\033[32m";
    string yellowColor = "\033[33m";

    cout << "1. One life\n";
    cout << "2. Return by death\n";
    cout << "Your choice(1 or 2): ";
    cin >> option;

    while (option < 1 || option > 2)
    {
        cout << "Your choice(1 or 2): ";
        cin >> option;
    }

    boardSize = (N + 2) * (N + 2);

    // Insert placeholder
    vector<char> mainArray(boardSize, ' ');

    // Insert world border
    for (int i = 0; i < boardSize; i++)
    {
        if (i % (N + 2) == 0 || (i + 1) % (N + 2) == 0 || i >= boardSize - (N + 2) || i < (N + 2))
        {
            mainArray[i] = worldBorder;
        }
    }

    // Add apples based on input
    appleSpawnRate = N >= 5 ? N : N - 2;

    for (int i = 0; i < appleSpawnRate; i++)
    {
        do
        {
            apples = rand() % boardSize;
        } while (mainArray[apples] != placeholder);

        mainArray[apples] = appleItem;
    }

    // Insert player at middle
    int playerPositionStorage = (boardSize - 1) / 2;
    mainArray[playerPositionStorage] = playerCharUp;

    char keyboardCharacter = 'w';
    vector<int> bodyArray; // Stores the positions of the snake's body/tail

    int playerNewPosition = playerPositionStorage - (N + 2);

    bool isup = false;
    bool isleft = false;
    bool isdown = false;
    bool isright = false;
    unsigned int points = 0;

    do
    {
        system("cls");

        cout << "Points: " << points << "\n";

        // Print board
        for (int i = 0; i < boardSize; i++)
        {
            // Check if it is a player or body that is going to be printed
            if (mainArray[i] != '#' && mainArray[i] != 'A')
            {
                cout << redColor << mainArray[i] << resetColor << " ";
            }
            else if (mainArray[i] != '#' && mainArray[i] != '^' && mainArray[i] != 'v' && mainArray[i] != '<' && mainArray[i] != '>' && mainArray[i] != 'O')
            {
                cout << greenColor << mainArray[i] << resetColor << " ";
            }
            else
            {
                cout << mainArray[i] << " ";
                if ((i + 1) % (N + 2) == 0)
                {
                    cout << "\n";
                }
            }
        }

        // Mechanism so the snake cannot turn 180 degree of its current direction to avoid eating its own most front body
        char currentDirection = keyboardCharacter;

        while (_kbhit())
        {
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
            else if (tempKey == 'q')
                keyboardCharacter = tempKey;
        }

        if (keyboardCharacter == currentDirection)
            Sleep(200);

        // Player movement mechanics and boundaries
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
        default:
            continue;
        }

        // Check bounds / walls
        if (mainArray[playerNewPosition] != worldBorder)
        {
            bool ateApple = (mainArray[playerNewPosition] == appleItem);
            if (mainArray[playerNewPosition] == 'O')
            {
                if (option == 1)
                {
                    system("cls");
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

                else
                {
                    isDead++;
                    system("cls");
                    if (isDead == 1) {
                        cout << redColor << "???: " << resetColor << "Youre Back\n";
                        system("pause"); // Pauses so you can actually read it before respawning
                    }
                    else if (isDead == 2) {
                        cout << redColor << "???: " << resetColor << "Again\n";
                        system("pause");
                    }
                    else if (isDead == 3) {
                        cout << redColor << "???: " << resetColor << "And again\n";
                        system("pause");
                    }

                    for (unsigned int i = 0; i < bodyArray.size(); i++)
                    {
                        mainArray[bodyArray[i]] = placeholder;
                    }

                    bodyArray.clear();
                    mainArray[playerPositionStorage] = placeholder;
                    playerPositionStorage = (boardSize - 1) / 2;
                    playerNewPosition = playerPositionStorage - (N + 2);
                    mainArray[playerPositionStorage] = playerCharUp;

                    keyboardCharacter = ' ';
                    isup = true;
                    isleft = false;
                    isdown = false;
                    isright = false;

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
                if (!bodyArray.empty())
                {
                    mainArray[bodyArray.front()] = placeholder;
                    bodyArray.erase(bodyArray.begin());
                }
            }
        }

    } while (keyboardCharacter != 'q' && isDead < 4);


        system("cls");
        cout << greenColor << "Kang Hamdan: " << resetColor << "Who is speaking and what is happening?\n";
        Sleep(3500);
        cout << redColor << "???: " << resetColor << "Are you really going to waste your time with such trivial question?\n";
        Sleep(3500);
        cout << redColor << "???: " << resetColor << "You, a mortal being cannot comprehend my existence in this so called 'world' and you are stuck in a 'timeloop'\n";
        Sleep(3500);
        cout << redColor << "???: " << resetColor << "I'll spare you a little of the great me, i am the architect of this bubble you are in and you are a prisoner of mine\n";
        Sleep(3500);
        cout << redColor << "???: " << resetColor << "It seems my words are too great, you can just percieve me as 'GOD'\n";
        Sleep(3500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "GOD?\n";
        Sleep(3500);
        cout << redColor << "GOD?: " << resetColor << "Yes, and i have had enough having you stepping in my 'world'. You know what this means dont you?\n";
        Sleep(3500);
        cout << redColor << "GOD?: " << resetColor << "You who had ate countless 'god apples' and slained dragons upon your ways and in the verge of death....is entertaining to watch from a mere mortal\n";
        Sleep(3500);
        cout << redColor << "GOD?: " << resetColor << "Though you had displeased me by dying three times in a row and you have not fullfilled my interest\n";
        Sleep(3500);
        cout << redColor << "GOD?: " << resetColor << "You have no worth anymore, so..\n";
        Sleep(3500);
        cout << redColor << "GOD?: " << resetColor << "DIE like how all the things you have killed\n";
        Sleep(3500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "Die? thats the last thing you could ever imagined\n";
        Sleep(3500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "My friends has entrusted me with this weight\n";
        Sleep(3500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "Countless obstacles have I passed to this point\n";
        Sleep(3500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "And if this is all worthless in your 'eyes'\n";
        Sleep(3500);
        cout << greenColor << "Kang Hamdan: " << resetColor << "Then your absence would improve the 'world' considerably\n";
        Sleep(3500);
        cout << redColor << "GOD?: " << resetColor << "Well its always a losing game afterall\n";
        Sleep(3500);
        cout << redColor << "GOD?: " << resetColor << "so you would never win\n";
        Sleep(3500);
        cout << redColor << "GOD?: " << resetColor << "Its nice knowing you Kang Hamdan 'the legendary GIM master' but your journey ends here\n";
        Sleep(3500);

        unsigned short spaceClick;
        unsigned short countDown = 3;
        cout << "Press Space quickly or you will die!\n";
        while (countDown != 0)
        {
            cout << countDown << " Seconds Left\n";

            for (int i = 0; i < 20; i++)
            {
                if (_kbhit())
                {                       // Memeriksa apakah ada tombol yang ditekan
                    char click = _getch(); // Mengambil tombol tersebut
                    if (click == ' ')
                    { // Jika tombol tersebut adalah Space
                        spaceClick++;
                    }
                }
                Sleep(50); // Jeda kecil 50ms x 20 = 1000ms (1 detik)
            }
            countDown--;
        }
        if (spaceClick < 10)
        {
            cout << "You Died\n";
            cout << "Your journey would be remembered, Kang Hamdan the GIM master";
            return 0;
        }

        if (spaceClick >= 15)
        {
            system("cls");
            cout << "You won against" << redColor << " GOD\n" << resetColor;
            Sleep(3500);
            cout << "Now recieve the" << yellowColor << " GRAND PRIZE!\n" << resetColor;
            Sleep(3500);
            cout << greenColor << "You recieved the power of" << resetColor << redColor << " GOD " << resetColor << greenColor << "and you have trancended from the timeline" << resetColor;
            return 0;
        }

    return 0;
}