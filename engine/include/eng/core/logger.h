#include <eng/core/log.h>
#include <vector>
namespace eng
{
#ifndef LOGGER_H
#define LOGGER_H
	class Logger
	{
	public:
		void AddSink(ILogSink& sink);
		void RemoveSink(ILogSink& sink);

		void Info(std::string text);
		void Warning(std::string text);
		void Error(std::string text);

		void Write(const Message& message);

		const std::vector<Message>& GetMessageHistory() const;
	private:
		std::vector<ILogSink*> m_sinks;
		std::vector<Message> m_messageHistory;
	};
#endif // !LOGGER_H
}

