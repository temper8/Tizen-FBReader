

#include "ZLibrary.h"

#include "ZLibraryImplementation.h"


bool ZLibrary::init(int &argc, char **&argv) {


	ZLibraryImplementation::initLibrary();

	if (ZLibraryImplementation::Instance == 0) {
		return false;
	}

	ZLibraryImplementation::Instance->init(argc, argv);
	return true;
}

ZLPaintContext *ZLibrary::createContext() {
	return ZLibraryImplementation::Instance->createContext();
}

void ZLibrary::run(ZLApplication *application) {
	ZLibraryImplementation::Instance->run(application);
}

void ZLibrary::shutdown() {

}
