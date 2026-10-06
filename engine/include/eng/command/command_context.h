#pragma once

namespace eng
{
    class Logger;
    class Scene;

    struct CommandContext
    {
        CommandContext(Logger& logger, Scene& scene)
            : logger(logger), scene(scene)
        {
        }

        Logger& logger;
        Scene& scene;
    };
}