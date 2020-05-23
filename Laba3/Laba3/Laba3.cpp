// Laba3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define Pi  3.14159265358979323846  /* pi */
using namespace std;

float fTg(float x)
{
    const float ctable[] = {
       1 / Pi,
       1.57079633,
       -0.645963711,
       0.0796892689,
       -0.00467295692,
       0.000151086471,
       -0.0,
       1.0 };
    const float* ct = ctable;
    _asm
    {
        movss xmm2, [x] // xmm2 = x
        mov edx, [ct] // В edx адрес таблицы констант
        mulss xmm2, [edx] // Разделить x на pi
        cvtss2si ecx, xmm2 // Перевести x/pi в целое число с округлением
        xorps xmm0, xmm0 // Инициализировать результат нулём
        cvtsi2ss xmm1, ecx // В xmm1 округлённое до целых x/pi
        dec ecx // OF=1, если ecx=80000000h (переполнение)
        jo tg_end // В случае слишком большого |x| вернуть 0
        subss xmm2, xmm1 // Дробная часть от x/pi в диапазоне [-0,5; 0,5]
        movss xmm1, [edx + 24] // 80000000h
        orps xmm1, xmm2 // Младшая часть xmm1 будет отрицательной
        movlhps xmm1, xmm2 // В старшей части xmm1 будет аргумент синуса
        addps xmm1, xmm1 // В старшей части редуцированное -1<=x<=1
        addss xmm1, [edx + 28] // В младшей части xmm1 аргумент косинуса: 1-|x|
        movaps xmm2, xmm1 // Скопировать аргументы в xmm2
        mulps xmm2, xmm2 // Сформировали аргументы полинома (xmm2 = x^2)
        mov ecx, 5 // Инициализировали счётчик цикла
        tg_loop: // Цикл вычисления полинома
        movss xmm3, [edx + 4 * ecx] // Загружаем текущий коэффициент в xmm3
        mulps xmm0, xmm2 // Умножаем предыдущий результат на x^2
        movlhps xmm3, xmm3 // Продублировать коэффициент в xmm3
        addps xmm0, xmm3 // Прибавляем текущий коэффициент (схема Горнера)
        loop tg_loop // Учесть все 5 коэффициентов
        mulps xmm1, xmm0 // Домножить на x, получаем готовый результат
        movhlps xmm0, xmm1 // Поместить в xmm0 старшую часть результата (синус)
        divss xmm0, xmm1 // Разделить синус на косинус
        tg_end : // Результат в xmm0 готов
        movss[x], xmm0 // Переносим результат в стек сопроцессора
        fld dword ptr[x]
    }
}

int main()
{
     
    cout << "fTg\n";
    for (double i = -1.57; i < 1.57; i+=0.1)
    {
        cout << "fTg("<< round(i * 100) / 100 <<")\t=\t" << fTg(i) << endl;
    }
    getchar();
}

