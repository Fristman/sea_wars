#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <limits>

using namespace std;
void clear()
{
    system("CLS");
}
bool is_valid_coordd(int A, int B)
{
    return A >= 1 && A <= 10 && B >= 1 && B <= 10;
}
class game
{
protected:
    int deck1[12][12];
    int deck2[12][12];
    char symbols[10];
    string password1;
    string password2;
    const int symbolssum = 64;
    /*
    0 - пустое поле (_)
    1 - пустое поле, нельзя ставить корабли (o)
    2 - корабль (X)
    3 - промах (O)
    4 - подбит (X) (x in public)
    5 - поле вокруг подбитого корабля(O)
    */
    int status1;
    int status2;
    /*
    0 - Игрок не ходит
    1 - Ход игрока
    2 - Попадание, ход игрока
    */
public:
    game()
    {
        status1 = 0; status2 = 0;
        for (int i = 0; i < 10; i++)
        {
            symbols[i] = char(i + symbolssum+1);
        }
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                deck1[i][j] = 0;
                deck2[i][j] = 0;
            }
        }
    }
    void cleardecks()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                deck1[i][j] = 0;
                deck2[i][j] = 0;
            }
        }
    }
    void cleardeck1()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                deck1[i][j] = 0;
            }
        }
    }
    void cleardeck2()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                deck2[i][j] = 0;
            }
        }
    }
    void printdeck1build()
    {
        cout << "_ - Пустое поле\no - поле вокруг корабля\nX - корабль" << endl << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 1; i < 11; i++)
        {
            cout << endl << i << "\t";
            for (int j = 1; j < 11; j++)
            {
                if (deck1[i][j] == 0)
                    cout << "_ ";
                else if (deck1[i][j] == 1)
                    cout << "o ";
                else if (deck1[i][j] == 2)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    void printdeck2build()
    {
        cout << "_ - Пустое поле\no - поле вокруг корабля\nX - корабль" << endl << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 1; i < 11; i++)
        {
            cout << endl << i << "\t";
            for (int j = 1; j < 11; j++)
            {
                if (deck2[i][j] == 0)
                    cout << "_ ";
                else if (deck2[i][j] == 1)
                    cout << "o ";
                else if (deck2[i][j] == 2)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    void printdeck1public()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nx - корабль\nX - попадание по кораблю" << endl << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 1; i < 11; i++)
        {
            cout << endl << i << "\t";
            for (int j = 1; j < 11; j++)
            {
                if (deck1[i][j] == 0 || deck1[i][j] == 1)
                    cout << "_ ";
                else if (deck1[i][j] == 3 || deck1[i][j] == 5)
                    cout << "O ";
                else if (deck1[i][j] == 2)
                    cout << "x ";
                else if (deck1[i][j] == 4)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    void printdeck1private()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - попадание по кораблю" << endl << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 1; i < 11; i++)
        {
            cout << endl << i << "\t";
            for (int j = 1; j < 11; j++)
            {
                if (deck1[i][j] == 0 || deck1[i][j] == 1 || deck1[i][j] == 2)
                    cout << "_ ";
                else if (deck1[i][j] == 3 || deck1[i][j] == 5)
                    cout << "O ";
                else if (deck1[i][j] == 4)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    void printdeck2public()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nx - корабль\nX - попадание по кораблю" << endl << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 1; i < 11; i++)
        {
            cout << endl << i << "\t";
            for (int j = 1; j < 11; j++)
            {
                if (deck2[i][j] == 0 || deck2[i][j] == 1)
                    cout << "_ ";
                else if (deck2[i][j] == 3 || deck2[i][j] == 5)
                    cout << "O ";
                else if (deck2[i][j] == 2)
                    cout << "x ";
                else if (deck2[i][j] == 4)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    void printdeck2private()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - попадание по кораблю" << endl << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 1; i < 11; i++)
        {
            cout << endl << i << "\t";
            for (int j = 1; j < 11; j++)
            {
                if (deck2[i][j] == 0 || deck2[i][j] == 1 || deck2[i][j] == 2)
                    cout << "_ ";
                else if (deck2[i][j] == 3 || deck2[i][j] == 5)
                    cout << "O ";
                else if (deck2[i][j] == 4)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    /*void printdeck1()
    {
        cout << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 0; i < 10; i++)
        {
            cout << endl << i + 1 << "\t";
            for (int j = 0; j < 10; j++)
            {
                cout << deck1[i][j] << " ";
            }
        }
    }
    void printdeck2()
    {
        cout << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 0; i < 10; i++)
        {
            cout << endl << i + 1 << "\t";
            for (int j = 0; j < 10; j++)
            {
                cout << deck2[i][j] << " ";
            }
        }
    }*/
    virtual void print2decks()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - попадание по кораблю" << endl << endl;
        cout << "\t\t1 Доска\t\t\t\t\t2 Доска" << endl;
        cout << "\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        cout << "\t\t\t";
        for (int i = 0; i < 10; i++)
        {
            cout << symbols[i] << " ";
        }
        for (int i = 1; i < 11; i++)
        {
            cout << endl << i << "\t";
            for (int j = 1; j < 11; j++)
            {
                if (deck1[i][j] == 0 || deck1[i][j] == 1 || deck1[i][j] == 2)
                    cout << "_ ";
                else if (deck1[i][j] == 3 || deck1[i][j] == 5)
                    cout << "O ";
                else if (deck1[i][j] == 4)
                    cout << "X ";
                else
                    cout << "? ";
            }
            cout << "\t\t" << i << "\t";
            for (int j = 1; j < 11; j++)
            {
                if (deck2[i][j] == 0 || deck2[i][j] == 1 || deck2[i][j] == 2)
                    cout << "_ ";
                else if (deck2[i][j] == 3 || deck2[i][j] == 5)
                    cout << "O ";
                else if (deck2[i][j] == 4)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    int checkdeck()
    {
        bool temper = false;
        while (!temper)
        {
            cout << endl << endl << "Введите пароль своей доски (0 - выход): ";
            string temp;
            cin >> temp;
            if (temp == password1)
            {
                clear();
                cout << "\n\nВНИМАНИЕ!!! Сейчас будет показаны местоположения кораблей на 1 доске. Если 2 игрок не смотрит, напишите \'+\': ";
                char temp1 = '-';
                while (temp1 != '+')
                    cin >> temp1;
                cout << "\n\n";
                printdeck1public();
                cout << endl << endl << "Напишите \'+\' для очистки консоли: ";
                temp1 = '-';
                while (temp1 != '+')
                    cin >> temp1;
                clear();
                print2decks();
                cout << "Напишите любой символ: ";
                temper = true;
            }
            else if (temp == password2)
            {
                clear();
                cout << "\n\nВНИМАНИЕ!!! Сейчас будет показаны местоположения кораблей на 2 доске. Если 1 игрок не смотрит, напишите \'+\': ";
                char temp1 = '-';
                while (temp1 != '+')
                    cin >> temp1;
                cout << "\n\n";
                printdeck2public();
                cout << endl << endl << "Напишите \'+\' для очистки консоли: ";
                temp1 = '-';
                while (temp1 != '+')
                    cin >> temp1;
                clear();
                print2decks();
                cout << "Напишите любой символ: ";
                temper = true;
            }
            else if (temp == "0")
            {
                temper = true;
            }
            else
            {
                cout << "Пароль неверный, попробуйте еще раз.";
            }
        }
        return 0;
    }
    void setshipdeck1(int lenght)
    {
        clear();
            bool temp = false;
            printdeck1build();
            cout << endl <<endl<< "Постановка " << lenght << "-палубного корабля на доску 1" <<endl << endl;
            int temp1 = 0; char temp2 = 'А'; bool temp3 = false; bool temp4 = false; int reboot = 0;
            int A, B;
            while (!temp)
            {
                while (!temp3)
                {
                    reboot++;
                    if (reboot == 10)
                    {
                        cout << "Произошел сбой! Откат изменений...";
                        temp3 = true;
                        temp = true;
                        break;
                    }
                    cout << "Выберите позицию хвоста корабля (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " слитно(1A, 2B)): ";
                    cin >> A;
                    cin >> temp2;
                    cin.clear();
                    B = int(temp2) - symbolssum;
                    if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && deck1[A][B] == 0)
                        temp3 = true;
                    else
                        cout << endl << "Программа не смогла определить позицию хвоста или в этой позиции нельзя установить корабль! Попробуйте еще раз" << endl;
                }
                if (lenght == 1)
                {
                    cout << "Позиция корабля " << A << temp2 << endl;
                    deck1[A][B] = 2; deck1[A - 1][B] = 1; deck1[A + 1][B] = 1;
                    deck1[A][B - 1] = 1; deck1[A - 1][B - 1] = 1; deck1[A + 1][B - 1] = 1;
                    deck1[A][B + 1] = 1; deck1[A + 1][B + 1] = 1; deck1[A - 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                }
                cout << "Позиция хвоста " << A << temp2 << endl;
                reboot = 0;
                temp3 = false;
                while (!temp3)
                {
                    reboot++;
                    if (reboot == 10)
                    {
                        cout << "Произошел сбой! Откат изменений...";
                        temp3 = true;
                        temp = true;
                        break;
                    }
                    cout << "Выберите направление корабля" << endl << "1 - влево" << "\n2 - вверх\n3 - вправо\n4 - вниз\nВыбор: ";
                    cin >> temp1;
                    cin.clear();
                    while (temp1 < 1 || temp1>4)
                    {
                        cout << "Неккоректный ввод, еще раз: ";
                        cin >> temp1;
                    }
                    switch (temp1)
                    {
                    case 1:
                        temp4 = false;
                        if ((B - lenght + 1) > 0)
                        {
                            for (int i = B - lenght + 1; i < B; i++)
                            {
                                if (deck1[A][i] != 0)
                                    temp4 = true;
                            }
                        }
                        if ((B - lenght + 1) < 1 || temp4 == true)
                        {
                            cout << "Нельзя поставить корабль влево, выберите другое направление" << endl;
                            break;
                        }
                        cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum + 1 - lenght) << " - " << A << char(B + symbolssum) << endl << "Выполняется постановка...";
                        for (int i = 0; i < lenght; i++)
                        {
                            deck1[A][B - i] = 2;
                            deck1[A - 1][B - i] = 1;
                            deck1[A + 1][B - i] = 1;
                        }
                        deck1[A][B - lenght] = 1; deck1[A - 1][B - lenght] = 1; deck1[A + 1][B - lenght] = 1;
                        deck1[A][B + 1] = 1; deck1[A + 1][B + 1] = 1; deck1[A - 1][B + 1] = 1;
                        temp = true;
                        temp3 = true;
                        break;
                    case 2:
                        temp4 = false;
                        if ((A - lenght + 1) > 0)
                        {
                            for (int i = A - lenght + 1; i < A; i++)
                            {
                                if (deck1[i][B] != 0)
                                    temp4 = true;
                            }
                        }
                        if ((A - lenght + 1) < 1 || temp4 == true)
                        {
                            cout << "Нельзя поставить корабль вверх, выберите другое направление" << endl;
                            break;
                        }
                        cout << endl << "Начальная и конечная позиция корабля " << A - lenght + 1 << char(B + symbolssum) << " - " << A << char(B + symbolssum) << endl << "Выполняется постановка...";
                        for (int i = 0; i < lenght; i++)
                        {
                            deck1[A - i][B] = 2;
                            deck1[A - i][B - 1] = 1;
                            deck1[A - i][B + 1] = 1;
                        }
                        deck1[A - lenght][B] = 1; deck1[A - lenght][B - 1] = 1; deck1[A - lenght][B + 1] = 1;
                        deck1[A + 1][B] = 1; deck1[A + 1][B - 1] = 1; deck1[A + 1][B + 1] = 1;
                        temp = true;
                        temp3 = true;
                        break;
                    case 3:
                        temp4 = false;
                        if ((B + lenght - 1) < 11)
                        {
                            for (int i = B; i < B + lenght - 1; i++)
                            {
                                if (deck1[A][i] != 0)
                                    temp4 = true;
                            }
                        }
                        if ((B + lenght - 1) > 10 || temp4 == true)
                        {
                            cout << "Нельзя поставить корабль вправо, выберите другое направление" << endl;
                            break;
                        }
                        cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum) << " - " << A << char(B + symbolssum + lenght - 1) << endl << "Выполняется постановка...";
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
                        temp4 = false;
                        if ((A + lenght - 1) < 11)
                        {
                            for (int i = A; i < A + lenght - 1; i++)
                            {
                                if (deck1[i][B] != 0)
                                    temp4 = true;
                            }
                        }
                        if ((A + lenght - 1) > 10 || temp4 == true)
                        {
                            cout << "Нельзя поставить корабль вниз, выберите другое направление" << endl;
                            break;
                        }
                        cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum) << " - " << A + lenght - 1 << char(B + symbolssum) << endl << "Выполняется постановка...";
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
    int setdeck1()
    {
        cout << "ВНИМАНИЕ!! Сейчас будет установка первой доски, не допускайте подглядывание 2 игрока." << endl << "Если 2 игрок не наблюдает, напишите \"+\":";
        char temp = '+';
        cin >> temp;
        while (temp != '+')
            cin >> temp;
        cout << "Введите пароль. В дальнейшем вы будете его использовать для просмотра доски: ";
        cin >> password1;
        int ship1 = 4; int ship2 = 3; int ship3 = 2; int ship4 = 1; int reboot = 0;
        int temp1;
        while (ship1 != 0 || ship2 != 0 || ship3 != 0 || ship4 != 0)
        {
            cout << endl << endl << "Выберите количество палуб корабля (1 - " << ship1 << " шт, 2 - " << ship2 << " шт, 3 - " << ship3 << " шт, 4 - " << ship4 << " шт) для расстановки : ";
            reboot++;
            if (reboot == 50)
            {
                clear();
                cin.clear();
                cout << "\n\nПроизошел сбой! Откат изменений...\n\n";
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        deck1[i][j] = 0;
                    }
                }
                ship1 = 0; ship2 = 0; ship3 = 0; ship4 = 0;
                return 1;
                break;
            }
            cin >> temp1;
            cin.clear();
            switch (temp1)
            {
            case 1:
                if (ship1 == 0)
                {
                    cout << "Однопалубные корабли закончились!";
                    break;
                }
                ship1--;
                setshipdeck1(1);
                break;
            case 2:
                if (ship2 == 0)
                {
                    cout << "Двухпалубные корабли закончились!";
                    break;
                }
                ship2--;
                setshipdeck1(2);
                break;
            case 3:
                if (ship3 == 0)
                {
                    cout << "Трехпалубные корабли закончились!";
                    break;
                }
                ship3--;
                setshipdeck1(3);
                break;
            case 4:
                if (ship4 == 0)
                {
                    cout << "Четырехпалубные корабли закончились!";
                    break;
                }
                ship4--;
                setshipdeck1(4);
                break;
            default:
                cout << "Неверный ввод, попробуйте еще раз..." << endl;
                break;
            }
        }
        clear();
        cout << "Итоговая доска 1:" << endl;
        printdeck1build();
        cout << "\n\nНапишите \"+\" чтобы очистить консоль: ";
        cin >> temp;
        while (temp != '+')
            cin >> temp;
        clear();
        return 0;
    }
    virtual int setshipdeck2(int lenght)
    {
        clear();
        bool temp = false;
        printdeck2build();
        cout << endl << endl <<"Постановка " << lenght << "-палубного корабля на доску 2" << endl << endl;
        int temp1 = 0; char temp2 = 'А'; bool temp3 = false; bool temp4 = false; int reboot = 0;
        int A, B;
        while (!temp)
        {
            while (!temp3)
            {
                reboot++;
                if (reboot == 10)
                {
                    cout << "Произошел сбой! Откат изменений...";
                    temp3 = true;
                    temp = true;
                    break;
                }
                cout << "Выберите позицию хвоста корабля (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " слитно(1A, 2B)): ";
                cin >> A;
                cin >> temp2;
                cin.clear();
                B = int(temp2) - symbolssum;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && deck2[A][B] == 0)
                    temp3 = true;
                else
                    cout << endl << "Программа не смогла определить позицию хвоста или в этой позиции нельзя установить корабль! Попробуйте еще раз" << endl;
            }
            if (lenght == 1)
            {
                cout << "Позиция корабля " << A << temp2 << endl;
                deck2[A][B] = 2; deck2[A - 1][B] = 1; deck2[A + 1][B] = 1;
                deck2[A][B - 1] = 1; deck2[A - 1][B - 1] = 1; deck2[A + 1][B - 1] = 1;
                deck2[A][B + 1] = 1; deck2[A + 1][B + 1] = 1; deck2[A - 1][B + 1] = 1;
                temp = true;
                temp3 = true;
                break;
            }
            cout << "Позиция хвоста " << A << temp2 << endl;
            reboot = 0;
            temp3 = false;
            while (!temp3)
            {
                reboot++;
                if (reboot == 10)
                {
                    cout << "Произошел сбой! Откат изменений...";
                    temp3 = true;
                    temp = true;
                    break;
                }
                cout << "Выберите направление корабля" << endl << "1 - влево" << "\n2 - вверх\n3 - вправо\n4 - вниз\nВыбор: ";
                cin >> temp1;
                while (temp1 < 1 || temp1>4)
                {
                    cout << "Неккоректный ввод, еще раз: ";
                    cin >> temp1;
                    cin.clear();
                }
                cin.clear();
                switch (temp1)
                {
                case 1:
                    temp4 = false;
                    if ((B - lenght + 1) > 0)
                    {
                        for (int i = B - lenght + 1; i < B; i++)
                        {
                            if (deck2[A][i] != 0)
                                temp4 = true;
                        }
                    }
                    if ((B - lenght + 1) < 1 || temp4 == true)
                    {
                        cout << "Нельзя поставить корабль влево, выберите другое направление" << endl;
                        break;
                    }
                    cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum - lenght + 1) << " - " << A << char(B + symbolssum) << endl << "Выполняется постановка...";
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A][B - i] = 2;
                        deck2[A - 1][B - i] = 1;
                        deck2[A + 1][B - i] = 1;
                    }
                    deck2[A][B - lenght] = 1; deck2[A - 1][B - lenght] = 1; deck2[A + 1][B - lenght] = 1;
                    deck2[A][B + 1] = 1; deck2[A + 1][B + 1] = 1; deck2[A - 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 2:
                    temp4 = false;
                    if ((A - lenght + 1) > 0)
                    {
                        for (int i = A - lenght + 1; i < A; i++)
                        {
                            if (deck2[i][B] != 0)
                                temp4 = true;
                        }
                    }
                    if ((A - lenght + 1) < 1 || temp4 == true)
                    {
                        cout << "Нельзя поставить корабль вверх, выберите другое направление" << endl;
                        break;
                    }
                    cout << endl << "Начальная и конечная позиция корабля " << A - lenght + 1 << char(B + symbolssum) << " - " << A << char(B + symbolssum) << endl << "Выполняется постановка...";
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A - i][B] = 2;
                        deck2[A - i][B - 1] = 1;
                        deck2[A - i][B + 1] = 1;
                    }
                    deck2[A - lenght][B] = 1; deck2[A - lenght][B - 1] = 1; deck2[A - lenght][B + 1] = 1;
                    deck2[A + 1][B] = 1; deck2[A + 1][B - 1] = 1; deck2[A + 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 3:
                    temp4 = false;
                    if ((B + lenght - 1) < 11)
                    {
                        for (int i = B; i < B + lenght - 1; i++)
                        {
                            if (deck2[A][i] != 0)
                                temp4 = true;
                        }
                    }
                    if ((B + lenght - 1) > 10 || temp4 == true)
                    {
                        cout << "Нельзя поставить корабль вправо, выберите другое направление" << endl;
                        break;
                    }
                    cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum) << " - " << A << char(B + symbolssum + lenght - 1) << endl << "Выполняется постановка...";
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A][B + i] = 2;
                        deck2[A - 1][B + i] = 1;
                        deck2[A + 1][B + i] = 1;
                    }
                    deck2[A][B + lenght] = 1; deck2[A - 1][B + lenght] = 1; deck2[A + 1][B + lenght] = 1;
                    deck2[A][B - 1] = 1; deck2[A + 1][B - 1] = 1; deck2[A - 1][B - 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 4:
                    temp4 = false;
                    if ((A + lenght - 1) < 11)
                    {
                        for (int i = A; i < A + lenght - 1; i++)
                        {
                            if (deck2[i][B] != 0)
                                temp4 = true;
                        }
                    }
                    if ((A + lenght - 1) > 10 || temp4 == true)
                    {
                        cout << "Нельзя поставить корабль вниз, выберите другое направление" << endl;
                        break;
                    }
                    cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum) << " - " << A + lenght - 1 << char(B + symbolssum) << endl << "Выполняется постановка...";
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A + i][B] = 2;
                        deck2[A + i][B - 1] = 1;
                        deck2[A + i][B + 1] = 1;
                    }
                    deck2[A + lenght][B] = 1; deck2[A + lenght][B - 1] = 1; deck2[A + lenght][B + 1] = 1;
                    deck2[A - 1][B] = 1; deck2[A - 1][B - 1] = 1; deck2[A - 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                default:
                    break;
                }
            }
        }
        return 0;
    }
    virtual int setdeck2()
    {
        clear();
        cout << "ВНИМАНИЕ!! Сейчас будет установка второй доски, не допускайте подглядывание 1 игрока." << endl << "Если 2 игрок не наблюдает, напишите \"+\":";
        char temp = '+';
        cin >> temp;
        while (temp != '+')
            cin >> temp;
        cout << "Введите пароль. В дальнейшем вы будете его использовать для просмотра доски: ";
        cin >> password2;
        int ship1 = 4; int ship2 = 3; int ship3 = 2; int ship4 = 1; int reboot = 0;
        int temp1;
        while (ship1 != 0 || ship2 != 0 || ship3 != 0 || ship4 != 0)
        {
            cout << endl << endl << "Выберите количество палуб корабля (1 - " << ship1 << " шт, 2 - " << ship2 << " шт, 3 - " << ship3 << " шт, 4 - " << ship4 << " шт) для расстановки : ";
            reboot++;
            if (reboot == 50)
            {
                clear();
                cout << "\n\nПроизошел сбой! Откат изменений...\n\n";
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        deck2[i][j] = 0;
                    }
                }
                ship1 = 0; ship2 = 0; ship3 = 0; ship4 = 0;
                return 1;
                break;
            }
            cin >> temp1;
            cin.clear();
            switch (temp1)
            {
            case 1:
                if (ship1 == 0)
                {
                    cout << "Однопалубные корабли закончились!";
                    break;
                }
                ship1--;
                setshipdeck2(1);
                break;
            case 2:
                if (ship2 == 0)
                {
                    cout << "Двухпалубные корабли закончились!";
                    break;
                }
                ship2--;
                setshipdeck2(2);
                break;
            case 3:
                if (ship3 == 0)
                {
                    cout << "Трехпалубные корабли закончились!";
                    break;
                }
                ship3--;
                setshipdeck2(3);
                break;
            case 4:
                if (ship4 == 0)
                {
                    cout << "Четырехпалубные корабли закончились!";
                    break;
                }
                ship4--;
                setshipdeck2(4);
                break;
            default:
                cout << "Неверный ввод, попробуйте еще раз..." << endl;
                break;
            }
        }
        clear();
        cout << "Итоговая доска 2:" << endl;
        printdeck2build();
        cout << "\n\nНапишите \"+\" чтобы очистить консоль: ";
        cin >> temp;
        while (temp != '+')
            cin >> temp;
        clear();
        return 0;
    }
    int setshipdeck1auto(int lenght)
    {
        clear();
        bool temp = false;
        int temp1 = 0; bool temp3 = false; bool temp4 = false; int reboot = 0;
        int A, B;
        while (!temp)
        {
            while (!temp3)
            {
                A = rand() % 10 + 1;
                B = rand() % 10 + 1;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && deck1[A][B] == 0)
                    temp3 = true;
            }
            if (lenght == 1)
            {
                deck1[A][B] = 2; deck1[A - 1][B] = 1; deck1[A + 1][B] = 1;
                deck1[A][B - 1] = 1; deck1[A - 1][B - 1] = 1; deck1[A + 1][B - 1] = 1;
                deck1[A][B + 1] = 1; deck1[A + 1][B + 1] = 1; deck1[A - 1][B + 1] = 1;
                temp = true;
                temp3 = true;
                break;
            }
            reboot = 0;
            temp3 = false;
            while (!temp3)
            {
                reboot++;
                if (reboot == 50)
                {
                    setshipdeck1auto(lenght);
                    return 0;
                }
                temp1 = rand() % 4 + 1;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10)
                {
                    switch (temp1)
                    {
                    case 1:
                        temp4 = false;
                        if ((B - lenght + 1) > 0)
                        {
                            for (int i = B - lenght + 1; i < B; i++)
                            {
                                if (deck1[A][i] != 0)
                                    temp4 = true;
                            }
                        }
                        if ((B - lenght + 1) < 1 || temp4 == true)
                        {
                            break;
                        }
                        for (int i = 0; i < lenght; i++)
                        {
                            deck1[A][B - i] = 2;
                            deck1[A - 1][B - i] = 1;
                            deck1[A + 1][B - i] = 1;
                        }
                        deck1[A][B - lenght] = 1; deck1[A - 1][B - lenght] = 1; deck1[A + 1][B - lenght] = 1;
                        deck1[A][B + 1] = 1; deck1[A + 1][B + 1] = 1; deck1[A - 1][B + 1] = 1;
                        temp = true;
                        temp3 = true;
                        break;
                    case 2:
                        temp4 = false;
                        if ((A - lenght + 1) > 0)
                        {
                            for (int i = A - lenght + 1; i < A; i++)
                            {
                                if (deck1[i][B] != 0)
                                    temp4 = true;
                            }
                        }
                        if ((A - lenght + 1) < 1 || temp4 == true)
                        {
                            break;
                        }
                        for (int i = 0; i < lenght; i++)
                        {
                            deck1[A - i][B] = 2;
                            deck1[A - i][B - 1] = 1;
                            deck1[A - i][B + 1] = 1;
                        }
                        deck1[A - lenght][B] = 1; deck1[A - lenght][B - 1] = 1; deck1[A - lenght][B + 1] = 1;
                        deck1[A + 1][B] = 1; deck1[A + 1][B - 1] = 1; deck1[A + 1][B + 1] = 1;
                        temp = true;
                        temp3 = true;
                        break;
                    case 3:
                        temp4 = false;
                        if (B + lenght - 1 < 11)
                        {
                            for (int i = B; i < B + lenght; i++)
                            {
                                if (deck1[A][i] != 0)
                                    temp4 = true;
                            }
                        }
                        if ((B + lenght - 1) > 10 || temp4 == true)
                        {
                            break;
                        }
                        for (int i = 0; i < lenght; i++)
                        {
                            deck1[A][B + i] = 2;
                            deck1[A - 1][B + i] = 1;
                            deck1[A + 1][B + i] = 1;
                        }
                        for (int i = -1; i < 2; i++)
                        {
                            deck1[A + i][B + lenght] = 1;
                            deck1[A + i][B - 1] = 1;
                        }
                        temp = true;
                        temp3 = true;
                        break;
                    case 4:
                        temp4 = false;
                        if ((A + lenght - 1) < 11)
                        {
                            for (int i = A; i < A + lenght - 1; i++)
                            {
                                if (deck1[i][B] != 0)
                                    temp4 = true;
                            }
                        }
                        if ((A + lenght) > 11 || temp4 == true)
                        {
                            break;
                        }
                        for (int i = 0; i < lenght; i++)
                        {
                            deck1[A + i][B] = 2;
                            deck1[A + i][B - 1] = 1;
                            deck1[A + i][B + 1] = 1;
                        }
                        for (int i = -1; i < 2; i++)
                        {
                            deck1[A + lenght][B + i] = 1;
                            deck1[A - 1][B + i] = 1;
                        }
                        temp = true;
                        temp3 = true;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        return 0;
    }
    int setdeck1auto()
    {
        cout << "\nВведите пароль. В дальнейшем вы будете его использовать для просмотра доски: ";
        cin >> password1;
        cout << "\nРасстановка кораблей роботом...\n\n";
        int ship1 = 4; int ship2 = 3; int ship3 = 2; int ship4 = 1; int reboot = 0;
        int temp1;
        while (ship1 != 0 || ship2 != 0 || ship3 != 0 || ship4 != 0)
        {
            temp1 = rand() % 4 + 1;
            switch (temp1)
            {
            case 1:
                if (ship1 == 0)
                {
                    break;
                }
                ship1--;
                setshipdeck1auto(1);
                break;
            case 2:
                if (ship2 == 0)
                {
                    break;
                }
                ship2--;
                setshipdeck1auto(2);
                break;
            case 3:
                if (ship3 == 0)
                {
                    break;
                }
                ship3--;
                setshipdeck1auto(3);
                break;
            case 4:
                if (ship4 == 0)
                {
                    break;
                }
                ship4--;
                setshipdeck1auto(4);
                break;
            default:
                break;
            }
        }
        cout << "Робот завершил расстановку\n\n";
        return 0;
    }
    int setshipdeck2auto(int lenght)
    {
        clear();
        bool temp = false;
        int temp1 = 0; bool temp3 = false; bool temp4 = false; int reboot = 0;
        int A, B;
        while (!temp)
        {
            while (!temp3)
            {
                A = rand() % 10 + 1;
                B = rand() % 10 + 1;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && deck2[A][B] == 0)
                    temp3 = true;
            }
            if (lenght == 1)
            {
                deck2[A][B] = 2; deck2[A - 1][B] = 1; deck2[A + 1][B] = 1;
                deck2[A][B - 1] = 1; deck2[A - 1][B - 1] = 1; deck2[A + 1][B - 1] = 1;
                deck2[A][B + 1] = 1; deck2[A + 1][B + 1] = 1; deck2[A - 1][B + 1] = 1;
                temp = true;
                temp3 = true;
                break;
            }
            reboot = 0;
            temp3 = false;
            while (!temp3)
            {
                reboot++;
                if (reboot == 50)
                {
                    setshipdeck1auto(lenght);
                    return 0;
                }
                temp1 = rand() % 4 + 1;
                switch (temp1)
                {
                case 1:
                    temp4 = false;
                    if ((B - lenght + 1) > 0)
                    {
                        for (int i = B - lenght + 1; i < B; i++)
                        {
                            if (deck2[A][i] != 0)
                                temp4 = true;
                        }
                    }
                    if ((B - lenght + 1) < 1 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A][B - i] = 2;
                        deck2[A - 1][B - i] = 1;
                        deck2[A + 1][B - i] = 1;
                    }
                    deck2[A][B - lenght] = 1; deck2[A - 1][B - lenght] = 1; deck2[A + 1][B - lenght] = 1;
                    deck2[A][B + 1] = 1; deck2[A + 1][B + 1] = 1; deck2[A - 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 2:
                    temp4 = false;
                    if ((A - lenght + 1) > 0)
                    {
                        for (int i = A - lenght + 1; i < A; i++)
                        {
                            if (deck2[i][B] != 0)
                                temp4 = true;
                        }
                    }
                    if ((A - lenght + 1) < 1 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A - i][B] = 2;
                        deck2[A - i][B - 1] = 1;
                        deck2[A - i][B + 1] = 1;
                    }
                    deck2[A - lenght][B] = 1; deck2[A - lenght][B - 1] = 1; deck2[A - lenght][B + 1] = 1;
                    deck2[A + 1][B] = 1; deck2[A + 1][B - 1] = 1; deck2[A + 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 3:
                    temp4 = false;
                    if (B + lenght - 1 < 11)
                    {
                        for (int i = B; i < B + lenght; i++)
                        {
                            if (deck2[A][i] != 0)
                                temp4 = true;
                        }
                    }
                    if ((B + lenght - 1) > 10 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A][B + i] = 2;
                        deck2[A - 1][B + i] = 1;
                        deck2[A + 1][B + i] = 1;
                    }
                    for (int i = -1; i < 2; i++)
                    {
                        deck2[A + i][B + lenght] = 1;
                        deck2[A + i][B - 1] = 1;
                    }
                    temp = true;
                    temp3 = true;
                    break;
                case 4:
                    temp4 = false;
                    if ((A + lenght - 1) < 11)
                    {
                        for (int i = A; i < A + lenght - 1; i++)
                        {
                            if (deck2[i][B] != 0)
                                temp4 = true;
                        }
                    }
                    if ((A + lenght) > 11 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A + i][B] = 2;
                        deck2[A + i][B - 1] = 1;
                        deck2[A + i][B + 1] = 1;
                    }
                    for (int i = -1; i < 2; i++)
                    {
                        deck2[A + lenght][B + i] = 1;
                        deck2[A - 1][B + i] = 1;
                    }
                    temp = true;
                    temp3 = true;
                    break;
                default:
                    break;
                }
            }
        }
        return 0;
    }
    int setdeck2auto()
    {
        cout << "\nВведите пароль. В дальнейшем вы будете его использовать для просмотра доски: ";
        cin >> password2;
        cout << "\nРасстановка кораблей роботом...\n\n";
        int ship1 = 4; int ship2 = 3; int ship3 = 2; int ship4 = 1; int reboot = 0;
        int temp1;
        while (ship1 != 0 || ship2 != 0 || ship3 != 0 || ship4 != 0)
        {
            temp1 = rand() % 4 + 1;
            switch (temp1)
            {
            case 1:
                if (ship1 == 0)
                {
                    break;
                }
                ship1--;
                setshipdeck2auto(1);
                break;
            case 2:
                if (ship2 == 0)
                {
                    break;
                }
                ship2--;
                setshipdeck2auto(2);
                break;
            case 3:
                if (ship3 == 0)
                {
                    break;
                }
                ship3--;
                setshipdeck2auto(3);
                break;
            case 4:
                if (ship4 == 0)
                {
                    break;
                }
                ship4--;
                setshipdeck2auto(4);
                break;
            default:
                break;
            }
        }
        cout << "Робот завершил расстановку\n\n";
        return 0;
    }
    void kill()
    {
        clear();
        print2decks();
        cout << "\n\nУбит!";
    }
    bool checkbot(bool C)
    {
        int temp1 = 2; int temp2 = 2; int temp3 = 2; int temp4 = 2; bool temp = false; int ship1 = 0; int ship2 = 0; int ship3 = 0; int ship4 = 0;
        int checkdeck[12][12];
        if (C == 1)
        {
            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    checkdeck[i][j] = deck1[i][j];
                }
            }
        }
        else
        {
            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    checkdeck[i][j] = deck2[i][j];
                }
            }
        }
        for (int A = 1; A < 11; A++)
        {
            for (int B = 1; B < 11; B++)
            {
                temp4 = 2;
                temp3 = 2;
                if (checkdeck[A][B] == 2)
                {
                    if (checkdeck[A+1][B] == 2)
                        temp4 = 1;
                    if (checkdeck[A][B+1] == 2)
                        temp3 = 1;
                    if (temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1)
                    {
                        ship1++;
                        checkdeck[A][B] = 1;
                    }
                    if (temp3 == 1)
                    {
                        if (checkdeck[A][B + 2] == 2)
                        {
                            if (checkdeck[A][B + 3] == 2)
                            {
                                checkdeck[A][B + 3] = 1;
                                ship4++;
                            }
                            checkdeck[A][B + 2] = 1;
                            ship3++;
                        }
                        checkdeck[A][B + 1] = 1; checkdeck[A][B] = 1;
                        ship2++;
                    }
                    if (temp4 == 1)
                    {
                        if (checkdeck[A+2][B] == 2)
                        {
                            if (checkdeck[A+3][B] == 2)
                            {
                                checkdeck[A+3][B] = 1;
                                ship4++;
                            }
                            checkdeck[A+2][B] = 1;
                            ship3++;
                        }
                        checkdeck[A+1][B] = 1; checkdeck[A][B] = 1;
                        ship2++;
                    }
                }
            }
        }
        if (ship1 == 4 && ship2 == 3 && ship3 == 2 && ship4 == 1)
            return 1;
        else
            return 0;
    }
    virtual int check(int A, int B)
    {
        cout << endl << "Выбранная позиция для удара " << A << char(B + symbolssum) << endl;
        int temp1 = 2; int temp2 = 2; int temp3 = 2; int temp4 = 2; int tempA = A; int tempB = B;
        if (status1 == 1 || status1 == 2 || status2 == 0)
        {
            if (!(A >= 1 && A <= 10 && B >= 1 && B <= 10))
            {
                cout << "\nНеверные координаты для удара\n";
                return 0;
            }
            else if (deck2[A][B] == 3 || deck2[A][B] == 4 || deck2[A][B] == 5)
            {
                cout << "\nВ эту позицию нельзя ударить!\n";
                return 0;
            }
            else if (deck2[A][B] == 0 || deck2[A][B] == 1)
            {
                deck2[A][B] = 3;
                clear();
                print2decks();
                cout << endl << "\nПромах!";
                status1 = 0;
                status2 = 1;
                return 0;
            }
            else if (deck2[A][B] == 2)
            {
                deck2[A][B] = 4;
                status1 = 2;
                status2 = 0;

                bool still_alive = false;

                if (deck2[A + 1][B] == 4 || deck2[A + 1][B] == 2)
                    temp4 = 0;
                if (deck2[A - 1][B] == 4 || deck2[A - 1][B] == 2)
                    temp2 = 0;
                if (deck2[A][B - 1] == 4 || deck2[A][B - 1] == 2)
                    temp1 = 0;
                if (deck2[A][B + 1] == 4 || deck2[A][B + 1] == 2)
                    temp3 = 0;
                if (temp1 == 0 && temp3 == 0)
                    if (deck2[A][B - 2] == 2 || deck2[A][B - 1] == 2 || deck2[A][B] == 2 || deck2[A][B + 1] == 2 || deck2[A][B + 2] == 2)
                        still_alive = true;
                if (temp2 == 0 && temp4 == 0)
                    if (deck2[A - 2][B] == 2 || deck2[A - 1][B] == 2 || deck2[A][B] == 2 || deck2[A + 1][B] == 2 || deck2[A + 2][B] == 2)
                        still_alive = true;
                if (temp1 == 0)
                {
                    if (deck2[A][B - 2] == 2 || deck2[A][B - 2] == 4)
                        temp1 = 2;
                    if (temp1 == 2)
                        if (deck2[A][B - 3] == 2 || deck2[A][B - 2] == 2 || deck2[A][B - 1] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                    if (temp1 == 0)
                        if (deck2[A][B - 1] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                }
                if (temp3 == 0)
                {
                    if (deck2[A][B + 2] == 2 || deck2[A][B + 2] == 4)
                        temp3 = 2;
                    if (temp3 == 2)
                        if (deck2[A][B + 3] == 2 || deck2[A][B + 2] == 2 || deck2[A][B + 1] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                    if (temp3 == 0)
                        if (deck2[A][B] == 2 || deck2[A][B + 1] == 2)
                            still_alive = true;
                }
                if (temp2 == 0)
                {
                    if (deck2[A - 2][B] == 2 || deck2[A - 2][B] == 4)
                        temp2 = 2;
                    if (temp2 == 2)
                        if (deck2[A - 3][B] == 2 || deck2[A - 2][B] == 2 || deck2[A][B] == 2 || deck2[A - 1][B] == 2)
                            still_alive = true;
                    if (temp2 == 0)
                        if (deck2[A - 1][B] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                }
                if (temp4 == 0)
                {
                    if (deck2[A + 2][B] == 2 || deck2[A + 2][B] == 4)
                        temp4 = 2;
                    if (temp4 == 2)
                        if (deck2[A + 3][B] == 2 || deck2[A + 2][B] == 2 || deck2[A][B] == 2 || deck2[A + 1][B] == 2)
                            still_alive = true;
                    if (temp4 == 0)
                        if (deck2[A + 1][B] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                }

                if (still_alive) 
                {
                    clear();
                    print2decks();
                    cout << endl<<"\nПопал!";
                }
                else
                {
                    if (deck2[A + 1][B] == 4)
                        temp4 = 1;
                    if (deck2[A - 1][B] == 4)
                        temp2 = 1;
                    if (deck2[A][B - 1] == 4)
                        temp1 = 1;
                    if (deck2[A][B + 1] == 4)
                        temp3 = 1;
                    if (temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1)
                    {
                        deck2[A - 1][B] = 5; deck2[A + 1][B] = 5; deck2[A][B + 1] = 5; deck2[A][B - 1] = 5; deck2[A - 1][B - 1] = 5; deck2[A + 1][B - 1] = 5; deck2[A - 1][B + 1] = 5; deck2[A + 1][B + 1] = 5;
                        kill();
                    }
                    if (temp1 == 1 && temp3 == 1)
                    {
                        if (deck2[A][B - 2] == 4)
                        {
                            deck2[A][B - 3] = 5; deck2[A][B + 2] = 5;
                            for (int i = B - 3; i < B + 3; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else if (deck2[A][B + 2] == 4)
                        {
                            deck2[A][B + 3] = 5; deck2[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 4; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else
                        {
                            deck2[A][B + 2] = 5; deck2[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                    }
                    if (temp2 == 1 && temp4 == 1)
                    {
                        if (deck2[A - 2][B] == 4)
                        {
                            deck2[A - 3][B] = 5; deck2[A + 2][B] = 5;
                            for (int i = A - 3; i < A + 3; i++)
                            {
                                deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else if (deck2[A + 2][B] == 4)
                        {
                            deck2[A + 3][B] = 5; deck2[A - 2][B] = 5;
                            for (int i = A - 2; i < A + 4; i++)
                            {
                                deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else
                        {
                            deck2[A + 2][B] = 5; deck2[A - 2][B] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                    }
                    if (temp1 == 1)
                    {
                        if (deck2[A][B - 2] == 4)
                        {
                            if (deck2[A][B - 3] == 4)
                            {
                                deck2[A][B + 1] = 5; deck2[A][B - 4] = 5;
                                for (int i = B - 4; i < B + 2; i++)
                                {
                                    deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck2[A][B + 1] = 5; deck2[A][B - 3] = 5;
                            for (int i = B - 3; i < B + 2; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck2[A][B + 1] = 5; deck2[A][B - 2] = 5;
                        for (int i = B - 2; i < B + 2; i++)
                        {
                            deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp3 == 1)
                    {
                        if (deck2[A][B + 2] == 4)
                        {
                            if (deck2[A][B + 3] == 4)
                            {
                                deck2[A][B - 1] = 5; deck2[A][B + 4] = 5;
                                for (int i = B - 1; i < B + 5; i++)
                                {
                                    deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck2[A][B + 1] = 5; deck2[A][B - 3] = 5;
                            for (int i = B - 1; i < B + 4; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck2[A][B + 1] = 5; deck2[A][B - 2] = 5;
                        for (int i = B - 1; i < B + 3; i++)
                        {
                            deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck2[A - 2][B] == 4)
                        {
                            if (deck2[A - 3][B] == 4)
                            {
                                deck2[A + 1][B] = 5; deck2[A - 4][B] = 5;
                                for (int i = A - 4; i < A + 2; i++)
                                {
                                    deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck2[A + 1][B] = 5; deck2[A - 3][B] = 5;
                            for (int i = A - 3; i < A + 2; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck2[A + 1][B] = 5; deck2[A - 2][B] = 5;
                        for (int i = A - 2; i < A + 2; i++)
                        {
                            deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp4 == 1)
                    {
                        if (deck2[A + 2][B] == 4)
                        {
                            if (deck2[A + 3][B] == 4)
                            {
                                deck2[A - 1][B] = 5; deck2[A + 4][B] = 5;
                                for (int i = A - 1; i < A + 5; i++)
                                {
                                    deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck2[A - 1][B] = 5; deck2[A + 3][B] = 5;
                            for (int i = A - 1; i < A + 4; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck2[A + 2][B] = 5; deck2[A - 1][B] = 5;
                        for (int i = A - 1; i < A + 3; i++)
                        {
                            deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                        }
                        kill();
                        return 0;
                    }
                }
            }
            return 0;
        }
        else if (status2 == 1 || status2 == 2 || status1 == 0)
        {
            if (!(A >= 1 && A <= 10 && B >= 1 && B <= 10))
            {
                cout << "\nНеверные координаты для удара\n";
                return 0;
            }
            else if (deck1[A][B] == 3 || deck1[A][B] == 4 || deck1[A][B] == 5)
            {
                cout << "\nВ эту позицию нельзя ударить!\n";
                return 0;
            }
            else if (deck1[A][B] == 0 || deck1[A][B] == 1)
            {
                deck1[A][B] = 3;
                clear();
                print2decks();
                cout << endl << "\nПромах!";
                status2 = 0;
                status1 = 1;
                return 0;
            }
            else if (deck1[A][B] == 2)
            {
                deck1[A][B] = 4;
                status2 = 2;
                status1 = 0;

                bool still_alive = false;

                if (deck1[A + 1][B] == 4 || deck1[A + 1][B] == 2)
                    temp4 = 0;
                if (deck1[A - 1][B] == 4 || deck1[A - 1][B] == 2)
                    temp2 = 0;
                if (deck1[A][B - 1] == 4 || deck1[A][B - 1] == 2)
                    temp1 = 0;
                if (deck1[A][B + 1] == 4 || deck1[A][B + 1] == 2)
                    temp3 = 0;
                if (temp1 == 0 && temp3 == 0)
                    if (deck1[A][B - 2] == 2 || deck1[A][B - 1] == 2 || deck1[A][B] == 2 || deck1[A][B + 1] == 2 || deck1[A][B + 2] == 2)
                        still_alive = true;
                if (temp2 == 0 && temp4 == 0)
                    if (deck1[A - 2][B] == 2 || deck1[A - 1][B] == 2 || deck1[A][B] == 2 || deck1[A + 1][B] == 2 || deck1[A + 2][B] == 2)
                        still_alive = true;
                if (temp1 == 0)
                {
                    if (deck1[A][B - 2] == 2 || deck1[A][B - 2] == 4)
                        temp2 = 2;
                    if (temp2 == 2)
                        if (deck1[A][B - 3] == 2 || deck1[A][B - 2] == 2 || deck1[A][B - 1] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                    if (temp2 == 0)
                        if (deck1[A][B - 1] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                }
                if (temp3 == 0)
                {
                    if (deck1[A][B + 2] == 2 || deck1[A][B + 2] == 4)
                        temp4 = 2;
                    if (temp4 == 2)
                        if (deck1[A][B + 3] == 2 || deck1[A][B + 2] == 2 || deck1[A][B + 1] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                    if (temp4 == 0)
                        if (deck1[A][B] == 2 || deck1[A][B + 1] == 2)
                            still_alive = true;
                }
                if (temp2 == 0)
                {
                    if (deck1[A - 2][B] == 2 || deck1[A - 2][B] == 4)
                        temp1 = 2;
                    if (temp1 == 2)
                        if (deck1[A - 3][B] == 2 || deck1[A - 2][B] == 2 || deck1[A][B] == 2 || deck1[A - 1][B] == 2)
                            still_alive = true;
                    if (temp1 == 0)
                        if (deck1[A - 1][B] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                }
                if (temp4 == 0)
                {
                    if (deck1[A + 2][B] == 2 || deck1[A + 2][B] == 4)
                        temp3 = 2;
                    if (temp3 == 2)
                        if (deck1[A + 3][B] == 2 || deck1[A + 2][B] == 2 || deck1[A][B] == 2 || deck1[A + 1][B] == 2)
                            still_alive = true;
                    if (temp3 == 0)
                        if (deck1[A + 1][B] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                }

                if (still_alive)
                {
                    clear();
                    print2decks();
                    cout << endl << "\nПопал!";
                }
                else
                {
                    if (deck1[A + 1][B] == 4)
                        temp4 = 1;
                    if (deck1[A - 1][B] == 4)
                        temp2 = 1;
                    if (deck1[A][B - 1] == 4)
                        temp1 = 1;
                    if (deck1[A][B + 1] == 4)
                        temp3 = 1;
                    if (temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1)
                    {
                        deck1[A - 1][B] = 5; deck1[A + 1][B] = 5; deck1[A][B + 1] = 5; deck1[A][B - 1] = 5; deck1[A - 1][B - 1] = 5; deck1[A + 1][B - 1] = 5; deck1[A - 1][B + 1] = 5; deck1[A + 1][B + 1] = 5;
                        kill();
                        return 0;
                    }
                    if (temp1 == 1 && temp3 == 1)
                    {
                        if (deck1[A][B - 2] == 4)
                        {
                            deck1[A][B - 3] = 5; deck1[A][B + 2] = 5;
                            for (int i = B - 3; i < B + 3; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else if (deck1[A][B + 2] == 4)
                        {
                            deck1[A][B + 3] = 5; deck1[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 4; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else
                        {
                            deck1[A][B + 2] = 5; deck1[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                    }
                    if (temp2 == 1 && temp4 == 1)
                    {
                        if (deck1[A - 2][B] == 4)
                        {
                            deck1[A - 3][B] = 5; deck1[A + 2][B] = 5;
                            for (int i = A - 3; i < A + 3; i++)
                            {
                                deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else if (deck1[A + 2][B] == 4)
                        {
                            deck1[A + 3][B] = 5; deck1[A - 2][B] = 5;
                            for (int i = A - 2; i < A + 4; i++)
                            {
                                deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else
                        {
                            deck1[A + 2][B] = 5; deck1[A - 2][B] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                    }
                    if (temp1 == 1)
                    {
                        if (deck1[A][B - 2] == 4)
                        {
                            if (deck1[A][B - 3] == 4)
                            {
                                deck1[A][B + 1] = 5; deck1[A][B - 4] = 5;
                                for (int i = B - 4; i < B + 2; i++)
                                {
                                    deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck1[A][B + 1] = 5; deck1[A][B - 3] = 5;
                            for (int i = B - 3; i < B + 2; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck1[A][B + 1] = 5; deck1[A][B - 2] = 5;
                        for (int i = B - 2; i < B + 2; i++)
                        {
                            deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp3 == 1)
                    {
                        if (deck1[A][B + 2] == 4)
                        {
                            if (deck1[A][B + 3] == 4)
                            {
                                deck1[A][B - 1] = 5; deck1[A][B + 4] = 5;
                                for (int i = B - 1; i < B + 5; i++)
                                {
                                    deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck1[A][B + 1] = 5; deck1[A][B - 3] = 5;
                            for (int i = B - 1; i < B + 4; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck1[A][B + 1] = 5; deck1[A][B - 2] = 5;
                        for (int i = B - 1; i < B + 3; i++)
                        {
                            deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck1[A - 2][B] == 4)
                        {
                            if (deck1[A - 3][B] == 4)
                            {
                                deck1[A + 1][B] = 5; deck1[A - 4][B] = 5;
                                for (int i = A - 4; i < A + 2; i++)
                                {
                                    deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck1[A + 1][B] = 5; deck1[A - 3][B] = 5;
                            for (int i = A - 3; i < A + 2; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck1[A + 1][B] = 5; deck1[A - 2][B] = 5;
                        for (int i = A - 2; i < A + 2; i++)
                        {
                            deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp4 == 1)
                    {
                        if (deck1[A + 2][B] == 4)
                        {
                            if (deck1[A + 3][B] == 4)
                            {
                                deck1[A - 1][B] = 5; deck1[A + 4][B] = 5;
                                for (int i = A - 1; i < A + 5; i++)
                                {
                                    deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck1[A - 1][B] = 5; deck1[A + 3][B] = 5;
                            for (int i = A - 1; i < A + 4; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck1[A + 1][B] = 5; deck1[A - 2][B] = 5;
                        for (int i = A - 1; i < A + 3; i++)
                        {
                            deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                        }
                        kill();
                        return 0;
                    }
                }
            }
            return 0;
        }
        else
        {
            cout << "Ошибка";
            return 0;
        }
        return 0;
    }
    int checkwin()
    {
        bool temp1 = 0; bool temp2 = 0;
        for (int i = 1; i < 11; i++)
        {
            for (int j = 1; j < 11; j++)
            {
                if (deck1[i][j] == 2)
                {
                    temp1 = true;
                }
                if (deck2[i][j] == 2)
                {
                    temp2 = true;
                }
            }
        }
        if (temp1 && temp2)
            return 0;
        else if (!temp1)
            return 2;
        else if (!temp2)
            return 1;
        else
            return 0;
    }
    virtual void step()
    {
        bool temp3 = 0; int temp1 = 0; char temp2 = 0; int A = 0; int B = 0;
        if (status1 == 1 || status1 == 2 || status2 == 0)
        {
            cout << "\n\nХод 1 игрока" << endl << endl;
            temp3 = false;
            while (!temp3)
            {
                cout << "Выберите позицию для удара (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " (A1, B2) (0 для просмотра доск)): ";
                cin >> temp1;
                if (temp1 == 0) { checkdeck(); continue; }
                cin>>temp2;
                A = temp1;
                B = int(temp2) - symbolssum;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && deck2[A][B] != 3 && deck2[A][B] != 4 && deck2[A][B] != 5)
                    temp3 = true;
                else
                    cout << endl << "Программа не смогла определить позицию удара или в эту позицию нельзя ударить! Попробуйте еще раз" << endl;
            }
            check(A, B);
        }
        else if (status2 == 1 || status2 == 2 || status1 == 0)
        {
            cout << "\n\nХод 2 игрока" << endl << endl;
            temp3 = false;
            while (!temp3)
            {
                cout << "Выберите позицию для удара (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " (A1, B2) (0 для просмотра доск)): ";
                cin >> temp1;
                if (temp1 == 0) { checkdeck(); continue; }
                cin >> temp2;
                A = temp1;
                B = int(temp2) - symbolssum;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && deck1[A][B] != 3 && deck1[A][B] != 4 && deck1[A][B] != 5)
                    temp3 = true;
                else
                    cout << endl << "Программа не смогла определить позицию удара или в эту позицию нельзя ударить! Попробуйте еще раз" << endl;
            }
            check(A, B);
        }
        else
        {
            cout << "Ошибка, ход 1 игрока.";
            status1 = 1;
            status2 = 0;
        }
    }
};
class botgame : public game
{
protected:
    int botcordx;
    int botcordy;
public:
    botgame()
    {
        password2 = "vanvonadonvsajnalgfnlajn5yg1tg1eg31134foangaojgfagojavnoaovodaijov dadv voiansovnaojnfoajofv ";
        status1 = 0; status2 = 0;
        for (int i = 0; i < 10; i++)
        {
            symbols[i] = char(i + symbolssum+1);
        }
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                deck1[i][j] = 0;
                deck2[i][j] = 0;
            }
        }
        botcordx = 0;
        botcordy = 0;
    }
    int setshipdeck2(int lenght)
    {
        clear();
        bool temp = false;
        int temp1 = 0; bool temp3 = false; bool temp4 = false; int reboot = 0;
        int A, B;
        while (!temp)
        {
            while (!temp3)
            {
                A = rand() % 10 + 1;
                B = rand() % 10 + 1;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && deck2[A][B] == 0)
                    temp3 = true;
            }
            if (lenght == 1)
            {
                deck2[A][B] = 2; deck2[A - 1][B] = 1; deck2[A + 1][B] = 1;
                deck2[A][B - 1] = 1; deck2[A - 1][B - 1] = 1; deck2[A + 1][B - 1] = 1;
                deck2[A][B + 1] = 1; deck2[A + 1][B + 1] = 1; deck2[A - 1][B + 1] = 1;
                temp = true;
                temp3 = true;
                break;
            }
            reboot = 0;
            temp3 = false;
            while (!temp3)
            {
                reboot++;
                if (reboot == 50)
                {
                    setshipdeck1auto(lenght);
                    return 0;
                }
                temp1 = rand() % 4 + 1;
                switch (temp1)
                {
                case 1:
                    temp4 = false;
                    if ((B - lenght + 1) > 0)
                    {
                        for (int i = B - lenght + 1; i < B; i++)
                        {
                            if (deck2[A][i] != 0)
                                temp4 = true;
                        }
                    }
                    if ((B - lenght + 1) < 1 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A][B - i] = 2;
                        deck2[A - 1][B - i] = 1;
                        deck2[A + 1][B - i] = 1;
                    }
                    deck2[A][B - lenght] = 1; deck2[A - 1][B - lenght] = 1; deck2[A + 1][B - lenght] = 1;
                    deck2[A][B + 1] = 1; deck2[A + 1][B + 1] = 1; deck2[A - 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 2:
                    temp4 = false;
                    if ((A - lenght + 1) > 0)
                    {
                        for (int i = A - lenght + 1; i < A; i++)
                        {
                            if (deck2[i][B] != 0)
                                temp4 = true;
                        }
                    }
                    if ((A - lenght + 1) < 1 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A - i][B] = 2;
                        deck2[A - i][B - 1] = 1;
                        deck2[A - i][B + 1] = 1;
                    }
                    deck2[A - lenght][B] = 1; deck2[A - lenght][B - 1] = 1; deck2[A - lenght][B + 1] = 1;
                    deck2[A + 1][B] = 1; deck2[A + 1][B - 1] = 1; deck2[A + 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 3:
                    temp4 = false;
                    if (B + lenght - 1 < 11)
                    {
                        for (int i = B; i < B + lenght; i++)
                        {
                            if (deck2[A][i] != 0)
                                temp4 = true;
                        }
                    }
                    if ((B + lenght - 1) > 10 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A][B + i] = 2;
                        deck2[A - 1][B + i] = 1;
                        deck2[A + 1][B + i] = 1;
                    }
                    for (int i = -1; i < 2; i++)
                    {
                        deck2[A + i][B + lenght] = 1;
                        deck2[A + i][B - 1] = 1;
                    }
                    temp = true;
                    temp3 = true;
                    break;
                case 4:
                    temp4 = false;
                    if ((A + lenght - 1) < 11)
                    {
                        for (int i = A; i < A + lenght - 1; i++)
                        {
                            if (deck2[i][B] != 0)
                                temp4 = true;
                        }
                    }
                    if ((A + lenght) > 11 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        deck2[A + i][B] = 2;
                        deck2[A + i][B - 1] = 1;
                        deck2[A + i][B + 1] = 1;
                    }
                    for (int i = -1; i < 2; i++)
                    {
                        deck2[A + lenght][B + i] = 1;
                        deck2[A - 1][B + i] = 1;
                    }
                    temp = true;
                    temp3 = true;
                    break;
                default:
                    break;
                }
            }
        }
            return 0;
    }
    int setdeck2()
    {
        cout << "\nРасстановка кораблей роботом...\n\n";
        int ship1 = 4; int ship2 = 3; int ship3 = 2; int ship4 = 1; int reboot = 0;
        int temp1;
        while (ship1 != 0 || ship2 != 0 || ship3 != 0 || ship4 != 0)
        {
            temp1 = rand() % 4 + 1;
            switch (temp1)
            {
            case 1:
                if (ship1 == 0)
                {
                    break;
                }
                ship1--;
                setshipdeck2(1);
                break;
            case 2:
                if (ship2 == 0)
                {
                    break;
                }
                ship2--;
                setshipdeck2(2);
                break;
            case 3:
                if (ship3 == 0)
                {
                    break;
                }
                ship3--;
                setshipdeck2(3);
                break;
            case 4:
                if (ship4 == 0)
                {
                    break;
                }
                ship4--;
                setshipdeck2(4);
                break;
            default:
                break;
            }
        }
        cout << "Робот завершил расстановку\n\n";
        return 0;
    }
    int check(int A, int B)
    {
        cout << endl << "Выбранная позиция для удара " << A << char(B + symbolssum) << endl;
        int temp1 = 2; int temp2 = 2; int temp3 = 2; int temp4 = 2; int tempA = A; int tempB = B;
        if (status1 == 1 || status1 == 2 || status2 == 0)
        {
            if (!(A >= 1 && A <= 10 && B >= 1 && B <= 10))
            {
                cout << "\nНеверные координаты для удара\n";
                return 0;
            }
            else if (deck2[A][B] == 3 || deck2[A][B] == 4 || deck2[A][B] == 5)
            {
                cout << "\nВ эту позицию нельзя ударить!\n";
                return 0;
            }
            else if (deck2[A][B] == 0 || deck2[A][B] == 1)
            {
                deck2[A][B] = 3;
                clear();
                print2decks();
                cout << endl << "\nПромах!";
                status1 = 0;
                status2 = 1;
                return 0;
            }
            else if (deck2[A][B] == 2)
            {
                deck2[A][B] = 4;
                status1 = 2;
                status2 = 0;

                bool still_alive = false;

                if (deck2[A + 1][B] == 4 || deck2[A + 1][B] == 2)
                    temp4 = 0;
                if (deck2[A - 1][B] == 4 || deck2[A - 1][B] == 2)
                    temp2 = 0;
                if (deck2[A][B - 1] == 4 || deck2[A][B - 1] == 2)
                    temp1 = 0;
                if (deck2[A][B + 1] == 4 || deck2[A][B + 1] == 2)
                    temp3 = 0;
                if (temp1 == 0 && temp3 == 0)
                    if (deck2[A][B - 2] == 2 || deck2[A][B - 1] == 2 || deck2[A][B] == 2 || deck2[A][B + 1] == 2 || deck2[A][B + 2] == 2)
                        still_alive = true;
                if (temp2 == 0 && temp4 == 0)
                    if (deck2[A - 2][B] == 2 || deck2[A - 1][B] == 2 || deck2[A][B] == 2 || deck2[A + 1][B] == 2 || deck2[A + 2][B] == 2)
                        still_alive = true;
                if (temp1 == 0)
                {
                    if (deck2[A][B - 2] == 2 || deck2[A][B - 2] == 4)
                        temp1 = 2;
                    if (temp1 == 2)
                        if (deck2[A][B - 3] == 2 || deck2[A][B - 2] == 2 || deck2[A][B - 1] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                    if (temp1 == 0)
                        if (deck2[A][B - 1] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                }
                if (temp3 == 0)
                {
                    if (deck2[A][B + 2] == 2 || deck2[A][B + 2] == 4)
                        temp3 = 2;
                    if (temp3 == 2)
                        if (deck2[A][B + 3] == 2 || deck2[A][B + 2] == 2 || deck2[A][B + 1] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                    if (temp3 == 0)
                        if (deck2[A][B] == 2 || deck2[A][B + 1] == 2)
                            still_alive = true;
                }
                if (temp2 == 0)
                {
                    if (deck2[A - 2][B] == 2 || deck2[A - 2][B] == 4)
                        temp2 = 2;
                    if (temp2 == 2)
                        if (deck2[A - 3][B] == 2 || deck2[A - 2][B] == 2 || deck2[A][B] == 2 || deck2[A - 1][B] == 2)
                            still_alive = true;
                    if (temp2 == 0)
                        if (deck2[A - 1][B] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                }
                if (temp4 == 0)
                {
                    if (deck2[A + 2][B] == 2 || deck2[A + 2][B] == 4)
                        temp4 = 2;
                    if (temp4 == 2)
                        if (deck2[A + 3][B] == 2 || deck2[A + 2][B] == 2 || deck2[A][B] == 2 || deck2[A + 1][B] == 2)
                            still_alive = true;
                    if (temp4 == 0)
                        if (deck2[A + 1][B] == 2 || deck2[A][B] == 2)
                            still_alive = true;
                }

                if (still_alive)
                {
                    clear();
                    print2decks();
                    cout << endl << "\nПопал!";
                }
                else
                {
                    if (deck2[A + 1][B] == 4)
                        temp4 = 1;
                    if (deck2[A - 1][B] == 4)
                        temp2 = 1;
                    if (deck2[A][B - 1] == 4)
                        temp1 = 1;
                    if (deck2[A][B + 1] == 4)
                        temp3 = 1;
                    if (temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1)
                    {
                        deck2[A - 1][B] = 5; deck2[A + 1][B] = 5; deck2[A][B + 1] = 5; deck2[A][B - 1] = 5; deck2[A - 1][B - 1] = 5; deck2[A + 1][B - 1] = 5; deck2[A - 1][B + 1] = 5; deck2[A + 1][B + 1] = 5;
                        kill();
                    }
                    if (temp1 == 1 && temp3 == 1)
                    {
                        if (deck2[A][B - 2] == 4)
                        {
                            deck2[A][B - 3] = 5; deck2[A][B + 2] = 5;
                            for (int i = B - 3; i < B + 3; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else if (deck2[A][B + 2] == 4)
                        {
                            deck2[A][B + 3] = 5; deck2[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 4; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else
                        {
                            deck2[A][B + 2] = 5; deck2[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                    }
                    if (temp2 == 1 && temp4 == 1)
                    {
                        if (deck2[A - 2][B] == 4)
                        {
                            deck2[A - 3][B] = 5; deck2[A + 2][B] = 5;
                            for (int i = A - 3; i < A + 3; i++)
                            {
                                deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else if (deck2[A + 2][B] == 4)
                        {
                            deck2[A + 3][B] = 5; deck2[A - 2][B] = 5;
                            for (int i = A - 2; i < A + 4; i++)
                            {
                                deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else
                        {
                            deck2[A + 2][B] = 5; deck2[A - 2][B] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                    }
                    if (temp1 == 1)
                    {
                        if (deck2[A][B - 2] == 4)
                        {
                            if (deck2[A][B - 3] == 4)
                            {
                                deck2[A][B + 1] = 5; deck2[A][B - 4] = 5;
                                for (int i = B - 4; i < B + 2; i++)
                                {
                                    deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck2[A][B + 1] = 5; deck2[A][B - 3] = 5;
                            for (int i = B - 3; i < B + 2; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck2[A][B + 1] = 5; deck2[A][B - 2] = 5;
                        for (int i = B - 2; i < B + 2; i++)
                        {
                            deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp3 == 1)
                    {
                        if (deck2[A][B + 2] == 4)
                        {
                            if (deck2[A][B + 3] == 4)
                            {
                                deck2[A][B - 1] = 5; deck2[A][B + 4] = 5;
                                for (int i = B - 1; i < B + 5; i++)
                                {
                                    deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck2[A][B + 1] = 5; deck2[A][B - 3] = 5;
                            for (int i = B - 1; i < B + 4; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck2[A][B + 1] = 5; deck2[A][B - 2] = 5;
                        for (int i = B - 1; i < B + 3; i++)
                        {
                            deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck2[A - 2][B] == 4)
                        {
                            if (deck2[A - 3][B] == 4)
                            {
                                deck2[A + 1][B] = 5; deck2[A - 4][B] = 5;
                                for (int i = A - 4; i < A + 2; i++)
                                {
                                    deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck2[A + 1][B] = 5; deck2[A - 3][B] = 5;
                            for (int i = A - 3; i < A + 2; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck2[A + 1][B] = 5; deck2[A - 2][B] = 5;
                        for (int i = A - 2; i < A + 2; i++)
                        {
                            deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp4 == 1)
                    {
                        if (deck2[A + 2][B] == 4)
                        {
                            if (deck2[A + 3][B] == 4)
                            {
                                deck2[A - 1][B] = 5; deck2[A + 4][B] = 5;
                                for (int i = A - 1; i < A + 5; i++)
                                {
                                    deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck2[A - 1][B] = 5; deck2[A + 3][B] = 5;
                            for (int i = A - 1; i < A + 4; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck2[A + 2][B] = 5; deck2[A - 1][B] = 5;
                        for (int i = A - 1; i < A + 3; i++)
                        {
                            deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                        }
                        kill();
                        return 0;
                    }
                }
            }
            return 0;
        }
        else if (status2 == 1 || status2 == 2 || status1 == 0)
        {
            if (!(A >= 1 && A <= 10 && B >= 1 && B <= 10))
            {
                cout << "\nНеверные координаты для удара\n";
                return 0;
            }
            else if (deck1[A][B] == 3 || deck1[A][B] == 4 || deck1[A][B] == 5)
            {
                cout << "\nВ эту позицию нельзя ударить!\n";
                return 0;
            }
            else if (deck1[A][B] == 0 || deck1[A][B] == 1)
            {
                deck1[A][B] = 3;
                clear();
                print2decks();
                cout << endl << "\nПромах!";
                status2 = 0;
                status1 = 1;
                return 0;
            }
            else if (deck1[A][B] == 2)
            {
                deck1[A][B] = 4;
                status2 = 2;
                status1 = 0;
                botcordx = B;
                botcordy = A;

                bool still_alive = false;

                if (deck1[A + 1][B] == 4 || deck1[A + 1][B] == 2)
                    temp4 = 0;
                if (deck1[A - 1][B] == 4 || deck1[A - 1][B] == 2)
                    temp2 = 0;
                if (deck1[A][B - 1] == 4 || deck1[A][B - 1] == 2)
                    temp1 = 0;
                if (deck1[A][B + 1] == 4 || deck1[A][B + 1] == 2)
                    temp3 = 0;
                if (temp1 == 0 && temp3 == 0)
                    if (deck1[A][B - 2] == 2 || deck1[A][B - 1] == 2 || deck1[A][B] == 2 || deck1[A][B + 1] == 2 || deck1[A][B + 2] == 2)
                        still_alive = true;
                if (temp2 == 0 && temp4 == 0)
                    if (deck1[A - 2][B] == 2 || deck1[A - 1][B] == 2 || deck1[A][B] == 2 || deck1[A + 1][B] == 2 || deck1[A + 2][B] == 2)
                        still_alive = true;
                if (temp1 == 0)
                {
                    if (deck1[A][B - 2] == 2 || deck1[A][B - 2] == 4)
                        temp2 = 2;
                    if (temp2 == 2)
                        if (deck1[A][B - 3] == 2 || deck1[A][B - 2] == 2 || deck1[A][B - 1] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                    if (temp2 == 0)
                        if (deck1[A][B - 1] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                }
                if (temp3 == 0)
                {
                    if (deck1[A][B + 2] == 2 || deck1[A][B + 2] == 4)
                        temp4 = 2;
                    if (temp4 == 2)
                        if (deck1[A][B + 3] == 2 || deck1[A][B + 2] == 2 || deck1[A][B + 1] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                    if (temp4 == 0)
                        if (deck1[A][B] == 2 || deck1[A][B + 1] == 2)
                            still_alive = true;
                }
                if (temp2 == 0)
                {
                    if (deck1[A - 2][B] == 2 || deck1[A - 2][B] == 4)
                        temp1 = 2;
                    if (temp1 == 2)
                        if (deck1[A - 3][B] == 2 || deck1[A - 2][B] == 2 || deck1[A][B] == 2 || deck1[A - 1][B] == 2)
                            still_alive = true;
                    if (temp1 == 0)
                        if (deck1[A - 1][B] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                }
                if (temp4 == 0)
                {
                    if (deck1[A + 2][B] == 2 || deck1[A + 2][B] == 4)
                        temp3 = 2;
                    if (temp3 == 2)
                        if (deck1[A + 3][B] == 2 || deck1[A + 2][B] == 2 || deck1[A][B] == 2 || deck1[A + 1][B] == 2)
                            still_alive = true;
                    if (temp3 == 0)
                        if (deck1[A + 1][B] == 2 || deck1[A][B] == 2)
                            still_alive = true;
                }

                if (still_alive)
                {
                    clear();
                    print2decks();
                    cout << endl << "\nПопал!";
                }
                else
                {
                    botcordx = 0;
                    botcordy = 0;
                    if (deck1[A + 1][B] == 4)
                        temp4 = 1;
                    if (deck1[A - 1][B] == 4)
                        temp2 = 1;
                    if (deck1[A][B - 1] == 4)
                        temp1 = 1;
                    if (deck1[A][B + 1] == 4)
                        temp3 = 1;
                    if (temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1)
                    {
                        deck1[A - 1][B] = 5; deck1[A + 1][B] = 5; deck1[A][B + 1] = 5; deck1[A][B - 1] = 5; deck1[A - 1][B - 1] = 5; deck1[A + 1][B - 1] = 5; deck1[A - 1][B + 1] = 5; deck1[A + 1][B + 1] = 5;
                        kill();
                        return 0;
                    }
                    if (temp1 == 1 && temp3 == 1)
                    {
                        if (deck1[A][B - 2] == 4)
                        {
                            deck1[A][B - 3] = 5; deck1[A][B + 2] = 5;
                            for (int i = B - 3; i < B + 3; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else if (deck1[A][B + 2] == 4)
                        {
                            deck1[A][B + 3] = 5; deck1[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 4; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else
                        {
                            deck1[A][B + 2] = 5; deck1[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                    }
                    if (temp2 == 1 && temp4 == 1)
                    {
                        if (deck1[A - 2][B] == 4)
                        {
                            deck1[A - 3][B] = 5; deck1[A + 2][B] = 5;
                            for (int i = A - 3; i < A + 3; i++)
                            {
                                deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else if (deck1[A + 2][B] == 4)
                        {
                            deck1[A + 3][B] = 5; deck1[A - 2][B] = 5;
                            for (int i = A - 2; i < A + 4; i++)
                            {
                                deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        else
                        {
                            deck1[A + 2][B] = 5; deck1[A - 2][B] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                    }
                    if (temp1 == 1)
                    {
                        if (deck1[A][B - 2] == 4)
                        {
                            if (deck1[A][B - 3] == 4)
                            {
                                deck1[A][B + 1] = 5; deck1[A][B - 4] = 5;
                                for (int i = B - 4; i < B + 2; i++)
                                {
                                    deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck1[A][B + 1] = 5; deck1[A][B - 3] = 5;
                            for (int i = B - 3; i < B + 2; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck1[A][B + 1] = 5; deck1[A][B - 2] = 5;
                        for (int i = B - 2; i < B + 2; i++)
                        {
                            deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp3 == 1)
                    {
                        if (deck1[A][B + 2] == 4)
                        {
                            if (deck1[A][B + 3] == 4)
                            {
                                deck1[A][B - 1] = 5; deck1[A][B + 4] = 5;
                                for (int i = B - 1; i < B + 5; i++)
                                {
                                    deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck1[A][B + 1] = 5; deck1[A][B - 3] = 5;
                            for (int i = B - 1; i < B + 4; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck1[A][B + 1] = 5; deck1[A][B - 2] = 5;
                        for (int i = B - 1; i < B + 3; i++)
                        {
                            deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck1[A - 2][B] == 4)
                        {
                            if (deck1[A - 3][B] == 4)
                            {
                                deck1[A + 1][B] = 5; deck1[A - 4][B] = 5;
                                for (int i = A - 4; i < A + 2; i++)
                                {
                                    deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck1[A + 1][B] = 5; deck1[A - 3][B] = 5;
                            for (int i = A - 3; i < A + 2; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck1[A + 1][B] = 5; deck1[A - 2][B] = 5;
                        for (int i = A - 2; i < A + 2; i++)
                        {
                            deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                        }
                        kill();
                        return 0;
                    }
                    if (temp4 == 1)
                    {
                        if (deck1[A + 2][B] == 4)
                        {
                            if (deck1[A + 3][B] == 4)
                            {
                                deck1[A - 1][B] = 5; deck1[A + 4][B] = 5;
                                for (int i = A - 1; i < A + 5; i++)
                                {
                                    deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                                }
                                kill();
                                return 0;
                            }
                            deck1[A - 1][B] = 5; deck1[A + 3][B] = 5;
                            for (int i = A - 1; i < A + 4; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            kill();
                            return 0;
                        }
                        deck1[A + 1][B] = 5; deck1[A - 2][B] = 5;
                        for (int i = A - 1; i < A + 3; i++)
                        {
                            deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                        }
                        kill();
                        return 0;
                    }
                }
            }
            return 0;
        }
        else
        {
            cout << "Ошибка";
            return 0;
        }
        return 0;
    }
    void step()
    {
        bool temp3 = 0; int temp1 = 0; char temp2 = 0; int A = 0; int B = 0;
        if (status1 == 1 || status1 == 2 || status2 == 0)
        {
            cout << "\n\nХод 1 игрока" << endl << endl;
            temp3 = false;
            while (!temp3)
            {
                cout << "Выберите позицию для удара (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " (A1, B2)(0 - показать свою доску)): ";
                cin >> temp1; 
                if (temp1 == 0) { printdeck1public(); continue; }
                cin >> temp2;
                A = temp1;
                B = int(temp2) - symbolssum;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && deck2[A][B] != 3 && deck2[A][B] != 4 && deck2[A][B] != 5)
                    temp3 = true;
                else
                    cout << endl << "Программа не смогла определить позицию удара или в эту позицию нельзя ударить! Попробуйте еще раз" << endl;
            }
            check(A, B);
        }
        else if (status2 == 1 || status2 == 2 || status1 == 0)
        {
        status2 = 1;
        status1 = 0;
            cout << "\n\nХод робота" << endl << endl;
            temp3 = false;
            while (status2 != 0)
            {
                A = 0; B = 0;
                if (botcordx > 0 && botcordy > 0)
                {
                    int temp = rand() % 4;
                    switch (temp)
                    {
                    case 0:
                        if (botcordx - 1 > 0)
                        {
                            A = botcordy;
                            B = botcordx - 1;
                        }
                        break;
                    case 1:
                        if (botcordx + 1 <= 10)
                        {
                            A = botcordy;
                            B = botcordx + 1;
                        }
                        break;
                    case 2:
                        if (botcordy - 1 > 0)
                        {
                            A = botcordy - 1;
                            B = botcordx;
                        }
                        break;
                    case 3:
                        if (botcordy + 1 <= 10)
                        {
                            A = botcordy + 1;
                            B = botcordx;
                        }
                        break;
                    }
                    if ((deck1[botcordy + 1][botcordx] == 3 || deck1[botcordy + 1][botcordx] == 4 || deck1[botcordy + 1][botcordx] == 5))
                    {
                        if ((deck1[botcordy][botcordx - 1] == 3 || deck1[botcordy][botcordx - 1] == 4 || deck1[botcordy][botcordx - 1] == 5))
                        {
                            if ((deck1[botcordy][botcordx + 1] == 3 || deck1[botcordy][botcordx + 1] == 4 || deck1[botcordy][botcordx + 1] == 5))
                            {
                                if (botcordy - 1 > 0 && (deck1[botcordy - 1][botcordx] == 3 || deck1[botcordy - 1][botcordx] == 4 || deck1[botcordy - 1][botcordx] == 5))
                                {
                                    int temp = 0;
                                    if (deck1[botcordy][botcordx - 1] == 4 && deck1[botcordy][botcordx + 1] == 4)
                                    {
                                        temp = rand() % 2;
                                        switch (temp)
                                        {
                                        case 0: A = botcordy; if (botcordx - 2 > 0) { B = botcordx - 2; break; }
                                              else { temp = 1; continue; }
                                        case 1: A = botcordy; if (botcordx + 2 <= 10) { B = botcordx + 2; break; }
                                              else { temp = 0; continue; }
                                        }
                                    }
                                    else if (deck1[botcordy - 1][botcordx] == 4 && deck1[botcordy + 1][botcordx] == 4)
                                    {
                                        temp = rand() % 2;
                                        switch (temp)
                                        {
                                        case 0: B = botcordx; if (botcordy - 2 > 0) { A = botcordy - 2; break; }
                                              else { temp = 1; continue; }
                                        case 1: B = botcordx; if (botcordy + 2 <= 10) { A = botcordy + 2; break; }
                                              else { temp = 0; continue; }
                                        }
                                    }
                                    else if (deck1[botcordy][botcordx - 1] == 4)
                                    {
                                        if (botcordx - 3 > 0)
                                        {
                                            A = botcordy;
                                            temp = rand() % 2;
                                            switch (temp)
                                            {
                                            case 0: if (botcordx - 2 > 0) { B = botcordx - 2; break; }
                                                  else { temp = 1; continue; }
                                            case 1: if (botcordx - 3 > 0) { B = botcordx - 3; break; }
                                                  else { temp = 0; continue; }
                                            }
                                        }
                                        else
                                            B = botcordy - 2;
                                    }
                                    else if (deck1[botcordy][botcordx + 1] == 4)
                                    {
                                        A = botcordy;
                                        if (botcordx + 3 <= 10)
                                        {
                                            temp = rand() % 2;
                                            switch (temp)
                                            {
                                            case 0: if (botcordx + 2 <= 10) { B = botcordx + 2; break; }
                                                  else { temp = 1; continue; }
                                            case 1: if (botcordx + 3 <= 10) { B = botcordx + 3; break; }
                                                  else { temp = 0; continue; }
                                            }
                                        }
                                        else
                                            B = botcordx + 2;
                                    }
                                    else if (deck1[botcordy - 1][botcordx] == 4)
                                    {
                                        B = botcordx;
                                        if (botcordy - 3 > 0)
                                        {
                                            temp = rand() % 2;
                                            switch (temp)
                                            {
                                            case 0: if (botcordy - 2 > 0) { A = botcordy - 2; break; }
                                                  else { temp = 1; continue; }
                                            case 1: if (botcordy - 3 > 0) { A = botcordy - 3; break; }
                                                  else { temp = 0; continue; }
                                            }
                                        }
                                        else
                                            A = botcordy - 2;
                                    }
                                    else if (deck1[botcordy + 1][botcordx] == 4)
                                    {
                                        B = botcordx;
                                        if (botcordy + 3 <= 10)
                                        {
                                            temp = rand() % 2;
                                            switch (temp)
                                            {
                                            case 0: if (botcordy + 2 <= 10) { A = botcordy + 2; break; }
                                                  else { temp = 1; continue; }
                                            case 1: if (botcordy + 3 <= 10) { A = botcordy + 3; break; }
                                                  else { temp = 0; continue; }
                                            }
                                        }
                                        else
                                            A = botcordy + 2;
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    A = rand() % 10+1;
                    B = rand() % 10+1;
                }
                check(A, B);
            }
        }
        else
        {
            cout << "Ошибка, ход игрока.";
            status1 = 1;
            status2 = 0;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int choice = 0; char choicechar = '+';
    botgame botplay;
    game play;
    cout << "Добро пожаловать в морской бой!\n";
    while (choice != 3)
    {
        cout << "\nВыбери режим игры:";
        cout << "\n1 - С другом";
        cout << "\n2 - С роботом";
        cout << "\n3 - Выход";
        cout << "\nВыбор: ";
        cin >> choice;
        while (choice < 1 || choice > 3)
            cin >> choice;
        cin.clear();
        switch (choice)
        {
        case 1:
            clear();
            cout << "Режим игры с другом. Приятной игры!\n";
            play.cleardecks();
            cout << "\nИгрок 1: Желаете сделать автоматическую расстановку кораблей? (\'+\'):";
            cin >> choicechar;
            if (choicechar == '+')
                    play.setdeck1auto();
            else
                play.setdeck1();
            cout << "\nИгрок 2: Желаете сделать автоматическую расстановку кораблей? (\'+\'):";
            cin >> choicechar;
            if (choicechar == '+')
                    play.setdeck2auto();
            else
                play.setdeck2();
            play.print2decks();
            while (play.checkwin() == 0)
            {
                cin.clear();
                cin.ignore();
                play.step();
            }
            cout << "\n\nИгра окончена! \nПо итогам игры победу одержал игрок " << play.checkwin() << endl << "Желаете сыграть еще раз?";
            break;
        case 2:
            clear();
            cout << "Режим игры с роботом. Приятной игры!\n";
            botplay.cleardecks();
            cout << "\nЖелаете сделать автоматическую расстановку кораблей? (\'+\'):";
            cin >> choicechar;
            if (choicechar == '+')
                    botplay.setdeck1auto();
            else
                botplay.setdeck1();
            botplay.setdeck2();
            botplay.print2decks();
            while (botplay.checkwin() == 0)
            {
                cin.clear();
                cin.ignore();
                botplay.step();
            }
            cout << "\n\nИгра окончена! \nПо итогам игры победу одержал игрок " << botplay.checkwin() << endl << "Желаете сыграть еще раз?";
            break;
        case 3:
            return 0;
        default:
            break;
        }
    }
    return 0;
}