// Laba1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
using namespace std;
#include <iostream>

double ipow(double x, long n)
{
    _asm
    {
        mov eax, [n]
        cdq                 //edx =0, если n>=0, edx = -1, если n<0
        xor eax, edx        //eax = -1-a, если n<0
        sub eax, edx        //eax = (-1-n)-(-1) = -n, если n<0
        fld qword ptr[x]
        ja start_loop1      //если n>0
        fld1
        fxch                //1,x
        jz p_end
        fdivp st(1), st(0)  //1/x
        jmp start_loop1
        loop1 :
        fmul st(0), st(0)
        start_loop1 :
        shr eax, 1
        jnc loop1
        jz p_exit
        fld st(0)       //x,x
        P_loop :
        fmul st(0), st(0)
        shr eax, 1
        jnc p_test_z
        fmul st(1), st(0)
        p_test_z :
        jnc p_loop
        p_end :
        fstp st(0)
        p_exit :
    }
}

int main()
{

    cout << "ipow\n";
    int n = 3;
    for (int i = -3; i < 5; i ++) {
        cout << "ipow(" << 2 << "," << i << ") \t=\t" << ipow(2, i) << endl;
    }
    for (double i = -4; i < 4; i += 0.5) {
        cout << "ipow(" << i << "," << n << ") \t=\t" << ipow(i, n) << endl;
    }
    getchar();
}