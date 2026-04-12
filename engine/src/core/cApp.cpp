#include "simpleton/core/cApp.hpp"
#include "../managers/cWindowManager.hpp"
#include "../util/cLog.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Simpleton {
    struct CApp::AppImpl {
        unsigned int engineTicks = 0;
        bool isRunning = true;
        
        cLogger logger;
    };

    CApp::CApp() {};
    CApp::~CApp() {};

    void CApp::OnInit() {
        mpInternal->logger << "Engine Init...\n";
        mWindowManager = std::make_unique<CWindowManager>();
        mWindowManager->OnInit();



        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            mpInternal->logger << "Failed to create GLFW window.\n";
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            mpInternal->logger << "Failed to initialize GLAD.\n";
            return;
        }   

        glViewport(0, 0, 800, 600);
    };

    void CApp::OnDestroy() {
        mpInternal->logger << "Engine Destroy...\n";
        mWindowManager->OnDestroy();
    };

    void CApp::OnUpdate() {
        mpInternal->engineTicks++;
    }

    void CApp::Shutdown() {
        mpInternal->logger << "Shutting engine down...\n";
        mpInternal->isRunning = false;
        mIsRunning = false;
    }

    void CApp::Restart() {
        mpInternal->logger << "Restarting engine...\n";
        mpInternal->isRunning = false;
    }

    void CApp::Run() {
        // External loop - used to restart engine without killing the process
        while(mIsRunning) {
            // Allocate engine internals
            mpInternal = std::make_unique<AppImpl>();

            CApp::OnInit();
            OnInit();
            for(int i = 0; i < 10; i++) {
                mpInternal->logger << mpInternal->engineTicks << " ticks" << "\n";
                CApp::OnUpdate();
                OnUpdate();
            }

            // Flag engine exit here for now
            Shutdown();
            
            OnDestroy();
            CApp::OnDestroy();
        }
    }
}