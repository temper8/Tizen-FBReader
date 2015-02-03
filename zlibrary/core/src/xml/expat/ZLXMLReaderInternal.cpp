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
#include "logger.h"
#include <string.h>

#include <ZLFile.h>
#include <ZLInputStream.h>
#include <ZLEncodingConverter.h>

#include "ZLXMLReaderInternal.h"
#include "ZLXMLReader.h"
#include <stdlib.h>
#include <libxml/xmlexports.h>

#include <libxml/parser.h>

//void ZLXMLReaderInternal::fCharacterDataHandler(void *userData, const char *text, int len) {
//void fCharacterDataHandler(void *userData, const char *text, int len) {
static void fCharacterDataHandler(void *userData,	const xmlChar *text, int len) {
//	char buf[100];
//	DBG("ZLXMLReaderInternal::fCharacterDataHandler");
//	DBG("fCharacterDataHandler len=%d",len);
	ZLXMLReader &reader = *(ZLXMLReader*)userData;
	if (!reader.isInterrupted()) {
		//DBG("fCharacterDataHandler l=%d",l);
		reader.characterDataHandler((const char*)text, len);
	//	if (len<50) {
	//		memset(buf, 0, 99);
	//	    strncpy(buf, (const char*)text, len);
	//	AppLog("fCharacterDataHandler text=%s",buf);
	//	}
	//DBG("fCharacterDataHandler end");
	}
}


//void ZLXMLReaderInternal::fStartElementHandler(void *userData, const char *name, const char **attributes) {
//typedef void(* startElementSAXFunc)(void *ctx, const xmlChar *name, const xmlChar **atts)
//void fStartElementHandler(void *userData, const char *name, const char **attributes) {
void fStartElementHandler2(void *userData, const char *name, const char **attributes) {

//	DBG("fStartElementHandler2::name=%s",(const char*)name);
//	if (*attributes!=0) 	AppLog("fStartElementHandler:: attr = %s::%s",(const char*)attributes[0],(const char*)attributes[1]);
//	else {AppLog("A!=0"); return;}
	ZLXMLReader *reader = (ZLXMLReader*)userData;
	//AppLog("ZLXMLReader &reader");
	if (!reader->isInterrupted()) {
		//DBG("!reader.isInterrupted()");
		if (reader->processNamespaces()) {
			int count = 0;
			//DBG("int count = 0");
			//DBG("attr = %s::%s",(const char*)attributes[0],(const char*)attributes[1]);
			for (const char **a = (const char**)attributes; (*a != 0) && (*(a + 1) != 0); a += 2) {
				//AppLog("*a=%s",*a);
				if (strncmp(*a, "xmlns:", 6) == 0) {
					if (count == 0) {
						reader->myNamespaces.push_back(
							new std::map<std::string,std::string>(*reader->myNamespaces.back())
						);
					}
					++count;
					const std::string id(*a + 6);
					const std::string reference(*(a + 1));
					(*reader->myNamespaces.back())[id] = reference;
				}
			}
			if (count == 0) {
				reader->myNamespaces.push_back(reader->myNamespaces.back());
			} else {
				reader->namespaceListChangedHandler();
			}
		}
		//DBG("reader.startElementHandler");
		if (attributes!=0)
		{
		//	DBG("reader.startElementHandler if ");
			reader->startElementHandler((const char*)name, (const char**)attributes);
			//reader->endElementHandler((const char*)name);
		}
		else
		{
		//	DBG("reader.startElementHandler if attributes==0 сюда не должен попадать");
			const char* c[1];
			*c=0;
			reader->startElementHandler((const char*)name, c);
		}
		//DBG("reader.startElementHandler end ");

	}
}
static void fStartElementHandler(void *userData, const xmlChar *name, const xmlChar **attributes){
//	DBG("fStartElementHandler  name = %s",(const char*)name);

	if (attributes!=0)
	{
			fStartElementHandler2(userData, (const char*)name, (const char**)attributes);
	    }
		else
		{
			const char* c[1];
			*c=0;//DBG("c=0");
			fStartElementHandler2(userData, (const char*)name, c);
		}
}
//void ZLXMLReaderInternal::fEndElementHandler(void *userData, const char *name) {
//typedef void(* endElementSAXFunc)(void *ctx, const xmlChar *name)
//void fEndElementHandler(void *userData, const char *name) {
static void fEndElementHandler(void *userData, const xmlChar *name) {
	//DBG("fEndElementHandler name = %s",(const char*)name );
	ZLXMLReader &reader = *(ZLXMLReader*)userData;
	if (!reader.isInterrupted()) {
	//	AppLog("reader.endElementHandler");
		reader.endElementHandler((const char*)name);
	//	AppLog("reader.endElementHandler ok");
		if (reader.processNamespaces()) {
	//		AppLog("reader.processNamespaces ok");
			shared_ptr<std::map<std::string,std::string> > oldMap = reader.myNamespaces.back();
	//		AppLog("reader.myNamespaces.pop_back()");
			reader.myNamespaces.pop_back();
			if (reader.myNamespaces.back() != oldMap) {
			//	AppLog("reader.namespaceListChangedHandler()");
				reader.namespaceListChangedHandler();
			}
		}
	}
}

static xmlDocPtr ParseEntity;

xmlEntityPtr fgetEntity(	void * 	user_data, 	const xmlChar * name){
//	AppLog("fgetEntity %s",name );
	//ZLXMLReader &reader = *(ZLXMLReader*)userData;
	xmlEntityPtr ep = xmlGetPredefinedEntity(name);
	if (ep) {
//		AppLog("ExternalID	 %s",ep->ExternalID);
//		AppLog("SystemID	 %s",ep->SystemID);
		 return ep;}
	//if (strncmp((const char*)name, "FBReaderVersion", 14) == 0) {
//	AppLog("FBReaderVersion !!!!!!!");
	//return  xmlGetPredefinedEntity(name);
	//const xmlChar *const xmlChar *c="lt"="lt";
	ep = xmlGetDocEntity( ParseEntity, name);
	if (ep) return ep;
//	AppLog("Облом с  xmlGetDocEntity!!!!!!!");
	return xmlGetPredefinedEntity((xmlChar *)"lt");
}

static void	funparsedEntityDeclSAXFunc	(void * ctx,
					 const xmlChar * name,
					 const xmlChar * publicId,
					 const xmlChar * systemId,
					 const xmlChar * notationName){
//	AppLog("funparsedEntityDeclSAXFunc %s",name );
}


static int fHasInternalSubsetSAXFunc (void *ctx)
{
//	AppLog("fHasInternalSubsetSAXFunc" );
	return 0;
}


static int fHasExternalSubsetSAXFunc (void *ctx)
{
//	AppLog("fHasExternalSubsetSAXFunc" );
	return 0;
}


static void fWarningSAXFunc (void *ctx,
				const char *msg, ...)
{
//	AppLog("fWarningSAXFunc msg = %s",msg );
}
static xmlParserInputPtr fResolveEntitySAXFunc (void *ctx, const xmlChar *publicId, const xmlChar *systemId)
{
//	AppLog("fResolveEntitySAXFunc" );
	return NULL;
}

static void fEntityDeclSAXFunc (void *ctx, 	const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId, xmlChar *content)
{
//	AppLog("fEntityDeclSAXFunc" );
}
static void fUnparsedEntityDeclSAXFunc(void *ctx, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName)
{
//	AppLog("fUnparsedEntityDeclSAXFunc" );
}


/*
static int fUnknownEncodingHandler(void*, const XML_Char *name, XML_Encoding *encoding) {
	ZLEncodingConverterInfoPtr info = ZLEncodingCollection::Instance().info(name);
	if (!info.isNull()) {
		shared_ptr<ZLEncodingConverter> converter = info->createConverter();
		//converter
		if (!converter.isNull() && converter->fillTable(encoding->map)) {
			return XML_STATUS_OK;
		}
	}
	return XML_STATUS_ERROR;
}
*/

//static void parseDTD(XML_Parser parser, const std::string &fileName) {
static void parseDTD(xmlParserCtxtPtr ctxt, const std::string &fileName) {
/*	AppLog("parseDTD XML_ParserCreate");
	//xmlSAXParseEntity(xmlSAXHandlerPtr sax, filename.c_str());
	const char *URL = fileName.c_str();
	xmlParserCtxtPtr entityCtxt = xmlCreateEntityParserCtxt((const xmlChar*)URL,(const xmlChar*)"FBReader Ent",NULL);
	if (entityCtxt == NULL) AppLog("entityCtxt == NULL");

//	XML_Parser entityParser = XML_ExternalEntityParserCreate(parser, 0, 0);
	ZLFile dtdFile(fileName);
	shared_ptr<ZLInputStream> entityStream = dtdFile.inputStream();
	if (!entityStream.isNull() && entityStream->open()) {
		const size_t BUFSIZE = 2048;
		char buffer[BUFSIZE];
		size_t length;
		do {
			length = entityStream->read(buffer, BUFSIZE);
			int r = xmlParseChunk(entityCtxt, buffer, length, 0);
			AppLog("parseDTD xmlParseChunk r=%d len = %d", r, length);
			//AppLog("ctxt->encoding = %s", entityStream->encoding);
			if (r != 0) {
				break;
			}
		} while (length == BUFSIZE);
	}
    xmlParseChunk(entityCtxt, 0, 0, 1);
    xmlFreeParserCtxt(entityCtxt);
	//XML_ParserFree(entityParser);

	 */
}



static void fErrorSAXFunc (void *ctx, const char *msg, ...)
{
//    va_list args;

//    va_start(args, msg);
    //g_logv("XML", G_LOG_LEVEL_CRITICAL, msg, args);
//    AppLog("fErrorSAXFunc %s", msg);
//    AppLog(msg, args);
 //   va_end(args);

}

static void fFatalErrorSAXFunc (void *ctx,	const char *msg, ...)
{
//	AppLog("fFatalErrorSAXFunc %s", msg);
}

//ZLEncodingConverterInfoPtr ZLXMLReaderInternal::encodingInfo;

int	ZLXMLReaderInternal::fxmlCharEncodingInputFunc(unsigned char * out, int * outlen,
					 const unsigned char * in,  int * inlen)
{
//	AppLog("fxmlCharEncodingInputFunc inlen=%d",*inlen);
	*outlen = *inlen;
	memcpy(out,(char*)in,*outlen);
	return *outlen;

}
int	fxmlCharEncodingOutputFunc(unsigned char * out, int * outlen,
					 const unsigned char * in,  int * inlen)
{
//	AppLog("xmlCharEncodingOutputFunc");
	return -1;
}
//MySaxhandler.startElement = fStartElementHandler;
//MySaxhandler.endElement = fEndElementHandler;
//MySaxhandler.characters = fCharacterDataHandler;
//MySaxhandler.warning =	fWarningSAXFunc;
//MySaxhandler.hasExternalSubset = fHasInternalSubsetSAXFunc;
//MySaxhandler.hasInternalSubset = fHasExternalSubsetSAXFunc;
//MySaxhandler.resolveEntity = fResolveEntitySAXFunc;
//MySaxhandler.unparsedEntityDecl = fUnparsedEntityDeclSAXFunc;
//MySaxhandler.getEntity = fgetEntity;
//MySaxhandler.error = fErrorSAXFunc;
//MySaxhandler.fatalError = fFatalErrorSAXFunc;
//MySaxhandler.unparsedEntityDecl = funparsedEntityDeclSAXFunc;

xmlSAXHandler mySaxHandler =
{
		NULL,
		NULL,
fHasInternalSubsetSAXFunc,
fHasExternalSubsetSAXFunc,
fResolveEntitySAXFunc,
fgetEntity,
NULL,
NULL,
NULL,
NULL,
fUnparsedEntityDeclSAXFunc,
NULL,
NULL,
NULL,
fStartElementHandler,
fEndElementHandler,
NULL,
fCharacterDataHandler,
NULL,
NULL,
NULL,
fWarningSAXFunc,
fErrorSAXFunc,
fFatalErrorSAXFunc,
NULL,
NULL,
NULL,
0,
NULL,
NULL,
NULL,
NULL
};



void ZLXMLReaderInternal::init(const char *encoding) {

	if (myInitialized) {
//		AppLog("ZLXMLReaderInternal::myInitialized");
	//	xmlCleanupParser();
//		XML_ParserReset(myParser, encoding);
	}

//	AppLog("ZLXMLReaderInternal::init");

	myInitialized = true;
	/*
	//XML_UseForeignDTD(myParser, XML_TRUE);
	//MySaxhandler.initialized = 1;//XML_PARSER_DTD;//XML_PARSER_START;
//	AppLog("XML_UseForeignDTD %d",xmlSubstituteEntitiesDefault(0));
	const std::vector<std::string> &dtds = myReader.externalDTDs();
	for (std::vector<std::string>::const_iterator it = dtds.begin(); it != dtds.end(); ++it) {
		//myDTDStreamLocks.insert(ZLFile(*it).inputStream());
		AppLog("parseDTD %s",((std::string)*it).c_str());
		//const char *URL = ((std::string)*it).c_str();
		//xmlNodePtr children;
		//if (ctxt == null) AppLog("ctxt == null");
		//if (ctxt->myDoc == NULL) AppLog("ctxt->myDoc == null");
		//int r = xmlParseCtxtExternalEntity(ctxt,(const xmlChar*)URL,(const xmlChar*)"FBReader Ent",	&children);
		//ParseEntity=xmlSAXParseEntity(&MySaxhandler,((std::string)*it).c_str());
		//ParseEntity=xmlParseEntity(((std::string)*it).c_str());
		//AppLog("xmlParseCtxtExternalEntity =%d",r);
	//	if (r==0) AppLog("xmlParseEntity OK"); else AppLog("xmlParseEntity bad");

		//parseDTD(ctxt, *it);
	}
//	XML_SetUserData(myParser, &myReader);
	AppLog("XML_SetUserData");
	if (encoding != 0) {
		AppLog("encoding %s",encoding);
		encodingInfo = ZLEncodingCollection::Instance().info(encoding);
		if (!encodingInfo.isNull()) converter = encodingInfo->createConverter();

		xmlNewCharEncodingHandler(encoding,fxmlCharEncodingInputFunc,fxmlCharEncodingOutputFunc);
		AppLog("xmlNewCharEncodingHandler encoding %s",encoding);
	    }
	//if (encoding != 0) {
		//XML_SetEncoding(myParser, encoding);
//	XML_SetEncoding(myParser, "");
	//}
//	AppLog("xmlSAXVersion %d",xmlSAXVersion(&MySaxhandler,2));
	//xmlInitCharEncodingHandlers	();

*/
//	AppLog("XML_SetEncoding");

}

bool ZLXMLReaderInternal::parseBuffer(const char *buffer, size_t len) {
//	AppLog("xmlParseChunk len = %d",len);
    if (len == 0) return false;
	if (!converter.isNull()) {
//				AppLog("!converter.isNull()");
				//AppLog("fxmlCharEncodingInputFunc parseBuffer 2");
				std::string myBuffer;
				converter->convert(myBuffer, (const char*)buffer, (const char*)(buffer + len));
				int outlen = myBuffer.length();
				int r = xmlParseChunk(ctxt, (char*)myBuffer.data(), outlen, 0);
//				AppLog("ctxt->encoding = %s", ctxt->encoding);
//				AppLog("xmlParseChunk r=%d outlen = %d", r, outlen);
				return (r == 0);
			}

//	AppLog("0ctxt->encoding = %s", ctxt->encoding);
	int r = xmlParseChunk(ctxt, buffer, len, 0);
//	AppLog("xmlParseChunk r=%d len = %d", r, len);
	//TryReturn(r, E_FAILURE, "xmlParseChunk failed.");

//	AppLog("ctxt->encoding = %s", ctxt->encoding);
//	CATCH:
	//	AppLog("CATCH");
	return (r == 0);
	//return true;
}
void ZLXMLReaderInternal::createPushParserCtxt(const char *buffer){
//	AppLog("createPushParserCtxt");
	//ctxt = xmlCreatePushParserCtxt(&MySaxhandler,  &myReader, buffer, 4, NULL);
	ctxt = xmlCreatePushParserCtxt(&mySaxHandler,  myReader, buffer, 4, NULL);
	if (ctxt == NULL) {
//			AppLog("xmlCreatePushParserCtxt контекст создать не удалось");
	     return;
	 }
//	AppLog("1ctxt->encoding = %s", ctxt->encoding);
}
void ZLXMLReaderInternal::freePushParserCtxt(const char *buffer){
//	AppLog("freePushParserCtxt");
	if (ctxt == 0) return;
//	AppLog("freePushParserCtxt 2");
	int r = xmlParseChunk(ctxt, buffer, 0, 1);
//    AppLog("xmlParseChunk r=%d ", r);
    //ctxt = 0;
    xmlFreeParserCtxt(ctxt);
}
ZLXMLReaderInternal::ZLXMLReaderInternal(ZLXMLReader* reader, const char *encoding) : myReader(reader) {
//	AppLog("XML_ParserCreate");
	/*
	MySaxhandler.startElement = fStartElementHandler;
	MySaxhandler.endElement = fEndElementHandler;
	MySaxhandler.characters = fCharacterDataHandler;
	MySaxhandler.warning =	fWarningSAXFunc;
	MySaxhandler.hasExternalSubset = fHasInternalSubsetSAXFunc;
	MySaxhandler.hasInternalSubset = fHasExternalSubsetSAXFunc;
	MySaxhandler.resolveEntity = fResolveEntitySAXFunc;
	MySaxhandler.unparsedEntityDecl = fUnparsedEntityDeclSAXFunc;
	MySaxhandler.getEntity = fgetEntity;
	MySaxhandler.error = fErrorSAXFunc;
	MySaxhandler.fatalError = fFatalErrorSAXFunc;
	MySaxhandler.unparsedEntityDecl = funparsedEntityDeclSAXFunc;
//	AppLog("xmlCreatePushParserCtxt");*/
	myInitialized = false;
}

ZLXMLReaderInternal::~ZLXMLReaderInternal() {
//	AppLog("XML_ParserFree");

//	xmlCleanupParser();
//	XML_ParserFree(myParser);
}

