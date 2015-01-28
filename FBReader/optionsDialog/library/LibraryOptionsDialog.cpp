/*
 * Copyright (C) 2010 Geometer Plus <contact@geometerplus.com>
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

#include "ZLOptionEntry.h"
#include "LibraryOptionsDialog.h"

#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>

#include "../../fbreader/FBReader.h"

#include <ZLFile.h>
#include <ZLDir.h>

//TODO #include "../../network/NetworkLinkCollection.h"


class BookPathComboEntry : public ZLComboOptionEntry {

public:
	BookPathComboEntry(ZLStringOption &typeOption);
	//void addDependentEntry(ZLOptionEntry *entry);
	const std::string &initialValue() const;

private:
	const std::vector<std::string> &values() const;
	void onAccept(const std::string &value);
	void onValueSelected(int index) {};

private:
	ZLStringOption &myOption;
	std::vector<std::string> myValues;
	//std::vector<ZLOptionEntry*> myDependentEntries;
};

BookPathComboEntry::BookPathComboEntry(ZLStringOption &typeOption) : myOption(typeOption){
	myValues.push_back("path1");
	myValues.push_back("path2");
	{
		ZLFile f("/Media/");
		shared_ptr<ZLDir> dir = f.directory();
		if (!dir.isNull()) {
				dir->collectSubDirs(myValues, true);
		}
	}
	{
		ZLFile f("/Storagecard/Media/");
		shared_ptr<ZLDir> dir = f.directory();
		if (!dir.isNull()) {
				dir->collectSubDirs(myValues, true);
		}
	}


}

const std::string &BookPathComboEntry::initialValue() const {
	return myOption.value();
}

const std::vector<std::string> &BookPathComboEntry::values() const {
	return myValues;
}

void BookPathComboEntry::onAccept(const std::string &value) {
//	myOption.setValue(value);

}

LibraryOptionsDialog::LibraryOptionsDialog() : AbstractOptionsDialog(ZLResourceKey("LibraryOptionsDialog"), true) {

	ZLDialogContent &libraryTab = dialog().createTab(ZLResourceKey("Library"));

	Library &library = Library::Instance();
	libraryTab.addOption(ZLResourceKey("bookPath"), library.PathOption);

//	BookPathComboEntry *bookPathComboEntry =
//			new BookPathComboEntry(library.PathOption);
//	libraryTab.addOption(ZLResourceKey("bookPath"), bookPathComboEntry);

	libraryTab.addOption(ZLResourceKey("lookInSubdirectories"), library.ScanSubdirsOption);
//	libraryTab.addOption(ZLResourceKey("collectBooksWithoutMetaInfo"), library.CollectAllBooksOption);
//	libraryTab.addOption(ZLResourceKey("downloadDirectory"), NetworkLinkCollection::Instance().DirectoryOption);
}
