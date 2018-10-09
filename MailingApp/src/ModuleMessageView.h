#pragma once

#include "Module.h"

class ModuleMessageView : public Module
{
public:
	bool update() override;

	void SetMessageToShow(const char* subject, const char* sender, const char* sentDate, const char* message);
	void EmptyWindow();

private:
	const char* message = "";
	const char* sender = "";
	const char* subject = "";
	const char* sentDate = "";
};