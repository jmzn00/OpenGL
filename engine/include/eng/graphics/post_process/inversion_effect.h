#ifndef INVERSION_EFFECT_H
#define INVERSION_EFFECT_H

#include <eng/graphics/post_process/post_process_effect.h>
#include <eng/graphics/shader_program.h>

#include <memory>

namespace eng
{
	class InversionEffect : public PostProcessEffect
	{
	public:
		const char* Name() const override
		{
			return "inversion";
		}
		void Init() override
		{
			m_shader = std::make_unique<ShaderProgram>(
				ENGINE_ASSET_DIR "/shaders/post_process/copy.vert",
				ENGINE_ASSET_DIR "/shaders/post_process/inversion.frag");
		}
		void Render(
			GraphicsAPI& graphics,
			PostProcessDraw& draw,
			GLuint inputTexture,
			Framebuffer& output) override
		{
			draw.Draw(graphics, *m_shader, inputTexture, output);
		}
	private:
		std::unique_ptr<ShaderProgram> m_shader;
	};
}

#endif // !INVERSION_EFFECT_H
