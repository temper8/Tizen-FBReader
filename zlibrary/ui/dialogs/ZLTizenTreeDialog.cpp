/*
 * ZLTizenTreeDialog.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: alex
 */

#include "ZLTizenTreeDialog.h"
#include "ZLTreeTitledNode.h"
#include "logger.h"
#include "../ZLTizenApplicationWindow.h"


class item_data	{
	public:
		item_data() {};
		~item_data() {};
		int index;
		char* title;
		char* subtitle;
		Elm_Object_Item *item;
		ZLTreeNode *node;
};

ZLTizenTreeDialog::ZLTizenTreeDialog(const ZLResource &resource): ZLTreeDialog(resource) {
	// TODO Auto-generated constructor stub

}

ZLTizenTreeDialog::~ZLTizenTreeDialog() {
	// TODO Auto-generated destructor stub
	DBG("ZLTizenTreeDialog::destructor");
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
	DBG("ZLTizenTreeDialog::run end");
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

/*
const char *list_items[] = {
	"default",
	"default_style",
	"double_label",
	"end_icon",
	"full",
	"group_index",
	"one_icon",
	"message",
	NULL
};
*/

static Eina_Bool tree_dialog_pop_cb(void *data, Elm_Object_Item *it) {
	DBG("tree_dialog_pop_cb");
	ZLTizenApplicationWindow *tw = (ZLTizenApplicationWindow*)data;
	tw->myTreeDialog = 0;
//	 elm_naviframe_item_pop(it);
	return EINA_TRUE;//EINA_FALSE;
}

static Evas_Object* gl_content_get_cb(void *data, Evas_Object *obj, const char *part) {
	DBG("gl_content_get_cb");
	return NULL;
}

static void gl_del_cb(void *data, Evas_Object *obj) {
	DBG("gl_del_cb");
	/* FIXME: Unrealized callback can be called after this. */
	/* Accessing item_data_s can be dangerous on unrealized callback. */
	//item_data_s *id = data;
	//free(id);
}
static char* gl_text_get_cb(void *data, Evas_Object *obj, const char *part) {
//	DBG("gl_text_get_cb %s", part);
	item_data *id = (item_data *)data;
//	DBG("id->index %d", id->index);
	if (!strcmp(part, "elm.text")) {
						return strdup(id->title);
			}
	else {
		return strdup(id->subtitle);
	}
/*	ZLTreeTitledNode* node = (ZLTreeTitledNode*) id->node;//->children().at(id->index);
	if (node == NULL) DBG(" node = NULL");
	std::string title = node->title();
	DBG("title %s",title.c_str());
/*	std::string subtitle = node->subtitle();
 return strdup(title.c_str());*/

}
static void gl_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	ZLTizenTreeDialog* myTreeDialog = (ZLTizenTreeDialog* )data;

	Elm_Object_Item *it = (Elm_Object_Item *)event_info;
	item_data *id = (item_data *) elm_object_item_data_get(it);
	DBG("%d", id->index);
	ZLTreeNode* node = myTreeDialog->myCurrentNode->children().at(id->index);
	DBG("treenode");
    int actionsCount = node->actions().size();
	DBG("node->actions().size %d", actionsCount);
	/* Unhighlight item */
	elm_genlist_item_selected_set(it, EINA_FALSE);
}

void ZLTizenTreeDialog::createItemsList(Evas_Object *nf){
	/* Create genlist */
	itemsList = elm_genlist_add(nf);

	/* Optimize your application with appropriate genlist block size. */
	elm_genlist_block_count_set(itemsList, 14);

	/* COMPRESS MODE
   	   For the Mobile view, because it has full window, compresse mode should be used.
   	   If multiline text (multiline textblock or sliding mode)
   	   is used, use compress mode for compressing width to fit the viewport width. */

	elm_genlist_mode_set(itemsList, ELM_LIST_COMPRESS);

//	evas_object_event_callback_add(genlist, EVAS_CALLBACK_MOUSE_DOWN, gl_mouse_down_cb, NULL);
//	evas_object_smart_callback_add(genlist, "realized", gl_realized_cb, NULL);
//	evas_object_smart_callback_add(genlist, "loaded", gl_loaded_cb, NULL);
	evas_object_smart_callback_add(itemsList, "selected", gl_selected_cb, this);
//	evas_object_smart_callback_add(genlist, "longpressed", gl_longpressed_cb, NULL);

	Elm_Object_Item *nf_it = elm_naviframe_item_push(nf, "tree dialog", NULL, NULL,	itemsList, NULL);
	elm_naviframe_item_pop_cb_set(nf_it, tree_dialog_pop_cb, myWindows);
}

void ZLTizenTreeDialog::updateContent(){
	DBG("updateContent");
	if (myCurrentNode == NULL) return;
	ItemCount = myCurrentNode->children().size();
	if (ItemCount == 0) DBG("Empty List!");
	if (itemsList == NULL) DBG("itemsList == NULL!");

	const char *style = "double_label";

	/* Create item class */
	Elm_Genlist_Item_Class *itc = elm_genlist_item_class_new();
	itc->item_style = style;
	itc->func.content_get = gl_content_get_cb;
	itc->func.text_get = gl_text_get_cb;
	itc->func.del = gl_del_cb;

	int i;
	Elm_Object_Item *it;
	for (i = 0; i<ItemCount; i++) {
		ZLTreeTitledNode* node = (ZLTreeTitledNode*) myCurrentNode->children().at(i);
		//std::string title = node->title();
		//std::string subtitle = node->subtitle();
		//DBG("title %s",title.c_str());
		DBG("i %d",i);
		item_data *id = new item_data();
		id->index = i;
		//id->node = myCurrentNode->children().at(i);
		id->title = strdup(node->title().c_str());
		id->subtitle = strdup(node->subtitle().c_str());
		it = elm_genlist_item_append(itemsList,					/* genlist object */
									itc,						/* item class */
									id,							/* item class user data */
									NULL,
									ELM_GENLIST_ITEM_NONE,		/* item type */
									NULL,						/* select smart callback */
									id);
		id->item = it;
		}

	elm_genlist_item_class_free(itc);
}
