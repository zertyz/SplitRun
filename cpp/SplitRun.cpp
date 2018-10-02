#include <iostream>
#include <string>
#include <exception>
#include <thread>
#include <sstream>
#include <vector>
#include <algorithm>

#include "SplitRun.h"

using namespace mutua::testutils;

std::vector<SplitRun*> SplitRun::instances     = {};
std::vector<string>    SplitRun::exceptions    = {};
std::vector<string>    SplitRun::exceptionMsgs = {};


SplitRun::SplitRun(int taskArgument)
        : taskArgument(taskArgument) {}

void SplitRun::
        reset() {
    instances    .clear();
    exceptions   .clear();
    exceptionMsgs.clear();
}

void SplitRun::
        add(SplitRun& instance) {
    instances    .push_back(&instance);
    exceptions   .push_back("");
    exceptionMsgs.push_back("");
}

std::tuple<std::vector<string>, std::vector<string>> SplitRun::
        runAndWaitForAll() {

    std::vector<std::thread> threads(instances.size());

    // run
    for (int i=0; i<instances.size(); i++) {
        SplitRun* instance = instances[i];
        threads[i] = thread([](SplitRun* instance, int n) {instance->run();}, instance, i);
    }

    // wait
    for (int i=0; i<threads.size(); i++) {
        threads[i].join();
    }

    std::tuple<std::vector<string>, std::vector<string>> executionReport = {exceptions, exceptionMsgs};

    // prepare for next use
    reset();

    return executionReport;
}

void SplitRun::
        run() {

    try {
        splitRun();
    } catch (const std::exception& e) {
        std::stringstream stringStream;
        stringStream << std::this_thread::get_id();
        string threadId = stringStream.str();
        string exceptionDebugMsg = BUILD_EXCEPTION_DEBUG_MSG(e, "Exception while running a SplitRun task at thread #" + threadId,
                                                             "taskArgument", std::to_string(taskArgument));
        // dump the exception debug message to stderr
        std::cerr << exceptionDebugMsg << std::endl << std::flush;
        // keep track of the exception and the exception dumping message
        auto element = std::find(instances.begin(), instances.end(), this);
        if (element == instances.end()) {
            cerr << "--> additional error: 'element' is not in 'instances'. Ignoring returning exceptions for this one...";
        } else {
            auto index = std::distance(instances.begin(), element);
            exceptions   [index] = e.what();
            exceptionMsgs[index] = exceptionDebugMsg;
        }
    }

}
