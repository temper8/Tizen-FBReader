/*
 * BookPreviewDialog.cpp
 *
 *  Created on: 28.01.2012
 *      Author: Alex
 */
#include <algorithm>

#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>
#include <ZLOptionEntry.h>
#include <ZLFile.h>
#include <ZLLanguageList.h>
#include <ZLStringUtil.h>

#include <optionEntries/ZLStringInfoEntry.h>
#include <optionEntries/ZLSimpleOptionEntry.h>
#include <optionEntries/ZLLanguageOptionEntry.h>

#include "BookInfoDialog.h"
#include "../../libraryTree/LibraryNodes.h"
#include "../../library/Library.h"
#include "../../encodingOption/EncodingOptionEntry.h"
#include "../../library/Book.h"
#include "../../library/Tag.h"
#include "../../library/Author.h"
#include "../../libraryActions/LibraryBookActions.h"
#include "BookPreviewDialog.h"

#include "../../tree/FBNode.h"
#include "../../fbreader/FBReader.h"
#include "../../formats/FormatPlugin.h"
#include "PreviewEntries.h"
#include "BookInfoDialog.h"

class BookMenuEntry : public ZLMenuOptionEntry {

public:
	BookMenuEntry(shared_ptr<Book> book);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);
};


BookMenuEntry::BookMenuEntry(shared_ptr<Book> book) : ZLMenuOptionEntry() {

menuActions.push_back(new BookReadAction(book));
menuActions.push_back(new BookReadAction(book));
//	menuActions.push_back(new BookRemoveAction(book));
}

const std::string &BookMenuEntry::initialValue() const {
	return std::string();
}

void BookMenuEntry::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}


class BookPictureEntry : public ZLPictureOptionEntry {

public:
	BookPictureEntry(shared_ptr<Book> book);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);
};



BookPictureEntry::BookPictureEntry(shared_ptr<Book> book) : ZLPictureOptionEntry() {
	shared_ptr<FormatPlugin> plugin = PluginCollection::Instance().plugin(*book);
	if (!plugin.isNull()) {
		myImage = plugin->coverImage(book->file());
		}
	if (myImage.isNull())	myImage = FBNode::defaultCoverImage("booktree-book.png");
	bookActions.push_back(new BookReadAction(book));
	bookActions.push_back(new BookReadAction(book));
	bookActions.push_back(new BookRemoveAction(book));
}

const std::string &BookPictureEntry::initialValue() const {
	return std::string();
}

void BookPictureEntry::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}


class BookPreviewTitleEntry : public ZLStringOptionEntry {

public:
	BookPreviewTitleEntry(BookPreviewDialog &dialog);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);

private:
	BookPreviewDialog &myPreviewDialog;
};

BookPreviewTitleEntry::BookPreviewTitleEntry(BookPreviewDialog &dialog) : myPreviewDialog(dialog) {
}

const std::string &BookPreviewTitleEntry::initialValue() const {
	return myPreviewDialog.myBook->title();
}

void BookPreviewTitleEntry::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}

/*

class BookOpenAction : public ZLRunnable {

public:
	BookOpenAction(shared_ptr<Book> book);
	void run();

private:
	shared_ptr<Book> myBook;
};

BookOpenAction::BookOpenAction(shared_ptr<Book> book) : myBook(book) {}

void BookOpenAction::run() {
	AppLog("BookOpenAction::run");
	//Book &book = *myPreviewDialog.myBook;
	FBReader &fbreader = FBReader::Instance();
	fbreader.openBook(myBook);
	fbreader.showBookTextView();
	//AppLog("BookOpenAction %s",book.title().c_str());
}
*/
//-----------------------------   SimpleBookPreviewDialog -----------

SimpleBookPreviewDialog::SimpleBookPreviewDialog(shared_ptr<Book> book) : myBook(book)  {
	// TODO Auto-generated constructor stub
//	myDialog = ZLDialogManager::Instance().createOptionsDialog(ZLResourceKey("InfoDialog"), new BookReadAction(myBook));
	myDialog = ZLDialogManager::Instance().createOptionsDialog(ZLResourceKey("InfoDialog"), 0);

//	myDialog->setMenuEntry( new BookMenuEntry(book));
	ZLDialogContent &commonTab = myDialog->createTab(ZLResourceKey("Cover"));
//	AppLog("myDialog->createTab");
	shared_ptr<ZLImage> bookImage;


    bookImage = FBNode::defaultCoverImage("booktree-book.png");
	commonTab.addOption(ZLResourceKey("cover"), new BookPictureEntry(book));
//	commonTab.addOption(ZLResourceKey("cover"), new BookMenuEntry(book));

	ZLDialogContent &BookInfoTab = myDialog->createTab(ZLResourceKey("BookInfo"));
	//commonTab.addOption(ZLResourceKey("title"), new BookPreviewTitleEntry(*this));
	BookInfoTab.addOption(ZLResourceKey("title"), new StaticTextEntry(myBook->title()));
//	AppLog("commonTab.addOption title");
	//ZLStringUtil::join(book->authors(), AuthorFunctor(), FBNode::COMMA_JOIN_SEPARATOR);
	std::string authors = ZLStringUtil::join(myBook->authors(),AuthorFunctor(), FBNode::COMMA_JOIN_SEPARATOR);
	BookInfoTab.addOption(ZLResourceKey("authors"), new StaticTextEntry(authors));
	BookInfoTab.addOption(ZLResourceKey("seriesTitle"), new StaticTextEntry(myBook->seriesTitle()));

	std::vector<std::string> languageCodes = ZLLanguageList::languageCodes();
	languageCodes.push_back("de-traditional");
	BookLanguageEntry* bookLanEntry = new BookLanguageEntry(myBook, languageCodes);
	std::string language = bookLanEntry->initialValue();
	//BookInfoTab.addOption(ZLResourceKey("language"), bookLanEntry);
	//bookLanEntry->setActive(false);
	BookInfoTab.addOption(ZLResourceKey("language"), new StaticTextEntry(language));
	delete bookLanEntry;

	//commonTab.addOption(ZLResourceKey("file"), new ZLStringInfoEntry(ZLFile::fileNameToUtf8(book->file().path())));
	ZLDialogContent &SummaryTab = myDialog->createTab(ZLResourceKey("Common"));
	//SummaryTab.addOption(ZLResourceKey("title"), new StaticTextEntry(myBook.Summary));
//	ZLStringInfoEntry* fileNameOption =  new ZLStringInfoEntry(ZLFile::fileNameToUtf8(book->file().path()));
//	SummaryTab.addOption(ZLResourceKey("file"),fileNameOption);
//	fileNameOption->setActive(false);
	std::string filePath = ZLFile::fileNameToUtf8(book->file().path());
	SummaryTab.addOption(ZLResourceKey("file"), new StaticTextEntry(filePath));
//	AppLog("commonTab.addOption file");

//	std::vector<std::string> languageCodes = ZLLanguageList::languageCodes();
//	languageCodes.push_back("de-traditional");

//	myLanguageEntry = new BookLanguageEntry(*this, languageCodes);
	//	AppLog("myLanguageEntry = new BookLanguageEntry");
//	BookLanguageEntry* bookLanEntry = new BookLanguageEntry(myBook, languageCodes);
//	SummaryTab.addOption(ZLResourceKey("language"), bookLanEntry);
//	bookLanEntry->setActive(false);

}

SimpleBookPreviewDialog::~SimpleBookPreviewDialog() {
	// TODO Auto-generated destructor stub
}

// ----------------------------     BookPreviewDialog  ---------------
BookPreviewDialog::BookPreviewDialog(shared_ptr<Book> book) : myBook(book)  {
	// TODO Auto-generated constructor stub
//	myDialog = ZLDialogManager::Instance().createOptionsDialog(ZLResourceKey("InfoDialog"), new BookReadAction(myBook));
	myDialog = ZLDialogManager::Instance().createOptionsDialog(ZLResourceKey("InfoDialog"), 0);

	myDialog->setMenuEntry( new BookMenuEntry(book));
	ZLDialogContent &commonTab = myDialog->createTab(ZLResourceKey("Cover"));
//	AppLog("myDialog->createTab");
	shared_ptr<ZLImage> bookImage;


    bookImage = FBNode::defaultCoverImage("booktree-book.png");
	commonTab.addOption(ZLResourceKey("cover"), new BookPictureEntry(book));
//	commonTab.addOption(ZLResourceKey("cover"), new BookMenuEntry(book));

	ZLDialogContent &BookInfoTab = myDialog->createTab(ZLResourceKey("BookInfo"));
	//commonTab.addOption(ZLResourceKey("title"), new BookPreviewTitleEntry(*this));
	BookInfoTab.addOption(ZLResourceKey("title"), new StaticTextEntry(myBook->title()));
//	AppLog("commonTab.addOption title");
	//ZLStringUtil::join(book->authors(), AuthorFunctor(), FBNode::COMMA_JOIN_SEPARATOR);
	std::string authors = ZLStringUtil::join(myBook->authors(),AuthorFunctor(), FBNode::COMMA_JOIN_SEPARATOR);
	BookInfoTab.addOption(ZLResourceKey("authors"), new StaticTextEntry(authors));
	BookInfoTab.addOption(ZLResourceKey("seriesTitle"), new StaticTextEntry(myBook->seriesTitle()));

	std::vector<std::string> languageCodes = ZLLanguageList::languageCodes();
	languageCodes.push_back("de-traditional");
	BookLanguageEntry* bookLanEntry = new BookLanguageEntry(myBook, languageCodes);
	std::string language = bookLanEntry->initialValue();
	//BookInfoTab.addOption(ZLResourceKey("language"), bookLanEntry);
	//bookLanEntry->setActive(false);
	BookInfoTab.addOption(ZLResourceKey("language"), new StaticTextEntry(language));
	delete bookLanEntry;

	//commonTab.addOption(ZLResourceKey("file"), new ZLStringInfoEntry(ZLFile::fileNameToUtf8(book->file().path())));
	ZLDialogContent &SummaryTab = myDialog->createTab(ZLResourceKey("Common"));
	//SummaryTab.addOption(ZLResourceKey("title"), new StaticTextEntry(myBook.Summary));
	//ZLStringInfoEntry* fileNameOption =  new ZLStringInfoEntry(ZLFile::fileNameToUtf8(book->file().path()));
	//SummaryTab.addOption(ZLResourceKey("file"),fileNameOption);
	//fileNameOption->setActive(false);

	std::string filePath = ZLFile::fileNameToUtf8(book->file().path());
	SummaryTab.addOption(ZLResourceKey("file"), new StaticTextEntry(filePath));

//	AppLog("commonTab.addOption file");



//	myLanguageEntry = new BookLanguageEntry(*this, languageCodes);
	//	AppLog("myLanguageEntry = new BookLanguageEntry");


}

BookPreviewDialog::~BookPreviewDialog() {
	// TODO Auto-generated destructor stub
}
