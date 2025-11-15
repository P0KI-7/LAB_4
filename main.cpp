#include <iostream>
#include <windows.h>

using namespace std;

float dayAverage(float* row, int h);
float overallAverage(float** p, int d, int h);
void showHotDays(float** p, int d, int h); // выводит дни, где средняя температура > общей средней


int main()
{
    SetConsoleOutputCP(65001); // Переключаем консоль в UTF-8
    SetConsoleCP(65001);
    
    int day, meterage;
    float** data;

    cout << "Введите количество дней: ";
    cin >> day;
    cout << "Введите количество измерений в дне: ";
    cin >> meterage;
    if (day > 30 || meterage > 24){
        cout << "Ошибка: превышено максимальное количество дней или измерений." << endl;
        return 1;
    }

    // Создание двумерного динамического массива
    data = new float*[day];
    for (int i = 0; i < day; i++){
        data[i] = new float[meterage];
    }

    // Считывание значений (температуру) с клавиатуры
    for (int i = 0; i < day; i++){
        cout << "День " << (i+1) << ": ";
        for (int j = 0; j < meterage; j++){
            cin >> *(*(data+i) + j);
        }
    }
    
    cout << "Общая средняя температура: " << overallAverage(data,day,meterage) << endl;

    showHotDays(data,day,meterage);

    // Освобождение памяти
    for (int i = 0; i < day; i++){
        delete[] data[i];
    }
    delete[] data;

    return 0;
}

float dayAverage(float* row, int h)
{
    float sum = 0;
    for (int i = 0; i < h; i++){
        sum += *(row+i);
    } 
    return (sum / h);
}

float overallAverage(float** p, int d, int h)
{
    float sum = 0;
    for (int i = 0; i < d; i++){
        for (int j = 0; j < h; j++){
            sum += *(*(p+i) + j);
        }
    }
    return (sum / (d*h));
}

void showHotDays(float** p, int d, int h)
{
    float average = overallAverage(p,d,h);
    float currentAverage;

    cout << "Тёплые дни:" << endl;

    for (int i = 0; i < d; i++){
        currentAverage = dayAverage(*(p+i),h);
        if (currentAverage > average){
            cout << "День " << (i+1) << " (среднее = " << currentAverage << ")" << endl;
        }
    }
}