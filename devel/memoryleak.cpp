/**

    Fornux C++ Superset -- Example.

    Outputs ('clang' on Linux):

    foo
    foo: 30
    node 1
    Test1... test2... this is a test
    Test1Test1... t.. this is a test
    Test1XXXXXXXXXX.. this is a test
    Test1XXXXXXXXXX.. this is a test"s" (33) out of range [0, 33[
    #0 main in devel/memoryleak.cpp
    
    "p" is not a buffer
    #0 main in devel/memoryleak.cpp
    
    'p' is a 'B'
    Speed: 255195.25066 loops / s; Memory usage: 6824 k
    
 */


#if defined(_WIN32)
#include <Windows.h>
#include <Psapi.h>
#define strdup _strdup
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/resource.h>
#endif

#include <string.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <list>
#include <type_traits>


using namespace std;
using namespace std::chrono;


class A
{
    int x;

    int i;
    int j;
};

struct B : virtual A
{
    int k;
    int l;
    
    virtual ~B() {}
};

struct C : virtual A
{
    int m;
    int n;
    
    virtual ~C() {}
};

struct D : B
{
    int o;
    int p;
};

struct E : C
{
    int o;
    int p;
};

struct list_node : D, E
{
    struct parent
    {
        struct child
        {
            int i;
        } j;
        
        int i;
    } j;
    
    int q;
    int r = 20;

    list_node * p;
    
    list_node() : q(10) {}
    
    void foo()
    {
        int i;
        double d;
        
        auto n = i;
        auto p = & n;
        auto o = j;
        auto f = [this, i, d](int a) { return r + a; };
        
        cout << __func__ << ": " << f(10) << endl;
    }
};

typedef struct { int i; } test;

test * foo()
{
    cout << __func__ << endl;
    
    return (test *) 0;
}

namespace Dummy
{
template <bool>
    struct Predicate
    {
        static bool constexpr value() { return false; }
    };
    
template <>
    struct Predicate<true>
    {
        static bool constexpr value() { return true; }
    };
    
template <typename T, typename U = void>
    struct Value
    {
        typedef T value;
    };
    
template <typename T>
    struct Value<T, typename std::enable_if<Predicate<true>::value(), int>::type>
    {
        typedef T value;
    };
    
    struct Funny
    {
        typedef int value;

        Funny(int, int) {}
    };

template <typename T>
    struct Dummy
    {
        Dummy(T, T) {}
        ~Dummy() {}
    };
}

#if defined(_WIN32)
SIZE_T GetMemoryUsage( DWORD processID );
#endif

int main(int argc, char * argv_[])
{
    // Transfering 2D external buffers into internal buffers:
    char ** argv = new char *[argc];
    
    for (int i = 0; i < argc; ++ i)
        argv[i] = argv_[i];

    // Lambda functions tests:
    list_node n;
    list_node m(n);
    
    foo();    
    n.foo();
    
    // STL container friendly:
    list<char *> l;
    l.push_back(strdup("node 1"));
    l.push_back(strdup("node 2"));
    l.push_back(l.front());
    
    cout << l.back() << endl;
    
    // Efficient memcpy() & memset():
    char * s = strdup("Test1... test2... this is a test");
    
    cout << s << endl;
    
    memcpy(s + 5, s, 10);
    cout << s << endl;
    
    memset(s + 5, 'X', 10);
    cout << s << endl;

    // Buffer overflow implicit detection:
    try
    {
        while (true)
        {
            cout << * s ++ << flush;
        }
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    // Polymorphism:
    struct C * p = new list_node;
        
    // Not-a-buffer implicit detection:
    try
    {
        p++;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    
    if (dynamic_cast<B *>(p))
        cout << "'p' is a 'B'" << endl;
    
    // Proper cyclic memory leaks management:
    milliseconds before, after;
 
    before = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    
    for (int i = 0; ; ++ i)
    {
        // cycle
        struct list_node * p = new list_node;
        p->p = new list_node;
        p->p->p = new list_node;
        p->p->p->p = p;
        
        // stats
        after = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		
#if defined(_WIN32)
		cout << "\rSpeed: " << setprecision(11) << i * 1000.0 / (after - before).count() << " loops / s; Memory usage: " << GetMemoryUsage(GetCurrentProcessId()) / 1024 << " kilobytes" << flush;
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
        struct rusage r_usage;
        getrusage(RUSAGE_SELF, & r_usage);

        cout << "\rSpeed: " << setprecision(11) << i * 1000.0 / (after - before).count() << " loops / s; Memory usage: " << r_usage.ru_maxrss << " kilobytes" << flush;
#endif
    }

    // Templates:
    Dummy::Funny(8, 8);
    Dummy::Dummy<typename Dummy::Value<int, int>::value>(9, 9);
    
    return 0;
}

#if defined(_WIN32)
SIZE_T GetMemoryUsage( DWORD processID )
{
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;

    hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
                             PROCESS_VM_READ,
                             FALSE, 
                             processID );
    if (NULL == hProcess)
        return 0;

    if ( GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)) )
        return pmc.WorkingSetSize;

    CloseHandle( hProcess );
	
	return 0;
}
#endif
