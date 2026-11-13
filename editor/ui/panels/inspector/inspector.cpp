#include "inspector.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <algorithm>
#include <cstring>
#include <string_view>

namespace eng
{
	Inspector::Inspector(Scene& scene, EditorContext& editorContext, CommandExecutor& executor)
		: m_scene {scene}, m_editorContext {editorContext}
		, m_executor {executor}
	{		
	}
	bool Inspector::Init(EngineContext& ctx)
	{	
		m_log = &ctx.GetLogger();
		return true;
	}
	void Inspector::Destroy()
	{
	}
	void Inspector::Draw()
	{
		ImGui::Begin(
			"Inspector"
			,nullptr,
			ImGuiWindowFlags_NoCollapse
			);

		if(ImGui::Button("Create"))
		{
			ImGui::OpenPopup("CreateEntityPopup");
		}
		if (ImGui::BeginPopup("CreateEntityPopup"))
		{
			if (ImGui::BeginMenu("Entity"))
			{
				if (ImGui::MenuItem("New"))
				{
					m_executor.Submit("ent.create empty");
				}				

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Lights"))
			{
				if (ImGui::MenuItem("Light"))
				{
					m_executor.Submit("ent.create light");
				}					
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}		
		ImGui::Selectable("ROOT", false);

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload =
				ImGui::AcceptDragDropPayload("SCENE_ENTITY"))
			{
				if (payload->DataSize == sizeof(std::uint32_t))
				{
					const auto childId =
						*static_cast<const std::uint32_t*>(payload->Data);

					m_pendingParentChange =
						ParentChange{ childId, std::nullopt };
				}
			}

			ImGui::EndDragDropTarget();
		}

		for (const auto& entity : m_scene.GetEntities())
		{
			if (!entity->GetParent())
				DrawEntityNode(*entity);
		}

		if (m_pendingParentChange)
		{
			m_scene.SetParent(
				m_pendingParentChange->child,
				m_pendingParentChange->parent);

			m_pendingParentChange.reset();
		}

		ImGui::End();
	}
	void Inspector::DrawEntityNode(Entity& entity)
	{
		ImGui::PushID(static_cast<int>(entity.GetID()));

		ImGuiTreeNodeFlags flags =
			ImGuiTreeNodeFlags_OpenOnArrow |
			ImGuiTreeNodeFlags_SpanAvailWidth;

		if (entity.GetChildren().empty())
			flags |= ImGuiTreeNodeFlags_Leaf;

		const bool open = ImGui::TreeNodeEx(
			"EntityNode", flags, "%s", entity.GetName().c_str());

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			m_editorContext.SetSelectedEntityId(entity.GetID());

		if (ImGui::BeginPopupContextItem("EntityContext"))
		{
			if (ImGui::IsWindowAppearing())
			{
				m_editorContext.SetSelectedEntityId(entity.GetID());
				const auto& name = entity.GetName();
				const auto length = std::min(name.size(), sizeof(m_renameBuffer) - 1);
				std::memcpy(m_renameBuffer, name.data(), length);
				m_renameBuffer[length] = '\0';
				ImGui::SetKeyboardFocusHere();
			}

			const bool enter = ImGui::InputText(
				"Name", m_renameBuffer, sizeof(m_renameBuffer),
				ImGuiInputTextFlags_EnterReturnsTrue |
				ImGuiInputTextFlags_AutoSelectAll);
			const bool valid =
				std::string_view(m_renameBuffer).find_first_not_of(" \t\r\n")
				!= std::string_view::npos;

			ImGui::BeginDisabled(!valid);
			const bool save = ImGui::Button("Rename");
			ImGui::EndDisabled();

			if (valid && (enter || save))
			{
				entity.SetName(m_renameBuffer);
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
				ImGui::CloseCurrentPopup();

			ImGui::EndPopup();
		}

		if (ImGui::BeginDragDropSource())
		{
			const std::uint32_t id = entity.GetID();

			ImGui::SetDragDropPayload("SCENE_ENTITY", &id, sizeof(id));
			ImGui::TextUnformatted(entity.GetName().c_str());

			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload =
				ImGui::AcceptDragDropPayload("SCENE_ENTITY"))
			{
				if (payload->DataSize == sizeof(std::uint32_t))
				{
					const auto childId =
						*static_cast<const std::uint32_t*>(payload->Data);

					m_pendingParentChange =
						ParentChange{ childId, entity.GetID() };
				}
			}

			ImGui::EndDragDropTarget();
		}

		if (open)
		{
			for (const auto childId : entity.GetChildren())
			{
				if (Entity* child = m_scene.FindEntityById(childId))
					DrawEntityNode(*child);
			}

			ImGui::TreePop();
		}

		ImGui::PopID();
	}
	void Inspector::Update(float)
	{	
	}
}
