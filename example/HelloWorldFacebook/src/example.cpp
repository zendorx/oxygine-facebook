#include "oxygine-framework.h"
#include "test.h"

#include "facebook.h"

using namespace oxygine;


//This contains our resources
//In a real project you would have more than one Resources declaration.
//It is important on mobile devices with limited memory and you would load/unload them
Resources resources;

//#define MULTIWINDOW 1

#if MULTIWINDOW
spStage stage2;
#endif

class TestActor : public Test
{
public:

    TestActor()
    {

        _x = 90;//getStage()->getWidth()/2.0f;
        _y = 80;


        addButton("login", "login");
    }

    void clicked(string id)
    {
        if (id == "login")
        {
        }
    }
};

void example_preinit()
{
}


void example_init()
{
    Test::init();

    Test::instance = new TestActor;
    getStage()->addChild(Test::instance);

    //Initialize http requests
    HttpRequestTask::init();

    facebook::init();
}

void example_update()
{
}

void example_destroy()
{
    resources.free();
    Test::free();
    HttpRequestTask::release();
    facebook::free();
}