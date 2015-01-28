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

#ifndef __ZLTREETITLEDNODE_H__
#define __ZLTREETITLEDNODE_H__

#include <ZLTreeNode.h>
#include <ZLImage.h>

class ZLTreeTitledNode : public ZLTreeNode {

public:
	static const ZLTypeId TYPE_ID;
	const ZLTypeId &typeId() const;

        static const std::string ZLIMAGE_SCHEME;
        static const std::string LOCALFILE_SCHEME;
        static const std::string SCHEME_POSTFIX;

public:
	ZLTreeTitledNode();
	virtual ~ZLTreeTitledNode();
	
	// Usually node looks like
	// +-------+---------------+
	// |       |  TITLE        |
	// | image |             > |
	// |       |  subtitle     |
	// +-------+---------------+
	// Name of book


	bool myIsInitialized;
	virtual void init();

	virtual std::string title() const = 0;
	// Short description
	virtual std::string subtitle() const;
	// Url to image
	virtual std::string imageUrl() const;
	// Or the image if there is no url
	virtual shared_ptr<ZLImage> image() const;
	virtual bool imageIsUploaded() const;
	char *myIconData;
	virtual char* getIconData() const;
	virtual void setIconData(char* iconData);
	virtual shared_ptr<ZLImage> extractCoverImage() const = 0;
};

#endif /* __ZLTREETITLEDNODE_H__ */
