#include <gmock/gmock.h>
#include <ontology/Ontology.hpp>

#include <math.h>

#define NAME Stress

using namespace Ontology;

// ----------------------------------------------------------------------------
// test fixture
// ----------------------------------------------------------------------------

struct Position : public Component
{
    Position(int x, int y) : x(x), y(y) {}
    unsigned int x, y;
};
inline bool operator==(const Position& lhs, const Position rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

struct Movement : public System
{
    void initialise() override {}
    void processEntity(Entity& e) override
    {
        for(volatile int i = 0; i != 100; ++i)
            float f = sqrt(953.245);
        e.getComponent<Position>().x += 2;
        e.getComponent<Position>().y += 1;
    }
    void configureEntity(Entity&, std::string param="") override {}
};

// ----------------------------------------------------------------------------
// tests
// ----------------------------------------------------------------------------

TEST(NAME, ThousandEntities)
{
    World world;
    world.getSystemManager()
        .addSystem<Movement>();
    world.getSystemManager().initialise();

    for(int i = 0; i != 1000; ++i)
        world.getEntityManager().createEntity("entity")
            .addComponent<Position>(0, 0)
            ;
    for(int i = 0; i != 10000; ++i)
        world.update();

    for(auto& entity : world.getEntityManager().getEntityList())
    {
        ASSERT_EQ(Position(20000, 10000), entity.getComponent<Position>());
    }
}
