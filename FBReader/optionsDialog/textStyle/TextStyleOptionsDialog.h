/*
 * TextStyleOptionsDialog.h
 *
 *  Created on: 21.12.2011
 *      Author: Alex
 */

#ifndef TEXTSTYLEOPTIONSDIALOG_H_
#define TEXTSTYLEOPTIONSDIALOG_H_

#include "../AbstractOptionsDialog.h"

class ZLTextStyleDecoration;

class TextStyleOptionsDialog : public AbstractOptionsDialog {
public:
	TextStyleOptionsDialog(ZLTextStyleDecoration &decoration);
	virtual ~TextStyleOptionsDialog();
	ZLTextStyleDecoration &myTextStyleDecoration;
};

#endif /* TEXTSTYLEOPTIONSDIALOG_H_ */
