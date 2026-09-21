#ifndef LOG_H
#define LOG_H
#include <string>
namespace eng
{
	enum class Level
	{
		Info,
		Warning,
		Error
	};
	struct Message
	{
		Level level;
		std::string text;
	};
	//void Inf(const std::string& text);
	//void War(const std::string& text);
	//void Err(const std::string& text);
	class ILogSink
	{
	public:
		virtual ~ILogSink() = default;
		virtual void Write(const Message& message) = 0;
	};

}
#endif // !LOG_H

