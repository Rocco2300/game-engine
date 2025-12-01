#pragma once

#include "light.hpp"
#include "shader.hpp"
#include "fps_camera.hpp"

#include <glm/mat4x4.hpp>

class Texture;
class Material;

class Program {
public:
    Program();
    ~Program();

    void attachShader(Shader shader);
    void link();
    void use() const;

    void setUniformInt(const std::string& name, int value) const;
    void setUniformBool(const std::string& name, bool value) const;
    void setUniformFloat(const std::string& name, float value) const;

    void setUniformVec3(const std::string& name, const glm::vec3& value) const;
    void setUniformMat4(const std::string& name, const glm::mat4& value) const;

    void setUniformLight(const Light& light) const;
    void setUniformCamera(const FPSCamera& camera) const;
    void setUniformTexture(const std::string& name, const Texture& texture) const;
    void setUniformMaterial(const Material& material) const;

private:
    uint32_t m_id{};
};