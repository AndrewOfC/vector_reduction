#include <iostream>
#include <immintrin.h>

using namespace std ;// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

double reduce256(double *src, double initial = 0.0) ;




int main()
{
    double data[256] ;
    for (int i = 0 ; i < 256 ; i++)
    {
        data[i] = i ;
    }
    auto result = reduce256(data);
    cout << "Result: " << result << endl;

    return 0;// TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}