/*
 * Copyright (C) 2009-2010 Geometer Plus <contact@geometerplus.com>
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

#include <ZLResource.h>
#include <ZLImage.h>
#include <ZLStringUtil.h>

#include "LibraryNodes.h"

#include "../library/Book.h"
#include "../library/Author.h"
#include "../library/Tag.h"
#include "../libraryActions/LibraryBookActions.h"

#include "../fbreader/FBReader.h"
#include "../formats/FormatPlugin.h"

//#include "../optionsDialogMobile/MobileBookInfoDialog.h"



static std::string generateSubtitle(const shared_ptr<Book> book, BookNode::SubtitleMode subtitleMode) {
    switch (subtitleMode) {
        case BookNode::SHOW_AUTHORS:
            return ZLStringUtil::join(book->authors(), AuthorFunctor(), FBNode::COMMA_JOIN_SEPARATOR);
        case BookNode::SHOW_TAGS:
            return ZLStringUtil::join(book->tags(), TagFunctor(), FBNode::COMMA_JOIN_SEPARATOR);
    }
    return std::string();
}

const ZLTypeId BookNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &BookNode::typeId() const {
	return TYPE_ID;
}
/*
class ReadBookAction : public ZLTreeAction {
public:
	ReadBookAction(BookNode *node) : myNode(node) {
	}
	
	virtual void run() {
                FBReader::Instance().openBook(myNode->book());
           //     finished(std::string());
                myNode->close();
	}

	virtual ZLResourceKey key() const {
		return ZLResourceKey("read");
	}
	
private:
	BookNode *myNode;
};
*/
BookNode::BookNode(shared_ptr<Book> book, SubtitleMode subtitleMode):
    myBook(book), mySubtitle(generateSubtitle(book,subtitleMode)), myCoverImageIsStored(false) {
	//registerAction(new ReadBookAction(this));
//	AppLog("BookNode::BookNode");
	registerAction(new BookEditInfoAction(myBook));
//	registerAction(new BookReadAction(myBook));
//	registerAction(new BookRemoveAction(myBook));
}

std::string BookNode::title() const {
	return myBook->title();
}
std::string BookNode::subtitle() const {
    return mySubtitle;
}

std::string BookNode::imageUrl() const {
	shared_ptr<ZLImage> image = originalImage();
	if (image.isNull())
		return FBNode::defaultImageUrl("booktree-book.png");
        //TODO may be use this type of link: ZLImage://book_id
        //this is useful for cache
//        std::string url(ZLIMAGE_SCHEME+SCHEME_POSTFIX);
//        ZLStringUtil::appendNumber(url, (unsigned int)myBook->bookId());
//        return url;
        return std::string();
}

shared_ptr<ZLImage> BookNode::extractCoverImage() const {
	return FBNode::defaultCoverImage("booktree-book.png");
}

shared_ptr<ZLImage> BookNode::image() const {
//	AppLog("BookNode::image()");
	shared_ptr<ZLImage> image = originalImage();
	if (image.isNull())
		image = FBNode::defaultCoverImage("booktree-book.png");
	return image;
}

bool BookNode::imageIsUploaded() const {
	return myCoverImageIsStored;
}

shared_ptr<ZLImage> BookNode::originalImage() const {
	if (myCoverImageIsStored)
		return myStoredCoverImage;
	myCoverImageIsStored = true;
//	AppLog("myCoverImageIsStored = true");
	shared_ptr<FormatPlugin> plugin = PluginCollection::Instance().plugin(*myBook);
	if (!plugin.isNull()) {
		myStoredCoverImage = plugin->coverImage(myBook->file());
	}
	return myStoredCoverImage;
}
/*
void BookNode::fillContent(ZLDialogContent &content) const {
	MobileBookInfoDialog::fillContent(content, LocalBookInfo(myBook));
}

ZLResourceKey BookNode::contentKey() const {
	return MobileBookInfoDialog::resourceKey();
}
*/
shared_ptr<Book> BookNode::book() const {
	return myBook;
}

const ZLResource &BookNode::resource() const {
	return ZLResource::resource("libraryView")["bookNode"];
}
