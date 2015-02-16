/*
 * TizenPictureView.h
 *
 *  Created on: Feb 14, 2015
 *      Author: alex
 */

#ifndef TIZENPICTUREVIEW_H_
#define TIZENPICTUREVIEW_H_

#include "ZLTizenOptionView.h"

class TizenPictureView: public ZLTizenOptionView {
public:

	TizenPictureView(const std::string &name, const std::string &tooltip, ZLPictureOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn);

protected:

	virtual Evas_Object* createViewItem(Evas_Object *parent);
	void _createItem();
	void _onAccept() const;
	shared_ptr<ZLImage> myImage;
	const  std::vector<shared_ptr<ZLRunnableWithKey> > &myActions;
//	Tizen::Graphics::Bitmap* makeCover(Tizen::Graphics::Bitmap* srcBmp);
//	void createActionButtons(Tizen::Ui::Controls::TableViewItem* pItem);

};
#endif /* TIZENPICTUREVIEW_H_ */