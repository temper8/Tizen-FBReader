/*
 * Copyright (C) 2009-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <ZLResource.h>
#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>
#include <ZLFile.h>
#include <ZLStringUtil.h>

#include "LibraryBookActions.h"
#include "../library/Book.h"
#include "../fbreader/FBReader.h"
#include "../optionsDialog/bookInfo/BookInfoDialog.h"
#include "../optionsDialog/bookInfo/BookPreviewDialog.h"
#include "../fbreader/BookTextView.h"

//#include "../optionsDialogMobile/MobileBookInfoDialog.h"

GotoParagraphAction::GotoParagraphAction(int reference) : paragraphReference(reference) {

}

void GotoParagraphAction::run() {
	FBReader &fbreader = FBReader::Instance();
	if (paragraphReference >= 0) {
		fbreader.bookTextView().gotoParagraph(paragraphReference);
		fbreader.showBookTextView();
		ZLDialogManager::Instance().deleteTreeDialog();
	}
}

ZLResourceKey GotoParagraphAction::key() const {
	return ZLResourceKey("gotoParagraph");
}


BookReadAction::BookReadAction(shared_ptr<Book> book) : myBook(book) {
}

void BookReadAction::run() {
	FBReader &fbreader = FBReader::Instance();
	fbreader.openBook(myBook);
	fbreader.showBookTextView();
	ZLDialogManager::Instance().deleteOptionsDialog();
	ZLDialogManager::Instance().deleteTreeDialog();
}

ZLResourceKey BookReadAction::key() const {
	return ZLResourceKey("read");
}

BookRemoveAction::BookRemoveAction(shared_ptr<Book> book) : myBook(book) {
}

void BookRemoveAction::run() {
//	AppLog("BookRemoveAction::run() ");
	switch (removeBookDialog()) {
		case Library::REMOVE_FROM_DISK:
		{
//			AppLog("REMOVE_FROM_DISK ");
			const std::string path = myBook->file().physicalFilePath();
			ZLFile physicalFile(path);
			if (!physicalFile.remove()) {
//				AppLog("!physicalFile.remove()");
				ZLResourceKey boxKey("removeFileErrorBox");
				const std::string message =
					ZLStringUtil::printf(ZLDialogManager::dialogMessage(boxKey), path);
				ZLDialogManager::Instance().errorBox(boxKey, message);
			}
		}
		// yes, we go through this label
		case Library::REMOVE_FROM_LIBRARY:
//			AppLog("REMOVE_FROM_LIBRARY ");
			Library::Instance().removeBook(myBook);
			FBReader::Instance().refreshWindow();
		case Library::REMOVE_DONT_REMOVE:
			break;
	}
}

ZLResourceKey BookRemoveAction::key() const {
	return ZLResourceKey("delete");
}

bool BookRemoveAction::makesSense() const {
	return Library::Instance().canRemove(myBook) != Library::REMOVE_DONT_REMOVE;
}

int BookRemoveAction::removeBookDialog() const {
	ZLResourceKey boxKey("removeBookBox");
	const ZLResource &msgResource = ZLResource::resource("dialog")[boxKey];

	switch (Library::Instance().canRemove(myBook)) {
		case Library::REMOVE_DONT_REMOVE:
			return Library::REMOVE_DONT_REMOVE;
		case Library::REMOVE_FROM_DISK:
		{ //  AppLog("REMOVE_FROM_DISK ");
			ZLFile physFile(myBook->file().physicalFilePath());
			const std::string message = ZLStringUtil::printf(msgResource["deleteFile"].value(), physFile.name(false));
			if (ZLDialogManager::Instance().questionBox(boxKey, message, ZLDialogManager::YES_BUTTON, ZLDialogManager::NO_BUTTON) == 0) {
				return Library::REMOVE_FROM_DISK;
			}
			return Library::REMOVE_DONT_REMOVE;
		}
		case Library::REMOVE_FROM_LIBRARY:
		{ //AppLog("REMOVE_FROM_LIBRARY ");
			const std::string message = ZLStringUtil::printf(ZLDialogManager::dialogMessage(boxKey), myBook->title());
			if (ZLDialogManager::Instance().questionBox(boxKey, message, ZLDialogManager::YES_BUTTON, ZLDialogManager::NO_BUTTON) == 0) {
				return Library::REMOVE_FROM_LIBRARY;
			}
			return Library::REMOVE_DONT_REMOVE;
		}
		case Library::REMOVE_FROM_LIBRARY_AND_DISK:
		{ //AppLog("REMOVE_FROM_LIBRARY_AND_DISK ");
			ZLResourceKey removeFileKey("removeFile");
			ZLResourceKey removeLinkKey("removeLink");
    
			const std::string message = ZLStringUtil::printf(ZLDialogManager::dialogMessage(boxKey), myBook->title());
			switch(ZLDialogManager::Instance().questionBox(boxKey, message, removeLinkKey, removeFileKey, ZLDialogManager::CANCEL_BUTTON)) {
				case 0:
					return Library::REMOVE_FROM_LIBRARY;
				case 1:
					return Library::REMOVE_FROM_DISK;
				case 2:
					return Library::REMOVE_DONT_REMOVE;
			}
		}
	}
	return Library::REMOVE_DONT_REMOVE;
}

SimpleBookPreviewAction::SimpleBookPreviewAction(shared_ptr<Book> book) : myBook(book) {
}

void SimpleBookPreviewAction::run() {
	if (SimpleBookPreviewDialog(myBook).dialog().run()) {
	//if (BookInfoDialog(myBook).dialog().run()) {
	//if (MobileBookInfoDialog(myBook).dialog().run()) {
		// TODO: select current node (?) again
		FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey SimpleBookPreviewAction::key() const {
	return ZLResourceKey("edit");
}

BookEditInfoAction::BookEditInfoAction(shared_ptr<Book> book) : myBook(book) {
}

void BookEditInfoAction::run() {
	if (BookPreviewDialog(myBook).dialog().run()) {
	//if (BookInfoDialog(myBook).dialog().run()) {
	//if (MobileBookInfoDialog(myBook).dialog().run()) {
		// TODO: select current node (?) again
		FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey BookEditInfoAction::key() const {
	return ZLResourceKey("edit");
}

