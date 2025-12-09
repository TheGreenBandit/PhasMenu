#pragma once

#include "common.hpp"
#include "core/file_manager/file_manager.hpp"

namespace menu
{
	class menu_settings
	{
	public:
		void destroy();
		void init(const file& save_file);
		void load();

	private:
		void save();

	private:
		bool m_running;

		file m_save_file;

		nlohmann::json m_default_options;
		nlohmann::json m_options;

	public:
		struct self
		{
			bool infinite_sprint = false;
			bool fast_sprint = false;
			float fast_sprint_value = 1.f;//normal
		} self;

		struct gui
		{
			int menu_toggle = VK_INSERT;
			bool editing_menu_toggle = false;

			struct style
			{
				ImVec2 WindowPadding = { 10.f, 10.f };
				float PopupRounding = 1.f;
				ImVec2 FramePadding = { 6.f, 4.f };
				ImVec2 ItemSpacing = { 5.f, 5.f };
				ImVec2 ItemInnerSpacing = { 10.f, 6.f };
				ImVec2 TouchExtraPadding = { 0.f, 0.f };
				float IndentSpacing = 1.f;
				float ScrollbarSize = 5.f;
				float GrabMinSize = 2.f;
				float WindowBorderSize = 1.f;
				float ChildBorderSize = 5.f;
				float PopupBorderSize = 1.f;
				float FrameBorderSize = 1.f;
				float TabBorderSize = 1.f;
				float WindowRounding = 0.f;
				float ChildRounding = 10.f;
				float FrameRounding = 40.f;
				float ScrollbarRounding = 10.f;
				float GrabRounding = 10.f;
				float TabRounding = 1.f;
				ImVec2 WindowTitleAlign = { 0.f, 0.5f };
				ImVec2 ButtonTextAlign = { 0.5f, 0.65f };
				ImVec2 DisplaySafeAreaPadding = { 3.f, 3.f };
			} style;

			struct color
			{
				ImVec4 Text = { 1.00f, 1.00f, 1.00f, 1.00f };
				ImVec4 TextDisabled = { 1.00f, 0.90f, 0.19f, 1.00f };
				ImVec4 WindowBg = { 0.f, 0.f, 0.f, .8f };
				ImVec4 ChildBg = { 1.f, 1.f, 1.f, .07f };
				ImVec4 PopupBg = { 0.08f, 0.08f, 0.08f, 0.94f };
				ImVec4 Border = { 0.0f, 0.50f, 0.00f, 1.0f };
				ImVec4 BorderShadow = { 0.00f, 0.00f, 0.00f, 0.00f };
				ImVec4 FrameBg = { 0.21f, 0.21f, 0.21f, 0.54f };
				ImVec4 FrameBgHovered = { 0.21f, 0.21f, 0.21f, 0.78f };
				ImVec4 FrameBgActive = { 0.28f, 0.27f, 0.27f, 0.54f };
				ImVec4 TitleBg = { 0.17f, 0.17f, 0.17f, 1.00f };
				ImVec4 TitleBgActive = { 0.19f, 0.19f, 0.19f, 1.00f };
				ImVec4 TitleBgCollapsed = { 0.00f, 0.00f, 0.00f, 0.51f };
				ImVec4 MenuBarBg = { 0.14f, 0.14f, 0.14f, .07f };
				ImVec4 ScrollbarBg = { 0.02f, 0.02f, 0.02f, 0.53f };
				ImVec4 ScrollbarGrab = { 0.31f, 0.31f, 0.31f, 1.00f };
				ImVec4 ScrollbarGrabHovered = { 0.41f, 0.41f, 0.41f, 1.00f };
				ImVec4 ScrollbarGrabActive = { 0.51f, 0.51f, 0.51f, 1.00f };
				ImVec4 CheckMark = { 0.0f, 0.5f, 0.0f, 1.00f };
				ImVec4 SliderGrab = { 0.34f, 0.34f, 0.34f, 1.00f };
				ImVec4 SliderGrabActive = { 0.39f, 0.38f, 0.38f, 1.00f };
				ImVec4 Button = { 0.228f, 0.856f, 0.0f, 0.72f };
				ImVec4 ButtonHovered = { 0.6f, .8f, .6f, .72f };
				ImVec4 ButtonActive = { 0.5f, 0.7f, 0.5f, 0.72f };
				ImVec4 Header = { 0.37f, 0.37f, 0.37f, 0.31f };
				ImVec4 HeaderHovered = { 0.38f, 0.38f, 0.38f, 0.37f };
				ImVec4 HeaderActive = { 0.37f, 0.37f, 0.37f, 0.51f };
				ImVec4 Separator = { 0.38f, 0.38f, 0.38f, 0.50f };
				ImVec4 SeparatorHovered = { 0.46f, 0.46f, 0.46f, 0.50f };
				ImVec4 SeparatorActive = { 0.46f, 0.46f, 0.46f, 0.64f };
				ImVec4 ResizeGrip = { 0.26f, 0.26f, 0.26f, 1.00f };
				ImVec4 ResizeGripHovered = { 0.31f, 0.31f, 0.31f, 1.00f };
				ImVec4 ResizeGripActive = { 0.35f, 0.35f, 0.35f, 1.00f };
				ImVec4 Tab = { 0.21f, 0.21f, 0.21f, 0.86f };
				ImVec4 TabHovered = { 0.27f, 0.27f, 0.27f, 0.86f };
				ImVec4 TabActive = { 0.34f, 0.34f, 0.34f, 0.86f };
				ImVec4 TabUnfocused = { 0.10f, 0.10f, 0.10f, 0.97f };
				ImVec4 TabUnfocusedActive = { 0.15f, 0.15f, 0.15f, 1.00f };
				ImVec4 PlotLines = { 0.61f, 0.61f, 0.61f, 1.00f };
				ImVec4 PlotLinesHovered = { 1.00f, 0.43f, 0.35f, 1.00f };
				ImVec4 PlotHistogram = { 0.90f, 0.70f, 0.00f, 1.00f };
				ImVec4 PlotHistogramHovered = { 1.00f, 0.60f, 0.00f, 1.00f };
				ImVec4 TextSelectedBg = { 0.26f, 0.59f, 0.98f, 0.35f };
				ImVec4 DragDropTarget = { 1.00f, 1.00f, 0.00f, 0.90f };
				ImVec4 NavHighlight = { 0.26f, 0.59f, 0.98f, 1.00f };
				ImVec4 NavWindowingHighlight = { 1.00f, 1.00f, 1.00f, 0.70f };
				ImVec4 NavWindowingDimBg = { 0.80f, 0.80f, 0.80f, 0.20f };
				ImVec4 ModalWindowDimBg = { 0.80f, 0.80f, 0.80f, 0.35f };
			} color;
		} gui;
	};

	inline auto g = menu_settings();
}
