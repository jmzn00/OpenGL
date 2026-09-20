#include "log/log.h"
#include "editor/tools/editor_component.h"
#include <vector>

namespace eng
{
#ifndef CONSOLE_H
#define CONSOLE_H
	class Console : public IEditorComponent, public ILogSink
	{
	public:
		bool Init(EngineContext& ctx) override;
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override;

		void Write(const Message& message) override;
	private:
		std::vector<Message> m_messages;
		char m_input[256] = {};
		bool m_scroll_to_bottom = false;
	};
#endif // !CONSOLE_H


}
