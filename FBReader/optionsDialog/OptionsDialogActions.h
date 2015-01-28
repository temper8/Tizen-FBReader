/*
 * OptionsDialogActions.h
 *
 *  Created on: 11.12.2011
 *      Author: Alex
 */

#ifndef OPTIONSDIALOGACTIONS_H_
#define OPTIONSDIALOGACTIONS_H_

#include <ZLResource.h>
#include "ZLRunnable.h"
#include <shared_ptr.h>
//ShowLibraryOptionsDialogAction       +
//ShowNetworkOptionsDialogAction       -
//ShowSystemOptionsDialogAction		   +
//ShowReadingOptionsDialogAction       +
//ShowLookAndFeelOptionsDialogAction   +


class ZLTextStyleDecoration;

class TextStyleOptionsDialogAction : public ZLRunnableWithKey {

public:
	TextStyleOptionsDialogAction(ZLTextStyleDecoration &decoration);
	void run();
	ZLResourceKey key() const;
	ZLTextStyleDecoration &myTextStyleDecoration;
};

class ColorOptionsDialogAction : public ZLRunnableWithKey {

public:
	ColorOptionsDialogAction();
	void run();
	ZLResourceKey key() const;
};



class LibraryOptionsDialogAction : public ZLRunnableWithKey {

public:
	LibraryOptionsDialogAction();
	void run();
	ZLResourceKey key() const;
};

class SystemOptionsDialogAction : public ZLRunnableWithKey {

public:
	SystemOptionsDialogAction();
	void run();
	ZLResourceKey key() const;
};

class ReadingOptionsDialogAction : public ZLRunnableWithKey {

public:
	ReadingOptionsDialogAction();
	void run();
	ZLResourceKey key() const;
};

class LookAndFeelOptionsDialogAction : public ZLRunnableWithKey {

public:
	LookAndFeelOptionsDialogAction();
	void run();
	ZLResourceKey key() const;

private:
	//const shared_ptr<Book> myBook;
};

class TextOptionsDialogAction : public ZLRunnableWithKey {
public:
	TextOptionsDialogAction();
	void run();
	ZLResourceKey key() const;

};


class MarginsOptionsDialogAction : public ZLRunnableWithKey {
public:
	MarginsOptionsDialogAction();
	void run();
	ZLResourceKey key() const;
};

class AppearanceOptionsDialogAction : public ZLRunnableWithKey {
public:
	AppearanceOptionsDialogAction();
	void run();
	ZLResourceKey key() const;
};

class IndicatorOptionsDialogAction : public ZLRunnableWithKey {
public:
	IndicatorOptionsDialogAction();
	void run();
	ZLResourceKey key() const;
};

class PageTurningOptionsDialogAction : public ZLRunnableWithKey {
public:
	PageTurningOptionsDialogAction();
	void run();
	ZLResourceKey key() const;
};


#endif /* OPTIONSDIALOGACTIONS_H_ */
