#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <boost/range/numeric.hpp>
#include <boost/align/aligned_allocator.hpp>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

#include "genericsum.hpp"

namespace po = boost::program_options;
using namespace std;
using boost::timer::cpu_timer;

typedef std::vector<double, boost::alignment::aligned_allocator<double, 64>> vector_aligned64_t;

double reduce256(double *src, size_t len, double initial = 0.0);

bool almostEqualAbsolute(double a, double b, double tolerance = 1e-8) {
    return std::fabs(a - b) <= tolerance;
}

int main(int argc, char *argv[])
{
    size_t count = 2;
    unsigned int iterations = 1 ;
    bool simple = false;

    try
    {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("simple,s", "run simple test")
            ("count,c", po::value<size_t>(&count)->default_value(2), "number of 256x elements to reduce")
            ("iterations,i", po::value<unsigned int>(&iterations)->default_value(1), "number of iterations to run");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            cout << desc << "\n";
            return 0;
        }
        simple = vm.count("simple") != 0;

    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    count *= 256 ;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1000.0, 1000.0);

    vector_aligned64_t data(count);
    if ( ! simple )
        for (size_t i = 0; i < count; i++)
        {
            data[i] = dist(gen);
        }
    else {
        for (size_t i = 0; i < count; i++)
        {
            data[i] = i ;
        }
    }

    string formatt = "%u" ;
    double result = 0, check_result = 0 ;
    /*
     * generic
     */
    cpu_timer timer2;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        result = genericSum(data.data(), count, 0.0);
    }
    timer2.stop();
    cout << "generic Result: " << result << "  " << timer2.format(5, formatt) << endl;
    /*
     *
     */
    cpu_timer timer3;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        check_result = boost::accumulate(data, 0.0);
    }
    timer3.stop();
    auto std_elapsed = timer3.elapsed().user    ;
    cout << "std Result: " << check_result << "  " << timer3.format(5, formatt) << endl;
    /*
     * avx/NEON
     */
    cpu_timer timer1;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        result = reduce256(data.data(), count);
    }
    timer1.stop();
    auto avx_elapsed = timer1.elapsed().user    ;
    cout << "avx Result: " << result << "  " << timer1.format(5, formatt) << endl;
    cout << "avx speedup: " << std::fixed << std::setprecision(2) << (double)std_elapsed / (double)avx_elapsed << endl;

    if (!almostEqualAbsolute(result, check_result))
    {
        cerr << "Error: Results do not match!  " << check_result - result << endl;
        return 1;
    }

    return 0;
}