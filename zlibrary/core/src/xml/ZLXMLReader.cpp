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

#include <string.h>

#include <algorithm>

#include <ZLFile.h>
#include <ZLInputStream.h>
#include <ZLUnicodeUtil.h>
#include <ZLEncodingConverter.h>

#include <ZLAsynchronousInputStream.h>

#include "ZLXMLReader.h"

#include "expat/ZLXMLReaderInternal.h"

//static const size_t BUFFER_SIZE = 1024;
//static const size_t BUFFER_SIZE = 2048;
//static const size_t BUFFER_SIZE = 4096;
//static const size_t BUFFER_SIZE = 8192*16;
static const size_t BUFFER_SIZE = 16384;
//static const size_t BUFFER_SIZE = 32768;

class ZLXMLReaderHandler : public ZLAsynchronousInputStream::Handler {

public:
	ZLXMLReaderHandler(ZLXMLReader &reader);

	void initialize(const char *encoding);
	void shutdown();
	bool handleBuffer(const char *data, size_t len);

private:
	ZLXMLReader &myReader;
};

ZLXMLReaderHandler::ZLXMLReaderHandler(ZLXMLReader &reader) : myReader(reader) {
}

void ZLXMLReaderHandler::initialize(const char *encoding) {
	myReader.initialize(encoding);
}

void ZLXMLReaderHandler::shutdown() {
	myReader.shutdown();
}

bool ZLXMLReaderHandler::handleBuffer(const char *data, size_t len) {
//	AppLog(" ZLXMLReader::handleBuffer   %d", len);
	return myReader.readFromBuffer(data, len);
	//myReader.myInternalReader->parseBuffer(data, len);
/*	size_t length, start = 0, BUFFER_SIZE = 512;
	do {
		length = len - start;
		if (length>BUFFER_SIZE) length=BUFFER_SIZE;
		AppLog(" handleBuffer length = %d", length);
		myReader.myInternalReader->parseBuffer(data + start, length);
		start += length;

	} while ((start < len) && !myReader.myInterrupted);
	AppLog(" ZLXMLReader::handleBuffer end");
	return true;*/
}





void ZLXMLReader::startElementHandler(const char*, const char**) {
}

void ZLXMLReader::endElementHandler(const char*) {
}

void ZLXMLReader::characterDataHandler(const char*, size_t) {
}

void ZLXMLReader::namespaceListChangedHandler() {
}

const std::map<std::string,std::string> &ZLXMLReader::namespaces() const {
	return *myNamespaces.back();
}

ZLXMLReader::ZLXMLReader(const char *encoding): myParserBuffer(0) {
//	AppLog("create ZLXMLReader");
	myInternalReader = new ZLXMLReaderInternal(*this, encoding);

}

ZLXMLReader::~ZLXMLReader() {
//	AppLog("delete ZLXMLReader");
	if 	(myParserBuffer !=0 ) delete[] myParserBuffer;
	delete myInternalReader;
}

void ZLXMLReader::afterReadDocument(){
//	AppLog("#######  afterReadDocument");
}

bool ZLXMLReader::readDocument(const ZLFile &file) {
	return readDocument(file.inputStream());
}

bool ZLXMLReader::readDocument(shared_ptr<ZLInputStream> stream) {
//	AppLog("#######  ZLXMLReader::readDocument");
	if (stream.isNull() || !stream->open()) {
//		AppLog(" ZLXMLReader::readDocument return false;");
		return false;
	}
//	AppLog(" ZLXMLReader::readDocument 1");
	bool useWindows1252 = false;
	char *encoding = 0;
	if 	(myParserBuffer ==0 ) myParserBuffer = new char[BUFFER_SIZE];
	stream->read(myParserBuffer, 4);
//	AppLog(" ZLXMLReader::readDocument 2");
	//std::string stringBuffer(myParserBuffer, 256);
//	stream->seek(0, true);
//	AppLog(" ZLXMLReader::readDocument 3");
	/*
	std::string stringBuffer(512,' ');
	stringBuffer.assign(myParserBuffer, 256);
	//	AppLog(" ZLXMLReader::readDocument stringBuffer =%s",stringBuffer.c_str());
	//AppLog(" ZLXMLReader::readDocument 4");
	int index = stringBuffer.find('>');

	if (index > 0) {
		stringBuffer = ZLUnicodeUtil::toLower(stringBuffer.substr(0, index));
		int index = stringBuffer.find("\"iso-8859-1\"");
		if (index > 0) {
			useWindows1252 = true;
			encoding ="windows-1252";
		}
		index = stringBuffer.find("\"windows-1251\"");
		if (index > 0) {
			//useWindows1252 = true;
			encoding ="windows-1251";
		}
		index = stringBuffer.find("\"koi8-r\"");
		if (index > 0) {
			//useWindows1252 = true;
			encoding ="KOI8-R";
		}
	}

	//initialize(useWindows1252 ? "windows-1252" : 0);
	if (encoding != 0) {AppLog("init encoding %s",encoding);}
	*/
//	AppLog("initialize(encoding);");

	initialize(encoding);
	size_t length;
//	AppLog("before do");
	do {
		length = stream->read(myParserBuffer, BUFFER_SIZE);
		//AppLog(" ZLXMLReader::readDocument length = %d", length);
		if (!readFromBuffer(myParserBuffer, length)) {
//			AppLog(" ZLXMLReader::readDocument break");
			break;
		}

	} while ((length == BUFFER_SIZE) && !myInterrupted);
//	AppLog("after while");
	stream->close();

	shutdown();

	return true;
}

void ZLXMLReader::initialize(const char *encoding) {
	myInternalReader->createPushParserCtxt(myParserBuffer);
	myInternalReader->init(encoding);
	myInterrupted = false;
	myNamespaces.push_back(new std::map<std::string, std::string>());
}

void ZLXMLReader::shutdown() {
	myInternalReader->freePushParserCtxt(myParserBuffer);
	myNamespaces.clear();
}

bool ZLXMLReader::readFromBuffer(const char *data, size_t len) {
//	AppLog(" ZLXMLReader::readFromBuffer");
	return myInternalReader->parseBuffer(data, len);
}

bool ZLXMLReader::processNamespaces() const {
	return false;
}

const std::vector<std::string> &ZLXMLReader::externalDTDs() const {
	static const std::vector<std::string> EMPTY_VECTOR;
	return EMPTY_VECTOR;
}

const char *ZLXMLReader::attributeValue(const char **xmlattributes, const char *name) {
	while (*xmlattributes != 0) {
		bool useNext = strcmp(*xmlattributes, name) == 0;
		++xmlattributes;
		if (*xmlattributes == 0) {
			return 0;
		}
		if (useNext) {
			return *xmlattributes;
		}
		++xmlattributes;
	}
	return 0;
}

ZLXMLReader::AttributeNamePredicate::~AttributeNamePredicate() {
}

ZLXMLReader::FixedAttributeNamePredicate::FixedAttributeNamePredicate(const std::string &attributeName) : myAttributeName(attributeName) {
}

bool ZLXMLReader::FixedAttributeNamePredicate::accepts(const ZLXMLReader&, const char *name) const {
	return myAttributeName == name;
}

ZLXMLReader::NamespaceAttributeNamePredicate::NamespaceAttributeNamePredicate(const std::string &ns, const std::string &name) : myNamespaceName(ns), myAttributeName(name) {
}

bool ZLXMLReader::NamespaceAttributeNamePredicate::accepts(const ZLXMLReader &reader, const char *name) const {
	const std::map<std::string,std::string> &namespaces = reader.namespaces();
	for (std::map<std::string,std::string>::const_iterator it = namespaces.begin(); it != namespaces.end(); ++it) {
		if (it->second == myNamespaceName) {
			return it->first + ':' + myAttributeName == name;
		}
	}
	return false;
}

const char *ZLXMLReader::attributeValue(const char **xmlattributes, const AttributeNamePredicate &predicate) {
	while (*xmlattributes != 0) {
		bool useNext = predicate.accepts(*this, *xmlattributes);
		++xmlattributes;
		if (*xmlattributes == 0) {
			return 0;
		}
		if (useNext) {
			return *xmlattributes;
		}
		++xmlattributes;
	}
	return 0;
}

bool ZLXMLReader::readDocument(shared_ptr<ZLAsynchronousInputStream> stream) {
//	AppLog("#######  readDocument ZLAsynchronousInputStream");
	ZLXMLReaderHandler handler(*this);
	bool result = stream->processInput(handler);
	afterReadDocument();
	return result;
}

const std::string &ZLXMLReader::errorMessage() const {
	return myErrorMessage;
}

void ZLXMLReader::setErrorMessage(const std::string &message) {
	myErrorMessage = message;
	interrupt();
}
