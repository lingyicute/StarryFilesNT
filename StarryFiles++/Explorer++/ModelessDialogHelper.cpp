// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#include "stdafx.h"
#include "ModelessDialogHelper.h"
#include "ModelessDialogList.h"
#include "../Helper/BaseDialog.h"

void CreateOrSwitchToModelessDialog(ModelessDialogList *modelessDialogList, const std::wstring &id,
	std::function<BaseDialog *()> dialogCreator)
{
	if (HWND existingDialog = modelessDialogList->MaybeGetDialogById(id))
	{
		SetFocus(existingDialog);
		return;
	}

	auto *dialog = dialogCreator();
	HWND dialogHwnd = dialog->ShowModelessDialog(
		[modelessDialogList, id]() { modelessDialogList->RemoveDialog(id); });
	modelessDialogList->AddDialog(id, dialogHwnd);
}
