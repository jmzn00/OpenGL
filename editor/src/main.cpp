#include <eng/core/engine.h>
#include "editor.h"

int main()
{
    eng::Engine engine{};

    engine.SetApplication(std::make_unique<eng::Editor>());

    if (engine.Init(960, 540))
    {        
        engine.Run();
    }    

    engine.Destroy();
    return 0;
}