#include <iostream>
#include <time.h>
#include <vector>
#include <dos.h>

using namespace std;

/*class pract
{
public:
    int rows;
    int cols;
    int** mass = new int* [rows];
    //vector<int> dad;
    //vector<>
    pract()
    {
        rows = 10;
        //cols = 10;
        //mass= new int* [rows];
        srand(time(NULL));
        for (int i = 0; i < rows; i++)
        {
            cols = 10;
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mass[i][j] = rand() % 10;
                cout << mass[i][j] << " ";
            }
            cout << endl;
        }
    }
    void fullandshow()
    {
        srand(time(NULL));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mass[i][j] = 0;
                cout << mass[i][j] << " ";
            }
            cout << endl;
        }
    }
};*/

class game
{
protected:
    int deck1[10][10];
    int deck2[10][10];
    char symbols[10];
    /*
    0 - пустое поле (_)
    1 - пустое поле, нельзя ставить корабли (O)
    2 - корабль (X)
    3 - промах (O)
    4 - подбит (X)
    5 - поле вокруг подбитого корабля(O)
    */
public:
    game()
    {
        symbols[0] = 'А'; symbols[1] = 'Б'; symbols[2] = 'В'; symbols[3] = 'Г'; symbols[4] = 'Д'; symbols[5] = 'Е'; symbols[6] = 'Ё'; symbols[7] = 'Ж'; symbols[8] = 'З'; symbols[9] = 'И';
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                deck1[i][j] = 0;
                deck2[i][j] = 0;
            }
        }
    }
    void printdeck1()
    {
        cout << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "\t" << symbols[i];
        }
        for (int i = 0; i < 10; i++)
        {
            cout << endl<<i+1;
            for (int j = 0; j < 10; j++)
            {
                cout<<"\t" << deck1[i][j];
            }
        }
    }
    void printdeck2()
    {
        cout << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "\t" << symbols[i];
        }
        for (int i = 0; i < 10; i++)
        {
            cout << endl << i+1;
            for (int j = 0; j < 10; j++)
            {
                cout << "\t" << deck2[i][j];
            }
        }
    }
    void print2decks()
    {
        cout << endl;
        cout << "\t\t\t\t\t\tДоска 1\t\t\t\t\t\t\t\t\t\t\tДоска 2"<<endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "\t" << symbols[i];
        }
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << "\t" << symbols[i];
        }
        for (int i = 0; i < 10; i++)
        {
            cout << endl << i+1;
            for (int j = 0; j < 10; j++)
            {
                cout << "\t" << deck1[i][j];
            }
            cout << "\t"<<i+1;
            for (int j = 0; j < 10; j++)
            {
                cout << "\t" << deck2[i][j];
            }
        }
    }
    void setshipdeck1(int lenght)
    {
        bool temp = false;
        printdeck1();
        cout <<endl<< "Постановка " << lenght << "-палубного корабля на доску 1"<<endl;
        while (temp != true)
        {
            int temp1 = 1; char temp2 = 'А', bool temp3 = false;
            int A, B;
            while (temp3 != true)
            {
                cout << "Выберите позицию хвоста корабля (цифру от 1 до 10): ";
                cin >> temp1;
                cout << "Выберите позицию хвоста корабля (букву от А до И на русском): ";
                cin >> temp2;
                A = temp1 - 1;
                B = int(temp2) + 112;
                if (A >= 0 && A <= 9 && B >= 0 && B <= 9 && deck1[A][B] == 0)
                    temp3 = true;
                else
                    cout << endl << "Программа не смогла определить позицию хвоста или в этой позиции нельзя установить корабль! Попробуйте еще раз" << endl;
            }
            cout << "Позиция хвоста " << temp1 << temp2 << endl;
            cout << "Выберите направление корабля" << endl << "1 - влево" << "\n2 - вверх\n3 - вправо\n4 - вниз\nВыбор:";
            cin >> temp1;
            while (temp3 != false)
            {
                while (temp1 < 1 && temp1>4)
                {
                    cout << "Неккоректный ввод, еще раз: ";
                    cin >> temp1;
                }
                switch (temp1)
                {
                case 1: 
                    bool temp4 = false;
                    for (int i = B; i < B-lenght+1; i--)
                    {
                        if (deck1[A][i] != 0)
                            temp4 = true;
                    }
                if ((B - lenght +1) < 0 && temp4 == false)
                {
                    cout << "Нельзя поставить корабль влево, выберите другое направление"<<endl;
                    break;
                }
                cout << endl << "Начальная и конечная позиция корабля" << A << char(B - 112 - lenght + 1) << " - " << A << char(B - 112)<<endl<<"Выполняется постановка...";
                for (int i = 0; i < lenght; i++)
                {
                    deck1[A][B - i] = 2;
                    deck1[A - 1][B - i] = 1;
                    deck1[A + 1][B - i] = 1;
                }
                deck1[A][B - lenght] = 1; deck1[A-1][B - lenght] = 1; deck1[A+1][B - lenght] = 1;
                deck1[A][B + 1] = 1; deck1[A+1][B + 1] = 1; deck1[A-1][B + 1] = 1;
                temp = true;
                temp3 = true;
                break;
                case 2:
                    bool temp4 = false;
                    for (int i = A; i < A - lenght + 1; i--)
                    {
                        if (deck1[i][B] != 0)
                            temp4 = true;
                    }
                    if ((A - lenght + 1) < 0 && temp4 == false)
                    {
                        cout << "Нельзя поставить корабль влево, выберите другое направление" << endl;
                        break;
                    }
                    cout << endl << "Начальная и конечная позиция корабля" << A-lenght+1 << char(B - 112) << " - " << A << char(B - 112) << endl << "Выполняется постановка...";
                    for (int i = 0; i < lenght; i++)
                    {
                        deck1[A-i][B] = 2;
                        deck1[A - i][B - 1] = 1;
                        deck1[A -i][B + 1] = 1;
                    }
                    deck1[A - lenght][B] = 1; deck1[A - lenght][B - 1] = 1; deck1[A - lenght][B + 1] = 1;
                    deck1[A +1 ][B] = 1; deck1[A + 1][B - 1] = 1; deck1[A + 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 3:
                    bool temp4 = false;
                    for (int i = B; i < B + lenght - 1; i--)
                    {
                        if (deck1[A][i] != 0)
                            temp4 = true;
                    }
                    if ((B + lenght - 1) < 0 && temp4 == false)
                    {
                        cout << "Нельзя поставить корабль влево, выберите другое направление" << endl;
                        break;
                    }
                    cout << endl << "Начальная и конечная позиция корабля" << A << char(B - 112 - lenght + 1) << " - " << A << char(B - 112) << endl << "Выполняется постановка...";
                    for (int i = 0; i < lenght; i++)
                    {
                        deck1[A][B + i] = 2;
                        deck1[A - 1][B + i] = 1;
                        deck1[A + 1][B + i] = 1;
                    }
                    deck1[A][B + lenght] = 1; deck1[A - 1][B + lenght] = 1; deck1[A + 1][B + lenght] = 1;
                    deck1[A][B - 1] = 1; deck1[A + 1][B - 1] = 1; deck1[A - 1][B - 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 4:
                    bool temp4 = false;
                    for (int i = A; i < A + lenght - 1; i--)
                    {
                        if (deck1[i][B] != 0)
                            temp4 = true;
                    }
                    if ((A + lenght - 1) < 0 && temp4 == false)
                    {
                        cout << "Нельзя поставить корабль влево, выберите другое направление" << endl;
                        break;
                    }
                    cout << endl << "Начальная и конечная позиция корабля" << A + lenght - 1 << char(B - 112) << " - " << A << char(B - 112) << endl << "Выполняется постановка...";
                    for (int i = 0; i < lenght; i++)
                    {
                        deck1[A + i][B] = 2;
                        deck1[A + i][B - 1] = 1;
                        deck1[A + i][B + 1] = 1;
                    }
                    deck1[A + lenght][B] = 1; deck1[A + lenght][B - 1] = 1; deck1[A + lenght][B + 1] = 1;
                    deck1[A - 1][B] = 1; deck1[A - 1][B - 1] = 1; deck1[A - 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                default:
                    break;
                }
            }
        }
    }
    void setdeck1()
    {
        cout << "ВНИМАНИЕ!! Сейчас будет установка первой доски, не допускайте подглядывание 2 игрока." << endl << "Если 2 игрок не наблюдает, напишите \"+\":";
        char temp;
        while (temp != '+')
            cin >> temp;
        int ship1 = 4; int ship2 = 3; int ship3 = 2; int ship4 = 1;
        int temp;
        while (ship1 != 0 || ship2 != 0 || ship3 != 0 || ship4 != 0);
        {
            cout << endl << "Выберите количество палуб корабля (1, 2, 3, 4) для расстановки:";
            cin >> temp;
            switch (temp)
            {
            case 1:
                if (ship1 == 0)
                {
                    cout << "Однопалубные корабли закончились!";
                    break;
                }
                ship1--;
                setshipdeck1(1);
            case 2:
                if (ship2 == 0)
                {
                    cout << "Двухпалубные корабли закончились!";
                    break;
                }
                ship2--;
                setshipdeck1(2);
            case 3:
                if (ship3 == 0)
                {
                    cout << "Трехпалубные корабли закончились!";
                    break;
                }
                ship3--;
                setshipdeck1(3);
            case 4:
                if (ship4 == 0)
                {
                    cout << "Четырехпалубные корабли закончились!";
                    break;
                }
                ship4--;
                setshipdeck1(4);
            default:
                break;
            }
        }
        cout << "Итоговая доска 1:" << endl;
        printdeck1();
        cout << "Напишите \"+\" чтобы очистить консоль: ";
        char temp;
        while (temp != '+')
            cin >> temp;
        system("CLS");
    }
};

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));

    /*int rowsA, colsA;
    cout << "Введите кол-во строк массива А: ";
    cin >> rowsA;

    int rowsB, colsB;
    cout << "Введите кол-во строк массива B: ";
    cin >> rowsB;

    int rowsC, colsC;
    cout << "Введите кол-во строк массива C: ";
    cin >> rowsC;

    int** A = new int* [rowsA];
    int** B = new int* [rowsB];
    int** C = new int* [rowsC];

    for (int i = 0; i < rowsA; i++)
    {
        cout << "Введите кол-во столбцов массива А: ";
        cin >> colsA;
    }
    for (int i = 0; i < rowsB; i++)
    {
        cout << "Введите кол-во столбцов массива B: ";
        cin >> colsB;
    }
    for (int i = 0; i < rowsC; i++)
    {
        cout << "Введите кол-во столбцов массива C: ";
        cin >> colsC;
    }

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            A[i][j] = rand() % 9;
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < rowsB; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            B[i][j] = rand() % 9;
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < rowsC; i++)
    {
        for (int j = 0; j < colsC; j++)
        {
            C[i][j] = rand() % 9;
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/
    //cout << "______________________________________";
    //pract practice;
    //practice.fullandshow();
    return 0;
}
