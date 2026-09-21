#include <charconv>
#include <string_view>

namespace eng
{
	namespace util
	{
		inline bool ParseFloat(std::string_view text, float& value)
		{
			const char* begin = text.data();
			const char* end = begin + text.size();

			const auto [parsedEnd, error] =
				std::from_chars(begin, end, value);

			return error == std::errc{} && parsedEnd == end;
		}
		inline bool ParseInt(std::string_view text, int& value)
		{
			const char* begin = text.data();
			const char* end = begin + text.size();

			const auto [parsedEnd, error]
				= std::from_chars(begin, end, value);

			return error == std::errc{} && parsedEnd == end;
		}
		inline bool ParseBool(std::string_view text, bool& value)
		{
			if (text == "1" || text == "true")
			{
				value = true;
				return true;
			}
			if (text == "0" || text == "false")
			{
				value = false;
				return true;
			}
			return false;
		}
	}
}
