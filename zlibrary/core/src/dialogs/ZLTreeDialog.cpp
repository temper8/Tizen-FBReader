#include "logger.h"
#include "ZLTreeDialog.h"
#include "ZLTreeTitledNode.h"
#include "ZLTimeManager.h"
//#include "../../../../fbreader/src/networkActions/NetworkOperationRunnable.h"
//#include "../../../../zlibrary/ui/src/bada/image/ZLbadaImageManager.h"
/*
const ZLTypeId ZLTreeDialog::TYPE_ID(ZLObjectWithRTTI::TYPE_ID);

const ZLTypeId &ZLTreeDialog::typeId() const {
	return TYPE_ID;
}
*/

/*
class CoverUpdater : public NetworkOperationRunnable {

private:
	//static volatile int Counter;
	static int Counter;

public:
	static shared_ptr<CoverUpdater> create();

//private:
	CoverUpdater();

public:
	~CoverUpdater();

	void addTask(shared_ptr<ZLExecutionData> data);
	bool hasTasks() const;

//private:
	void run();

private:
	ZLExecutionData::Vector myDataVector;
};

class CoverUpdaterRunner : public ZLRunnable {

public:
	CoverUpdaterRunner(shared_ptr<CoverUpdater> updater);

private:
	void run();

private:
	shared_ptr<CoverUpdater> myUpdater;
};

//volatile int CoverUpdater::Counter = 0;
int CoverUpdater::Counter = 0;

shared_ptr<CoverUpdater> CoverUpdater::create() {
	DBG("Counter = %d",Counter);
	return Counter == 0 ? new CoverUpdater() : 0;
}

//CoverUpdater::CoverUpdater() : NetworkOperationRunnable("downloadImages") {
CoverUpdater::CoverUpdater() : NetworkOperationRunnable() {
	++Counter;
}

CoverUpdater::~CoverUpdater() {
	DBG("~CoverUpdater");
	--Counter;
}

void CoverUpdater::addTask(shared_ptr<ZLExecutionData> data) {
	myDataVector.clear();
	if (!data.isNull()) {
		myDataVector.push_back(data);
	}
}

bool CoverUpdater::hasTasks() const {
	return !myDataVector.empty();
}

void CoverUpdater::run() {
	AppLog("CoverUpdater::run()");
	ZLExecutionData::perform(myDataVector);
}

CoverUpdaterRunner::CoverUpdaterRunner(shared_ptr<CoverUpdater> updater) : myUpdater(updater) {
}

void CoverUpdaterRunner::run() {
	DBG("CoverUpdaterRunner::run");
	if (myUpdater->hasTasks()) {
		DBG("myUpdater->hasTasks()");
		myUpdater->run();
		//myUpdater->executeWithUI();
		//FBReader::Instance().refreshWindow();
	}
}
*/
ZLTreeDialog::ZLTreeDialog(const ZLResource &resource):myResource(resource),showIcons(true) {
}

ZLTreeDialog::~ZLTreeDialog() {
}



/*
bool ZLTreeDialog::enter(ZLTreeNode* node) {
	 myCurrentNode = node;
	 myCurrentNode->requestChildren(myListener);
	return true;
}
*/
void ZLTreeDialog::update() {
 //   emit layoutChanged();
}
/*
Tizen::Graphics::Bitmap* ZLTreeDialog::makeIcon(Tizen::Graphics::Bitmap* srcBmp){
	Tizen::Graphics::Bitmap *pBmp = new Tizen::Graphics::Bitmap;
	Tizen::Graphics::Rectangle iconRect = Tizen::Graphics::Rectangle(5, 5, 70, 90);
	pBmp->Construct(Tizen::Graphics::Dimension(iconRect.width, iconRect.height), Tizen::Graphics::BITMAP_PIXEL_FORMAT_ARGB8888);
	int imageWidth = srcBmp->GetWidth();
	int imageHeight = srcBmp->GetHeight();
	AppLog("makeIcon image w = %d, h = %d", imageWidth, imageHeight);
	int dy = (iconRect.height - imageHeight) / 2;
	int dx = (iconRect.width - imageWidth) / 2;
	if ((dy<0)||(dx<0)) {
		srcBmp->Scale(Tizen::Graphics::Dimension(iconRect.width, iconRect.height));
		pBmp->Merge(Tizen::Graphics::Point(0,0), *srcBmp, Tizen::Graphics::Rectangle(0,0,iconRect.width,iconRect.height));
	}
	else
		pBmp->Merge(Tizen::Graphics::Point(dx,dy), *srcBmp, Tizen::Graphics::Rectangle(0,0,imageWidth,imageHeight));
	return pBmp;
}
*/
void ZLTreeDialog::loadCovers() {
	DBG("loadCovers");
	/*23
	CoverUpdater *updater = new CoverUpdater;//::create();
	//shared_ptr<CoverUpdater> updater = CoverUpdater::create();
	//if (!updater.isNull())
		{
		AppLog("!updater.isNull");

		const ZLTreeNode::List &nodes = myCurrentNode->children();
		AppLog("loadCovers countnode = %d ",nodes.size());
		int index =0;
		for (ZLTreeNode::List::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
			if (exitThread()) {
			//	AppLog("terminateThread 1");
				break;
			}
			ZLTreeTitledNode &node = *(ZLTreeTitledNode*)*it;
			AppLog("loadCovers loadNode %d",index);
			//if (!node.imageIsUploaded()) continue;
			if (node.getIconData() !=0 ) continue;
			shared_ptr<ZLImage> coverImage = node.image();
			if (exitThread()) {
				AppLog("loadCovers terminateThread 2");
				break;
			}
			if (!coverImage.isNull()) {
					AppLog("loadCovers addTask");
					shared_ptr<ZLExecutionData> exe = coverImage->synchronizationData();
					//if (!exe.isNull()) {AppLog("exe not null");ZLExecutionData::perform(exe);}
					//else {AppLog("exe = null");}
					if (!exe.isNull()) {
						AppLog("loadCovers exe not null");
						ZLExecutionData::perform(exe);
						//updater->addTask(exe);
						//if (updater->hasTasks()) updater->run();
						//coverImage = node.image();

						}
					shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*coverImage);
					if (!coverData.isNull()) {
						AppLog("loadCovers !coverData.isNull");
						ZLImageData &image = *coverData;
						Tizen::Graphics::Bitmap *tmpBmp = 	((ZLbadaImageData&)image).pBitmap;
						node.setIconData((char*)makeIcon(tmpBmp));
						}
					//ZLExecutionData::perform(coverImage->synchronizationData());
					coverImage = 0;
					if (exitThread()) {
								AppLog("terminateThread 2");
								break;
							}
					updateNode(node,index);
				}


			index++;
		//	if (exitThread()) {
		//			AppLog("terminateThread 3");
		//			break;
		//		}
		}
		/*
		if (updater->hasTasks()) {
				AppLog("hasTasks");
				updater->run();
				//ZLTimeManager::Instance().addAutoRemovableTask(new CoverUpdaterRunner(updater));
			}*/
//23	}

//23delete updater;

	DBG("loadCovers end");
}
