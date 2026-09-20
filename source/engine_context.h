#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H
#include <GLFW/glfw3.h>

namespace eng
{
	class EngineContext
	{	
	public:
		EngineContext(GLFWwindow* window)
			: m_window{ window }
		{			
		}		
		GLFWwindow* GetWindow()
		{
			return m_window;
		}
	private:
		GLFWwindow* m_window;
	};
}
#endif // !ENGINE_CONTEXT_H