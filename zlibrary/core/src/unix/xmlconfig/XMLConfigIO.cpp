/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
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

#include <ZLFile.h>
#include <ZLDir.h>
#include <ZLInputStream.h>
#include <ZLibrary.h>
#include <ZLOptions.h>

#include "XMLConfig.h"
#include "XMLConfigDelta.h"
#include "XMLConfigReader.h"
#include "XMLConfigWriter.h"
#include "XMLConfigDeltaWriter.h"

#include "logger.h"


const std::string XMLConfig::UNKNOWN_CATEGORY = ".unknown.";

static const std::string CHANGES_FILE = "config.changes";

void XMLConfig::load() {
	DBG("XMLConfig::load 1 ");
	XMLConfigReader(*this, "").readDocument(ZLFile(
		ZLibrary::DefaultFilesPathPrefix() + "config.xml"
	));
	DBG("XMLConfig::load 2 ");
	XMLConfigReader(*this, "").readDocument(ZLFile(
		ZLibrary::ZLibraryDirectory() + ZLibrary::FileNameDelimiter + "default" + ZLibrary::FileNameDelimiter + "config.xml"
	));
	DBG("XMLConfig::load 3 ");
	myDefaultGroups = myGroups;
	for (std::map<std::string,XMLConfigGroup*>::iterator it = myDefaultGroups.begin(); it != myDefaultGroups.end(); ++it) {
		it->second = new XMLConfigGroup(*it->second);
	}
	DBG("XMLConfig::load 4 ");
	shared_ptr<ZLDir> configDir = ZLFile(ZLibrary::ApplicationWritableDirectory()).directory(false);
	if (!configDir.isNull()) {
		std::vector<std::string> fileNames;
		configDir->collectFiles(fileNames, true);
		for (std::vector<std::string>::const_iterator it = fileNames.begin(); it != fileNames.end(); ++it) {
			ZLFile configFile(configDir->itemPath(*it));
			if (configFile.extension() == "xml") {
				XMLConfigReader(*this, configFile.name(true)).readDocument(configFile.inputStream());
			}
		}
	}
	DBG("XMLConfig::load 5 ");
	if (myDelta == 0) {
		myDelta = new XMLConfigDelta();
	}
	DBG("XMLConfig::load 6 ");
	if (!configDir.isNull()) {
		XMLConfigReader(*this, UNKNOWN_CATEGORY).readDocument(
			ZLFile(configDir->itemPath(CHANGES_FILE))
		);
	}
	DBG("XMLConfig::load 7 ");
}

void XMLConfig::saveAll() {
	DBG("XMLConfig::saveAll(); ");
	saveDelta();

	shared_ptr<ZLDir> configDir = ZLFile(ZLibrary::ApplicationWritableDirectory()).directory(true);
	//AppLog("shared_ptr<ZLDir> configDir");
	if (myDelta != 0) {
		DBG("myDelta != 0");
		if (!configDir.isNull()) {
			std::set<std::string> &categories = myDelta->myCategories;
			for (std::set<std::string>::const_iterator it = categories.begin(); it != categories.end(); ++it) {
				if (!it->empty()) {
					shared_ptr<ZLOutputStream> stream = ZLFile(configDir->itemPath(*it + ".xml")).outputStream();
					if (!stream.isNull()
							&& stream->open()) {
						XMLConfigWriter(*this, *stream, *it).write();
						stream->close();
					}
				}
			}
		}
		myDelta->clear();
	} // TODO: show error message if config was not saved
	ZLFile changesFile(ZLibrary::ApplicationWritableDirectory() + ZLibrary::FileNameDelimiter + CHANGES_FILE, ZLMimeType::EMPTY);
	//AppLog("ZLFile changesFile");
	changesFile.remove();
	//AppLog("changesFile.remove()");
}

void XMLConfig::saveDelta() {DBG("XMLConfig::saveDelta()");
	if ((myDelta == 0) || (myDelta->myIsUpToDate)) {
		return;
	}
	shared_ptr<ZLDir> configDir = ZLFile(ZLibrary::ApplicationWritableDirectory()).directory(true);
	shared_ptr<ZLOutputStream> stream = ZLFile(configDir->itemPath(CHANGES_FILE)).outputStream();
	if (!stream.isNull() && stream->open()) {
		XMLConfigDeltaWriter(*myDelta, *stream).write();
		stream->close();
	}
	myDelta->myIsUpToDate = true;
}
