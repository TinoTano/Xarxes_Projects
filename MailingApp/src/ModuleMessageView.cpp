#include "ModuleMessageView.h"
#include "imgui/imgui.h"

bool ModuleMessageView::update()
{
	ImGui::Begin("Message View");

	if (message != "")
	{
		ImGui::Text(subject);
		ImGui::TextWrapped("Sender: %s", sender);
		ImGui::TextWrapped("Date: %s", sentDate);
		ImGui::Separator();
		ImGui::Text(message);
	}

	ImGui::End();

	return true;
}

void ModuleMessageView::SetMessageToShow(const char* subject, const char* sender, const char* sentDate, const char* message)
{
	this->subject = subject;
	this->sender = sender;
	this->sentDate = sentDate;
	this->message = message;
}

void ModuleMessageView::EmptyWindow()
{
	message = "";
	sender = "";
	subject = "";
	sentDate = "";
}
