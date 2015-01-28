/*
 * Copyright (C) 2009-2011 Geometer Plus <contact@geometerplus.com>
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

#include "ZLTreeTitledNode.h"

const ZLTypeId ZLTreeTitledNode::TYPE_ID(ZLTreeNode::TYPE_ID);

const std::string ZLTreeTitledNode::ZLIMAGE_SCHEME("ZLImage");
const std::string ZLTreeTitledNode::LOCALFILE_SCHEME("file");
const std::string ZLTreeTitledNode::SCHEME_POSTFIX("://");

const ZLTypeId &ZLTreeTitledNode::typeId() const {
	return TYPE_ID;
}

ZLTreeTitledNode::ZLTreeTitledNode():myIsInitialized(false),myIconData(0) {
}

ZLTreeTitledNode::~ZLTreeTitledNode() {
	if (myIconData!=0) delete myIconData;
}

std::string ZLTreeTitledNode::subtitle() const {
	return std::string();
}

std::string ZLTreeTitledNode::imageUrl() const {
	return std::string();
}

shared_ptr<ZLImage> ZLTreeTitledNode::image() const {
	return shared_ptr<ZLImage>();
}

bool ZLTreeTitledNode::imageIsUploaded() const {
 return false;
}

void ZLTreeTitledNode::init() {
}


char* ZLTreeTitledNode::getIconData() const {
	return myIconData;
}

void ZLTreeTitledNode::setIconData(char* iconData)  {
	myIconData = iconData;
}
