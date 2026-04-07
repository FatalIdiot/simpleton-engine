#pragma once

#include <iostream>

namespace Simpleton {
    class Logger {
        private:
            bool m_LogFile = false;

        public:        
            template<typename T>
            Logger& operator<<(const T& value)
            {
                std::cout << value;
                return *this;
            }
    };
}