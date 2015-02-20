/*
 * ZLTizenApplicationWindow.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#include "logger.h"
#include "ZLTizenApplicationWindow.h"
#include "ZLTizenViewWidget.h"
#include "ZLView.h"
#include "../../FBReader/fbreader/FBReader.h"
#include "../../FBReader/fbreader/FBReaderActions.h"

#include "dialogs/ZLTizenTreeDialog.h"
#include "dialogs/ZLTizenOptionsDialog.h"

void ZLTizenApplicationWindow::initMenu() {
	DBG("ZLbadaApplicationWindow::initMenu() ");
	MenuBuilder(*this).processMenu(application());
}

ZLTizenApplicationWindow::MenuBuilder::MenuBuilder(ZLTizenApplicationWindow &window) : myWindow(window) {
	//myMenuStack.push(myWindow.myMenu);
}

void ZLTizenApplicationWindow::MenuBuilder::processSubmenuBeforeItems(ZLMenubar::Submenu &submenu) {
	DBG("ZLbadaApplicationWindow:::MenuBuilder::processSubmenuBeforeItems ");

}

void ZLTizenApplicationWindow::MenuBuilder::processSubmenuAfterItems(ZLMenubar::Submenu&) {
	//myMenuStack.pop();
}

void ZLTizenApplicationWindow::MenuBuilder::processItem(ZLMenubar::PlainItem &item) {
	DBG("MenuBuilder::processItem actionId=%s name=%s",item.actionId().c_str(),item.name().c_str());
	const std::string &id = item.actionId();
	const std::string &name = item.name();

	//shared_ptr<ZLApplication::Action> action = myWindow.application().action(id);
	//myWindow.myViewWidget->mybadaForm->AddMenuItem(name, id);
	myWindow.AddMenuItem(name, id);

}
typedef struct menu_data
{
	 const  std::string *id;
	 ZLTizenApplicationWindow *windows;
} menu_data_s;

void ZLTizenApplicationWindow::onMenuItemSelected(void *data, Evas_Object *obj, void *event_info){
//	elm_panel_hidden_set(drawer_panel, EINA_TRUE);

	//std::string *id = (std::string *)data;

	Elm_Object_Item *it = (Elm_Object_Item *)event_info;
	/* Unhighlight item */
	elm_list_item_selected_set(it, EINA_FALSE);

	menu_data_s *md = (menu_data_s *)data;

	DBG("selected item %s", md->id->c_str());
	FBReader &fbreader = FBReader::Instance();
	fbreader.doAction(*(md->id));
	elm_panel_hidden_set(md->windows->drawer_panel, EINA_TRUE);
}

void ZLTizenApplicationWindow::AddMenuItem(const std::string &name, const  std::string &id){
	menu_data_s *md = (menu_data_s *)calloc(sizeof(menu_data_s), 1);
	md->id = &id;
	md->windows = this;
	elm_list_item_append(menuList, name.c_str(), NULL, NULL, onMenuItemSelected, md);

}

void ZLTizenApplicationWindow::MenuBuilder::processSepartor(ZLMenubar::Separator&) {
}


static void win_delete_request_cb(void *data , Evas_Object *obj , void *event_info)
{
	ui_app_exit();
}

void ZLTizenApplicationWindow::win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	DBG("win_back_cb");
	ZLTizenApplicationWindow *tw = (ZLTizenApplicationWindow*)data;
	/* Let window go to hide state. */
	elm_win_lower(tw->win);
}
static void
anim_stop_cb(void *data, Evas_Object *obj, void *event_info)
{
/*	appdata_s *ad = data;
	Elm_Object_Item *item;
	int index, page = 0;

	elm_scroller_current_page_get(ad->scroller, &page, NULL);

	item = elm_toolbar_first_item_get(ad->tabbar);

	for (index = 0; index < page; index++) {
		item = elm_toolbar_item_next_get(item);
	}
	elm_toolbar_item_selected_set(item, EINA_TRUE);
	*/
}

static Evas_Object* create_scroller(Evas_Object *parent, ZLTizenApplicationWindow *tw)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_object_style_set(scroller, "dialogue");
//	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	//elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);

	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_OFF);
	elm_scroller_page_size_set(scroller, 0, 0);
	elm_scroller_page_scroll_limit_set(scroller, 1, 0);
	elm_scroller_single_direction_set(scroller, ELM_SCROLLER_SINGLE_DIRECTION_HARD);
	evas_object_smart_callback_add(scroller, "scroll,anim,stop", anim_stop_cb, tw);

	evas_object_show(scroller);

	return scroller;
}

static Evas_Object *
create_drawer_layout(Evas_Object *parent)
{
	Evas_Object *layout;
	layout = elm_layout_add(parent);
	elm_layout_theme_set(layout, "layout", "drawer", "panel");
	evas_object_show(layout);

	return layout;
}

static Eina_Bool naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	DBG("naviframe_pop_cb");
	Evas_Object *win = (Evas_Object *)data;

	elm_win_lower(win);

	return EINA_FALSE;
}

static void move_menu_popup(Evas_Object *parent, Evas_Object *obj)
{
	Evas_Coord w, h;
	int pos = -1;

	elm_win_screen_size_get(parent, NULL, NULL, &w, &h);
	pos = elm_win_rotation_get(parent);

	switch (pos) {
		case 0:
		case 180:
			evas_object_move(obj, 0, h);
			break;
		case 90:
			evas_object_move(obj, 0, w);
			break;
		case 270:
			evas_object_move(obj, h, w);
			break;
	}
}

static void popup_cb(void *data, Evas_Object *obj, void *event_info)
{
	 ZLTizenApplicationWindow *tw = (ZLTizenApplicationWindow*)data;
	 /*
	appdata_s *ad = (appdata_s *)data;
	Evas_Object *label;
	Elm_Object_Item *nf_it = elm_naviframe_top_item_get(ad->nf);
	const char *text = elm_object_item_text_get((Elm_Object_Item *) event_info);
	const char *title = elm_object_item_text_get(nf_it);

	evas_object_del(ad->popup);
	ad->popup = NULL;

	if (text && !strcmp(text, "Second View")) {
		if (title && strcmp(title, text)) {

			label = create_label(ad->nf, "Second View");
			elm_naviframe_item_push(ad->nf, "Second View", NULL, NULL, label, NULL);
		}
	} else if (text && !strcmp(text, "Settings")) {
		if (title && strcmp(title, text)) {
			elm_naviframe_item_pop(ad->nf);
		}
	}*/
}

static void
dismissed_popup_cb(void *data, Evas_Object *obj, void *event_info)
{
	ZLTizenApplicationWindow *tw = (ZLTizenApplicationWindow*)data;
	evas_object_del(obj);
	tw->popup = NULL;
}
static Evas_Object *
create_bg(Evas_Object *parent)
{
	Evas_Object *rect;
	rect = evas_object_rectangle_add(evas_object_evas_get(parent));
	evas_object_color_set(rect, 0, 0, 0, 0);
	evas_object_show(rect);

	return rect;
}

static void drawer_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_panel_hidden_set(obj, EINA_TRUE);
}


static void panel_scroll_cb(void *data, Evas_Object *obj, void *event_info)
{
//	DBG("panel_scroll_cb");
	Elm_Panel_Scroll_Info *ev = (Elm_Panel_Scroll_Info *)event_info;
	Evas_Object *bg = (Evas_Object *)data;
	int col = 127 * ev->rel_x;

	evas_object_color_set(bg, 0, 0, 0, col);
}

static Evas_Object * create_menu_popup(ZLTizenApplicationWindow *tw)
{
	Evas_Object *popup;

	popup = elm_ctxpopup_add(tw->win);
	elm_object_style_set(popup, "more/default");
	elm_ctxpopup_auto_hide_disabled_set(popup, EINA_TRUE);
	evas_object_smart_callback_add(popup, "dismissed", dismissed_popup_cb, tw);

	elm_ctxpopup_item_append(popup, "Settings", NULL, popup_cb, tw);
	elm_ctxpopup_item_append(popup, "Second View", NULL, popup_cb, tw);

	move_menu_popup(tw->win, popup);
	evas_object_show(popup);

	return popup;
}

Evas_Object * ZLTizenApplicationWindow::createDrawerPanel(Evas_Object *parent)
{
	Evas_Object *panel;
	int i;
	char buf[64];

	/* Panel */
	panel = elm_panel_add(parent);
	elm_panel_scrollable_set(panel, EINA_TRUE);

	/* Default is visible, hide the content in default. */
	elm_panel_hidden_set(panel, EINA_TRUE);
	elm_panel_orient_set(panel, ELM_PANEL_ORIENT_LEFT);
	evas_object_show(panel);

	/* Panel content */
	menuList = elm_list_add(panel);
	evas_object_size_hint_weight_set(menuList, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(menuList, EVAS_HINT_FILL, EVAS_HINT_FILL);
/*	for (i = 0; i < 5; i++) {
		sprintf(buf, "элемент %d", i);
		elm_list_item_append(menuList, buf, NULL, NULL, NULL, NULL);
	}
*/
	evas_object_show(menuList);

	elm_object_content_set(panel, menuList);

	return panel;
}

// menu button event

static void nf_more_cb(void *data, Evas_Object *obj, void *event_info)
{
 DBG("menu button event");
 ZLTizenApplicationWindow *tw = (ZLTizenApplicationWindow*)data;
 tw->createTestDialog();
}

static void drawer_panel_Show(void *data, Evas_Object *obj, void *event_info)
{
	ZLTizenApplicationWindow *tw = (ZLTizenApplicationWindow*)data;
	if (!elm_object_disabled_get(tw->drawer_panel)){
		elm_panel_toggle(tw->drawer_panel);
	}
}
void ZLTizenApplicationWindow::mouseDown(int x,int y){
if (x<200) prevPage();
else nextPage();
}

void ZLTizenApplicationWindow::prevPage(){
	 DBG("PrevPage");
	 FBReader &fbreader = FBReader::Instance();
	 fbreader.doAction(ActionCode::PAGE_SCROLL_BACKWARD);
}

void ZLTizenApplicationWindow::nextPage(){
	 DBG("NextPage");
	 FBReader &fbreader = FBReader::Instance();
	 fbreader.doAction(ActionCode::PAGE_SCROLL_FORWARD);
}

static void naviframe_back_cb(void *data, Evas_Object *obj, void *event_info) {
  DBG("naviframe_back_cb");
  ZLTizenApplicationWindow* tw = (ZLTizenApplicationWindow*)data;
  if (elm_panel_hidden_get(tw->drawer_panel) == EINA_TRUE){
	  	  elm_naviframe_item_pop(obj);
  	  }
  else {
	  elm_panel_hidden_set(tw->drawer_panel, EINA_TRUE);
  }
}

ZLTizenApplicationWindow::ZLTizenApplicationWindow(ZLApplication *application): ZLApplicationWindow(application),
																				win(NULL), conform(NULL), label(NULL), popup(NULL), myTizenViewWidget(NULL)
{
	// TODO Auto-generated constructor stub
	win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
	}

//	evas_object_smart_callback_add(win, "delete,request", win_delete_request_cb, NULL);
//	eext_object_event_callback_add(win, EEXT_CALLBACK_BACK, ZLTizenApplicationWindow::win_back_cb, this);
//	eext_object_event_callback_add(win, EEXT_CALLBACK_MORE, nf_more_cb, this);

	/* Conformant */
	conform = elm_conformant_add(win);
	elm_win_indicator_mode_set(win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	evas_object_show(conform);


	/* Naviframe */
	naviframe = elm_naviframe_add(conform);
	eext_object_event_callback_add(naviframe, EEXT_CALLBACK_BACK, naviframe_back_cb, this);
	eext_object_event_callback_add(naviframe, EEXT_CALLBACK_MORE, drawer_panel_Show, this);
	evas_object_size_hint_weight_set(naviframe, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(conform, naviframe);
	evas_object_show(naviframe);

	/* Show window after base gui is set up */
	evas_object_show(win);

}

ZLTizenApplicationWindow::~ZLTizenApplicationWindow() {
	// TODO Auto-generated destructor stub
}


static void image_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{

	ZLTizenViewWidget *viewWidget = (ZLTizenViewWidget*)data;
	viewWidget->draw();
}


static void
_on_mousedown(void *data, // evas object event EVAS_CALLBACK_MOUSE_DOWN callback function.
                 Evas *evas,
                 Evas_Object *o,
                 void *event_info)
{

   Evas_Event_Mouse_Down *ev;

   ev = (Evas_Event_Mouse_Down *)event_info;
   dlog_print(DLOG_DEBUG, LOG_TAG, "We've got mouse_down x=%d y=%d",ev->output.x, ev->output.y);
   ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;
   app->mouseDown(ev->output.x, ev->output.y);
}



void ZLTizenApplicationWindow::createTestDialog(){
	DBG("createTizenTreeDialog");
	Evas_Object *layout, *box;
	layout = create_drawer_layout(naviframe);
		DBG("create_drawer_layout");
		/* Box */
		box = elm_box_add(layout);
		evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
		elm_box_homogeneous_set(box, EINA_FALSE);
	//	elm_object_part_content_set(layout, "elm.swallow.content", box);
		Elm_Object_Item *nf_it = elm_naviframe_item_push(naviframe, "tree test dialog", NULL, NULL, layout, NULL);
}

shared_ptr<ZLOptionsDialog> ZLTizenApplicationWindow::createTizenOptionsDialog(const ZLResource &resource, shared_ptr<ZLRunnable> applyAction){
	DBG("createTizenOptionsDialog");
	ZLTizenOptionsDialog* tizenOptionsDialog = new ZLTizenOptionsDialog(this, resource, applyAction);
	myOptionsDialog = (ZLOptionsDialog*) tizenOptionsDialog;
	tizenOptionsDialog->createOptionsDialogObject(naviframe);
	return  myOptionsDialog;
}

shared_ptr<ZLTreeDialog> ZLTizenApplicationWindow::createTizenTreeDialog(const ZLResource &resource){
	DBG("createTizenTreeDialog");
	ZLTizenTreeDialog* tizenTreeDialog = new ZLTizenTreeDialog(this, resource);
	myTreeDialog = (ZLTreeDialog*) tizenTreeDialog;
	//tizenTreeDialog->myWindows = this;
	//tizenTreeDialog->createItemsList(naviframe);
	return  myTreeDialog;
}

ZLViewWidget *ZLTizenApplicationWindow::createViewWidget() {

	Evas_Object *layout, *box;

	//ZLTizenViewWidget *viewWidget = new ZLTizenViewWidget(&application(), ZLView::DEGREES0);
	myTizenViewWidget = new ZLTizenViewWidget(&application(), ZLView::DEGREES0);
	layout = create_drawer_layout(naviframe);

	/* Box */
	box = elm_box_add(layout);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_content_set(layout, "elm.swallow.content", box);

	myTizenViewWidget->scroller = create_scroller(box, this);
	evas_object_size_hint_weight_set(myTizenViewWidget->scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(myTizenViewWidget->scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(box, myTizenViewWidget->scroller);

	/* Label*/
	label = elm_label_add(myTizenViewWidget->scroller);
	elm_object_text_set(label, "Hello EFL and FBReader!");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(myTizenViewWidget->scroller, label);
	evas_object_show(label);


	// Adds a callback function to a given canvas event.
//	evas_event_callback_add(viewWidget->scroller, EVAS_CALLBACK_RENDER_FLUSH_PRE, _render_flush_cb, NULL);
	//Elm_Object_Item *nf_it =elm_naviframe_item_push(naviframe, "main navi", NULL, NULL, viewWidget->scroller, NULL);
	myTizenViewWidget->naviframe_item = elm_naviframe_item_push(naviframe, "FBReader", NULL, NULL, layout, NULL);
	//nf_it = elm_naviframe_item_push(ad->nf, "Layout Samples", NULL, NULL, main_list, NULL);
	elm_naviframe_item_pop_cb_set(myTizenViewWidget->naviframe_item, naviframe_pop_cb, win);

	Evas* canvas = evas_object_evas_get(myTizenViewWidget->scroller);

	Evas_Object *img = evas_object_image_add(canvas);
	evas_object_image_colorspace_set(img, EVAS_COLORSPACE_ARGB8888);
	evas_object_event_callback_add(img, EVAS_CALLBACK_RESIZE, image_resize_cb, myTizenViewWidget);
	evas_object_size_hint_weight_set(img, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_align_set(img, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_content_set(myTizenViewWidget->scroller, img);
	evas_object_show(img);							// Make the given Evas object visible

	myTizenViewWidget->image = img;

	// Add a callback function to a given Evas object event.
	evas_object_event_callback_add(img, EVAS_CALLBACK_MOUSE_DOWN, _on_mousedown, NULL);

	/* Drawer bg */
	Evas_Object *bg = create_bg(layout);
	elm_object_part_content_set(layout, "elm.swallow.bg", bg);

	/* create_panel */
	drawer_panel = createDrawerPanel(layout);
	//eext_object_event_callback_add(drawer, EEXT_CALLBACK_BACK, drawer_back_cb, ad);
//	eext_object_event_callback_add(drawer_panel, EEXT_CALLBACK_BACK, drawer_back_cb, this);
	evas_object_smart_callback_add(drawer_panel, "scroll", panel_scroll_cb, bg);
	elm_object_part_content_set(layout, "elm.swallow.right", drawer_panel);

	/* Drawers Button */
	//btn = create_drawers_btn(ad->nf, btn_cb, drawer);
	Evas_Object *btn = elm_button_add(naviframe);
	if (btn) {
		elm_object_style_set(btn, "naviframe/drawers");
		evas_object_smart_callback_add(btn, "clicked", drawer_panel_Show, this);
		}


	elm_object_item_part_content_set(myTizenViewWidget->naviframe_item, "title_left_btn", btn);

	/* Show window after base gui is set up */
	evas_object_show(win);

	return myTizenViewWidget;

}
