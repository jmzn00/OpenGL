#ifndef PROFILER_PANEL_H
#define PROFILER_PANEL_H

#include <eng/core/engine_context.h>
#include <editor_component.h>
#include "editor_context.h"

#include <eng/profiler/profiler.h>


namespace eng
{
	class ProfilerPanel : public IEditorComponent
	{
	public:
		ProfilerPanel();
		bool Init(EngineContext& engineContext) override;
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override;
	};
}
#endif // !PROFILER_PANEL_H
