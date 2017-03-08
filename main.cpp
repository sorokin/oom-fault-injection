#include <dlfcn.h>

thread_local void* malloc_next;
thread_local size_t next_oom_alloc = -1;

extern "C" void set_oom_malloc(size_t val)
{
    next_oom_alloc = val;
}

extern "C" void* malloc(size_t n)
{
    if (!malloc_next)
        malloc_next = dlsym(RTLD_NEXT, "malloc");

    if (next_oom_alloc == 0)
        return nullptr;

    --next_oom_alloc;

    return ((void* (*)(size_t))malloc_next)(n);
}
