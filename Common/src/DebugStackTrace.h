////////////////////////////////////////////////////////////////////////////////
// File:        DebugStackTrace.h
// Author:      Bohumil Homola
// Date:        01/13/2024
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include <cpptrace/cpptrace.hpp>
#include <csignal>
#include <cstdio>
#include <cstring>

namespace Backtrace
{
static void handler(int signo, siginfo_t *info, void *context)
{
    cpptrace::generate_trace(2).print();
    _exit(1);
}

static void SetupBacktrace()
{
    struct sigaction action = {0};
    action.sa_flags = 0;
    action.sa_sigaction = &handler;
    if (sigaction(SIGSEGV, &action, NULL) == -1)
    {
        perror("sigaction");
    }
}

static void PrintBacktrace(std::size_t skip)
{
    cpptrace::generate_trace(skip).print();
}

} // namespace Backtrace
