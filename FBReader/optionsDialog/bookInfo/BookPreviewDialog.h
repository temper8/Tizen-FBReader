/*
 * BookPreviewDialog.h
 *
 *  Created on: 28.01.2012
 *      Author: Alex
 */

#ifndef BOOKPREVIEWDIALOG_H_
#define BOOKPREVIEWDIALOG_H_

#include <string>

#include <ZLOptionEntry.h>

#include "../../formats/FormatPlugin.h"


class SimpleBookPreviewDialog {
public:
	SimpleBookPreviewDialog(shared_ptr<Book> book);
	virtual ~SimpleBookPreviewDialog();

	ZLOptionsDialog &dialog();

private:
	shared_ptr<ZLOptionsDialog> myDialog;
	shared_ptr<Book> myBook;

	friend class BookPreviewTitleEntry;
	friend class BookOpenAction;
};

inline ZLOptionsDialog &SimpleBookPreviewDialog::dialog() { return *myDialog; }


class BookPreviewDialog {
public:
	BookPreviewDialog(shared_ptr<Book> book);
	virtual ~BookPreviewDialog();

	ZLOptionsDialog &dialog();

private:
	shared_ptr<ZLOptionsDialog> myDialog;
	shared_ptr<Book> myBook;

	friend class BookPreviewTitleEntry;
	friend class BookOpenAction;
};

inline ZLOptionsDialog &BookPreviewDialog::dialog() { return *myDialog; }

#endif /* BOOKPREVIEWDIALOG_H_ */
