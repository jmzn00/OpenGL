#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H
#include <GLFW/glfw3.h>
#include <eng/core//logger.h>
#include <eng/graphics/graphics_api.h>

namespace eng
{
	class EngineContext
	{	
	public:
		EngineContext(GLFWwindow* window, Logger& logger, GraphicsAPI& graphics)
			: m_window{ window }, m_logger { logger }
			, m_graphicsApi { graphics }
		{			
		}		
		GLFWwindow* GetWindow()
		{
			return m_window;
		}
		Logger& GetLogger() const
		{
			return m_logger;
		}
		GraphicsAPI& GetGraphicsAPI() const
		{
			return m_graphicsApi;
		}
	private:
		GLFWwindow* m_window;
		Logger& m_logger;
		GraphicsAPI& m_graphicsApi;
	};
}
#endif // !ENGINE_CONTEXT_H