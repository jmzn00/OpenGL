#ifndef ENTITY_H
#define ENTITY_H

#include <glm.hpp>
#include <eng/entity/components.h>
#include <unordered_map>
#include <typeindex>
#include <string>
namespace eng
{
	class Entity
	{
	public:	
		Entity(const std::string& name = "Unnamed")
			: m_name {name}
		{		
		}
		TransformComponent& Transform() { return m_transform; }

		template<typename T, typename ... Args>
		T& AddComponent(Args&&... args)
		{
			auto component = std::make_shared<T>(std::forward<Args>(args)...);
			m_components[typeid(T)] = component;

			return *component;
		}
		template<typename T>
		T& GetComponent()
		{
			return *static_cast<T*>(m_components.at(typeid(T)).get());
		}
		template<typename T>
		bool HasComponent() const
		{
			return m_components.find(typeid(T)) != m_components.end();
		}
		const std::string& GetName() const
		{
			return m_name;
		}
	private:		
		TransformComponent m_transform{};

		std::unordered_map<std::type_index, std::shared_ptr<void>> m_components;
		std::string m_name{ "Unnamed" };
	};
}
#endif // !ENTITY_H
