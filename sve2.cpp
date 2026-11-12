//
// Created by parallels on 11/12/26.
//
#include <iostream>
#include <arm_sve.h>

using namespace std;

int main()
{
    svbool_t pg = svptrue_b64();
    double x[32] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0};
    double y[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
    svfloat64_t vec = svld1_f64(pg, &x[0]) ;

    uint64_t lanes = svcntd();

    cout << "lanes: " << lanes << endl;
    svst1_f64(pg, &y[0], vec);

    for (uint64_t i = 0; i < lanes; i++)
        cout << y[i] << " " ;
    cout << endl;

    return 0 ;
}