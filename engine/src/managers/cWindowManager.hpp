#pragma once

#include "../util/cLog.hpp"
#include "../core/cDependencyResolver.hpp"

#include "./iManagerInternal.hpp"
#include "simpleton/managers/iWindowManager.hpp"

#include "simpleton/util/primitives/point.hpp"
#include "simpleton/util/primitives/triangle.hpp"
#include "simpleton/util/primitives/rect.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton
{
    class CWindowManager : public IWindowManager, public IManagerInternal
    {
        public:
            CWindowManager() {};
            ~CWindowManager() {};

            bool OnInit(unsigned int wWidth, unsigned int wHeight, std::string windowName, std::shared_ptr<CDependencyResolver> depResolver);
            void OnDestroy();

            GLFWwindow* GetWindow();
            Point<unsigned int> GetWindowSize();

            Point<float> CastWindowToScreen(Point<unsigned int> point);
            Triangle<float> CastWindowToScreen(Triangle<unsigned int> triangle);
            Rect<float> CastWindowToScreen(Rect<unsigned int> rect);

        private:
            unsigned int mWidth, mHeight;

            std::shared_ptr<CLogger> mpLogger;
            GLFWwindow *mWindow;
    };
}