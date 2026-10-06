#include <string>
#ifndef LAYER_H
#define LAYER_H
namespace eng
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void Update(float dt) {}
		virtual void OnImGuiRender() {}
		// event handling

		const std::string& GetName() const { return m_name; }
	protected:
		std::string m_name;
	};

}
#endif // !LAYER_H