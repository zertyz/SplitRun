#include <iostream>
#include <map>
#include <unordered_map>
#include <thread>
#include <random>
#include <algorithm>

#include <mutex>

#include "../../cpp/SplitRun.h"
using namespace mutua::testutils;

// from CppUtils
#include <BetterExceptions.h>


void splitRunExperiments() {

    class SplitRunSleepExperiment: public SplitRun {
    public:
        SplitRunSleepExperiment(int taskArgument): SplitRun(taskArgument) {}
        void splitRun() override {
            this_thread::sleep_for(chrono::milliseconds(taskArgument*(1000/4)));
            for (int i=0; i<10; i++) {
                cout << "Here I am!! and my parameter is #" << taskArgument << endl << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    };

    SplitRunSleepExperiment sleep1(1);
    SplitRunSleepExperiment sleep2(2);
    SplitRunSleepExperiment sleep3(3);
    SplitRunSleepExperiment sleep4(4);

    SplitRun::add(sleep1);
    SplitRun::add(sleep2);
    SplitRun::add(sleep3);
    SplitRun::add(sleep4);

    SplitRun::runAndWaitForAll();

    class SplitRunExceptionExperiment: public SplitRun {
    public:
        SplitRunExceptionExperiment(int taskArgument): SplitRun(taskArgument) {}
        void splitRun() override {
            int t = 3;
            this_thread::sleep_for(chrono::milliseconds(taskArgument*(1000/4)));
            for (int i=0; i<t; i++) {
                cout << "Instance #" << taskArgument << " is about to throw in " << (t-i) << " seconds..." << endl << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            THROW_EXCEPTION(std::overflow_error, "Task " + to_string(taskArgument) + " deliberately died");
        }
    };

    SplitRunExceptionExperiment exceptionThrower1(1);
    SplitRunExceptionExperiment exceptionThrower2(2);
    SplitRunExceptionExperiment exceptionThrower3(3);
    SplitRunExceptionExperiment exceptionThrower4(4);

    SplitRun::add(exceptionThrower1);
    SplitRun::add(exceptionThrower2);
    SplitRun::add(exceptionThrower3);
    SplitRun::add(exceptionThrower4);

    std::vector<string> exceptions;
    std::vector<string> exceptionReports;
    tie(exceptions, exceptionReports) = SplitRun::runAndWaitForAll();

    for (int i=0; i<exceptions.size(); i++) {
        cout << "Thread #" << i << ": exception '" << exceptions[i] << "'. Report: " << exceptionReports[i] << endl;
    }
}

int main() {

    try {
        splitRunExperiments();
    } catch (const std::exception& e) {
        DUMP_EXCEPTION(e, "Error while running splitRunExperiments()");
    }

    return EXIT_SUCCESS;
}
