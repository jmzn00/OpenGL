#include <eng/core/engine_context.h>
namespace eng
{
#ifndef EDITOR_COMPONENT_H
#define EDITOR_COMPONENT_H
	class IEditorComponent
	{
	public:
		virtual ~IEditorComponent() = default;

		virtual bool Init(EngineContext& ctx) = 0;
		virtual void Update(float dt){}
		virtual void Draw() = 0;
		virtual void Destroy() {}
	};
#endif // !EDITOR_COMPONENT_H

}