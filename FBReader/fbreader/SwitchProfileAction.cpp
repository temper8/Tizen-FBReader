#include "FBReader.h"
#include "../options/FBOptions.h"
#include "SwitchProfileAction.h"

SwitchProfileAction::SwitchProfileAction(const std::string& profileName): myProfileName(profileName) { }

bool SwitchProfileAction::isVisible() const {
	return !(myProfileName == FBOptions::Instance().getColorProfileName());
}

void SwitchProfileAction::run() {
//	AppLog("SwitchProfileAction %s",myProfileName.c_str() );
	if (myProfileName==ColorProfile::DAY_NIGHT) {
		std::string currentProfile =  FBOptions::Instance().getColorProfileName();
//		AppLog("currentProfile %s",currentProfile.c_str() );
		if (currentProfile==ColorProfile::DAY)
			FBOptions::Instance().setColorProfileName(ColorProfile::NIGHT);
		else
			FBOptions::Instance().setColorProfileName(ColorProfile::DAY);
	}
	else
		FBOptions::Instance().setColorProfileName(myProfileName);
	FBReader::Instance().refreshWindow();
}
