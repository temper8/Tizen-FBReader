
#include "FBReader.h"
#include "TestView.h"

FBReader::FBReader(const std::string &bookToOpen): ZLApplication(bookToOpen)  {

}

FBReader::~FBReader() {

}


bool FBReader::createApplication(){

	ZLApplication::createApplication();
	myBookTextView = new TestView(*context());

return true;
}


void FBReader::initWindow() {
	ZLApplication::initWindow();
	refreshWindow();
}

void FBReader::refreshWindow() {
	ZLApplication::refreshWindow();
//	((RecentBooksPopupData&)*myRecentBooksPopupData).updateId();
//	((PreferencesPopupData&)*myPreferencesPopupData).updateId();
}

