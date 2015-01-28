#include "logger.h"

#include "FBReader.h"
#include "TestView.h"



FBReader::FBReader(const std::string &bookToOpen): ZLApplication(bookToOpen)  {
	DBG("FBR-FBReader");
}

FBReader::~FBReader() {

}


bool FBReader::createApplication(){
	DBG("FBR-createApp");

	ZLApplication::createApplication();
	myBookTextView = new TestView(*context());
	setView(myBookTextView);

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

