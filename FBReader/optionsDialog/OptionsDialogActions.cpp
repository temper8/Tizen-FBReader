/*
 * OptionsDialogActions.cpp
 *
 *  Created on: 11.12.2011
 *      Author: Alex
 */

#include "OptionsDialogActions.h"
#include "../fbreader/FBReader.h"
#include "lookAndFeel/LookAndFeelOptionsDialog.h"
#include "reading/AppearanceOptionsDialog.h"
#include "reading/IndicatorOptionsDialog.h"
#include "reading/PageTurningOptionsDialog.h"
#include "reading/ReadingOptionsDialog.h"
#include "system/SystemOptionsDialog.h"
#include "library/LibraryOptionsDialog.h"
#include "color/ColorOptionsDialog.h"
#include "textStyle/TextStyleOptionsDialog.h"
#include "text/TextOptionsDialog.h"
#include "text/MarginsOptionsDialog.h"
#include "ZLOptionsDialog.h"

//TextStyleOptionsDialogAction   +
//ColorOptionsDialogAction       +
//ShowLibraryOptionsDialogAction       +
//ShowNetworkOptionsDialogAction       -
//ShowSystemOptionsDialogAction        +
//ShowReadingOptionsDialogAction       +
//ShowLookAndFeelOptionsDialogAction   +





TextStyleOptionsDialogAction::TextStyleOptionsDialogAction(ZLTextStyleDecoration &decoration) : myTextStyleDecoration(decoration)  {
}

void TextStyleOptionsDialogAction::run() {
	if (TextStyleOptionsDialog(myTextStyleDecoration).dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey TextStyleOptionsDialogAction::key() const {
	return ZLResourceKey("textStyles");
}



LibraryOptionsDialogAction::LibraryOptionsDialogAction()  {
}

void LibraryOptionsDialogAction::run() {
	if (LibraryOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey LibraryOptionsDialogAction::key() const {
	return ZLResourceKey("LibraryOptionsDialog");
}


SystemOptionsDialogAction::SystemOptionsDialogAction()  {
}

void SystemOptionsDialogAction::run() {
	if (SystemOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey SystemOptionsDialogAction::key() const {
	return ZLResourceKey("SystemOptionsDialog");
}



ReadingOptionsDialogAction::ReadingOptionsDialogAction()  {
}

void ReadingOptionsDialogAction::run() {
	if (ReadingOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey ReadingOptionsDialogAction::key() const {
	return ZLResourceKey("text");
}


LookAndFeelOptionsDialogAction::LookAndFeelOptionsDialogAction()  {
}

void LookAndFeelOptionsDialogAction::run() {
	if (LookAndFeelOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey LookAndFeelOptionsDialogAction::key() const {
	return ZLResourceKey("LookAndFeelOptionsDialog");
}

TextOptionsDialogAction::TextOptionsDialogAction()  {
}

void TextOptionsDialogAction::run() {
	if (TextOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey TextOptionsDialogAction::key() const {
	return ZLResourceKey("text");
}

MarginsOptionsDialogAction::MarginsOptionsDialogAction() {
}

void MarginsOptionsDialogAction::run() {
	if (MarginsOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey MarginsOptionsDialogAction::key() const {
	return ZLResourceKey("margins");
}

AppearanceOptionsDialogAction::AppearanceOptionsDialogAction()  {
}

void AppearanceOptionsDialogAction::run() {
	if (AppearanceOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey AppearanceOptionsDialogAction::key() const {
	return ZLResourceKey("appearance");
}



ColorOptionsDialogAction::ColorOptionsDialogAction()  {
}

void ColorOptionsDialogAction::run() {
	if (ColorOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey ColorOptionsDialogAction::key() const {
	return ZLResourceKey("colors");
}




IndicatorOptionsDialogAction::IndicatorOptionsDialogAction()  {
}

void IndicatorOptionsDialogAction::run() {
	if (IndicatorOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey IndicatorOptionsDialogAction::key() const {
	return ZLResourceKey("indicator");
}

PageTurningOptionsDialogAction::PageTurningOptionsDialogAction()  {
}

void PageTurningOptionsDialogAction::run() {
	if (PageTurningOptionsDialog().dialog().run()) {
		// TODO: select current node (?) again
		//FBReader::Instance().refreshWindow();
	}
}

ZLResourceKey PageTurningOptionsDialogAction::key() const {
	return ZLResourceKey("scrolling");
}


