#ifndef EDITOR_CONTEXT_H
#define EDITOR_CONTEXT_H

namespace eng
{
	class EditorContext
	{
	public:
		void SetSelectedEntityId(std::uint32_t entityId)
		{
			m_selectedEntityId = entityId;
		}
		std::uint32_t GetSelectedEntityId() const
		{
			return m_selectedEntityId;
		}
	private:
		std::uint32_t m_selectedEntityId;
	};
}
#endif // !EDITOR_CONTEXT_H
