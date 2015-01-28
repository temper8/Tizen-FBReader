#include "LibraryTreeNodes.h"

#include "../library/Library.h"
#include "LibraryNodes.h"

const ZLTypeId TagTreeNode::TYPE_ID(FBNode::TYPE_ID);

const ZLTypeId &TagTreeNode::typeId() const {
        return TYPE_ID;
}

TagTreeNode::TagTreeNode() {
        //TODO may be add lazy initialization here
//	AppLog("TagTreeNode");
        const TagList &tags = Library::Instance().tags();
//    	AppLog("TagTreeNode 2");
        size_t index = 0;
        for (TagList::const_iterator it=tags.begin(); it!=tags.end(); ++it) {
 //       	AppLog("TagTreeNode insert TagNode");
                insert(new TagNode(*it), index++);
        }
}

std::string TagTreeNode::title() const {
        return ZLResource::resource("library")["byTag"].value();
}

std::string TagTreeNode::subtitle() const {
        return ZLResource::resource("library")["byTag"]["summary"].value();
}

std::string TagTreeNode::imageUrl() const {
	return FBNode::defaultImageUrl("booktree-tags.png");
}

shared_ptr<ZLImage> TagTreeNode::extractCoverImage() const {
	//AppLog("AuthorNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-tags.png");
}
