#ifndef EDITOR_CONTEXT_H
#define EDITOR_CONTEXT_H

#include <cstdint>
#include <eng/command/command_executor.h>
#include <eng/scene/scene.h>

namespace eng
{
	class EditorContext
	{
	public:
		EditorContext(CommandExecutor& commandExecutor, Scene& scene)
			: m_commandExecutor {commandExecutor}, m_currentScene {scene}
		{
		}		

		void SetSelectedEntityId(std::uint32_t entityId)
		{
			m_selectedEntityId = entityId;
		}
		std::uint32_t GetSelectedEntityId() const
		{
			return m_selectedEntityId;
		}
		CommandExecutor& GetCommandExecutor() const
		{
			return m_commandExecutor;
		}
		Scene& GetCurrentScene() const
		{
			return m_currentScene;
		}
	private:
		std::uint32_t m_selectedEntityId{};
		CommandExecutor& m_commandExecutor;
		Scene& m_currentScene;
	};
}
#endif // !EDITOR_CONTEXT_H
