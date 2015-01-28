/*
 * OptionsDialogTreeNodes.h
 *
 *  Created on: 12.12.2011
 *      Author: Alex
 */

#ifndef OPTIONSDIALOGTREENODES_H_
#define OPTIONSDIALOGTREENODES_H_

#include <ZLTreeTitledNode.h>
//#include <ZLTreeListener.h>
//#include <ZLTreeActionNode.h>
#include <ZLOptions.h>

#include <ZLResource.h>
#include "ZLRunnable.h"

#include "../tree/FBNode.h"

//ShowLibraryOptionsDialogAction       +
//ShowNetworkOptionsDialogAction       -
//ShowSystemOptionsDialogAction        +
//ShowReadingOptionsDialogAction       +
//ShowLookAndFeelOptionsDialogAction   +

//#include <ZLTextKind.h>

class ZLTextStyleDecoration;

class TextStyleNode : public FBNode {
	public:
		static const ZLTypeId TYPE_ID;

	public:
		const ZLTypeId &typeId() const;
		//TODO may be other name
		//ZLTextKind myTextStyle;
		//TextStyleNode(ZLTextKind style);

		TextStyleNode(ZLTextStyleDecoration &decoration);
		ZLTextStyleDecoration &myTextStyleDecoration;
	public:
		std::string title() const;
		std::string subtitle() const;
		virtual bool activate();
		std::string imageUrl() const;
		shared_ptr<ZLImage> extractCoverImage() const;

};


class TextStylesTreeNode : public FBNode {
	public:
		static const ZLTypeId TYPE_ID;

	public:
		const ZLTypeId &typeId() const;
		//TODO may be other name
		TextStylesTreeNode();

	public:
		std::string title() const;
		std::string subtitle() const;
		virtual bool activate();
		std::string imageUrl() const;
		shared_ptr<ZLImage> extractCoverImage() const;
};


class ColorOptionsDialogNode : public FBNode {
	public:
		static const ZLTypeId TYPE_ID;

	public:
		const ZLTypeId &typeId() const;
		//TODO may be other name
		ColorOptionsDialogNode();

	public:
		std::string title() const;
		std::string subtitle() const;
		virtual bool activate();
		std::string imageUrl() const;
		shared_ptr<ZLImage> extractCoverImage() const;
};


class LibraryOptionsDialogNode : public FBNode {
	public:
		static const ZLTypeId TYPE_ID;

	public:
		const ZLTypeId &typeId() const;
		//TODO may be other name
		LibraryOptionsDialogNode();


	public:
		std::string title() const;
		std::string subtitle() const;
		virtual bool activate();
		std::string imageUrl() const;
		shared_ptr<ZLImage> extractCoverImage() const;
};



class SystemOptionsDialogNode : public FBNode {
	public:
		static const ZLTypeId TYPE_ID;

	public:
		const ZLTypeId &typeId() const;
		//TODO may be other name
		SystemOptionsDialogNode();


	public:
		std::string title() const;
		std::string subtitle() const;
		virtual bool activate();
		std::string imageUrl() const;
		shared_ptr<ZLImage> extractCoverImage() const;
};


class ReadingOptionsDialogNode : public FBNode {
	public:
		static const ZLTypeId TYPE_ID;

	public:
		const ZLTypeId &typeId() const;
		//TODO may be other name
		ReadingOptionsDialogNode();


	public:
		std::string title() const;
		std::string subtitle() const;
		virtual bool activate();
		std::string imageUrl() const;
		shared_ptr<ZLImage> extractCoverImage() const;
};

class LookAndFeelOptionsDialogNode : public FBNode {
	public:
		static const ZLTypeId TYPE_ID;

	public:
		const ZLTypeId &typeId() const;
		//TODO may be other name
		LookAndFeelOptionsDialogNode();


	public:
		std::string title() const;
		std::string subtitle() const;
		virtual bool activate();
		std::string imageUrl() const;
		shared_ptr<ZLImage> extractCoverImage() const;

	private:
	//	ZLStringOption DirectoryOption;
	//	ZLStringOption FileOption;
};

class OptionsDialogNode : public FBNode {
	public:
		static const ZLTypeId TYPE_ID;

	public:
		const ZLTypeId &typeId() const;
		//TODO may be other name
		OptionsDialogNode(shared_ptr<ZLRunnableWithKey> action);

	public:

		std::string title() const;
		std::string subtitle() const;
		virtual bool activate();
		std::string imageUrl() const;
		shared_ptr<ZLImage> extractCoverImage() const;

	private:

		shared_ptr<ZLRunnableWithKey> myAction;
		//ZLRunnableWithKey &myRunnableWithKey;
	//	ZLStringOption DirectoryOption;
	//	ZLStringOption FileOption;
};


#endif /* OPTIONSDIALOGTREENODES_H_ */
