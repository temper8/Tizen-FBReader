
#include "FBReader.h"

FBReader::FBReader(const std::string &bookToOpen): ZLApplication(bookToOpen)  {

}

FBReader::~FBReader() {

}


bool FBReader::createApplication(){

	ZLApplication::createApplication();

return true;
}


