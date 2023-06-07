#pragma once

#include <glm/glm.hpp>
#include "renderer.hpp"
#include "texture.hpp"

class GameObject
{
public:
    GameObject() = default;
    GameObject(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size,
               const glm::vec2 velocity, const glm::vec3 color, float rotation);
    ~GameObject();

    void render(Renderer &renderer);

    Texture texture() const;
    void setTexture(const Texture &texture);

    glm::vec2 position() const;
    void setPosition(const glm::vec2 &position);

    glm::vec2 size() const;
    void setSize(const glm::vec2 &size);

    glm::vec2 velocity() const;
    void setVelocity(const glm::vec2 &velocity);

    glm::vec3 color() const;
    void setColor(const glm::vec3 &newColor);

    float rotation() const;
    void setRotation(float rotation);

private:
    Texture m_texture;

    glm::vec2 m_position = { 0.0f, 0.0f };
    glm::vec2 m_size = { 0.0f, 0.0f };
    glm::vec2 m_velocity = { 0.0f, 0.0f };
    glm::vec3 m_color = { 1.0f, 1.0f, 1.0f };

    float m_rotation = 0.0f;
};
