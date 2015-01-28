/*
 * OptionsDialogTreeNodes.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Alex
 */

#include "OptionsDialogTreeNodes.h"
#include "OptionsDialogActions.h"


#include <ZLTextStyle.h>
#include <ZLTextStyleCollection.h>
#include <ZLTextStyleOptions.h>

#include "../options/FBTextStyle.h"
#include "../bookmodel/FBTextKind.h"

const ZLTypeId OptionsDialogNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &OptionsDialogNode::typeId() const {
	return TYPE_ID;
}

const ZLTypeId LibraryOptionsDialogNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &LibraryOptionsDialogNode::typeId() const {
	return TYPE_ID;
}

const ZLTypeId SystemOptionsDialogNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &SystemOptionsDialogNode::typeId() const {
	return TYPE_ID;
}

const ZLTypeId ReadingOptionsDialogNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &ReadingOptionsDialogNode::typeId() const {
	return TYPE_ID;
}

const ZLTypeId LookAndFeelOptionsDialogNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &LookAndFeelOptionsDialogNode::typeId() const {
	return TYPE_ID;
}


const ZLTypeId ColorOptionsDialogNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &ColorOptionsDialogNode::typeId() const {
	return TYPE_ID;
}

const ZLTypeId TextStylesTreeNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &TextStylesTreeNode::typeId() const {
	return TYPE_ID;
}

const ZLTypeId TextStyleNode::TYPE_ID(ZLTreeTitledNode::TYPE_ID);

const ZLTypeId &TextStyleNode::typeId() const {
	return TYPE_ID;
}

std::string TextStyleNode::title() const {
        //TODO add not-toolbar resource for this node
        return myTextStyleDecoration.name();//ZLResource::resource("toolbar")["addBook"]["label"].value();
}

std::string TextStyleNode::subtitle() const {
        //TODO add not-toolbar resource for this node
        return std::string();//ZLResource::resource("toolbar")["addBook"]["tooltip"].value();
}
//(shared_ptr<Author> author): myAuthor(author)
//			TextStyleNode(const shared_ptr<ZLTextStyleDecoration> decoration)
//TextStyleNode::TextStyleNode(ZLTextKind style) : FBNode(), myTextStyle(style)  {
TextStyleNode::TextStyleNode(ZLTextStyleDecoration &decoration) : myTextStyleDecoration(decoration)  {
//	registerAction(new LookAndFeelOptionsDialogAction());
	registerAction(new TextStyleOptionsDialogAction(decoration));
}

bool TextStyleNode::activate() {
	return false;
}

std::string TextStyleNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-folder.png");
}

shared_ptr<ZLImage> TextStyleNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}

/*
std::string TextStylesTreeNode::title() const {
        //TODO add not-toolbar resource for this node
        return "Text Styles";//ZLResource::resource("toolbar")["addBook"]["label"].value();
}

std::string TextStylesTreeNode::subtitle() const {
        //TODO add not-toolbar resource for this node
        return ZLResource::resource("toolbar")["addBook"]["tooltip"].value();
}
*/
std::string TextStylesTreeNode::title() const {
        //TODO add not-toolbar resource for this node
 //       return myAction->key().Name;//"xxxLook And Feel Options";//ZLResource::resource("toolbar")["addBook"]["label"].value();
    return ZLResource::resource("Preferences")["textStyles"].value();
//   return ZLResource::resource("toolbar")["addBook"]["tooltip"].value();
}

std::string TextStylesTreeNode::subtitle() const {
        //TODO add not-toolbar resource for this node
	return ZLResource::resource("Preferences")["textStyles"]["summary"].value();
      //  return ZLResource::resource("toolbar")["addBook"]["tooltip"].value();
}



static const ZLResourceKey KEY_STYLE("style");

TextStylesTreeNode::TextStylesTreeNode()  {
	const ZLResource &styleResource = ZLResource::resource(KEY_STYLE);

    size_t index = 0;
	ZLTextStyleCollection &collection = ZLTextStyleCollection::Instance();
	ZLTextKind styles[] = { REGULAR, TITLE, SECTION_TITLE, SUBTITLE, H1, H2, H3, H4, H5, H6, CONTENTS_TABLE_ENTRY, LIBRARY_ENTRY, ANNOTATION, EPIGRAPH, AUTHOR, DATEKIND, POEM_TITLE, STANZA, VERSE, CITE, INTERNAL_HYPERLINK, EXTERNAL_HYPERLINK, BOOK_HYPERLINK, FOOTNOTE, ITALIC, EMPHASIS, BOLD, STRONG, DEFINITION, DEFINITION_DESCRIPTION, PREFORMATTED, CODE };
	const int STYLES_NUMBER = sizeof(styles) / sizeof(ZLTextKind);
	for (int i = 0; i < STYLES_NUMBER; ++i) {
		ZLTextStyleDecoration *decoration = collection.decoration(styles[i]);
		if (decoration != 0) {
		//	AppLog("ZLTextStyleDecoration %s",decoration->name().c_str());
			insert(new TextStyleNode(*decoration), index++);

		}
	}

}

bool TextStylesTreeNode::activate() {
	return false;
}

std::string TextStylesTreeNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-folder.png");
}

shared_ptr<ZLImage> TextStylesTreeNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}


std::string ColorOptionsDialogNode::title() const {
        //TODO add not-toolbar resource for this node
        return "Color Options";//ZLResource::resource("toolbar")["addBook"]["label"].value();
}

std::string ColorOptionsDialogNode::subtitle() const {
        //TODO add not-toolbar resource for this node
        return ZLResource::resource("toolbar")["addBook"]["tooltip"].value();
}

ColorOptionsDialogNode::ColorOptionsDialogNode()  {
//	registerAction(new LookAndFeelOptionsDialogAction());
	registerAction(new ColorOptionsDialogAction());
}

bool ColorOptionsDialogNode::activate() {
	return false;
}

std::string ColorOptionsDialogNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-folder.png");
}

shared_ptr<ZLImage> ColorOptionsDialogNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}




std::string LibraryOptionsDialogNode::title() const {
        //TODO add not-toolbar resource for this node
       // return "Library Options";//ZLResource::resource("toolbar")["addBook"]["label"].value();
        return ZLResource::resource("Preferences")["library"].value();
}

std::string LibraryOptionsDialogNode::subtitle() const {
        //TODO add not-toolbar resource for this node
       // return std::string();
        return ZLResource::resource("Preferences")["library"]["summary"].value();

}

//static const std::string GROUP_NAME = "OpenFileDialog";

LibraryOptionsDialogNode::LibraryOptionsDialogNode()  {
//	registerAction(new LookAndFeelOptionsDialogAction());
	registerAction(new LibraryOptionsDialogAction());
}

bool LibraryOptionsDialogNode::activate() {
	return false;
}

std::string LibraryOptionsDialogNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-folder.png");
}

shared_ptr<ZLImage> LibraryOptionsDialogNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}




std::string SystemOptionsDialogNode::title() const {
        //TODO add not-toolbar resource for this node
        return "System Options";//ZLResource::resource("toolbar")["addBook"]["label"].value();
}

std::string SystemOptionsDialogNode::subtitle() const {
        //TODO add not-toolbar resource for this node
        return std::string();
}

//static const std::string GROUP_NAME = "OpenFileDialog";

SystemOptionsDialogNode::SystemOptionsDialogNode()  {
//	registerAction(new LookAndFeelOptionsDialogAction());
	registerAction(new SystemOptionsDialogAction());
}

bool SystemOptionsDialogNode::activate() {
	return false;
}

std::string SystemOptionsDialogNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-folder.png");
}


shared_ptr<ZLImage> SystemOptionsDialogNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}


std::string ReadingOptionsDialogNode::title() const {
        //TODO add not-toolbar resource for this node
        return "Reading Options";//ZLResource::resource("toolbar")["addBook"]["label"].value();
}

std::string ReadingOptionsDialogNode::subtitle() const {
        //TODO add not-toolbar resource for this node
        return std::string();
}

//static const std::string GROUP_NAME = "OpenFileDialog";

ReadingOptionsDialogNode::ReadingOptionsDialogNode()  {
//	registerAction(new LookAndFeelOptionsDialogAction());
	registerAction(new ReadingOptionsDialogAction());
}

bool ReadingOptionsDialogNode::activate() {
	return false;
}

std::string ReadingOptionsDialogNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-folder.png");
}


shared_ptr<ZLImage> ReadingOptionsDialogNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}




std::string LookAndFeelOptionsDialogNode::title() const {
        //TODO add not-toolbar resource for this node
        return "Look And Feel Options";//ZLResource::resource("toolbar")["addBook"]["label"].value();
}

std::string LookAndFeelOptionsDialogNode::subtitle() const {
        //TODO add not-toolbar resource for this node
        return std::string();
}

//static const std::string GROUP_NAME = "OpenFileDialog";

LookAndFeelOptionsDialogNode::LookAndFeelOptionsDialogNode()  {
	registerAction(new LookAndFeelOptionsDialogAction());
//	registerAction(new ReadingOptionsDialogAction());
}

bool LookAndFeelOptionsDialogNode::activate() {
	return false;
}

std::string LookAndFeelOptionsDialogNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-folder.png");
}

shared_ptr<ZLImage> LookAndFeelOptionsDialogNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}

//-----------------------------------------------------------

OptionsDialogNode::OptionsDialogNode(shared_ptr<ZLRunnableWithKey> action):myAction(action)  {
	registerAction(action);
//	registerAction(new ReadingOptionsDialogAction());
}

std::string OptionsDialogNode::title() const {
        //TODO add not-toolbar resource for this node
 //       return myAction->key().Name;//"xxxLook And Feel Options";//ZLResource::resource("toolbar")["addBook"]["label"].value();
    return ZLResource::resource("Preferences")[myAction->key().Name].value();
//   return ZLResource::resource("toolbar")["addBook"]["tooltip"].value();
}

std::string OptionsDialogNode::subtitle() const {
        //TODO add not-toolbar resource for this node
	return ZLResource::resource("Preferences")[myAction->key().Name]["summary"].value();
      //  return ZLResource::resource("toolbar")["addBook"]["tooltip"].value();
}


bool OptionsDialogNode::activate() {
	return false;
}

std::string OptionsDialogNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-folder.png");
}

shared_ptr<ZLImage> OptionsDialogNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}
