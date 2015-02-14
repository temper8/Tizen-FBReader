#ifndef __ZLTREEDIALOG_H__
#define __ZLTREEDIALOG_H__


#include "../src/tree/ZLTreeListener.h"



class ZLTreeTitledNode;
// This object should be pure successor of ZLTreeListener
// or be merged with it.




class ZLTreeDialog : public ZLTreeListener  {

protected:
	ZLTreeDialog(const ZLResource &resource);
	bool showIcons;

private:
	//virtual bool exitThread() = 0;

public:
	virtual ~ZLTreeDialog();
	const ZLResource &myResource;
	//TODO maybe run() should return an integer?
	virtual void run() = 0;

	// Parent has new child at index
	virtual void onNodeBeginInsert(ZLTreeNode *parent, size_t index) = 0;
	virtual void onNodeEndInsert() = 0;
	// This is also easy to understand
	virtual void onNodeBeginRemove(ZLTreeNode *parent, size_t index) = 0;
	virtual void onNodeEndRemove() = 0;
	// This method should be called at every node state change except of adding/removing of children
	virtual void onNodeUpdated(ZLTreeNode *node) = 0;

	virtual void onUpdated() = 0;

public:
	virtual void setShowIcons(bool value) {}
	virtual bool back() = 0;
	virtual void updateNode(ZLTreeTitledNode &node, int index) = 0;
	virtual bool enter(ZLTreeNode* node) = 0;
    void update();
	ZLTreeNode* myCurrentNode;
	void loadCovers();
	virtual void treadTerminator() =0;

	//ZLTreeListener::RootNode& myRootNode;
	//Tizen::Graphics::Bitmap* makeIcon(Tizen::Graphics::Bitmap* srcBmp);
};


class ZLTreeDialogUpdater : public ZLRunnable {
public:
	ZLTreeDialogUpdater(ZLTreeDialog* treeDialog):myTreeDialog(treeDialog){};
	void run() {myTreeDialog->onUpdated();}
private:
	ZLTreeDialog* myTreeDialog;
};


#endif /* __ZLTREEDIALOG_H__ */
