/*
 * ZLTizenTreeDialog.h
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#ifndef ZLTIZENTREEDIALOG_H_
#define ZLTIZENTREEDIALOG_H_

#include <ZLTreeDialog.h>
#include <Elementary.h>

class ZLTizenApplicationWindow;
class ZLTizenTreeDialog: public ZLTreeDialog {
public:
	ZLTizenTreeDialog(const ZLResource &resource);
	virtual ~ZLTizenTreeDialog();

	virtual void onNodeBeginInsert(ZLTreeNode *parent, size_t index);
	virtual void onNodeEndInsert();
	virtual void onNodeBeginRemove(ZLTreeNode *parent, size_t index);
	virtual void onNodeEndRemove();
	virtual void onNodeUpdated(ZLTreeNode *node);
	virtual void run();

	virtual void onUpdated();

public:

	virtual bool back();
	virtual bool enter(ZLTreeNode* node);
	virtual void updateNode(ZLTreeTitledNode &node, int index);
	virtual void treadTerminator();
	//virtual void setShowIcons(bool value) {};
	//virtual bool exitThread();
public:
	void createItemsList(Evas_Object *nf);
	void updateContent();
	Evas_Object *itemsList;
	int ItemCount;
	ZLTizenApplicationWindow* myWindows;
};

#endif /* ZLTIZENTREEDIALOG_H_ */
