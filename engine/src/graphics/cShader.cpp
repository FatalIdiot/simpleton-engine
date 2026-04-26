// #include "./cShader.hpp"

// #include <iostream>
// #include <fstream>
// #include <sstream>

// #include "glad/glad.h"

// namespace Simpleton {
//     CShader::CShader() {
//         mVertexShader = glCreateShader(GL_VERTEX_SHADER);
//         mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//         mShaderProgId = glCreateProgram();

//         mIsValid = false;
//     }

//     CShader::~CShader() {
//         Terminate();
//     }

//     bool CShader::CheckShaderValid(ShaderType type) {
//         unsigned int shader = (type == ShaderType::VertexShader ? mVertexShader : mFragmentShader);

//         int success;
//         glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &success);
//         if(!success) {
//             return false;
//         }
//         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//         if(!success) {
//             return false;
//         }

//         return true;
//     }

//     bool CShader::CheckProgramValid() {
//         return mIsValid;
//     }

//     bool CShader::AddShaderSource(ShaderType type, const char* code) {
//         int success;
//         unsigned int shader = (type == ShaderType::VertexShader ? mVertexShader : mFragmentShader);

//         glShaderSource(shader, 1, &code, 0);
//         glCompileShader(shader);
//         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//         if(!success)
//         {
//             glGetShaderInfoLog(shader, 512, 0, mErrorLog);
//             return false;
//         }

//         return true;
//     }

//     bool CShader::AddShaderFile(ShaderType type, fs::path filePath) {
//         std::ifstream file(filePath);
//         if (!file.is_open()) {
//             return false;
//         }

//         std::stringstream buffer;
//         buffer << file.rdbuf();

//         file.close();

//         return AddShaderSource(type, buffer.str().c_str());
//     }

//     bool CShader::Compile() {
//         int success;

//         // Check both shaders for validity 
//         if(!CheckShaderValid(ShaderType::VertexShader)) {
//             return false;
//         }
//         if(!CheckShaderValid(ShaderType::FragmentShader)) {
//             return false;
//         }

//         glAttachShader(mShaderProgId, mVertexShader);
//         glAttachShader(mShaderProgId, mFragmentShader);
//         glLinkProgram(mShaderProgId);
//         glGetProgramiv(mShaderProgId, GL_LINK_STATUS, &success);
//         if(!success) {
//             mIsValid = false;
//             glGetProgramInfoLog(mShaderProgId, 512, 0, mErrorLog);
//             return false;
//         }

//         mIsValid = true;
//         return true;
//     }

//     void CShader::SetUniform(const char* name, float x, float y, float z, float w) {
//         int uniformLocation = glGetUniformLocation(mShaderProgId, name);
//         glUniform4f(uniformLocation, x, y, z, w);
//     }

//     void CShader::SetUniform(const char* name, int i) {
//         int uniformLocation = glGetUniformLocation(mShaderProgId, name);
//         glUniform1i(uniformLocation, i);
//     }

//     void CShader::Bind() const {
//         glUseProgram(mShaderProgId);
//     }

//     void CShader::Unbind() const {
//         glUseProgram(0);
//     }

//     void CShader::Terminate() {
//         glDeleteShader(mVertexShader);
//         glDeleteShader(mFragmentShader);

//         int currentShaderProg;
//         glGetIntegerv(GL_CURRENT_PROGRAM, &currentShaderProg);
//         if(currentShaderProg == mShaderProgId)
//             Unbind();
//         glDeleteProgram(mShaderProgId);
//     }
// }