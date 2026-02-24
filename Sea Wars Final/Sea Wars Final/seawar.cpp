
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <algorithm> // Для std::random_shuffle
#include <vector>
#include <string>
#include <cctype> // Для toupper
#include <limits> // Для numeric_limits

using namespace std;

void clear()
{
    system("CLS");
}
bool is_valid_coord(int A, int B)
{
    if (A >= 0 && A <= 9 && B >= 0 && B <= 9)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void setshipchecker(int r, int c, int(&board)[15][15]) {
    if (is_valid_coord(r, c) && board[r][c] == 0)
        board[r][c] = 1;
}

class game
{
protected:
    int deck1[15][15];
    int deck2[15][15];
    char symbols[10];
    string password1;
    string password2;
    const int symbolssum = 65;

    /*
    0 - пустое поле (_)
    1 - пустое поле, нельзя ставить корабли (o)
    2 - корабль (X)
    3 - промах (O)
    4 - подбит (x)
    5 - поле вокруг подбитого корабля (O) - это, по сути, такой же ореол как 1, но после уничтожения
    */
    int status1;
    int status2;

    /*
    0 - Игрок не ходит
    1 - Ход игрока
    2 - Попадание, ход игрока (еще один ход)
    */
public:
    game()
    {
        status1 = 1;
        status2 = 0;
        for (int i = 0; i < 10; i++)
        {
            symbols[i] = char(i + symbolssum);
        }
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
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
        for (int i = 0; i < 10; i++)
        {
            cout << endl << i + 1 << "\t";
            for (int j = 0; j < 10; j++)
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
        cout << endl;
    }
    void printdeck2build()
    {
        cout << "_ - Пустое поле\nO - поле вокруг корабля\nX - корабль" << endl << endl;
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
        cout << endl;
    }
    void printdeck1public()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - корабль\nx - попадание по кораблю" << endl << endl;
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
        cout << endl;
    }
    void printdeck1private()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - попадание по кораблю" << endl << endl;
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
        cout << endl;
    }
    void printdeck2public()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - корабль\nx - попадание по кораблю" << endl << endl;
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
        cout << endl;
    }
    void printdeck2private()
    {
        cout << "_ - Пустое поле\nO - Промах или поле вокруг разбитого корабля\nX - попадание по кораблю" << endl << endl;
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
        cout << endl;
    }
    virtual void print2decks()
    {
        cout << "1 ДОСКА (ВАША)\t\t\t2 ДОСКА (ВРАГА)" << endl;
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
        for (int i = 0; i < 10; i++)
        {
            cout << endl << i + 1 << "\t";
            for (int j = 0; j < 10; j++)
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
            cout << "\t\t" << i + 1 << "\t";
            for (int j = 0; j < 10; j++)
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
        cout << endl;
    }
    int checkdeck()
    {
        bool continue_loop = true;
        while (continue_loop)
        {
            cout << endl << endl << "Введите пароль своей доски (0 - выход): ";
            string temp;
            cin >> temp;

            if (temp == password1)
            {
                clear();
                cout << "\n\nВНИМАНИЕ!!! Сейчас будут показаны местоположения кораблей на 1 доске. Если 2 игрок не смотрит, напишите '+' : ";
                char temp1 = '-';
                cin >> temp1;
                while (temp1 != '+')
                    cin >> temp1;
                cout << "\n\n";
                printdeck1public();
                cout << endl << endl << "Напишите '+' для очистки консоли: ";
                temp1 = '-';
                cin >> temp1;
                while (temp1 != '+')
                    cin >> temp1;
                clear();
                continue_loop = false;
            }
            else if (temp == password2)
            {
                clear();
                cout << "\n\nВНИМАНИЕ!!! Сейчас будут показаны местоположения кораблей на 2 доске. Если 1 игрок не смотрит, напишите '+' : ";
                char temp1 = '-';
                cin >> temp1;
                while (temp1 != '+')
                    cin >> temp1;
                cout << "\n\n";
                printdeck2public();
                cout << endl << endl << "Напишите '+' для очистки консоли: ";
                temp1 = '-';
                cin >> temp1;
                while (temp1 != '+')
                    cin >> temp1;
                clear();
                continue_loop = false;
            }
            else if (temp == "0")
            {
                continue_loop = false;
            }
            else
            {
                cout << "Пароль неверный, попробуйте еще раз." << endl;
            }
        }
        return 0;
    }
    void setship(int lenght, int(&deck)[15][15])
    {
        bool placed = false;
        while (!placed)
        {
            int row;
            char col;

            if (&deck == &deck1) printdeck1build();
            else printdeck2build();

            cout << endl << "Постановка " << lenght << "-палубного корабля." << endl;
            cout << "Выберите позицию хвоста корабля (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " слитно(1A, 2B)): ";
            cin >> row >> col;

            int r = row - 1;
            int c = toupper(col) - symbolssum;

            if (!is_valid_coord(r, c) || deck[r][c] != 0)
            {
                cout << endl << "Неверная позиция для хвоста корабля или в этой позиции нельзя установить корабль! Попробуйте еще раз." << endl;
                clear();
                continue;
            }

            int y = 0, x = 0;
            int choice = 0;

            if (lenght == 1)
            {
                deck[r][c] = 2;
                setshipchecker(r - 1, c - 1, deck);
                setshipchecker(r - 1, c, deck);
                setshipchecker(r - 1, c + 1, deck);
                setshipchecker(r, c - 1, deck);
                setshipchecker(r, c + 1, deck);
                setshipchecker(r + 1, c - 1, deck);
                setshipchecker(r + 1, c, deck);
                setshipchecker(r + 1, c + 1, deck);

                placed = true;
            }
            else
            {
                bool collect = false;
                while (!collect)
                {
                    cout << "Позиция хвоста " << r + 1 << char(c + symbolssum) << endl;
                    cout << "Выберите направление корабля" << endl << "1 - влево" << "\n2 - вверх\n3 - вправо\n4 - вниз\nВыбор:";
                    cin >> choice;
                    if (choice < 1 || choice > 4)
                    {
                        cout << "Неккоректный ввод, попробуйте еще раз." << endl;
                        continue;
                    }

                    if (choice == 1) x = -1;
                    else if (choice == 2) y = -1;
                    else if (choice == 3) x = 1;
                    else if (choice == 4) y = 1;

                    vector<pair<int, int>> segments;
                    bool canplace = true;

                    for (int i = 0; i < lenght; ++i)
                    {
                        int nr = r + y * i;
                        int nc = c + x * i;
                        if (!is_valid_coord(nr, nc) || deck[nr][nc] != 0)
                        {
                            canplace = false;
                            break;
                        }
                        segments.push_back({ nr, nc });
                    }

                    if (canplace)
                    {
                        cout << endl << "Выполняется постановка...";

                        for (const auto& scoord : segments)
                        {
                            deck[scoord.first][scoord.second] = 2;
                        }

                        int minr = r, maxr = r;
                        int minc = c, maxc = c;
                        for (const auto& scoord : segments)
                        {
                            minr = min(minr, scoord.first);
                            maxr = max(maxr, scoord.first);
                            minc = min(minc, scoord.second);
                            maxc = max(maxc, scoord.second);
                        }
                        for (int i = max(0, minr - 1); i <= min(9, maxr + 1); i++)
                        {
                            for (int j = max(0, minc - 1); j <= min(9, maxc + 1); ++j)
                            {
                                bool isship = false;
                                for (const auto& scoord : segments) {
                                    if (scoord.first == i && scoord.second == j)
                                    {
                                        isship = true;
                                        break;
                                    }
                                }
                                if (!isship)
                                    setshipchecker(i, j, deck);
                            }
                        }
                        placed = true;
                        collect = true;
                    }
                    else
                    {
                        cout << "Нельзя поставить корабль в выбранном направлении (выходит за границы или пересекается с другим кораблем/ореолом). Попробуйте еще раз." << endl;
                    }
                }
            }
            system("pause");
            clear();
        }
    }
    void setdeck1()
    {
        clear();
        cout << "ВНИМАНИЕ!! Сейчас будет установка первой доски, не допускайте подглядывание 2 игрока." << endl << "Если 2 игрок не наблюдает, напишите \"+\": ";
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
            cout << endl << "Выберите количество палуб корабля (1 - " << ship1 << " шт, 2 - " << ship2 << " шт, 3 - " << ship3 << " шт, 4 - " << ship4 << " шт) для расстановки: ";
            cin >> temp1;
            reboot++;
            if (reboot == 20)
            {
                clear();
                cout << "\n\nПроизошел сбой! Откат изменений...\n\n";
                reboot = 0;
                continue;
            }
            switch (temp1)
            {
            case 1:
                if (ship1 == 0)
                {
                    cout << "Однопалубные корабли закончились!";
                    break;
                }
                ship1--;
                setship(1, deck1);
                break;
            case 2:
                if (ship2 == 0)
                {
                    cout << "Двухпалубные корабли закончились!";
                    break;
                }
                ship2--;
                setship(2, deck1);
                break;
            case 3:
                if (ship3 == 0)
                {
                    cout << "Трехпалубные корабли закончились!";
                    break;
                }
                ship3--;
                setship(3, deck1);
                break;
            case 4:
                if (ship4 == 0)
                {
                    cout << "Четырехпалубные корабли закончились!";
                    break;
                }
                ship4--;
                setship(4, deck1);
                break;
            default:
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
    }
    virtual void setdeck2()
    {
        clear();
        cout << "ВНИМАНИЕ!! Сейчас будет установка первой доски, не допускайте подглядывание 2 игрока." << endl << "Если 2 игрок не наблюдает, напишите \"+\": ";
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
            cout << endl << "Выберите количество палуб корабля (1 - " << ship1 << " шт, 2 - " << ship2 << " шт, 3 - " << ship3 << " шт, 4 - " << ship4 << " шт) для расстановки: ";
            cin >> temp1;
            reboot++;
            if (reboot == 20)
            {
                clear();
                cout << "\n\nПроизошел сбой! Откат изменений...\n\n";
                reboot = 0;
                continue;
            }
            switch (temp1)
            {
            case 1:
                if (ship1 == 0)
                {
                    cout << "Однопалубные корабли закончились!";
                    break;
                }
                ship1--;
                setship(1, deck2);
                break;
            case 2:
                if (ship2 == 0)
                {
                    cout << "Двухпалубные корабли закончились!";
                    break;
                }
                ship2--;
                setship(2, deck2);
                break;
            case 3:
                if (ship3 == 0)
                {
                    cout << "Трехпалубные корабли закончились!";
                    break;
                }
                ship3--;
                setship(3, deck2);
                break;
            case 4:
                if (ship4 == 0)
                {
                    cout << "Четырехпалубные корабли закончились!";
                    break;
                }
                ship4--;
                setship(4, deck2);
                break;
            default:
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
    }
    virtual int check(int r, int c)
    {
        cout << endl << "Выбранная позиция для удара " << r + 1 << char(c + symbolssum) << endl;

        if (!is_valid_coord(r, c))
        {
            cout << "Неверные координаты для удара!" << endl;
            return 0;
        }
        /*if (status1 == 1 || status1 == 2 || status2 == 0)
            int(&deck)[15][15] = deck2;
        else
            int(&deck)[15][15] = deck1;*/
        int(&deck)[15][15] = (status1 == 1 || status1 == 2 || status2 == 0) ? deck2 : deck1;

        if (deck[r][c] == 3 || deck[r][c] == 4 || deck[r][c] == 5)
        {
            cout << "В эту позицию нельзя ударить! (Уже было попадание/промах/окружение)" << endl;
            return 0;
        }

        if (deck[r][c] == 0 || deck[r][c] == 1)
        {
            deck[r][c] = 3;
            cout << endl << "Промах!";
            if (status1 == 1 || status1 == 2)
            {
                status1 = 0;
                status2 = 1;
            }
            else
            {
                status2 = 0;
                status1 = 1;
            }
            return 1;
        }
        else if (deck[r][c] == 2)
        {
            deck[r][c] = 4;
            cout << endl << "Попал!";
            if (status1 == 1 || status1 == 2)
            {
                status1 = 2;
                status2 = 0;
            }
            else
            {
                status2 = 2;
                status1 = 0;
            }

            bool destroy = true;
            vector<pair<int, int>> hit_segments;

            for (int y = -1; y <= 1; ++y) {
                for (int x = -1; x <= 1; ++x)
                {
                    int nr = r, nc = c;
                    while (is_valid_coord(nr, nc) && (deck[nr][nc] == 4 || deck[nr][nc] == 2)) {
                        if (deck[nr][nc] == 2)
                        {
                            destroy = false;
                            break;
                        }
                        if (deck[nr][nc] == 4)
                        {
                            bool already_added = false;
                            for (const auto& p : hit_segments) {
                                if (p.first == nr && p.second == nc) {
                                    already_added = true;
                                    break;
                                }
                            }
                            if (!already_added) {
                                hit_segments.push_back({ nr, nc });
                            }
                        }

                        nr += y;
                        nc += x;
                    }
                    if (!destroy)
                        break;
                }
                if (!destroy)
                    break;
            }

            if (destroy)
            {
                cout << " КОРАБЛЬ УНИЧТОЖЕН!";
                for (const auto& scoord : hit_segments) {
                    for (int i = scoord.first - 1; i <= scoord.first + 1; ++i) {
                        for (int j = scoord.second - 1; j <= scoord.second + 1; ++j) {
                            if (is_valid_coord(i, j) && deck[i][j] < 2) {
                                deck[i][j] = 5;
                            }
                        }
                    }
                }
            }
            return 0;
        }
        return 0;
    }
    int checkwin()
    {
        bool temp1 = 0; bool temp2 = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
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
        print2decks();

        int row;
        char col;
        int r, c;

        if (status1 == 1 || status1 == 2)
        {
            cout << "\n\nХод игрока 1" << endl;
            bool isvalid = false;
            while (!isvalid)
            {
                cout << "Выберите позицию для удара (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " слитно): ";
                cin >> row >> col;
                r = row - 1;
                c = toupper(col) - symbolssum;

                if (is_valid_coord(r, c))
                {
                    isvalid = true;
                }
                else
                {
                    cout << "Неверные координаты! Попробуйте снова." << endl;
                }
            }
            check(r, c);
        }
        else if (status2 == 1 || status2 == 2)
        {
            cout << "\n\nХод игрока 2" << endl;
            bool isvalid = false;
            while (!isvalid)
            {
                cout << "Выберите позицию для удара (цифру от 1 до 10 и заглавную английскую букву от " << symbols[0] << " до " << symbols[9] << " слитно): ";
                cin >> row >> col;
                r = row - 1;
                c = toupper(col) - symbolssum;

                if (is_valid_coord(r, c))
                {
                    isvalid = true;
                }
                else
                {
                    cout << "Неверные координаты! Попробуйте снова." << endl;
                }
            }
            check(r, c);
        }
        else
        {
            cout << "Ошибка: неопределенный ход. Ход переходит игроку 1." << endl;
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
            symbols[i] = char(i + symbolssum);
        }
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                deck1[i][j] = 0;
                deck2[i][j] = 0;
            }
        }
        botcordx = -1;
        botcordy = -1;
    }

    void setbotdeck()
    {
        int ships_to_place[5] = { 0, 4, 3, 2, 1 };

        for (int len = 1; len <= 4; ++len)
        {
            for (int count = 0; count < ships_to_place[len]; ++count)
            {
                bool placed = false;
                while (!placed)
                {
                    int r = rand() % 10;
                    int c = rand() % 10;
                    int y = 0, x = 0;
                    int dir = rand() % 4;

                    if (dir == 0) x = -1;
                    else if (dir == 1) y = -1;
                    else if (dir == 2) x = 1;
                    else y = 1;

                    vector<pair<int, int>> segments;
                    bool canplace = true;

                    for (int i = 0; i < len; ++i)
                    {
                        int nr = r + y * i;
                        int nc = c + x * i;
                        if (!is_valid_coord(nr, nc) || deck2[nr][nc] != 0)
                        {
                            canplace = false;
                            break;
                        }
                        segments.push_back({ nr, nc });
                    }

                    if (canplace)
                    {
                        for (const auto& scoord : segments)
                        {
                            deck2[scoord.first][scoord.second] = 2;
                        }
                        int minr = r, maxr = r;
                        int minc = c, maxc = c;
                        for (const auto& scoord : segments)
                        {
                            minr = min(minr, scoord.first);
                            maxr = max(maxr, scoord.first);
                            minc = min(minc, scoord.second);
                            maxc = max(maxc, scoord.second);
                        }
                        for (int i = max(0, minr - 1); i <= min(9, maxr + 1); ++i)
                        {
                            for (int j = max(0, minc - 1); j <= min(9, maxc + 1); ++j)
                            {
                                bool isship = false;
                                for (const auto& scoord : segments) {
                                    if (scoord.first == i && scoord.second == j) {
                                        isship = true;
                                        break;
                                    }
                                }
                                if (!isship) {
                                    setshipchecker(i, j, deck2);
                                }
                            }
                        }
                        placed = true;
                    }
                }
            }
        }
    }

    int check(int r, int c)
    {
        cout << endl << "Выбранная позиция для удара " << r + 1 << char(c + symbolssum) << endl;

        if (!is_valid_coord(r, c))
        {
            cout << "Неверные координаты для удара!" << endl;
            return 0;
        }

        if (status1 == 1 || status1 == 2)
        {
            if (deck2[r][c] == 3 || deck2[r][c] == 4 || deck2[r][c] == 5)
            {
                cout << "В эту позицию нельзя ударить!" << endl;
                return 0;
            }

            if (deck2[r][c] == 0 || deck2[r][c] == 1)
            {
                deck2[r][c] = 3;
                cout << endl << "Промах!";
                status1 = 0;
                status2 = 1;
                return 1;
            }
            else if (deck2[r][c] == 2)
            {
                deck2[r][c] = 4;
                cout << endl << "Попал!";
                status1 = 2;
                status2 = 0;

                bool destroy = true;
                vector<pair<int, int>> hit_segments;
                for (int y = -1; y <= 1; ++y) {
                    for (int x = -1; x <= 1; ++x) {
                        if (y == 0 && x == 0) continue;
                        int nr = r, nc = c;
                        while (is_valid_coord(nr, nc) && (deck2[nr][nc] == 4 || deck2[nr][nc] == 2)) {
                            if (deck2[nr][nc] == 2) {
                                destroy = false;
                                break;
                            }
                            if (deck2[nr][nc] == 4) {
                                bool already_added = false;
                                for (const auto& p : hit_segments) {
                                    if (p.first == nr && p.second == nc) {
                                        already_added = true;
                                        break;
                                    }
                                }
                                if (!already_added) {
                                    hit_segments.push_back({ nr, nc });
                                }
                            }
                            nr += y; nc += x;
                        }
                        if (!destroy) break;
                    }
                    if (!destroy) break;
                }

                if (destroy)
                {
                    cout << "Убит!";
                    for (const auto& scoord : hit_segments) {
                        for (int i = scoord.first - 1; i <= scoord.first + 1; ++i) {
                            for (int j = scoord.second - 1; j <= scoord.second + 1; ++j) {
                                if (is_valid_coord(i, j) && deck2[i][j] < 2) {
                                    deck2[i][j] = 5;
                                }
                            }
                        }
                    }
                }
                return 0;
            }
        }
        else if (status2 == 1 || status2 == 2)
        {
            cout << "Ход робота.";
            if (deck1[r][c] == 3 || deck1[r][c] == 4 || deck1[r][c] == 5)
            {
                cout << "Робот выбрал неверную позицию, переопределение...";
                return 0;
            }

            if (deck1[r][c] == 0 || deck1[r][c] == 1)
            {
                deck1[r][c] = 3;
                cout << endl << "Промах!";
                botcordx = -1;
                botcordy = -1;
                status2 = 0;
                status1 = 1;
                return 1;
            }
            else if (deck1[r][c] == 2)
            {
                deck1[r][c] = 4;
                cout << endl << "Попал!";
                botcordx = c;
                botcordy = r;
                status2 = 2;
                status1 = 0;

                bool destroy = true;
                vector<pair<int, int>> hit_segments;
                for (int y = -1; y <= 1; ++y) {
                    for (int x = -1; x <= 1; ++x) {
                        if (y == 0 && x == 0) continue;
                        int nr = r, nc = c;
                        while (is_valid_coord(nr, nc) && (deck1[nr][nc] == 4 || deck1[nr][nc] == 2)) {
                            if (deck1[nr][nc] == 2) {
                                destroy = false;
                                break;
                            }
                            if (deck1[nr][nc] == 4) {
                                bool already_added = false;
                                for (const auto& p : hit_segments) {
                                    if (p.first == nr && p.second == nc) {
                                        already_added = true;
                                        break;
                                    }
                                }
                                if (!already_added) {
                                    hit_segments.push_back({ nr, nc });
                                }
                            }
                            nr += y; nc += x;
                        }
                        if (!destroy) break;
                    }
                    if (!destroy) break;
                }

                if (destroy)
                {
                    cout << "Убит!";
                    botcordx = -1; botcordy = -1;
                    for (const auto& scoord : hit_segments) {
                        for (int i = scoord.first - 1; i <= scoord.first + 1; ++i) {
                            for (int j = scoord.second - 1; j <= scoord.second + 1; ++j) {
                                if (is_valid_coord(i, j) && deck1[i][j] < 2) {
                                    deck1[i][j] = 5;
                                }
                            }
                        }
                    }
                }
                return 0;
            }
        }
        return 0;
    }
    void step()
    {
        if (status1 == 1 || status1 == 2)
        {
            game::step();
        }
        else if (status2 == 1 || status2 == 2)
        {
            clear();
            print2decks();
            cout << "\n\nХод робота" << endl << endl;

            int r_shot, c_shot;
            bool target_found = false;

            while (!target_found)
            {
                if (botcordx != -1 && botcordy != -1)
                {
                    int y_options[] = { -1, 1, 0, 0 };
                    int x_options[] = { 0, 0, -1, 1 };
                    vector<pair<int, int>> potential_targets;

                    for (int i = 0; i < 4; ++i)
                    {
                        int nr = botcordy + y_options[i];
                        int nc = botcordx + x_options[i];
                        if (is_valid_coord(nr, nc) && deck1[nr][nc] < 3)
                        {
                            potential_targets.push_back({ nr, nc });
                        }
                    }

                    if (!potential_targets.empty())
                    {
                        int idx = rand() % potential_targets.size();
                        r_shot = potential_targets[idx].first;
                        c_shot = potential_targets[idx].second;
                        target_found = true;
                    }
                    else
                    {
                        botcordx = -1;
                        botcordy = -1;
                    }
                }

                if (!target_found)
                {
                    r_shot = rand() % 10;
                    c_shot = rand() % 10;
                    if (deck1[r_shot][c_shot] < 3)
                    {
                        target_found = true;
                    }
                }
            }

            cout << "Робот стреляет в: " << r_shot + 1 << " " << char(c_shot + symbolssum) << endl;
            check(r_shot, c_shot);
        }
        else
        {
            cout << "Ошибка: неопределенный ход. Ход переходит игроку 1." << endl;
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

    while (choice != 3)
    {
        clear();
        cout << "Добро пожаловать в Морской Бой!\n\n";
        cout << "1. Игра с другом" << endl;
        cout << "2. Игра с роботом" << endl;
        cout << "3. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        while (choice < 1 || choice > 3)
        {
            cout << "Некорректный выбор. Пожалуйста, выберите 1, 2 или 3: ";
            cin >> choice;
        }
        game play;
        botgame botplay;
        switch (choice)
        {
        case 1:
            clear();
            cout << "Режим игры с другом. Приятной игры!" << endl;
            play.setdeck1();
            play.setdeck2();

            while (play.checkwin() == 0)
            {
                play.step();
            }
            clear();
            play.print2decks();
            if (play.checkwin() == 1)
                cout << "\n\nИгрок 1 победил!" << endl;
            else
                cout << "\n\nИгрок 2 победил!" << endl;

            cout << "\nВведите 0 для возврата в меню...\n\n";
            cin >> choice;
            break;
        case 2:
            clear();
            cout << "Режим игры с роботом. Приятной игры!" << endl;
            botplay.setdeck1();
            botplay.setbotdeck();

            while (botplay.checkwin() == 0)
            {
                botplay.step();
            }
            clear();
            botplay.print2decks();
            if (botplay.checkwin() == 1)
                cout << "\n\nПоздравляем! Вы обыграли робота!" << endl;
            else
                cout << "\n\nК сожалению, робот победил вас..." << endl;

            cout << "\nВведите 0 для возврата в меню...\n\n";
            cin >> choice;
            break;
        case 3:
            cout << "До свидания!" << endl;
            return 0;
        }
    }
    return 0;
}