/*
 * PreviewEntries.cpp
 *
 *  Created on: 01.02.2012
 *      Author: Alex
 */

#include "PreviewEntries.h"

StaticTextEntry::StaticTextEntry(const std::string &value) : myString(value) {
}

const std::string &StaticTextEntry::initialValue() const {
	return myString;
}


StringEntry::StringEntry(const std::string &value) : myString(value) {
}

const std::string &StringEntry::initialValue() const {
	return myString;
}

void StringEntry::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}


ButtonEntry::ButtonEntry(shared_ptr<ZLRunnableWithKey> action) : ZLButtonOptionEntry(action) {
}

const std::string &ButtonEntry::initialValue() const {
	return "Button";
}

void ButtonEntry::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}
