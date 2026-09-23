#ifndef TIME_H
#define TIME_H
#include <chrono>
namespace eng
{
	class Time
	{
	public:
		Time()
		{
		
		}
		void Reset()
		{
			m_start = m_prev = Clock::now();
			m_delta = 0.0f;
			m_elapsed = 0.0f;
		}
		void Update()
		{
			const auto now = Clock::now();
			std::chrono::duration<float> dt = now - m_prev;
			m_delta = dt.count();
			m_prev = now;
			m_elapsed = std::chrono::duration<float>(now - m_start).count();
		}
		float Delta() const { return m_delta; }
		float Elapsed() const { return m_elapsed; }
	private:
		using Clock = std::chrono::high_resolution_clock;
		Clock::time_point m_start;
		Clock::time_point m_prev;
		float m_delta{ 0.0f };
		float m_elapsed{ 0.0f };
	};
}
#endif // !TIME_H
