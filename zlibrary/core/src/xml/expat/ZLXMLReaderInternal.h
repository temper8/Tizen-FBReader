/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
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

#ifndef __ZLXMLREADERINTERNAL_H__
#define __ZLXMLREADERINTERNAL_H__

//#include <expat.h>
//#include "FXml.h"

#include <libxml/parser.h>

//using namespace Tizen::Xml;
//#include "xmlstring.h"

#include <set>

class ZLXMLReader;

class ZLXMLReaderInternal {

private:
//	static void fStartElementHandler(void *userData, const char *name, const char **attributes);
//	static void fEndElementHandler(void *userData, const char *name);
//	static void fCharacterDataHandler(void *userData, const char *text, int len);

public:
	ZLXMLReaderInternal(ZLXMLReader &reader, const char *encoding);
	~ZLXMLReaderInternal();
	void init(const char *encoding = 0);
	bool parseBuffer(const char *buffer, size_t len);
    void createPushParserCtxt(const char *buffer);
    void freePushParserCtxt(const char *buffer);
private:
	ZLXMLReader &myReader;
	xmlSAXHandler _MySaxhandler;
	xmlParserCtxtPtr ctxt;
	//XML_Parser myParser;
	bool myInitialized;
	//static ZLEncodingConverterInfoPtr encodingInfo;
	ZLEncodingConverterInfoPtr encodingInfo;
	shared_ptr<ZLEncodingConverter> converter;
	std::set<shared_ptr<ZLInputStream> > myDTDStreamLocks;
	static int	fxmlCharEncodingInputFunc(unsigned char * out, int * outlen, const unsigned char * in,  int * inlen);
};

#endif /* __ZLXMLREADERINTERNAL_H__ */
