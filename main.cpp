#include <iostream>
#include "engine.h"
#include "editor/editor.h"

int main()
{
    eng::Engine& engine = eng::Engine::GetInstance();       
    eng::Editor* editor = new eng::Editor{};
    engine.SetApplication(editor);

    if (engine.Init(960, 540))
    {        
        engine.Run();
    }    
    engine.Destroy();
    return 0;
}