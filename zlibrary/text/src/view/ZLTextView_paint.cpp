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

#include <algorithm>

#include "ZLTextView.h"
#include "ZLTextPositionIndicator.h"

void ZLTextView::paint() {
	context().clear(backgroundColor());
	DBG("ZLTextView::paint()");
//    context().clear(ZLColor(255, 0, 255));

// Тестовый крест
//	context().setColor(ZLColor(127, 127, 127));
//	context().drawLine(10, 10, 200 , 400);

//	context().setColor(ZLColor(0, 255, 0));
//	context().drawLine(10, 600, 200 , 100);

	myTextAreaController.area().setOffsets(
		textArea().isRtl() ? rightMargin() : leftMargin(), topMargin()
	);

	preparePaintInfo();
	DBG("textArea()");
	if (textArea().isEmpty()) {
		DBG("правда  textArea().isEmpty()");
		return;
	}
	DBG("myTextAreaController.area().paint();");
	myTextAreaController.area().paint();

	shared_ptr<ZLTextPositionIndicatorInfo> indicatorInfo = this->indicatorInfo();
	if (!indicatorInfo.isNull() && (indicatorInfo->type() == ZLTextPositionIndicatorInfo::FB_INDICATOR)) {
		positionIndicator()->draw();
	}

	if (myDoUpdateScrollbar && !indicatorInfo.isNull()) {
		myDoUpdateScrollbar = false;
		const size_t full = positionIndicator()->sizeOfTextBeforeParagraph(positionIndicator()->endTextIndex());
		const size_t from = positionIndicator()->sizeOfTextBeforeCursor(textArea().startCursor());
		const size_t to = positionIndicator()->sizeOfTextBeforeCursor(textArea().endCursor());

		bool showScrollbar =
			(indicatorInfo->type() == ZLTextPositionIndicatorInfo::OS_SCROLLBAR) &&
			(to - from < full);
		if (showScrollbar) {
		//	setScrollbarEnabled(VERTICAL, true);
		//	setScrollbarParameters(VERTICAL, full, from, to);
		} else {
		//	setScrollbarEnabled(VERTICAL, false);
		}
	}

	ZLTextParagraphCursorCache::cleanup();
}
