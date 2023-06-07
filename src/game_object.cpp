#include "game_object.hpp"

GameObject::GameObject(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size,
                       const glm::vec2 velocity, const glm::vec3 color, float rotation)
    : m_texture(texture)
    , m_position(position)
    , m_size(size)
    , m_velocity(velocity)
    , m_color(color)
    , m_rotation(rotation)
{
}

GameObject::~GameObject()
{
}

void GameObject::render(Renderer &renderer)
{
    renderer.render_sprite(m_texture, m_position, m_size, m_color, m_rotation);
}

Texture GameObject::texture() const
{
    return m_texture;
}

void GameObject::setTexture(const Texture &texture)
{
    m_texture = texture;
}

glm::vec2 GameObject::position() const
{
    return m_position;
}

void GameObject::setPosition(const glm::vec2 &position)
{
    m_position = position;
}

glm::vec2 GameObject::size() const
{
    return m_size;
}

void GameObject::setSize(const glm::vec2 &size)
{
    m_size = size;
}

glm::vec2 GameObject::velocity() const
{
    return m_velocity;
}

void GameObject::setVelocity(const glm::vec2 &velocity)
{
    m_velocity = velocity;
}

glm::vec3 GameObject::color() const
{
    return m_color;
}

void GameObject::setColor(const glm::vec3 &color)
{
    m_color = color;
}

float GameObject::rotation() const
{
    return m_rotation;
}

void GameObject::setRotation(float rotation)
{
    m_rotation = rotation;
}
