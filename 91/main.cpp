#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

class Experiment {
private:
    // ������, ������������� �� 0 �� 1
    double rand1() {
        return 1.0*rand() / RAND_MAX;
    }

public:
    // ������ ������������
    double Run(double p, int N) {
        int ill = 0; // ���������� �������
        int health = N - 1; // ���������� ��������
        int infected = 1; // ���������� ����������
        int day = 0; // ����
        long long ill_ammount = 0; // ����� ����� ���������
        for (day = 1; day <= 500; day++) { // ������ �� ���� ����
            ill = infected; // ���������� ���������� ��������
            ill_ammount += ill;
            infected = 0;
            for (int person = 0; person < health; person++) // ��� ������� ��������
                if (rand1() < 1 - pow(1.0 - p, ill)) // ���� �� �� ���� �� ���������� �� �� ���� �� �������
                    infected++; // ����������� ���������� ����������
            health -= infected; // ���������� ��������� ���� ���������
            health += ill; // ��� ������� �����������
            if (!ill) // ���� ������� ������ ���
                break; // ���������� �� �����. ����� � ����, ��� ����� day �� ��������� �������� 500
        }
        return ill_ammount / day; // ������� ������� ����� �������
    }

    // ��������� ������ �� ������
    void Solve(int experiments_ammount = 100, int N = 1000) { // ��������� ���-�� ������������� � ����� ������������ � ����� �����
        for (double p = 0; p < 0.005; p += 0.0001) { // ��� ������ ����������� ����������
            double average_from_all_experiments = 0; // ������� �� ������ �������������
            for (int experiment_number = 0; experiment_number < experiments_ammount; experiment_number++) { // ��� ������� ������������
                double average_from_one_experiment = Run(p, N); // ������� �� ������ ������������
                average_from_all_experiments += average_from_one_experiment / experiments_ammount; // ���������� �������� �� ���� �������������
            }
            cout << "p = " << p << ", average: " << average_from_all_experiments << endl; // ����� ������
        }
    }
};

int main() {
    srand(time(NULL)); // ���������������� ������ ��������� �����
    Experiment Ex; // ����������� �����������
    Ex.Solve(); // 3, 2, 1 - ����!
    return 0;
}
