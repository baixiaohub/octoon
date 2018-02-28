#include <octoon/circle_collider2d_component.h>
#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(CircleCollider2D, GameComponent, "CircleCollider2D")

    CircleCollider2D::CircleCollider2D() noexcept
    {

    }

    CircleCollider2D::~CircleCollider2D()
    {

    }

    GameComponentPtr CircleCollider2D::clone() const noexcept
    {
        return std::make_shared<CircleCollider2D>();
    }

    void CircleCollider2D::set_radius(float r) noexcept
    {
        radius = r;
    }
    float CircleCollider2D::get_radius() const noexcept
    {
        return radius;
    }


    void CircleCollider2D::on_collision_change() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;
        
        b2CircleShape shape_def;
        shape_def.m_p = b2Vec2(rigid_body->get_position().x, rigid_body->get_position().y);
        shape_def.m_radius = this->get_radius();

        b2FixtureDef fixture_def;
        fixture_def.shape = &shape_def;
        
        rigid_body->body->DestroyFixture(collider);
        collider = rigid_body->body->CreateFixture(&fixture_def);
    }
    void CircleCollider2D::on_collision_enter() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;
        
        b2CircleShape shape_def;
        shape_def.m_p = b2Vec2(rigid_body->get_position().x, rigid_body->get_position().y);
        shape_def.m_radius = this->get_radius();

        b2FixtureDef fixture_def;
        fixture_def.shape = &shape_def;
        
        collider = rigid_body->body->CreateFixture(&fixture_def);

    }
    void CircleCollider2D::on_collision_exit() noexcept
    {
        auto rigid_body = get_component<Rigidbody2D>();
        if (!rigid_body)
            return;

        rigid_body->body->DestroyFixture(collider);
    }
    void CircleCollider2D::on_collision_stay() noexcept
    {

    }
}