#include <eng/core/log.h>
#include <eng/core/engine_context.h>
#include "editor_component.h"
#include <vector>

#include <eng/command/command_context.h>
#include <eng/command/command_registry.h>

namespace eng
{
#ifndef CONSOLE_H
#define CONSOLE_H
	class Console : public IEditorComponent, public ILogSink
	{
	public:
		Console(CommandRegistry& commands, CommandContext& commandContext);
		bool Init(EngineContext& ctx) override;
		void Update(float dt) override;
		void Draw() override;
		void Destroy() override;

		void Write(const Message& message) override;
	private:
		CommandRegistry& m_commands;
		CommandContext& m_commandContext;

		Logger* m_logger = nullptr;
		std::vector<Message> m_messages;
		char m_input[256] = {};
		bool m_scroll_to_bottom = false;
	};
#endif // !CONSOLE_H


}
