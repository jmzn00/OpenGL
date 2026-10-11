#ifndef PROFILER_H
#define PROFILER_H

#include <chrono>
#include <string>
#include <unordered_map>
#include <vector>
#include <atomic>
#include <mutex>
#include <memory>

#include <optional>

namespace eng
{
	class Profiler
	{
	public:
		struct FrameSample
		{
			double FrameMs = 0.0;
			double CpuRenderMs = 0.0;
			double CpuUpdateMs = 0.0;
			double GpuMs = 0.0;

			uint32_t drawCalls = 0;
			uint32_t triangles = 0;
			
		};
		static Profiler& Get()
		{
			static Profiler instance;
			return instance;
		}
		void BeginFrame()
		{
			m_frameStart = Clock::now();

			m_drawCalls.store(0, std::memory_order_relaxed);
			m_triangles.store(0, std::memory_order_relaxed);
		}
		void EndFrame()
		{
			using namespace std::chrono;

			auto now = Clock::now();
			double frameMs = duration_cast<duration<double, std::milli>>(now - m_frameStart).count();

			FrameSample s;
			s.FrameMs = frameMs;
			s.CpuRenderMs = m_cpuRenderMs.exchange(0.0);
			s.CpuUpdateMs = m_cpuUpdateMs.exchange(0.0);
			s.GpuMs = m_gpuMs.exchange(0.0);
			s.drawCalls = m_drawCalls.load();
			s.triangles = m_triangles.load();

			std::lock_guard<std::mutex> lg(m_historyMutex);
			if (m_history.size() >= m_historySize)
				m_history.erase(m_history.begin());
			m_history.push_back(s);
		}		
		void IncrementDrawCalls(uint32_t n = 1) { m_drawCalls.fetch_add(n); }
		void AddTriangles(uint32_t n) { m_triangles.fetch_add(n); }

		const std::vector<FrameSample> GetHistory()
		{
			std::lock_guard<std::mutex> lg(m_historyMutex);

			return m_history;
		}
		const std::vector<FrameSample>& GetHistoryRef()
		{
			std::lock_guard<std::mutex> lg(m_historyMutex);
			return m_history;
		}
		std::optional<FrameSample> GetLatestSample()
		{
			std::lock_guard<std::mutex> lg(m_historyMutex);
			if (m_history.empty())
				return std::nullopt;
			return m_history.back();
		}
	private:
		using Clock = std::chrono::high_resolution_clock;
		Profiler() = default;

		std::chrono::time_point<Clock> m_frameStart;
		std::atomic<double> m_cpuRenderMs{ 0.0 };
		std::atomic<double> m_cpuUpdateMs{ 0.0 };
		std::atomic<double> m_gpuMs{0.0};
		std::atomic<uint32_t> m_drawCalls{ 0 };
		std::atomic<uint32_t> m_triangles{ 0 };

		std::mutex m_historyMutex;
		std::vector<FrameSample> m_history;
		size_t m_historySize{ 240 };
	};
}

#endif