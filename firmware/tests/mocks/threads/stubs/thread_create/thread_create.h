#pragma once

#include "thread_create/i_thread_create.h"
#include <array>
#include <cstdint>

namespace threads
{

class ThreadCreate : public IThreadCreate
{
public:
  ThreadCreate(uint32_t* stack, size_t stack_size, void (*task)(uint32_t)) {}
};

}
