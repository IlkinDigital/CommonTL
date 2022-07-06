#pragma once

#ifndef CTL_CONFIG_DISTRIBUTION
#include <iostream>

#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif