#ifndef ENTITY_COMPONENT_REGISTRY
#define ENTITY_COMPONENT_REGISTRY

#include <string>
#include <eng/entity/entity.h>
#include <eng/entity/components.h>
#include "editor_context.h"

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace eng
{
	struct ComponentEditor
	{
		std::string id;
		std::string label;

		std::function<bool(const Entity&)> has;
		std::function<void(Entity&)> add;
		std::function<void(Entity&)> remove;
		std::function<void(Entity&, EditorContext& context)> draw;

	};
	class EntityComponentRegistry
	{
	public:
		void Init()
		{

		}
		template<typename T>
		void Register(
			std::string id,
			std::string label,
			std::function<void(Entity&)> create,
			std::function<void(T&, EditorContext&)> draw)
		{
			ComponentEditor entry;
			entry.id = std::move(id);
			entry.label = std::move(label);

			entry.has = [](const Entity& ent)
			{
				return ent.HasComponent<T>();
			};
			entry.add = [create = std::move(create)](Entity& ent)
			{
				if (!ent.HasComponent<T>())
					create(ent);
			};
			entry.remove = [](Entity& ent)
			{
				ent.RemoveComponent<T>();
			};
			entry.draw = [draw = std::move(draw)](
				Entity& ent, EditorContext& context)
			{
				draw(ent.GetComponent<T>(), context);
			};
			Register(std::move(entry));
		}
		void Register(ComponentEditor entry)
		{
			for (const auto& e : m_entries)
			{
				if (e.id == entry.id)
					throw std::logic_error("DUPLICATE COMPONENT EDITOR: " + entry.id);
			}
			m_entries.push_back(std::move(entry));
		}
		const std::vector<ComponentEditor>& Entries() const
		{
			return m_entries;
		}
	private:
		std::vector<ComponentEditor> m_entries;
	};
}
#endif // !ENTITY_COMPONENT_REGISTRY
