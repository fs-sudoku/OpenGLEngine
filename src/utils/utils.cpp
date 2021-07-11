#include <stdio.h>
#include <string.h>
#include <memory\memory.h>

#include "utils.h"

void utils::print_at_console(const cstr& message)
{
	std::puts(message.c_str());
}