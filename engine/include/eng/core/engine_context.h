#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H
#include <GLFW/glfw3.h>
#include <eng/core//logger.h>
#include <eng/graphics/graphics_api.h>
#include <eng/input/input.h>

namespace eng
{
	class EngineContext
	{	
	public:
		EngineContext(GLFWwindow* window, Logger& logger, GraphicsAPI& graphics, Input& input)
			: m_window{ window }, m_logger { logger }
			, m_graphicsApi { graphics }, m_input { input }
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
		Input& GetInput() const
		{
			return m_input;
		}
	private:
		GLFWwindow* m_window;
		Logger& m_logger;
		GraphicsAPI& m_graphicsApi;
		Input& m_input;
	};
}
#endif // !ENGINE_CONTEXT_H