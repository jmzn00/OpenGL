#ifndef WINDOW_RESIZE_EVENT_H
#define WINDOW_RESIZE_EVENT_H

#include <cstdint>

namespace eng
{
	struct WindowResizeEvent
	{
		uint32_t Width;
		uint32_t Height;
	};
}
#endif // !WINDOW_RESIZE_EVENT_H
