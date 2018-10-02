#ifndef MUTUA_TESTUTILS_SPLITRUN_H
#define MUTUA_TESTUTILS_SPLITRUN_H

#include <exception>
#include <vector>
#include <sstream>
#include <array>

#define BUILD_EXCEPTION_DEBUG_MSG(exception, message, ...)                                                           \
    [](auto const& e, string msg, string pretty_func, std::array<string, 100> paramDuples) {                         \
        /* paramDuples := {param1Name, param1Value, param2Name, param2Value, ...} */                                 \
        int paramDuplesLength = paramDuples.size();                                                                  \
        std::stringstream cstr;                                                                                      \
        cstr << "\n## Exception '" << e.what() << "' caught in:" << std::endl                                        \
             <<   "##     " << __FILE__ << ":" << __LINE__ << " -- " << pretty_func << std::endl                     \
             <<   "##     Debug Info: {";                                                                            \
        for (int i=0; i<paramDuplesLength; i+=2) {                                                                   \
            if (paramDuples[i] != "") {                                                                              \
                cstr << (i > 0 ? ", " : "") << paramDuples[i] << "='" << paramDuples[i+1] << "'";                    \
            }                                                                                                        \
        }                                                                                                            \
        cstr << "}" << std::endl                                                                                     \
             <<   "## --> " << msg << std::endl                                                                      \
             <<   "## Stack: " << std::endl                                                                          \
             <<   "##     (no stack trace available -- see https://www.italiancpp.org/2017/01/27/spy-your-memory-usage-with-operator-new/)" << std::endl                                                   \
             <<   "## Caused by: Exception '....' ... https://en.cppreference.com/w/cpp/error/rethrow_if_nested" << std::endl; \
        return cstr.str();                                                                                           \
    }(exception, message, __PRETTY_FUNCTION__, {__VA_ARGS__});

#define DUMP_EXCEPTION(exception, message, ...)                                                \
    {                                                                                          \
        string exceptionDebugMsg = BUILD_EXCEPTION_DEBUG_MSG(exception, message, __VA_ARGS__); \
        std::cerr << exceptionDebugMsg << std::endl << std::flush;                             \
    }

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
        static  void                                                 add(SplitRun& instance);
        static  std::tuple<std::vector<string>, std::vector<string>> runAndWaitForAll();
        virtual void                                                 splitRun() = 0;
                void                                                 run();

    private:

        static void reset();

    };
}

#endif //MUTUA_TESTUTILS_SPLITRUN_H
