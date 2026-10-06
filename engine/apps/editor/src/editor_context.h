#ifndef EDITOR_CONTEXT_H
#define EDITOR_CONTEXT_H
#include <eng/graphics/shader_library.h>
#include <eng/renderer/mesh_library.h>
namespace eng
{
	class EditorContext
	{
	public:
		EditorContext(ShaderLibrary& shaderLibrary)
			: m_shaderLibrary {shaderLibrary}
		{		
		}
		ShaderLibrary& GetShaderLibrary() const
		{
			return m_shaderLibrary;
		}
	private:
		ShaderLibrary& m_shaderLibrary;
	};
}
#endif // !EDITOR_CONTEXT_H
