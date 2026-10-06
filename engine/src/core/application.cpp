#include <eng/core/application.h>
#include <iostream>
#include <eng/debug/assert.h>
namespace eng
{
	void Application::SetNeedsToBeClosed(bool value)
	{
		m_needsToBeClosed = value;
	}
	bool Application::NeedsToBeClosed() const
	{
		return m_needsToBeClosed;
	}
	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	void Application::Update(float dt)
	{
		for (Layer* layer : m_layerStack)
		{
			layer->Update(dt);
		}
		m_imguiLayer->Begin();
		for (Layer* layer : m_layerStack)
		{
			layer->OnImGuiRender();
		}
		m_imguiLayer->End();
	}
	Application::Application()
	{		
		ENG_ASSERT(m_instance == nullptr, "Application already exists");

		m_instance = this;
	}
	Application& Application::Get()
	{		
		return *m_instance;
	}
	Application* Application::m_instance = nullptr;
}