#ifndef APPLICATION_H
#define APPLICATION_H
#include "engine_context.h"
#include <vector>

#include <eng/core/layer_stack.h>
#include <eng/core/layer.h>
#include <eng/imgui/imgui_layer.h>

namespace eng
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        virtual bool Init(EngineContext& context) = 0;
        virtual void Update(float deltaTime);
        virtual void Destroy() = 0;

        void SetNeedsToBeClosed(bool value);
        bool NeedsToBeClosed() const;

		void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        static Application& Get();
    private:
        bool m_needsToBeClosed = false;  
    protected:
        LayerStack m_layerStack;
        ImGuiLayer* m_imguiLayer = nullptr;
        static Application* m_instance;
    };
}

#endif // !APPLICATION_H
