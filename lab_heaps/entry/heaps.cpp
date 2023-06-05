/**
 * @file testheap.cpp
 * Heap Testing Code
 *
 * @author Jack Toole
 * @date Fall 2011
 *
 * @author Chase Geigle
 * @date Fall 2012
 */

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include <random>

#include "coloredout.h"
#include "heap.h"

using namespace std;

typedef std::function<std::mt19937 (int seed)> create_rng_function;

void testConstructor(create_rng_function create_rng, int count);
void testPop(create_rng_function create_rng, int count);
void testPush(create_rng_function create_rng, int count);
void testUpdateElem(create_rng_function create_rng, int count);

void printHeader(const string& headline)
{
    cout << string(64, colored_out::BORDER_CHAR) << endl;
    colored_out::output_bold(headline);
    cout << endl << string(64, colored_out::BORDER_CHAR) << endl;
}

void printAfter(int value, std::string operation = "remove")
{
    cout << endl;
    colored_out::output_bold("After " + operation + "(");
    colored_out::output_bold(value);
    colored_out::output_bold(")");
    cout << endl;
}

int main(int argc, const char** argv)
{
    // Set up Colored Output (if 'color' parameter passed)
    bool is_colored
        = (argc > 1 && tolower(argv[1][0]) == 'c') && isatty(STDOUT_FILENO);

    // Specify random vs. fixed seed
    bool is_fixed_seed = is_colored || (argc > 1 && tolower(argv[1][0]) == 'f');

    colored_out coloroutput;
    if (is_colored) {
        coloroutput.set_expected_file("../data/soln_testheap.out");
        int status = coloroutput.start();
        if (status < 0)
            return 0;
    }

    // Read command line 'count' - number of things to put in our
    int count = 15;
    if (argc > 1 && !(is_colored || is_fixed_seed)) {
        stringstream arg(argv[1]);
        arg >> count;
    }

    // create_rng is a lambda that returns a std::mt19937 urng instance
    auto create_rng = [is_fixed_seed](int seed) {
        // use fixed_seed if is_fixed_seed, else create a new seed using std::random_device
        return std::mt19937(is_fixed_seed ? seed : std::random_device()());
    };

    testConstructor(create_rng, count);
    testPush(create_rng, count);
    testPop(create_rng, count);
    testUpdateElem(create_rng, count);

    return 0;
}

vector<int> setUpVector(std::mt19937 urng, int count)
{
    vector<int> result;
    result.reserve(count);
    for (int i = 0; i < count; i++)
        result.push_back(i);

    std::shuffle(result.begin(), result.end(), urng);
    return result;
}

void testPush(create_rng_function create_rng, int count)
{
    vector<int> to_insert = setUpVector(create_rng(128), count);
    printHeader("Testing push:");
    heap<int> myHeap;
    for (size_t i = 0; i < to_insert.size(); ++i) {
        myHeap.push(to_insert[i]);
        printAfter(to_insert[i], "push");
        cout << myHeap;
    }
}

void testPop(create_rng_function create_rng, int count)
{
    printHeader("Testing pop (requires constructor to be working):");
    vector<int> to_insert = setUpVector(create_rng(173), count);
    heap<int> myHeap(to_insert);
    cout << "Original Heap:" << endl;
    cout << myHeap;

    bool passed = true;
    for (int i = 0; i < (int)to_insert.size(); i++) {
        if (myHeap.empty()) {
            colored_out::output_bold("Incorrect: Heap should not be empty yet");
            cout << endl;
            passed = false;
            break;
        }
        int min = myHeap.pop();

        if (count < 64 || i != min) {
            printAfter(min, "pop");
            cout << myHeap;
        }
        if (i != min) {
            colored_out::output_bold("Incorrect: pop returned ");
            colored_out::output_bold(min);
            colored_out::output_bold(", but it should have returned ");
            colored_out::output_bold(i);
            cout << endl;
            passed = false;
            break;
        }
    }

    if (passed) {
        if (myHeap.empty())
            colored_out::output_bold("Pop Passed!");
        else
            colored_out::output_bold("Incorrect: Heap should be empty now");
        cout << endl;
    }
    cout << endl;
}

void testUpdateElem(create_rng_function create_rng, int count)
{
    printHeader("Testing updateElem (requires constructor to be working):");
    vector<int> to_insert = setUpVector(create_rng(225), count);
    heap<int> myHeap(to_insert);
    cout << "Original Heap:" << endl;
    cout << myHeap;
    cout << "Heap after updating index at 2 and 4:" << endl;
    myHeap.updateElem(myHeap.root() + 2, 93);
    myHeap.updateElem(myHeap.root() + 4, 0);
    cout << myHeap;
}

void testConstructor(create_rng_function create_rng, int count)
{
    vector<int> myArray = setUpVector(create_rng(124), count);

    cout << myArray.size() << endl;

    printHeader("Testing Constructor");
    cout << colored_out::BORDER_CHAR
         << " Original array: " << colored_out::BORDER_CHAR << endl;
    cout << "[";
    for (size_t i = 0; i < myArray.size(); ++i)
        cout << " " << myArray[i];
    cout << " ]" << endl << endl;

    cout << colored_out::BORDER_CHAR
         << " After buildheap: " << colored_out::BORDER_CHAR << endl;

    heap<int> myHeap(myArray);
    cout << myHeap;
    cout << endl << endl;
}

/**
 *  This test is NEVER RUN, but ONLY COMPILED.
 *   Its compilation checks that you aren't using any values, i.e.
 *   array[i], as an index into the array (since a string can't be
 *   used as an index into an array. If you do, this code will
 *   prevent the heap code from compiling. Neat, huh?
 **/
void testCompileOnly()
{
    vector<string> testHeapStringsCompiles;
    heap<string> myHeap(testHeapStringsCompiles);
    myHeap.pop();
}
