#ifndef POST_PROCESS_PASS_H
#define POST_PROCESS_PASS_H

#include <eng/renderer/render_pass.h>
#include <eng/graphics/shader_program.h>
#include <eng/graphics/graphics_api.h>
#include <eng/renderer/mesh.h>
#include <eng/graphics/framebuffer.h>
#include <eng/graphics/post_process/post_process_draw.h>

#include <memory>
#include <vector>
#include <utility>
#include <type_traits>
#include <string>

#include <eng/graphics/post_process/post_process_effect.h>
#include <eng/graphics/post_process/inversion_effect.h>
#include <eng/graphics/post_process/grayscale_effect.h>
#include <eng/graphics/post_process/kernel_effect.h>

namespace eng
{
	class PostProcessPass : public RenderPass
	{
	public:
        const char* Name() const override
        {
            return "PostProcess";
        }
		RenderStage Stage() const override { return RenderStage::PostProcess; }

		void Init() override
		{
			m_draw.Init();
            m_copyShader = std::make_unique<ShaderProgram>
				(ENGINE_ASSET_DIR "/shaders/post_process/copy.vert",
                ENGINE_ASSET_DIR "/shaders/post_process/copy.frag");            

            AddEffect<InversionEffect>();         
            AddEffect<GrayscaleEffect>();
            AddEffect<KernelEffect>();

		}
        template<typename T, typename... Args>
        T& AddEffect(Args&&... args)
        {
            static_assert(
                std::is_base_of_v<PostProcessEffect, T>,
                "T must derive from PostProcessEffect");

            auto effect = std::make_unique<T>(
                std::forward<Args>(args)...);
			effect->Init();

            T& ref = *effect;

            m_effects.push_back(std::move(effect));
            return ref;
        }

		void Execute(RenderContext& context) override
		{
            GLuint input = context.sceneTarget.GetColorTexture();

            std::vector<PostProcessEffect*> enabled;
            for (auto& effect : m_effects)
            {
                if (effect->IsEnabled())
                    enabled.push_back(effect.get());
            }
            if (enabled.empty())
            {
				m_draw.Draw(context.graphicsAPI, *m_copyShader, input, context.outputTarget);
                return;
            }

			const uint32_t width = context.outputTarget.GetWidth();
			const uint32_t height = context.outputTarget.GetHeight();
			auto ensureTargetSize = [width, height](Framebuffer& target)
            {
				if (target.GetID() == 0)
					return target.Create(width, height);
				return target.Resize(width, height);
			};
			if (enabled.size() > 1 &&
				(!ensureTargetSize(m_framebufferA) || !ensureTargetSize(m_framebufferB)))
				return;
            Framebuffer* intermediate[] = { &m_framebufferA, &m_framebufferB };
            int nextBuffer = 0;

            for (size_t i = 0; i < enabled.size(); ++i)
            {
                const bool isLast = i == enabled.size() - 1;
                Framebuffer& output = isLast
                    ? context.outputTarget
                    : *intermediate[nextBuffer];

				enabled[i]->Render(context.graphicsAPI, m_draw, input, output);

                input = output.GetColorTexture();

                if (!isLast)
                    nextBuffer = 1 - nextBuffer;
            }
		}
        bool ToggleEffect(const std::string& name, bool value)
        {
            bool exists = false;

            for (auto& effect : m_effects)
            {
                if (effect->Name() == name)
                {
                    effect->SetEnabled(value);
                    exists = true;
                }
            }            
            return exists;
        }
        bool IsActive(const std::string& name)
        {
            bool exists = false;

            for (auto& effect : m_effects)
            {
                if (effect->Name() == name)
                {
                    return effect->IsEnabled();
                }
            }
            if (!exists)
                return false;            
        }
	private:
        std::vector<std::unique_ptr<PostProcessEffect>> m_effects;

		std::unique_ptr<ShaderProgram> m_copyShader;
		PostProcessDraw m_draw;

        Framebuffer m_framebufferA;
        Framebuffer m_framebufferB;
	};	
}
#endif // !POST_PROCESS_PASS_H
