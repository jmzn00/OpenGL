#ifndef APPLICATION_H
#define APPLICATION_H
#include "engine_context.h"
namespace eng
{
    class Application
    {
    public:
        virtual ~Application() = default;

        virtual bool Init(EngineContext& context) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Destroy() = 0;

        void SetNeedsToBeClosed(bool value);
        bool NeedsToBeClosed() const;

    private:
        bool m_needsToBeClosed = false;
    };
}

#endif // !APPLICATION_H
