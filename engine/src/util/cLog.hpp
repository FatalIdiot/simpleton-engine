#pragma once

#include <iostream>

namespace Simpleton {
    class CLogger {
        public:        
            template<typename T>
            CLogger& operator<<(const T& value)
            {
                std::cout << value;
                return *this;
            }
    };
}