/*
 * ZLTizenTreeDialog.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#include "ZLTizenTreeDialog.h"
#include "ZLTreeTitledNode.h"
#include "logger.h"

ZLTizenTreeDialog::ZLTizenTreeDialog(const ZLResource &resource): ZLTreeDialog(resource) {
	// TODO Auto-generated constructor stub

}

ZLTizenTreeDialog::~ZLTizenTreeDialog() {
	// TODO Auto-generated destructor stub
}

void ZLTizenTreeDialog::onNodeBeginInsert(ZLTreeNode *parent, size_t index) {
//	DBG("ZLbadaTreeDialog::onNodeBeginInsert");
     //   myModel->onNodeBeginInsert(parent,index);
}

void ZLTizenTreeDialog::onNodeEndInsert() {
//	DBG("ZLbadaTreeDialog::onNodeEndInsert");
    //    myModel->onNodeEndInsert();
	// myForm->requestUpdateContent();
}

void ZLTizenTreeDialog::onNodeBeginRemove(ZLTreeNode *parent, size_t index) {
//	DBG("ZLbadaTreeDialog::onNodeBeginRemove");
     //   myModel->onNodeBeginRemove(parent,index);
}
void ZLTizenTreeDialog::onNodeEndRemove() {
//	DBG("ZLbadaTreeDialog::onNodeEndRemove");
    //    myModel->onNodeEndRemove();
}


void ZLTizenTreeDialog::onNodeUpdated(ZLTreeNode *node) {
//	DBG("ZLbadaTreeDialog::onNodeUpdated");
   // myModel->onNodeUpdated(node);
}

void ZLTizenTreeDialog::run() {
	DBG("ZLTizenTreeDialog::run");
	myCurrentNode = &rootNode();
	updateContent();
}


void ZLTizenTreeDialog::updateNode(ZLTreeTitledNode &node, int index){
	DBG("updateNode %d", index);
}

bool ZLTizenTreeDialog::enter(ZLTreeNode* node) {
	 DBG("enter node");
	 return true;
}

void ZLTizenTreeDialog::onUpdated(){

}

bool ZLTizenTreeDialog::back() {
	DBG("ZLbadaTreeDialog::back()");
	 return true;
}

void ZLTizenTreeDialog::treadTerminator(){

}

void ZLTizenTreeDialog::updateContent(){
	DBG("updateContent");
	if (myCurrentNode == NULL) return;
	ItemCount = myCurrentNode->children().size();
	if (ItemCount == 0) DBG("Empty List!");
	int i;
	for (i = 0; i<ItemCount; i++) {

		ZLTreeTitledNode* node = (ZLTreeTitledNode*) myCurrentNode->children().at(i);
		//	const ZLTreeTitledNode *TitledNode = zlobject_cast<const ZLTreeTitledNode*>(node);
			std::string title = node->title();
			DBG("title %s",title.c_str());
			elm_list_item_append(listItems, title.c_str(), NULL, NULL, NULL, NULL);
		}

	elm_list_go(listItems);
}
