using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace sea_wars
{
    public class Profiles
    {
        public string[] logins = new string[0];
        public string[] password = new string[0];
        public int[] ratings = new int[0];
        public bool[,] wins = new bool[0, 10];
        public string[,] winsperson = new string[0, 10];

        public bool[] wins1 = new bool[10];
        public bool[] wins2 = new bool[10];
        public string[] winsperson1 = new string[10];
        public string[] winsperson2 = new string[10];

        public string login1;
        public string login2;
        public string password1;
        public string password2;
        public int rating1;
        public int rating2;
        public int tryautorize1 = 5;
        public int tryautorize2 = 5;

        public int initialRating = 1000;
        public bool Checkpassword1(string pass)
        {
            return password1 == pass;
        }
        public bool Checkpassword2(string pass)
        {
            return password2 == pass;
        }
        public bool AuthorizeUser1(string login, string pass)
        {
            for (int i = 0; i < logins.Length; i++)
            {
                if (logins[i] == login && password[i] == pass)
                {
                    login1 = logins[i];
                    password1 = password[i];
                    rating1 = ratings[i];

                    for (int j = 0; j < 10; j++)
                    {
                        wins1[j] = wins[i, j];
                        winsperson1[j] = winsperson[i, j];
                    }
                    return true;
                }
            }
            if (tryautorize1 == 5)
            {
                tryautorize1--;
                return false;
            }
            Console.Clear();
            tryautorize1--;
            Console.WriteLine($"Введен неверный логин или пароль! Осталось {tryautorize1} попытки.");
            if (tryautorize1 == 0) { Console.WriteLine("\nПопытки кончились!"); Environment.Exit(0); }
            return false;
        }
        public bool AuthorizeUser2(string login, string pass)
        {
            for (int i = 0; i < logins.Length; i++)
            {
                if (logins[i] == login && password[i] == pass)
                {
                    login2 = logins[i];
                    password2 = password[i];
                    rating2 = ratings[i];

                    for (int j = 0; j < 10; j++)
                    {
                        wins2[j] = wins[i, j];
                        winsperson2[j] = winsperson[i, j];
                    }
                    return true;
                }
            }
            if (tryautorize2 == 5)
            {
                tryautorize2--;
                return false;
            }
            Console.Clear();
            tryautorize2--;
            Console.WriteLine($"Введен неверный логин или пароль! Осталось {tryautorize2} попытки.");
            if (tryautorize2 == 0) { Console.WriteLine("\nПопытки кончились! Вы возвращаетесь в меню."); Environment.Exit(0); }
            return false;
        }
        public bool RegisterUser(string login, string pass, string filePath)
        {
            for (int i = 0; i < logins.Length; i++)
            {
                if (logins[i] == login) return false;
            }

            int oldLength = logins.Length;
            int newLength = oldLength + 1;

            Array.Resize(ref logins, newLength);
            Array.Resize(ref password, newLength);
            Array.Resize(ref ratings, newLength);

            wins = Resize2DArray(wins, newLength, 10);
            winsperson = Resize2DArray(winsperson, newLength, 10);

            logins[oldLength] = login;
            password[oldLength] = pass;
            ratings[oldLength] = initialRating;

            for (int j = 0; j < 10; j++)
            {
                wins[oldLength, j] = false;
                winsperson[oldLength, j] = "-";
            }

            SaveToFile(filePath);
            return true;
        }
        public void Showprofile1()
        {
            Console.Clear();
            Console.WriteLine($"=== Статистика игрока {login1} ===");
            Console.WriteLine($"Рейтинг: {rating1}");

            int totalGames = 0;
            int winCount = 0;
            for (int j = 0; j < 10; j++)
            {
                if (winsperson1[j] != "-")
                {
                    totalGames++;
                    if (wins1[j]) winCount++;
                }
            }

            double winRate = totalGames > 0 ? (double)winCount / totalGames * 100 : 0;
            Console.WriteLine($"Процент последних 10 побед: {winRate:F1}%");

            Console.WriteLine("=== Ваши игры ===");
            for (int j = 0; j < 10; j++)
            {
                if (winsperson1[j] != "-")
                {
                    string result = wins1[j] ? "Win" : "Lose";
                    Console.WriteLine($"{result}\t | {winsperson1[j]}");
                }
            }
        }
        public void Showprofile2()
        {
            Console.Clear();
            Console.WriteLine($"=== Статистика игрока {login2} ===");
            Console.WriteLine($"Рейтинг: {rating2}");

            int totalGames = 0;
            int winCount = 0;
            for (int j = 0; j < 10; j++)
            {
                if (winsperson2[j] != "-")
                {
                    totalGames++;
                    if (wins2[j]) winCount++;
                }
            }

            double winRate = totalGames > 0 ? (double)winCount / totalGames * 100 : 0;
            Console.WriteLine($"Процент последних 10 побед: {winRate:F1}%");

            Console.WriteLine("=== Ваши игры ===");
            for (int j = 0; j < 10; j++)
            {
                if (winsperson2[j] != "-")
                {
                    string result = wins2[j] ? "Win" : "Lose";
                    Console.WriteLine($"{result}\t | {winsperson2[j]}");
                }
            }
        }
        public void Wingame1(string filePath)
        {
            if (string.IsNullOrEmpty(login1) || string.IsNullOrEmpty(login2)) return;

            rating1 += 30;
            rating2 -= 30;
            if (rating2 < 0) rating2 = 0;

            for (int i = 0; i < 9; i++)
            {
                wins1[i] = wins1[i + 1];
                winsperson1[i] = winsperson1[i + 1];
            }
            wins1[9] = true;
            winsperson1[9] = login2;

            for (int i = 0; i < 9; i++)
            {
                wins2[i] = wins2[i + 1];
                winsperson2[i] = winsperson2[i + 1];
            }
            wins2[9] = false;
            winsperson2[9] = login1;

            UpdateMainArraysFromActivePlayers();
            SaveToFile(filePath);
        }
        public void Wingame2(string filePath)
        {
            if (string.IsNullOrEmpty(login1) || string.IsNullOrEmpty(login2)) return;

            rating2 += 30;
            rating1 -= 30;
            if (rating1 < 0) rating1 = 0;

            for (int i = 0; i < 9; i++)
            {
                wins1[i] = wins1[i + 1];
                winsperson1[i] = winsperson1[i + 1];
            }
            wins1[9] = false;
            winsperson1[9] = login2;

            for (int i = 0; i < 9; i++)
            {
                wins2[i] = wins2[i + 1];
                winsperson2[i] = winsperson2[i + 1];
            }
            wins2[9] = true;
            winsperson2[9] = login1;

            UpdateMainArraysFromActivePlayers();
            SaveToFile(filePath);
        }
        public void ShowTop10()
        {
            var userIndices = new List<int>();
            for (int i = 0; i < logins.Length; i++)
            {
                userIndices.Add(i);
            }

            userIndices.Sort((a, b) => ratings[b].CompareTo(ratings[a]));

            Console.WriteLine("\n=== ТАБЛИЦА ЛИДЕРОВ (ТОП 10) ===");
            int limit = Math.Min(10, userIndices.Count);
            for (int i = 0; i < limit; i++)
            {
                int idx = userIndices[i];
                Console.WriteLine($"{i + 1}. Логин: {logins[idx]} | Рейтинг: {ratings[idx]}");
            }
            Console.WriteLine("================================\n");
        }
        public void ShowUserProfile()
        {
            Console.Write("Введите логин игрока: ");
            string inputLogin = Console.ReadLine();
            int index = -1;
            for (int i = 0; i < logins.Length; i++)
            {
                if (logins[i] == inputLogin)
                {
                    index = i;
                    break;
                }
            }
            if (index == -1)
            {
                Console.WriteLine($"Пользователь с логином {inputLogin} не найден.");
                return;
            }
            Console.Clear();
            Console.WriteLine($"=== Статистика игрока {logins[index]} ===");
            Console.WriteLine($"Рейтинг: {ratings[index]}");

            int totalGames = 0;
            int winCount = 0;
            for (int j = 0; j < 10; j++)
            {
                if (winsperson[index, j] != "-")
                {
                    totalGames++;
                    if (wins[index, j]) winCount++;
                }
            }

            double winRate = totalGames > 0 ? (double)winCount / totalGames * 100 : 0;
            Console.WriteLine($"Процент последних 10 побед: {winRate:F1}%");

            Console.WriteLine("=== Последние игры ===");
            for (int j = 0; j < 10; j++)
            {
                if (winsperson[index, j] != "-")
                {
                    string result = wins[index, j] ? "Win" : "Lose";
                    Console.WriteLine($"{result}\t | {winsperson[index, j]}");
                }
            }
            Console.Write("\n\nНапишите '+' для очистки консоли: ");
            char temp1 = '-';
            while (temp1 != '+')
            {
                string tk = ReadToken();
                if (tk.Length > 0) temp1 = tk[0];
            }
            Console.Clear();
        }
        public void SaveToFile(string filePath)
        {
            using (StreamWriter sw = new StreamWriter(filePath, false, Encoding.UTF8))
            {
                for (int i = 0; i < logins.Length; i++)
                {
                    StringBuilder sb = new StringBuilder();
                    sb.Append($"{logins[i]} {password[i]} {ratings[i]}");

                    for (int j = 0; j < 10; j++)
                    {
                        sb.Append(wins[i, j] ? " win" : " lose");
                    }

                    for (int j = 0; j < 10; j++)
                    {
                        sb.Append($" {winsperson[i, j]}");
                    }

                    sw.WriteLine(sb.ToString());
                }
            }
        }
        public void ReadFromFile(string filePath)
        {
            if (!File.Exists(filePath)) return;

            string[] lines = File.ReadAllLines(filePath);
            int count = lines.Length;

            logins = new string[count];
            password = new string[count];
            ratings = new int[count];
            wins = new bool[count, 10];
            winsperson = new string[count, 10];

            for (int i = 0; i < count; i++)
            {
                if (string.IsNullOrWhiteSpace(lines[i])) continue;
                string[] parts = lines[i].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                if (parts.Length >= 23)
                {
                    logins[i] = parts[0];
                    password[i] = parts[1];
                    ratings[i] = int.Parse(parts[2]);

                    for (int j = 0; j < 10; j++)
                    {
                        wins[i, j] = (parts[3 + j] == "win");
                    }

                    for (int j = 0; j < 10; j++)
                    {
                        winsperson[i, j] = parts[13 + j];
                    }
                }
            }
        }
        public void UpdateMainArraysFromActivePlayers()
        {
            for (int i = 0; i < logins.Length; i++)
            {
                if (logins[i] == login1)
                {
                    ratings[i] = rating1;
                    for (int j = 0; j < 10; j++)
                    {
                        wins[i, j] = wins1[j];
                        winsperson[i, j] = winsperson1[j];
                    }
                }
                if (logins[i] == login2)
                {
                    ratings[i] = rating2;
                    for (int j = 0; j < 10; j++)
                    {
                        wins[i, j] = wins2[j];
                        winsperson[i, j] = winsperson2[j];
                    }
                }
            }
        }
        private static T[,] Resize2DArray<T>(T[,] original, int newRows, int newCols)
        {
            T[,] newArray = new T[newRows, newCols];
            int minRows = Math.Min(original.GetLength(0), newRows);
            int minCols = Math.Min(original.GetLength(1), newCols);
            for (int i = 0; i < minRows; i++)
                for (int j = 0; j < minCols; j++)
                    newArray[i, j] = original[i, j];
            return newArray;
        }
        private string ReadToken()
        {
            string token = "";
            int ch;
            while ((ch = Console.Read()) != -1)
            {
                char c = (char)ch;
                if (char.IsWhiteSpace(c))
                {
                    if (token.Length > 0) break;
                }
                else
                {
                    token += c;
                }
            }
            return token;
        }
    }
}