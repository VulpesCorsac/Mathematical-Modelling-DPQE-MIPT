#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

class Experiment {
private:
    // Рандом, нормированный от 0 до 1
    double rand1() {
        return 1.0*rand() / RAND_MAX;
    }

public:
    // Запуск эксперимента
    double Run(double p, int N) {
        int ill = 0; // количество больных
        int health = N - 1; // количество здоровых
        int infected = 1; // количество зараженных
        int day = 0; // День
        long long ill_ammount = 0; // Общее число заражений
        for (day = 1; day <= 500; day++) { // Проход по всем дням
            ill = infected; // Зараженные становятся больными
            ill_ammount += ill;
            infected = 0;
            for (int person = 0; person < health; person++) // Для каждого человека
                if (rand1() < 1 - pow(1.0 - p, ill)) // Если он не смог не заразиться ни от кого из больных
                    infected++; // Увеличиваем количество зараженных
            health -= infected; // Зараженные перестали быть здоровыми
            health += ill; // Все больные выздоровили
            if (!ill) // Если больных больше нет
                break; // Вывалиться из цикла. Иметь в виду, что тогда day не достигнет значения 500
        }
        return ill_ammount / day; // Вернуть среднее число больных
    }

    // Получение ответа на задачу
    void Solve(int experiments_ammount = 100, int N = 1000) { // Принимает кол-во экспериментов с одной вероятностью и число людей
        for (double p = 0; p < 0.005; p += 0.0001) { // Для каждой вероятности заразиться
            double average_from_all_experiments = 0; // Среднее по разным экспериментам
            for (int experiment_number = 0; experiment_number < experiments_ammount; experiment_number++) { // Для каждого эксперимента
                double average_from_one_experiment = Run(p, N); // среднее по одному эксперименту
                average_from_all_experiments += average_from_one_experiment / experiments_ammount; // Построение среднего по всем экспериментам
            }
            cout << "p = " << p << ", average: " << average_from_all_experiments << endl; // Вывод ответа
        }
    }
};

int main() {
    srand(time(NULL)); // Инициализировать датчик случайных чисел
    Experiment Ex; // Подготовить эксперимнет
    Ex.Solve(); // 3, 2, 1 - ПУСК!
    return 0;
}
