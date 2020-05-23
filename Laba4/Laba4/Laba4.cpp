// Laba4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std; 


double arccos(double x) {
    _asm
    {
        fld qword ptr[x]       // Загрузить x
        fld1                   // В стеке: x, 1
        fsub st(0), st(1)      // В стеке: x, 1-x
        fld1                   // В стеке: x, 1-x, 1
        fadd st(0), st(2)      // В стеке: x, 1-x, 1+x
        fmulp st(1), st(0)     // В стеке: x, (1-x)*(1+x)=1-x^2
        fsqrt                  // В стеке: x; (1-x^2)^0,5
        fxch                   // В стеке: (1-x^2)^0,5; x
        fpatan                 // В стеке: arcctg(x/(1-x^2)^0,5) = arccos x
    }
}

int main()
{

    cout << "arccos\n";
    for (double i = -1; i < 1; i += 0.1)
    {
        cout << "arccos(" << round(i*100)/100 << ")\t=\t" << arccos(i) << endl;
    }
    getchar();
}
