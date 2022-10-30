
#include "pch.h"

void r::R_GameMenuBrowser_WindowProperties(windowDef_t& wnd)
{

	Material* bg = wnd.background;
	rectDef_s rect = wnd.rect;

	ImGui::Text("BackColor: %.2f %.2f %.2f %.2f", wnd.backColor[0], wnd.backColor[1], wnd.backColor[2], wnd.backColor[3]);

	if (bg) {
		if (ImGui::TreeNode("background##04")) {
			ImGui::TreePop();
		}
	}
	ImGui::Text("border: %i", wnd.border);
	ImGui::Text("borderColor: %.2f %.2f %.2f %.2f", wnd.borderColor[0], wnd.borderColor[1], wnd.borderColor[2], wnd.borderColor[3]);
	ImGui::Text("borderSize: %i", wnd.borderSize);
	ImGui::Text("dynamicFlags: %i", wnd.dynamicFlags[0]);
	ImGui::Text("foreColor: %.2f %.2f %.2f %.2f", wnd.foreColor[0], wnd.foreColor[1], wnd.foreColor[2], wnd.foreColor[3]);
	ImGui::Text("group: %s", wnd.group);
	ImGui::Text("name: %s", wnd.name);
	ImGui::Text("nextTime: %i", wnd.nextTime);
	ImGui::Text("outlineColor: %.2f %.2f %.2f %.2f", wnd.outlineColor[0], wnd.outlineColor[1], wnd.outlineColor[2], wnd.outlineColor[3]);
	ImGui::Text("ownerDraw: %i", wnd.ownerDraw);
	ImGui::Text("ownerDrawFlags: %i", wnd.ownerDrawFlags);

	if (ImGui::TreeNode("rect##04")) {
		ImGui::Text("x: %i", rect.x);
		ImGui::Text("y: %i", rect.y);
		ImGui::Text("width: %i", rect.w);
		ImGui::Text("height: %i", rect.h);
		ImGui::Text("horzAlign: %i", rect.horzAlign);
		ImGui::Text("vertAlign: %i", rect.vertAlign);
		ImGui::TreePop();
	}

	ImGui::Text("staticFlags: %i", wnd.staticFlags);
	ImGui::Text("style: %i", wnd.style);



	
}
void r::R_GameMenuBrowser_ItemDef(itemDef_s* item)
{

	rectDef_s rect = item->textRect[0];
	ImGui::Text("action: %s", item->action);
	ImGui::Text("alignment: %i", item->alignment);
	ImGui::Text("cursorPos: %i", item->cursorPos[0]);
	ImGui::Text("dataType: %i", item->dataType);
	ImGui::Text("dvar: %s", item->dvar);
	ImGui::Text("dvarFlags: %i", item->dvarFlags);
	ImGui::Text("dvarTest: %s", item->dvarTest);
	ImGui::Text("enableDvar: %s", item->enableDvar);
	ImGui::Text("feeder: %i", item->feeder);
	ImGui::Text("fontEnum: %i", item->fontEnum);
	ImGui::Text("gameMsgWindowIndex: %i", item->gameMsgWindowIndex);
	ImGui::Text("gameMsgWindowMode: %i", item->gameMsgWindowMode);
	ImGui::Text("imageTrack: %i", item->imageTrack);
	ImGui::Text("leaveFocus: %s", item->leaveFocus);
	if (item->materialExp.numEntries) {
		ImGui::Text("exp materialExp: %s", GetExpressionResultString(0, &item->materialExp));
	}
	ImGui::Text("mouseEnter: %s", item->mouseEnter);
	ImGui::Text("mouseEnterText: %s", item->mouseEnterText);
	ImGui::Text("mouseExit: %s", item->mouseExit);
	ImGui::Text("mouseExitText: %s", item->mouseExitText);
	ImGui::Text("onAccept: %s", item->onAccept);
	ImGui::Text("onFocus: %s", item->onFocus);
	if (item->onKey) {
		ImGui::Text("onKey [action]: %s", item->onKey->action);
		ImGui::Text("onKey [key]: %i", item->onKey->key);
	}
	ImGui::Text("text: %s", item->text);
	if (item->textExp.numEntries) {
		ImGui::Text("exp text: %s", GetExpressionResultString(0, &item->textExp));
	}
	ImGui::Text("textAlignMode: %i", item->textAlignMode);
	ImGui::Text("textalignx: %.2f", item->textalignx);
	ImGui::Text("textaligny: %.2f", item->textaligny);

	if (ImGui::TreeNode("rect##05")) {
		ImGui::Text("x: %i", rect.x);
		ImGui::Text("y: %i", rect.y);
		ImGui::Text("width: %i", rect.w);
		ImGui::Text("height: %i", rect.h);
		ImGui::Text("horzAlign: %i", rect.horzAlign);
		ImGui::Text("vertAlign: %i", rect.vertAlign);
		ImGui::TreePop();
	}

	ImGui::Text("textSavegame: %i", item->textSavegame);
	ImGui::Text("textscale: %.2f", item->textscale);
	ImGui::Text("textStyle: %i", item->textStyle);
	ImGui::Text("type: %i", item->type);
	if (item->visibleExp.numEntries) {
		ImGui::Text("visible: %s", GetExpressionResultString(0, &item->visibleExp));
	}

	//if (GetAsyncKeyState(VK_END) & 1) {

	//	if (item->textExp.numEntries) {
	//		char* hmm = GetExpressionResultString(0, &item->textExp);

	//		if (hmm) {
	//			std::cout << hmm << '\n';
	//		}
	//		else std::cout << "nope\n";

	//	}
	//	std::cout << "nullptr\n";
	//}


}
void r::R_GameMenuBrowser(bool& isOpen)
{
	if (!isOpen)
		return;

	std::string separator;
	ImGui::Begin("Menu Browser", &isOpen);

	for (int i = 0; i < menuInfo.context->menuCount; i++) {
		menuDef_t* menu = menuInfo.context->Menus[i];

		if (menu) {
			if (ImGui::TreeNode(menu->window.name)) {

				ImGui::Text("allowedBinding: %s", menu->allowedBinding);
				ImGui::Text("blurRadius: %.3f", menu->blurRadius);
				ImGui::Text("cursorItem: %i", menu->cursorItem[0]);
				ImGui::Text("disableColor: %.2f %.2f %.2f %.2f", menu->disableColor[0], menu->disableColor[1], menu->disableColor[2], menu->disableColor[3]);
				ImGui::Text("fadeAmount: %.3f", menu->fadeAmount);
				ImGui::Text("fadeClamp: %.3f", menu->fadeClamp);
				ImGui::Text("fadeCycle: %i", menu->fadeCycle);
				ImGui::Text("fadeInAmount: %.3f", menu->fadeInAmount);
				ImGui::Text("focusColor: %.2f %.2f %.2f %.2f", menu->focusColor[0], menu->focusColor[1], menu->focusColor[2], menu->focusColor[3]);
				ImGui::Text("font: %s", menu->font);
				ImGui::Text("fontIndex: %i", menu->fontIndex);
				ImGui::Text("fullScreen: %i", menu->fullScreen);
				ImGui::Text("imageTrack: %i", menu->imageTrack);
				ImGui::Text("itemCount: %i", menu->itemCount);

				if (menu->items) {
					if (ImGui::TreeNode("items")) {
						for (int j = 0; j < menu->itemCount; j++) {
							itemDef_s* item = menu->items[j];

							if (!item)
								continue;

							char buffer[20];

							sprintf_s(buffer, "item [%i]", j);

							if (ImGui::TreeNode(buffer)) {
								R_GameMenuBrowser_ItemDef(item);
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}

				}


				ImGui::Text("onClose: %s", menu->onClose);
				ImGui::Text("onESC: %s", menu->onESC);

				if (menu->onKey) {
					ImGui::Text("onKey [action]: %s", menu->onKey->action);
					ImGui::Text("onKey [key]: %i", menu->onKey->key);
				}

				ImGui::Text("onOpen: %s", menu->onOpen);
				ImGui::Text("soundName: %s", menu->soundName);

				if (ImGui::TreeNode("window##02")) {
					R_GameMenuBrowser_WindowProperties(menu->window);
					ImGui::TreePop();
				}

				ImGui::TreePop();

			}
			

			ImGui::Separator();
		}


	}

	ImGui::End();
}