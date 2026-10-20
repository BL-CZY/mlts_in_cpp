#pragma once

#ifdef DEBUG
#define debug(a)                                                               \
    do {                                                                       \
        std::cerr << "[Debug]: " << __FILE__ << ":" << __LINE__ << ": " << a   \
                  << '\n';                                                     \
    } while (false)
#else
#define debug(...)
#endif
