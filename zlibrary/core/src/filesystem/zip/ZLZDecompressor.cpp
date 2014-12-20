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
#include <FBase.h>
#include <string.h>

#include <algorithm>

#include "../ZLInputStream.h"
#include "ZLZDecompressor.h"

const size_t IN_BUFFER_SIZE = 2048*2;
const size_t OUT_BUFFER_SIZE = 32768*2;

ZLZDecompressor::ZLZDecompressor(size_t size) : myAvailableSize(size) {
	AppLog("ZLZDecompressor size=%d",size);
	myZStream = new z_stream;
	memset(myZStream, 0, sizeof(z_stream));
	AppLog("ZLZDecompressor myZStream size=%d",sizeof(z_stream));
	inflateInit2(myZStream, -MAX_WBITS);
//	AppLog("ZLZDecompressor::inflateInit2");
	myInBuffer = new char[IN_BUFFER_SIZE];
	myOutBuffer = new char[OUT_BUFFER_SIZE];
//	AppLog("ZLZDecompressor::ZLZDecompressor end");

//	myZStream2 = new z_stream;
//	memset(myZStream2, 0, sizeof(z_stream));
//	inflateInit2(myZStream2, -MAX_WBITS);
//	AppLog("ZLZDecompressor::inflateInit2");
//	myInBuffer2 = new char[IN_BUFFER_SIZE];
//	myOutBuffer2 = new char[OUT_BUFFER_SIZE];
}

ZLZDecompressor::~ZLZDecompressor() {
	AppLog("ZLZDecompressor delete");
	delete[] myInBuffer;
	AppLog("ZLZDecompressor delete myInBuffer");
	delete[] myOutBuffer;
	AppLog("ZLZDecompressor delete myOutBuffer");
	//inflateEnd
    inflateEnd(myZStream);
	AppLog("ZLZDecompressor delete inflateEnd");

	delete myZStream;
	AppLog("ZLZDecompressor delete myZStream");
/*	delete[] myInBuffer2;
	delete[] myOutBuffer2;
	//inflateEnd
    inflateEnd(myZStream2);

	delete myZStream2;*/
}

size_t ZLZDecompressor::decompress(ZLInputStream &stream, char *buffer, size_t maxSize) {
//	AppLog("ZLZDecompressor::decompress myBuffer.length()=%d",myBuffer.length());
	while ((myBuffer.length() < maxSize) && (myAvailableSize > 0)) {
		size_t size = std::min(myAvailableSize, (size_t)IN_BUFFER_SIZE);

		myZStream->next_in = (Bytef*)myInBuffer;
		myZStream->avail_in = stream.read(myInBuffer, size);
	//	AppLog("stream.read=%d",myZStream->avail_in);
	//	memcpy(myInBuffer2,myInBuffer,myZStream->avail_in);

		if (myZStream->avail_in == size) {
			myAvailableSize -= size;
		} else {
			myAvailableSize = 0;
		}
		while (myZStream->avail_in == 0) {
			break;
		}
		while (myZStream->avail_in > 0) {
		/*	myZStream2->next_in = (Bytef*)myInBuffer2;
			myZStream2->avail_in = myZStream->avail_in;
			myZStream2->avail_out = OUT_BUFFER_SIZE;
			myZStream2->next_out = (Bytef*)myOutBuffer2;
*/
		//	AppLog("avail_in=%d",myZStream->avail_in);

			myZStream->avail_out = OUT_BUFFER_SIZE;
			myZStream->next_out = (Bytef*)myOutBuffer;

			int code = ::inflate(myZStream, Z_SYNC_FLUSH);
			if ((code != Z_OK) && (code != Z_STREAM_END)) {
	//			AppLog("break 1");
				break;
			}
			if (OUT_BUFFER_SIZE == myZStream->avail_out) {
	//			AppLog("break 2");
				break;
			}
	//		AppLog("inflate myZStream avail_out=%d",myZStream->avail_out);

	/*		int code2 = ::inflate(myZStream2, Z_SYNC_FLUSH);
			if ((code2 != Z_OK) && (code2 != Z_STREAM_END)) {
	//			AppLog("break 3");
				break;
			}
			if (OUT_BUFFER_SIZE == myZStream2->avail_out) {
	//			AppLog("break 4");
				break;
			}*/
			int iSize = OUT_BUFFER_SIZE - myZStream->avail_out;
/*			bool test = true;
			for (int i=0;i<iSize;i++){
				if (myOutBuffer[i]!=myOutBuffer2[i]) test=false;
			}*/
	//		AppLog("iSize= %d Undecompress test %s",iSize,(test)?"true":"false");
			myBuffer.append(myOutBuffer, OUT_BUFFER_SIZE - myZStream->avail_out);
			if (code == Z_STREAM_END) {
				myAvailableSize = 0;
				stream.seek(0 - myZStream->avail_in, false);
				break;
			}
		}
	}
	size_t realSize = std::min(maxSize, myBuffer.length());
	if (buffer != 0) {
		memcpy(buffer, myBuffer.data(), realSize);
	}
	myBuffer.erase(0, realSize);
	return realSize;
}
