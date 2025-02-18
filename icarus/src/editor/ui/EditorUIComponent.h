#pragma once

#include <vector>
#include "imgui.h"


namespace Editor
{
	class EditorUIComponent
	{
	public:
		static std::vector<EditorUIComponent*>& GetComponents()
		{
			static std::vector<EditorUIComponent*> components;
			return components;
		}

		static void RenderComponents()
		{
			for (EditorUIComponent* c : GetComponents())
			{
				c->Render();
			}
		}

		EditorUIComponent()
		{
			GetComponents().push_back(this);
		}

		virtual ~EditorUIComponent() = default;

		virtual void Render() = 0;
	};
}
