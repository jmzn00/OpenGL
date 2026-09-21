#include <eng/graphics/graphics_api.h>
#include <eng/graphics/shader_program.h>
#include <iostream>

namespace eng
{
	bool GraphicsAPI::Init()
	{
		
		return true;
	}
	void GraphicsAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void GraphicsAPI::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void GraphicsAPI::BindShaderProgram(ShaderProgram* program)
	{
		glUseProgram(program ? program->GetId() : 0);
	}
	void GraphicsAPI::ToggleWireframe(bool isWireframe)
	{
		if (isWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}
