#include <eng/core/application.h>
#include <eng/command/commands/application_quit_command.h>

namespace eng
{
	void Application::SetNeedsToBeClosed(bool value)
	{
		m_needsToBeClosed = value;
	}
	bool Application::NeedsToBeClosed() const
	{
		return m_needsToBeClosed;
	}
}