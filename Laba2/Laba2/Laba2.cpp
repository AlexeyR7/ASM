// Laba2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
using namespace std;
#include <iostream>

double pow(double x, double y)
{
    _asm
    {
        fld qword ptr[y]
        fld qword ptr[x]   //y, x
        ftst
        fnstsw ax
        sahf
        jnz p_norm
        fcomi st(0), st(1)
        jc p_end
        p_norm :
        fyl2x
        fld st(0)
        frndint
        fsub st(1), st(0)
        fxch st(1)
        f2xm1
        fld1
        faddp st(1), st(0)
        fscale
        p_end :
        fstp st(1)
    }
}

int main()
{
    cout << "pow\n";
    double n = 2.5;
    for (double i = 1; i < 5; i += 1) {
        cout << "pow(" << i << "," << n << ") \t=\t" << pow(i, n) << endl;
    }
    for (double i = 1; i <= 10; i += 0.5) {
        cout << "pow(" << 2 << "," << i << ") \t=\t" << pow(2, i) << endl;
    }
    getchar();
}