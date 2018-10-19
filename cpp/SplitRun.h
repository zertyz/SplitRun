#ifndef MUTUA_TESTUTILS_SPLITRUN_H
#define MUTUA_TESTUTILS_SPLITRUN_H

#include <exception>
#include <vector>
#include <array>

using namespace std;

namespace mutua::testutils {

    /**
     * SplitRun.cpp
     * ============
     * created (in Java) by luiz, Jul 25, 2015)
     * transcoded to C++ by luiz, Sep 19, 2018
     * last transcoding  by luiz, Sep 19, 2018
     *
     * Allows several threads to run, simultaneously, their tasks -- waiting for all of them
     * to finish. Made for profiling/tuning and reentrancy tests purposes.
     *
    */
    class SplitRun {

    private:
        static std::vector<SplitRun*> instances;
        static std::vector<string>    exceptions;
        static std::vector<string>    exceptionMsgs;

    protected:
        int taskArgument;

    public:

        SplitRun(int taskArgument);
        //virtual ~SplitRun();
        static  void                                                 add(SplitRun& instance);
        static  std::tuple<std::vector<string>, std::vector<string>> runAndWaitForAll();
        virtual void                                                 splitRun() = 0;
                void                                                 run();

    private:

        static void reset();

    };
}

#endif //MUTUA_TESTUTILS_SPLITRUN_H
