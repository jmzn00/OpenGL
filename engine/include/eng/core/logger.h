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
	private:
		std::vector<ILogSink*> m_sinks;
	};
#endif // !LOGGER_H
}

