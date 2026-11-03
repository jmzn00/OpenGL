#ifndef POST_PROCESS_EFFECT_H
#define POST_PROCESS_EFFECT_H

#include <glad/glad.h>
#include <eng/graphics/graphics_api.h>
#include <eng/graphics/framebuffer.h>
#include <eng/graphics/post_process/post_process_draw.h>
#include <cstdint>

namespace eng
{	
	class PostProcessEffect
	{	
	public:
		virtual~PostProcessEffect() = default;

		virtual const char* Name() const = 0;
		virtual void Init() {}

		virtual void Render(
			GraphicsAPI& graphics,
			PostProcessDraw& draw,
			GLuint inputTexture,
			Framebuffer& output) = 0;

		bool IsEnabled() const
		{
			return m_enabled;
		}
		void SetEnabled(bool enabled)
		{
			m_enabled = enabled;
		}
	private:
		bool m_enabled = true;

	};
}
#endif // !POST_PROCESS_EFFECT_H
