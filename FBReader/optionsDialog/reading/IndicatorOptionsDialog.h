/*
 * IndicatorOptionsDialog.h
 *
 *  Created on: 13.04.2012
 *      Author: Alex
 */

#ifndef INDICATOROPTIONSDIALOG_H_
#define INDICATOROPTIONSDIALOG_H_

#include "../AbstractOptionsDialog.h"

class IndicatorOptionsDialog : public AbstractOptionsDialog {
private:
	void createIndicatorTab();
public:
	IndicatorOptionsDialog();
	virtual ~IndicatorOptionsDialog();
};

#endif /* INDICATOROPTIONSDIALOG_H_ */
