#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <functional>
#include <vector>

namespace eng
{
	template<typename TEvent>
	class Event
	{
	public:
		using Listner = std::function<void(const TEvent&)>;

		void Subscribe(Listner listner)
		{
			m_listners.push_back(std::move(listner));
		}
		void Publish(const TEvent& event)
		{
			for (auto& listner : m_listners)
			{
				listner(event);
			}
		}
	private:
		std::vector<Listner> m_listners;
	};
}
#endif // !EVENT_BUS_H
