#pragma once

#include <iostream>

namespace Simpleton {
    class cLogger {
        private:
            bool m_LogFile = false;

        public:        
            template<typename T>
            cLogger& operator<<(const T& value)
            {
                std::cout << value;
                return *this;
            }
    };
}