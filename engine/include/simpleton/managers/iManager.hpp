// Base class for future managers implementation
#pragma once

namespace Simpleton {
    class IManager {
        public:
            virtual ~IManager() = default;

            virtual bool OnInit() = 0;
            virtual void OnDestroy() = 0;
    };
}