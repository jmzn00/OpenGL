#include <eng/graphics/graphics_api.h>
#include <eng/graphics/shader_program.h>
#include <iostream>

namespace eng
{
	bool GraphicsAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);

		return true;
	}
	void GraphicsAPI::EnableTest(GLenum test)
	{
		glEnable(test);
	}
	void GraphicsAPI::DisableTest(GLenum test)
	{
		glDisable(test);
	}
	void GraphicsAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void GraphicsAPI::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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
	// func: can be GL_NEVER, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL, GL_ALWAYS
	// ref: specifies the reference value for the stencil test, stencil buffers value is compared to this
	// mask: specifies a mask that is ANDed with both ref and stored stencil value
	void GraphicsAPI::SetStencilFunc(GLenum func, GLint ref, GLuint mask)
	{
		glStencilFunc(func, ref, mask);
	}
	// what happens to the buffer on pass / fail
	// GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR, GL_DECR_WRAP, GL_INVERT
	void GraphicsAPI::SetStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass)
	{
		glStencilOp(sfail, dpfail, dppass);
	}
	// 0xFF enables writes | 0x00 disables writes
	void GraphicsAPI::SetStencilMask(GLuint mask)
	{
		glStencilMask(mask);
	}
	void GraphicsAPI::SetColorMask(GLenum a, GLenum b, GLenum c, GLenum d)
	{
		glColorMask(a, b, c, d);
	}
}
