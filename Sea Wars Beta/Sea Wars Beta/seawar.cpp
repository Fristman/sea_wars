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
    virtual void cleardecks()
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
    void printdeck1build()
    {
        cout << "_ - Пустое поле\nO - поле вокруг корабля\nX - корабль" << endl << endl;
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
                    cout << "O ";
                else if (deck1[i][j] == 2)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    void printdeck2build()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - корабль\nx - попадание по кораблю" << endl << endl;
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
                    cout << "O ";
                else if (deck2[i][j] == 2)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    void printdeck1public()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - корабль\nx - попадание по кораблю" << endl << endl;
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
                    cout << "X ";
                else if (deck1[i][j] == 4)
                    cout << "x ";
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
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - корабль\nx - попадание по кораблю" << endl << endl;
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
                    cout << "X ";
                else if (deck2[i][j] == 4)
                    cout << "x ";
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
            bool temp = false;
            printdeck1build();
            cout << endl << "Постановка " << lenght << "-палубного корабля на доску 1" <<endl << endl;
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
                        cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum + 1 - lenght + 1) << " - " << A << char(B + symbolssum + 1) << endl << "Выполняется постановка...";
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
                        cout << endl << "Начальная и конечная позиция корабля " << A - lenght + 1 << char(B + symbolssum + 1) << " - " << A << char(B + symbolssum + 1) << endl << "Выполняется постановка...";
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
                        cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum + 1) << " - " << A << char(B + symbolssum + 1 + lenght - 1) << endl << "Выполняется постановка...";
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
                        cout << endl << "Начальная и конечная позиция корабля" << A << char(B + symbolssum + 1) << " - " << A + lenght - 1 << char(B + symbolssum + 1) << endl << "Выполняется постановка...";
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
        cout << "Итоговая доска 1:" << endl;
        printdeck1build();
        cout << "\n\nНапишите \"+\" чтобы очистить консоль: ";
        cin >> temp;
        while (temp != '+')
            cin >> temp;
        clear();
        return 0;
    }
    virtual void setshipdeck2(int lenght)
    {
        bool temp = false;
        printdeck2build();
        cout << endl << "Постановка " << lenght << "-палубного корабля на доску 2" << endl << endl;
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
                    cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum + 1 - lenght + 1) << " - " << A << char(B + symbolssum + 1) << endl << "Выполняется постановка...";
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
                    cout << endl << "Начальная и конечная позиция корабля " << A - lenght + 1 << char(B + symbolssum + 1) << " - " << A << char(B + symbolssum + 1) << endl << "Выполняется постановка...";
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
                    cout << endl << "Начальная и конечная позиция корабля " << A << char(B + symbolssum + 1) << " - " << A << char(B + symbolssum + 1 + lenght - 1) << endl << "Выполняется постановка...";
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
                    cout << endl << "Начальная и конечная позиция корабля" << A << char(B + symbolssum + 1) << " - " << A + lenght - 1 << char(B + symbolssum + 1) << endl << "Выполняется постановка...";
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
    }
    virtual int setdeck2()
    {
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
        cout << "Итоговая доска 2:" << endl;
        printdeck2build();
        cout << "\n\nНапишите \"+\" чтобы очистить консоль: ";
        cin >> temp;
        while (temp != '+')
            cin >> temp;
        clear();
        return 0;
    }
    virtual int check(int A, int B)
    {
        cout << endl << "Выбранная позиция для удара " << A << char(B + symbolssum + 1) << endl;
        int temp1 = 2; int temp2 = 2; int temp3 = 2; int temp4 = 2; int tempA = A; int tempB = B;
        if (status1 == 1 || status1 == 2 || status2 == 0)
        {
            if (!(A >= 1 && A <= 10 && B >= 1 && B <= 10))
            {
                cout << "Неверные координаты для удара";
                return 0;
            }
            if (deck2[A][B] == 3 || deck2[A][B] == 4 || deck2[A][B] == 5)
            {
                cout << "В эту позицию нельзя ударить!";
                return 0;
            }
            if (deck2[A][B] == 0 || deck2[A][B] == 1)
            {
                deck2[A][B] = 3;
                cout << endl << "Промах!";
                status1 = 0;
                status2 = 1;
                return 0;
            }
            if (deck2[A][B] == 2)
            {
                deck2[A][B] = 4;
                status1 = 2;
                status2 = 0;

                bool still_alive = false;

                int dr[] = { -1, 1, 0, 0 };
                int dc[] = { 0, 0, -1, 1 };

                for (int i = 0; i < 4; i++) 
                {
                    int nr = A + dr[i];
                    int nc = B + dc[i];

                    while (nr >= 1 && nr < 11 && nc >= 1 && nc < 11 && (deck2[nr][nc] == 2 || deck2[nr][nc] == 4)) {

                        if (deck2[nr][nc] == 2) 
                        {
                            still_alive = true;
                            break;
                        }
                        nr += dr[i];
                        nc += dc[i];
                    }
                    if (still_alive) 
                        break;
                }

                if (still_alive) 
                {
                    cout << "Попал!" << endl;
                }
                else
                {
                    cout << endl << "Убит!";
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
                        }
                        else if (deck2[A][B + 2] == 4)
                        {
                            deck2[A][B + 3] = 5; deck2[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 4; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                        }
                        else
                        {
                            deck2[A][B + 2] = 5; deck2[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                        }
                        return 0;
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
                        }
                        else if (deck2[A + 2][B] == 4)
                        {
                            deck2[A + 3][B] = 5; deck2[A - 2][B] = 5;
                            for (int i = A - 2; i < A + 4; i++)
                            {
                                deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                            }
                        }
                        else
                        {
                            deck2[A + 2][B] = 5; deck2[A - 2][B] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                        }
                        return 0;
                    }
                    if (temp1 == 1)
                    {
                        if (deck2[A][B - 2] == 4)
                        {
                            if (deck2[A][B - 3] == 4)
                            {
                                deck2[A][B + 1] = 5; deck2[A][B - 4] = 5;
                                for (int i = B - 4; i < B + 1; i++)
                                {
                                    deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                                }
                                return 0;
                            }
                            deck2[A][B + 1] = 5; deck2[A][B - 3] = 5;
                            for (int i = B - 3; i < B + 1; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            return 0;
                        }
                        deck2[A][B + 1] = 5; deck2[A][B - 2] = 5;
                        for (int i = B - 2; i < B + 1; i++)
                        {
                            deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                        }
                        return 0;
                    }
                    if (temp3 == 1)
                    {
                        if (deck2[A][B + 2] == 4)
                        {
                            if (deck2[A][B + 3] == 4)
                            {
                                deck2[A][B - 1] = 5; deck2[A][B + 4] = 5;
                                for (int i = B - 1; i < B + 4; i++)
                                {
                                    deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                                }
                                return 0;
                            }
                            deck2[A][B + 1] = 5; deck2[A][B - 3] = 5;
                            for (int i = B - 1; i < B + 3; i++)
                            {
                                deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                            }
                            return 0;
                        }
                        deck2[A][B + 1] = 5; deck2[A][B - 2] = 5;
                        for (int i = B - 1; i < B + 2; i++)
                        {
                            deck2[A - 1][i] = 5; deck2[A + 1][i] = 5;
                        }
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck2[A - 2][B] == 4)
                        {
                            if (deck2[A - 3][B] == 4)
                            {
                                deck2[A + 1][B] = 5; deck2[A - 4][B] = 5;
                                for (int i = A - 4; i < A + 1; i++)
                                {
                                    deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                                }
                                return 0;
                            }
                            deck2[A + 1][B] = 5; deck2[A - 3][B] = 5;
                            for (int i = A - 3; i < A + 1; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                            return 0;
                        }
                        deck2[A + 1][B] = 5; deck2[A - 2][B] = 5;
                        for (int i = A - 2; i < A + 1; i++)
                        {
                            deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                        }
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck2[A + 2][B] == 4)
                        {
                            if (deck2[A + 3][B] == 4)
                            {
                                deck2[A - 1][B] = 5; deck2[A + 4][B] = 5;
                                for (int i = A - 1; i < A + 4; i++)
                                {
                                    deck2[i][B - 1] = 5; deck2[i][B + 1] = 5;
                                }
                                return 0;
                            }
                            deck2[A - 1][B] = 5; deck2[A + 3][B] = 5;
                            for (int i = A - 1; i < A + 3; i++)
                            {
                                deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                            }
                            return 0;
                        }
                        deck2[A + 1][B] = 5; deck2[A - 2][B] = 5;
                        for (int i = A - 1; i < A + 2; i++)
                        {
                            deck2[i][B + 1] = 5; deck2[i][B - 1] = 5;
                        }
                        return 0;
                    }
                }
            }
        }
        else if (status2 == 1 || status2 == 2)
        {
            if (!(A >= 1 && A <= 10 && B >= 1 && B <= 10))
            {
                cout << "Неверные координаты для удара";
                return 0;
            }
            if (deck1[A][B] == 3 || deck1[A][B] == 4 || deck1[A][B] == 5)
            {
                cout << "В эту позицию нельзя ударить!";
                return 0;
            }
            if (deck1[A][B] == 0 || deck1[A][B] == 1)
            {
                deck1[A][B] = 3;
                cout << endl << "Промах!";
                status2 = 0;
                status1 = 1;
                return 0;
            }
            if (deck1[A][B] == 2)
            {
                deck1[A][B] = 4;
                status2 = 2;
                status1 = 0;

                bool still_alive = false;

                int dr[] = { -1, 1, 0, 0 };
                int dc[] = { 0, 0, -1, 1 };

                for (int i = 0; i < 4; i++)
                {
                    int nr = A + dr[i];
                    int nc = B + dc[i];

                    while (nr >= 1 && nr < 11 && nc >= 1 && nc < 11 && (deck1[nr][nc] == 2 || deck1[nr][nc] == 4)) {

                        if (deck1[nr][nc] == 2)
                        {
                            still_alive = true;
                            break;
                        }
                        nr += dr[i];
                        nc += dc[i];
                    }
                    if (still_alive)
                        break;
                }

                if (still_alive)
                {
                    cout << "Попал!" << endl;
                }
                else
                {
                    cout << endl << "Убит!";
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
                        }
                        else if (deck1[A][B + 2] == 4)
                        {
                            deck1[A][B + 3] = 5; deck1[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 4; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                        }
                        else
                        {
                            deck1[A][B + 2] = 5; deck1[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                        }
                        return 0;
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
                        }
                        else if (deck1[A + 2][B] == 4)
                        {
                            deck1[A + 3][B] = 5; deck1[A - 2][B] = 5;
                            for (int i = A - 2; i < A + 4; i++)
                            {
                                deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                            }
                        }
                        else
                        {
                            deck1[A + 2][B] = 5; deck1[A - 2][B] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                        }
                        return 0;
                    }
                    if (temp1 == 1)
                    {
                        if (deck1[A][B - 2] == 4)
                        {
                            if (deck1[A][B - 3] == 4)
                            {
                                deck1[A][B + 1] = 5; deck1[A][B - 4] = 5;
                                for (int i = B - 4; i < B + 1; i++)
                                {
                                    deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                                }
                                return 0;
                            }
                            deck1[A][B + 1] = 5; deck1[A][B - 3] = 5;
                            for (int i = B - 3; i < B + 1; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            return 0;
                        }
                        deck1[A][B + 1] = 5; deck1[A][B - 2] = 5;
                        for (int i = B - 2; i < B + 1; i++)
                        {
                            deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                        }
                        return 0;
                    }
                    if (temp3 == 1)
                    {
                        if (deck1[A][B + 2] == 4)
                        {
                            if (deck1[A][B + 3] == 4)
                            {
                                deck1[A][B - 1] = 5; deck1[A][B + 4] = 5;
                                for (int i = B - 1; i < B + 4; i++)
                                {
                                    deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                                }
                                return 0;
                            }
                            deck1[A][B + 1] = 5; deck1[A][B - 3] = 5;
                            for (int i = B - 1; i < B + 3; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            return 0;
                        }
                        deck1[A][B + 1] = 5; deck1[A][B - 2] = 5;
                        for (int i = B - 1; i < B + 2; i++)
                        {
                            deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                        }
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck1[A - 2][B] == 4)
                        {
                            if (deck1[A - 3][B] == 4)
                            {
                                deck1[A + 1][B] = 5; deck1[A - 4][B] = 5;
                                for (int i = A - 4; i < A + 1; i++)
                                {
                                    deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                                }
                                return 0;
                            }
                            deck1[A + 1][B] = 5; deck1[A - 3][B] = 5;
                            for (int i = A - 3; i < A + 1; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            return 0;
                        }
                        deck1[A + 1][B] = 5; deck1[A - 2][B] = 5;
                        for (int i = A - 2; i < A + 1; i++)
                        {
                            deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                        }
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck1[A + 2][B] == 4)
                        {
                            if (deck1[A + 3][B] == 4)
                            {
                                deck1[A - 1][B] = 5; deck1[A + 4][B] = 5;
                                for (int i = A - 1; i < A + 4; i++)
                                {
                                    deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                                }
                                return 0;
                            }
                            deck1[A - 1][B] = 5; deck1[A + 3][B] = 5;
                            for (int i = A - 1; i < A + 3; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            return 0;
                        }
                        deck1[A + 1][B] = 5; deck1[A - 2][B] = 5;
                        for (int i = A - 1; i < A + 2; i++)
                        {
                            deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                        }
                        return 0;
                    }
                }
            }
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
            return 1;
        else if (!temp2)
            return 2;
        else
            return 0;
    }
    virtual void step()
    {
        clear();
        bool temp3 = 0; int temp1 = 0; char temp2 = 0; int A = 0; int B = 0;
        if (status1 == 1 || status1 == 2 || status2 == 0)
        {
            clear();
            print2decks();
            cout << "\n\nХод 1 игрока" << endl << endl;
            temp3 = false;
            while (!temp3)
            {
                cout << "Выберите позицию для удара (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " (A1, B2)): ";
                cin >> temp1>>temp2;
                cin.clear();
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
            clear();
            print2decks();
            cout << "\n\nХод 2 игрока" << endl << endl;
            temp3 = false;
            while (!temp3)
            {
                cout << "Выберите позицию для удара (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " (A1, B2)): ";
                cin >> temp1 >> temp2;
                cin.clear();
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
    int botdeck[15][15];
public:
    botgame()
    {
        password2 = "vanvonadonvsajnalgfnlajn5yg1tg1eg31134foangaojgfagojavnoaovodaijov dadv voiansovnaojnfoajofv ";
        status1 = 0; status2 = 0;
        for (int i = 0; i < 10; i++)
        {
            symbols[i] = char(i + symbolssum);
        }
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                deck1[i][j] = 0;
            }
        }
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                botdeck[i][j] = 0;
            }
        }
        botcordx = 0;
        botcordy = 0;
    }
    void print2decks()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - попадание по кораблю" << endl << endl;
        cout << "\t\t1 Доска\t\t\t\t\tДоска робота" << endl;
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
                if (botdeck[i][j] == 0 || botdeck[i][j] == 1 || botdeck[i][j] == 2)
                    cout << "_ ";
                else if (botdeck[i][j] == 3 || botdeck[i][j] == 5)
                    cout << "O ";
                else if (botdeck[i][j] == 4)
                    cout << "X ";
                else
                    cout << "? ";
            }
        }
    }
    virtual void cleardecks()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                deck1[i][j] = 0;
            }
        }
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                botdeck[i][j] = 0;
            }
        }
    }
    void setshipbotdeck(int lenght)
    {
        bool temp = false;
        int temp1 = 1; char temp2 = 'А'; bool temp3 = false; bool temp4 = false;
        int A = rand() % 10 + 1; int B = rand() % 10 + 1;
        while(botdeck[A][B]!=0)
            A = rand() % 10 + 1; B = rand() % 10 + 1;
        while (!temp)
        {
            temp3 = false;
            if (lenght == 1)
            {
                for (int i = 0; i < lenght; i++)
                {
                    botdeck[A][B - i] = 2;
                    botdeck[A - 1][B - i] = 1;
                    botdeck[A + 1][B - i] = 1;
                }
                botdeck[A][B - 1] = 1; botdeck[A - 1][B - 1] = 1; botdeck[A + 1][B - 1] = 1;
                botdeck[A][B + 1] = 1; botdeck[A + 1][B + 1] = 1; botdeck[A - 1][B + 1] = 1;
                temp = true;
                temp3 = true;
                continue;
            }
            while (!temp3)
            {
                temp1 = rand() % 4;
                switch (temp1)
                {
                case 0:
                    temp4 = false;
                    if ((B - lenght + 1) > 0)
                    {
                        for (int i = B - lenght + 1; i < B; i++)
                        {
                            if (botdeck[A][i] != 0)
                                temp4 = true;
                        }
                    }
                    if ((B - lenght + 1) < 1 || temp4 == true)
                        break;
                    for (int i = 0; i < lenght; i++)
                    {
                        botdeck[A][B - i] = 2;
                        botdeck[A - 1][B - i] = 1;
                        botdeck[A + 1][B - i] = 1;
                    }
                    for (int i = -1; i < 2; i++)
                    {
                        botdeck[A + i][B - lenght] = 1; botdeck[A + i][B + 1] = 1;
                    }
                    temp = true;
                    temp3 = true;
                    break;
                case 1:
                    temp4 = false;
                    if ((A - lenght + 1) > 0)
                    {
                        for (int i = A - lenght + 1; i < A; i++)
                        {
                            if (botdeck[i][B] != 0)
                                temp4 = true;
                        }
                    }
                    if ((A - lenght + 1) < 1 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        botdeck[A - i][B] = 2;
                        botdeck[A - i][B - 1] = 1;
                        botdeck[A - i][B + 1] = 1;
                    }
                    botdeck[A - lenght][B] = 1; botdeck[A - lenght][B - 1] = 1; botdeck[A - lenght + 1][B + 1] = 1;
                    botdeck[A + 1][B] = 1; botdeck[A + 1][B - 1] = 1; botdeck[A + 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 2:
                    temp4 = false;
                    if (B + lenght - 1 < 11)
                    {
                        for (int i = B; i < B + lenght - 1; i++)
                        {
                            if (botdeck[A][i] != 0)
                                temp4 = true;
                        }
                    }
                    if ((B + lenght - 1) > 10 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        botdeck[A][B + i] = 2;
                        botdeck[A - 1][B + i] = 1;
                        botdeck[A + 1][B + i] = 1;
                    }
                    botdeck[A][B + lenght] = 1; botdeck[A - 1][B + lenght] = 1; botdeck[A + 1][B + lenght] = 1;
                    botdeck[A][B - 1] = 1; botdeck[A + 1][B - 1] = 1; botdeck[A - 1][B - 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                case 3:
                    temp4 = false;
                    if (A + lenght - 1 < 11)
                    {
                        for (int i = A; i < A + lenght - 1; i++)
                        {
                            if (botdeck[i][B] != 0)
                                temp4 = true;
                        }
                    }
                    if ((A + lenght - 1) > 10 || temp4 == true)
                    {
                        break;
                    }
                    for (int i = 0; i < lenght; i++)
                    {
                        botdeck[A + i][B] = 2;
                        botdeck[A + i][B - 1] = 1;
                        botdeck[A + i][B + 1] = 1;
                    }
                    botdeck[A + lenght][B] = 1; botdeck[A + lenght][B - 1] = 1; botdeck[A + lenght][B + 1] = 1;
                    botdeck[A - 1][B] = 1; botdeck[A - 1][B - 1] = 1; botdeck[A - 1][B + 1] = 1;
                    temp = true;
                    temp3 = true;
                    break;
                default:
                    break;
                }
            }
        }
    }
    void setbotdeck()
    {
        int ship1 = 4; int ship2 = 3; int ship3 = 2; int ship4 = 1;
        int temp1;
        while (ship1 != 0 || ship2 != 0 || ship3 != 0 || ship4 != 0)
        {
            temp1 = rand() % 4;
            switch (temp1)
            {
            case 0:
                if (ship1 == 0)
                {
                    break;
                }
                ship1--;
                setshipbotdeck(1);
                break;
            case 1:
                if (ship2 == 0)
                {
                    break;
                }
                ship2--;
                setshipbotdeck(2);
                break;
            case 2:
                if (ship3 == 0)
                {
                    break;
                }
                ship3--;
                setshipbotdeck(3);
                break;
            case 3:
                if (ship4 == 0)
                {
                    break;
                }
                ship4--;
                setshipbotdeck(4);
                break;
            default:
                break;
            }
        }
    }
    int check(int A, int B)
    {
        cout << endl << "Выбранная позиция для удара " << A << char(B + symbolssum + 1) << endl;
        int temp1 = 2; int temp2 = 2; int temp3 = 2; int temp4 = 2; int tempA = A; int tempB = B;
        if (status1 == 1 || status1 == 2 || status2 == 0)
        {
            if (!(A >= 1 && A <= 10 && B >= 1 && B <= 10))
            {
                cout << "Неверные координаты для удара";
                return 0;
            }
            if (botdeck[A][B] == 3 || botdeck[A][B] == 4 || botdeck[A][B] == 5)
            {
                cout << "В эту позицию нельзя ударить!";
                return 0;
            }
            if (botdeck[A][B] == 0 || botdeck[A][B] == 1)
            {
                botdeck[A][B] = 3;
                cout << endl << "Промах!";
                status1 = 0;
                status2 = 1;
                return 0;
            }
            if (botdeck[A][B] == 2)
            {
                botdeck[A][B] = 4;
                status1 = 2;
                status2 = 0;

                bool still_alive = false;

                int dr[] = { -1, 1, 0, 0 };
                int dc[] = { 0, 0, -1, 1 };

                for (int i = 0; i < 4; i++)
                {
                    int nr = A + dr[i];
                    int nc = B + dc[i];

                    while (nr >= 1 && nr < 11 && nc >= 1 && nc < 11 && (botdeck[nr][nc] == 2 || botdeck[nr][nc] == 4)) {

                        if (botdeck[nr][nc] == 2)
                        {
                            still_alive = true;
                            break;
                        }
                        nr += dr[i];
                        nc += dc[i];
                    }
                    if (still_alive)
                        break;
                }

                if (still_alive)
                {
                    cout << "Попал!" << endl;
                }
                else
                {
                    cout << endl << "Убит!";
                    if (botdeck[A + 1][B] == 4)
                        temp4 = 1;
                    if (botdeck[A - 1][B] == 4)
                        temp2 = 1;
                    if (botdeck[A][B - 1] == 4)
                        temp1 = 1;
                    if (botdeck[A][B + 1] == 4)
                        temp3 = 1;
                    if (temp1 != 1 && temp2 != 1 && temp3 != 1 && temp4 != 1)
                    {
                        botdeck[A - 1][B] = 5; botdeck[A + 1][B] = 5; botdeck[A][B + 1] = 5; botdeck[A][B - 1] = 5; botdeck[A - 1][B - 1] = 5; botdeck[A + 1][B - 1] = 5; botdeck[A - 1][B + 1] = 5; botdeck[A + 1][B + 1] = 5;
                    }
                    if (temp1 == 1 && temp3 == 1)
                    {
                        if (botdeck[A][B - 2] == 4)
                        {
                            botdeck[A][B - 3] = 5; botdeck[A][B + 2] = 5;
                            for (int i = B - 3; i < B + 3; i++)
                            {
                                botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                            }
                        }
                        else if (botdeck[A][B + 2] == 4)
                        {
                            botdeck[A][B + 3] = 5; botdeck[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 4; i++)
                            {
                                botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                            }
                        }
                        else
                        {
                            botdeck[A][B + 2] = 5; botdeck[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                            }
                        }
                        return 0;
                    }
                    if (temp2 == 1 && temp4 == 1)
                    {
                        if (botdeck[A - 2][B] == 4)
                        {
                            botdeck[A - 3][B] = 5; botdeck[A + 2][B] = 5;
                            for (int i = A - 3; i < A + 3; i++)
                            {
                                botdeck[i][B - 1] = 5; botdeck[i][B + 1] = 5;
                            }
                        }
                        else if (botdeck[A + 2][B] == 4)
                        {
                            botdeck[A + 3][B] = 5; botdeck[A - 2][B] = 5;
                            for (int i = A - 2; i < A + 4; i++)
                            {
                                botdeck[i][B - 1] = 5; botdeck[i][B + 1] = 5;
                            }
                        }
                        else
                        {
                            botdeck[A + 2][B] = 5; botdeck[A - 2][B] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                botdeck[i][B + 1] = 5; botdeck[i][B - 1] = 5;
                            }
                        }
                        return 0;
                    }
                    if (temp1 == 1)
                    {
                        if (botdeck[A][B - 2] == 4)
                        {
                            if (botdeck[A][B - 3] == 4)
                            {
                                botdeck[A][B + 1] = 5; botdeck[A][B - 4] = 5;
                                for (int i = B - 4; i < B + 1; i++)
                                {
                                    botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                                }
                                return 0;
                            }
                            botdeck[A][B + 1] = 5; botdeck[A][B - 3] = 5;
                            for (int i = B - 3; i < B + 1; i++)
                            {
                                botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                            }
                            return 0;
                        }
                        botdeck[A][B + 1] = 5; botdeck[A][B - 2] = 5;
                        for (int i = B - 2; i < B + 1; i++)
                        {
                            botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                        }
                        return 0;
                    }
                    if (temp3 == 1)
                    {
                        if (botdeck[A][B + 2] == 4)
                        {
                            if (botdeck[A][B + 3] == 4)
                            {
                                botdeck[A][B - 1] = 5; botdeck[A][B + 4] = 5;
                                for (int i = B - 1; i < B + 4; i++)
                                {
                                    botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                                }
                                return 0;
                            }
                            botdeck[A][B + 1] = 5; botdeck[A][B - 3] = 5;
                            for (int i = B - 1; i < B + 3; i++)
                            {
                                botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                            }
                            return 0;
                        }
                        botdeck[A][B + 1] = 5; botdeck[A][B - 2] = 5;
                        for (int i = B - 1; i < B + 2; i++)
                        {
                            botdeck[A - 1][i] = 5; botdeck[A + 1][i] = 5;
                        }
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (botdeck[A - 2][B] == 4)
                        {
                            if (botdeck[A - 3][B] == 4)
                            {
                                botdeck[A + 1][B] = 5; botdeck[A - 4][B] = 5;
                                for (int i = A - 4; i < A + 1; i++)
                                {
                                    botdeck[i][B - 1] = 5; botdeck[i][B + 1] = 5;
                                }
                                return 0;
                            }
                            botdeck[A + 1][B] = 5; botdeck[A - 3][B] = 5;
                            for (int i = A - 3; i < A + 1; i++)
                            {
                                botdeck[i][B + 1] = 5; botdeck[i][B - 1] = 5;
                            }
                            return 0;
                        }
                        botdeck[A + 1][B] = 5; botdeck[A - 2][B] = 5;
                        for (int i = A - 2; i < A + 1; i++)
                        {
                            botdeck[i][B + 1] = 5; botdeck[i][B - 1] = 5;
                        }
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (botdeck[A + 2][B] == 4)
                        {
                            if (botdeck[A + 3][B] == 4)
                            {
                                botdeck[A - 1][B] = 5; botdeck[A + 4][B] = 5;
                                for (int i = A - 1; i < A + 4; i++)
                                {
                                    botdeck[i][B - 1] = 5; botdeck[i][B + 1] = 5;
                                }
                                return 0;
                            }
                            botdeck[A - 1][B] = 5; botdeck[A + 3][B] = 5;
                            for (int i = A - 1; i < A + 3; i++)
                            {
                                botdeck[i][B + 1] = 5; botdeck[i][B - 1] = 5;
                            }
                            return 0;
                        }
                        botdeck[A + 1][B] = 5; botdeck[A - 2][B] = 5;
                        for (int i = A - 1; i < A + 2; i++)
                        {
                            botdeck[i][B + 1] = 5; botdeck[i][B - 1] = 5;
                        }
                        return 0;
                    }
                }
            }
        }
        else if (status2 == 1 || status2 == 2)
        {
            if (!(A >= 1 && A <= 10 && B >= 1 && B <= 10))
            {
                return 0;
            }
            if (deck1[A][B] == 3 || deck1[A][B] == 4 || deck1[A][B] == 5)
            {
                return 0;
            }
            if (deck1[A][B] == 0 || deck1[A][B] == 1)
            {
                deck1[A][B] = 3;
                cout << endl << "Промах!";
                status2 = 0;
                status1 = 1;
                return 0;
            }
            if (deck1[A][B] == 2)
            {
                deck1[A][B] = 4;
                status2 = 2;
                status1 = 0;
                botcordx = 0;
                botcordy = 0;

                bool still_alive = false;

                int dr[] = { -1, 1, 0, 0 };
                int dc[] = { 0, 0, -1, 1 };

                for (int i = 0; i < 4; i++)
                {
                    int nr = A + dr[i];
                    int nc = B + dc[i];

                    while (nr >= 1 && nr < 11 && nc >= 1 && nc < 11 && (deck1[nr][nc] == 2 || deck1[nr][nc] == 4)) {

                        if (deck1[nr][nc] == 2)
                        {
                            still_alive = true;
                            break;
                        }
                        nr += dr[i];
                        nc += dc[i];
                    }
                    if (still_alive)
                        break;
                }

                if (still_alive)
                {
                    cout << "Попал!" << endl;
                    botcordx = A;
                    botcordy = B;
                    return 0;
                }
                else
                {
                    cout << endl << "Убит!";
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
                        }
                        else if (deck1[A][B + 2] == 4)
                        {
                            deck1[A][B + 3] = 5; deck1[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 4; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                        }
                        else
                        {
                            deck1[A][B + 2] = 5; deck1[A][B - 2] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                        }
                        return 0;
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
                        }
                        else if (deck1[A + 2][B] == 4)
                        {
                            deck1[A + 3][B] = 5; deck1[A - 2][B] = 5;
                            for (int i = A - 2; i < A + 4; i++)
                            {
                                deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                            }
                        }
                        else
                        {
                            deck1[A + 2][B] = 5; deck1[A - 2][B] = 5;
                            for (int i = B - 2; i < B + 3; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                        }
                        return 0;
                    }
                    if (temp1 == 1)
                    {
                        if (deck1[A][B - 2] == 4)
                        {
                            if (deck1[A][B - 3] == 4)
                            {
                                deck1[A][B + 1] = 5; deck1[A][B - 4] = 5;
                                for (int i = B - 4; i < B + 1; i++)
                                {
                                    deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                                }
                                return 0;
                            }
                            deck1[A][B + 1] = 5; deck1[A][B - 3] = 5;
                            for (int i = B - 3; i < B + 1; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            return 0;
                        }
                        deck1[A][B + 1] = 5; deck1[A][B - 2] = 5;
                        for (int i = B - 2; i < B + 1; i++)
                        {
                            deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                        }
                        return 0;
                    }
                    if (temp3 == 1)
                    {
                        if (deck1[A][B + 2] == 4)
                        {
                            if (deck1[A][B + 3] == 4)
                            {
                                deck1[A][B - 1] = 5; deck1[A][B + 4] = 5;
                                for (int i = B - 1; i < B + 4; i++)
                                {
                                    deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                                }
                                return 0;
                            }
                            deck1[A][B + 1] = 5; deck1[A][B - 3] = 5;
                            for (int i = B - 1; i < B + 3; i++)
                            {
                                deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                            }
                            return 0;
                        }
                        deck1[A][B + 1] = 5; deck1[A][B - 2] = 5;
                        for (int i = B - 1; i < B + 2; i++)
                        {
                            deck1[A - 1][i] = 5; deck1[A + 1][i] = 5;
                        }
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck1[A - 2][B] == 4)
                        {
                            if (deck1[A - 3][B] == 4)
                            {
                                deck1[A + 1][B] = 5; deck1[A - 4][B] = 5;
                                for (int i = A - 4; i < A + 1; i++)
                                {
                                    deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                                }
                                return 0;
                            }
                            deck1[A + 1][B] = 5; deck1[A - 3][B] = 5;
                            for (int i = A - 3; i < A + 1; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            return 0;
                        }
                        deck1[A + 1][B] = 5; deck1[A - 2][B] = 5;
                        for (int i = A - 2; i < A + 1; i++)
                        {
                            deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                        }
                        return 0;
                    }
                    if (temp2 == 1)
                    {
                        if (deck1[A + 2][B] == 4)
                        {
                            if (deck1[A + 3][B] == 4)
                            {
                                deck1[A - 1][B] = 5; deck1[A + 4][B] = 5;
                                for (int i = A - 1; i < A + 4; i++)
                                {
                                    deck1[i][B - 1] = 5; deck1[i][B + 1] = 5;
                                }
                                return 0;
                            }
                            deck1[A - 1][B] = 5; deck1[A + 3][B] = 5;
                            for (int i = A - 1; i < A + 3; i++)
                            {
                                deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                            }
                            return 0;
                        }
                        deck1[A + 1][B] = 5; deck1[A - 2][B] = 5;
                        for (int i = A - 1; i < A + 2; i++)
                        {
                            deck1[i][B + 1] = 5; deck1[i][B - 1] = 5;
                        }
                        return 0;
                    }
                }
            }
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
        clear();
        bool temp3 = 0; int temp1 = 0; char temp2 = 0; int A = 0; int B = 0;
        if (status1 == 1 || status1 == 2 || status2 == 0)
        {
            clear();
            print2decks();
            cout << "\n\nХод 1 игрока" << endl << endl;
            temp3 = false;
            while (!temp3)
            {
                cout << "Выберите позицию для удара (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " (A1, B2)): ";
                cin >> temp1 >> temp2;
                cin.clear();
                A = temp1;
                B = int(temp2) - symbolssum;
                if (A >= 1 && A <= 10 && B >= 1 && B <= 10 && botdeck[A][B] != 3 && botdeck[A][B] != 4 && botdeck[A][B] != 5)
                    temp3 = true;
                else
                    cout << endl << "Программа не смогла определить позицию удара или в эту позицию нельзя ударить! Попробуйте еще раз" << endl;
            }
            check(A, B);
        }
        else if (status2 == 1 || status2 == 2 || status1 == 0)
        {
            cout << "\n\nХод робота" << endl << endl;
            temp3 = false;
            while (status2 != 0)
            {
                A = 0; B = 0;
                if (botcordx > 0 || botcordy > 0)
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
                    if (deck1[botcordy + 1][botcordx] == 3 || deck1[botcordy + 1][botcordx] == 4 || deck1[botcordy + 1][botcordx] == 5)
                    {
                        if (deck1[botcordy][botcordx - 1] == 3 || deck1[botcordy][botcordx - 1] == 4 || deck1[botcordy][botcordx - 1] == 5)
                        {
                            if (deck1[botcordy][botcordx + 1] == 3 || deck1[botcordy][botcordx + 1] == 4 || deck1[botcordy][botcordx + 1] == 5)
                            {
                                if (deck1[botcordy - 1][botcordx] == 3 || deck1[botcordy - 1][botcordx] == 4 || deck1[botcordy - 1][botcordx] == 5)
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
            }
            check(A, B);
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
    int choice = 0;
    botgame botplay;
    game play;
    while (choice != 3)
    {
        cout << "Добро пожаловать в морской бой V1.0!\n\n";
        cout << "Выбери режим игры:";
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
            cout << "Режим игры с другом. Приятной игры!";
            clear();
            play.cleardecks();
            play.setdeck1();
                while(play.setdeck1() == 1)
            play.setdeck2();
                while (play.setdeck2() == 1)
            while (play.checkwin() == 0)
            {
                clear();
                cin.clear();
                play.step();
            }
            cout << "Игра окончена! По итогам игры победу одержал игрок " << play.checkwin() << endl << "Желаете сыграть еще раз?";
            break;
        case 2:
            cout << "Режим игры с другом. Приятной игры!";
            clear();
            botplay.cleardecks();
            botplay.setdeck1();
            botplay.setbotdeck();
            while (botplay.checkwin() == 0)
            {
                clear();
                cin.clear();
                botplay.step();
            }
            cout << "Игра окончена! По итогам игры победу одержал игрок " << botplay.checkwin() << endl << "Желаете сыграть еще раз?";
            break;
        case 3:
            return 0;
        default:
            break;
        }
    }
    return 0;
}