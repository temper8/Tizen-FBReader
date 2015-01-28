/*
 * PreviewEntries.h
 *
 *  Created on: 01.02.2012
 *      Author: Alex
 */

#ifndef PREVIEWENTRIES_H_
#define PREVIEWENTRIES_H_

#include <ZLOptionEntry.h>

class ButtonEntry : public ZLButtonOptionEntry {

public:
	ButtonEntry(shared_ptr<ZLRunnableWithKey> action);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);

private:
//	const std::string &myString;
};


class StaticTextEntry : public ZLStaticTextOptionEntry {

public:
	StaticTextEntry(const std::string &value);

	const std::string &initialValue() const;

private:
	const std::string &myString;
};

class StringEntry : public ZLStringOptionEntry {

public:
	StringEntry(const std::string &value);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);

private:
	const std::string &myString;
};

#endif /* PREVIEWENTRIES_H_ */
