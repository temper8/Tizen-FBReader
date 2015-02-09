/*
 * ZLTizenTreeDialog.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#include "ZLTizenTreeDialog.h"

#include "logger.h"

ZLTizenTreeDialog::ZLTizenTreeDialog(const ZLResource &resource): ZLTreeDialog(resource) {
	// TODO Auto-generated constructor stub

}

ZLTizenTreeDialog::~ZLTizenTreeDialog() {
	// TODO Auto-generated destructor stub
}

void ZLTizenTreeDialog::onNodeBeginInsert(ZLTreeNode *parent, size_t index) {
	DBG("ZLbadaTreeDialog::onNodeBeginInsert");
     //   myModel->onNodeBeginInsert(parent,index);
}

void ZLTizenTreeDialog::onNodeEndInsert() {
	DBG("ZLbadaTreeDialog::onNodeEndInsert");
    //    myModel->onNodeEndInsert();
	// myForm->requestUpdateContent();
}

void ZLTizenTreeDialog::onNodeBeginRemove(ZLTreeNode *parent, size_t index) {
	DBG("ZLbadaTreeDialog::onNodeBeginRemove");
     //   myModel->onNodeBeginRemove(parent,index);
}
void ZLTizenTreeDialog::onNodeEndRemove() {
	DBG("ZLbadaTreeDialog::onNodeEndRemove");
    //    myModel->onNodeEndRemove();
}


void ZLTizenTreeDialog::onNodeUpdated(ZLTreeNode *node) {
	DBG("ZLbadaTreeDialog::onNodeUpdated");
   // myModel->onNodeUpdated(node);
}

void ZLTizenTreeDialog::run() {
	DBG("ZLbadaTreeDialog::run");
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
