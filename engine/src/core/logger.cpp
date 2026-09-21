#include <eng/core/logger.h>
#include <typeinfo>
namespace eng
{
	void Logger::AddSink(ILogSink& sink)
	{
		m_sinks.push_back(&sink);

		std::string message{ "[Logger] Added sink: " };
		message += typeid(sink).name();

		Info(message);
	}
	void Logger::RemoveSink(ILogSink& sink)
	{
		m_sinks.erase(
			std::remove(m_sinks.begin(), m_sinks.end(), &sink),
			m_sinks.end()
		);

		std::string message{ "[Logger] Removed sink: " };
		message += typeid(sink).name();

		Info(message);
	}
	void Logger::Info(std::string text)
	{
		Write({ Level::Info, std::move(text) });
	}
	void Logger::Warning(std::string text)
	{
		Write({ Level::Warning, std::move(text) });
	}
	void Logger::Error(std::string text)
	{
		Write({ Level::Error, std::move(text) });
	}
	void Logger::Write(const Message& message)
	{
		for (ILogSink* sink : m_sinks)
		{
			sink->Write(message);
		}
	}
}