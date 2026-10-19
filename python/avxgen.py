import argparse
import sys

import jinja2 as j2

TEMPLATE2 ="""
#include <cstdint>
#include <immintrin.h>
double reduce{{"%03d"|format(n*8)}}(double *src, double initial)
{

   register uint64_t r8_val asm("r8");
   __asm__ __volatile__ (
       "movq %1, %0"
       : "=r" (r8_val)  // Output: write to the register bound to r8_val
       : "m" (src)     // Input: the pointer address
   );
    /*
     * load
     */
{%- for i in range(n) %}
   asm volatile( 
   "vmovapd {{i*64}}(%%r8), %%zmm{{i}}\\n\\t" : "=r" (src) : : "zmm{{i}}"
   ) ;
{%- endfor %}


{%- for j in steps %}
{% for i in range(j) %}     
     asm(
        "vaddpd %zmm{{i}}, %zmm{{i+j}}, %zmm{{i}}"
     ) ;
{%- endfor %}
{%- endfor %}

    double result[8];
    
    asm ( 
        "vmovapd %%zmm0, %0\\n\\t" : "=m" (result)
   ) ;
    
    for( int i = 0 ; i < 8 ; i++ )
        initial += result[i] ;

     
    return initial ;
}
"""

TEMPLATE = """

#include <immintrin.h>

double reduce{{"%03d"|format(n*8)}}(double *src, double initial)
{
{%- for i in range(n) %}
    __m512d r{{"%03d" | format(i)}} = _mm512_loadu_pd(src+{{i*8}});
{%- endfor %}

{%- for j in steps %}
{% for i in range(j) %}
    // r{{"%03d" | format(i)}} += r{{"%03d" | format(i+j)}} ;
    r{{"%03d" | format(i)}} = _mm512_add_pd(r{{"%03d" | format(i)}}, r{{"%03d" | format(i+j)}});
{%- endfor %}
{%- endfor %}

    double result[8];
    
    _mm512_storeu_pd(result, r000);
    for( int i = 0 ; i < 8 ; i++ )
        initial += result[i] ;

    return initial ;
}
"""

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output")
    parser.add_argument("--n", type=int, default=32)
    parser.add_argument("-v", "--verbose", action="store_true")
    args = parser.parse_args()


    template = j2.Template(TEMPLATE2)

    i = args.n
    steps = []
    while i >= 1:
        i //= 2
        steps.append(i)

    if args.output is None:
        outs = sys.stdout
    else:
        outs = open(args.output, "w")

    text = template.render(n=args.n, steps=steps)
    if args.verbose:
        print(text)
    if args.output:
        print(text, file=outs)

    return


if __name__ == "__main__":
    main()
