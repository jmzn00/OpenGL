#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H
#include <GLFW/glfw3.h>
#include <eng/core//logger.h>

namespace eng
{
	class EngineContext
	{	
	public:
		EngineContext(GLFWwindow* window, Logger& logger)
			: m_window{ window }, m_logger { logger }
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
	private:
		GLFWwindow* m_window;
		Logger& m_logger;
	};
}
#endif // !ENGINE_CONTEXT_H