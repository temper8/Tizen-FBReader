/*
 * ZLTizenDialog.h
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#ifndef ZLTIZENDIALOG_H_
#define ZLTIZENDIALOG_H_



#include <ZLDialog.h>

class ZLTizenDialog :  public ZLDialog {

public:
	ZLTizenDialog(const ZLResource &resource);
	~ZLTizenDialog();

	void addButton(const ZLResourceKey &key, bool accept);
	bool run();

private:

};
#endif /* ZLTIZENDIALOG_H_ */
