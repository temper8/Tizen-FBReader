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
//#include "../../FBReader/fbreader/FBReader.h"
#include "../../FBReader/fbreader/FBReaderActions.h"

//#include "../../../../../fbreader/src/fbreader/FBReader.h"
//#include "../../../../../fbreader/src/fbreader/FBReaderActions.h"
#include "../../fbreader/fbreader/BookTextView.h"

#include "ZLTextArea.h"

#include "dialogs/ZLTizenTreeDialog.h"
#include "dialogs/ZLTizenOptionsDialog.h"
#include "dialogs/ZLTizenProgressDialog.h"

#include "dialogs/ZLTizen.h"

void ZLTizenApplicationWindow::close(){
	DBG("ZLTizenApplicationWindow::close() ");
	ui_app_exit();
}

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
	myWindow.AddMenuItem(name, id);
}

typedef struct menu_data  {
	 const  std::string *id;
	 ZLTizenApplicationWindow *windows;
} menu_data_s;

void ZLTizenApplicationWindow::onMenuItemSelected(void *data, Evas_Object *obj, void *event_info){
	Elm_Object_Item *it = (Elm_Object_Item *)event_info;
	/* Unhighlight item */
	elm_list_item_selected_set(it, EINA_FALSE);

	menu_data_s *md = (menu_data_s *)data;

	DBG("selected item %s", md->id->c_str());
	//FBReader &fbreader = FBReader::Instance();
	//fbreader.doAction(*(md->id));
	md->windows->doAppAction(*(md->id));

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

	//elm_win_lower(win);
	ui_app_exit();

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

void ZLTizenApplicationWindow::deleteOptionsDialog(){
	DBG("ZLTizenApplicationWindow::deleteOptionsDialog");
	myOptionsDialog = 0;
}

void ZLTizenApplicationWindow::deleteTreeDialog(){
	DBG("ZLTizenApplicationWindow::deleteTreeDialog");
	elm_naviframe_item_promote(myTizenViewWidget->naviframe_item);
	myTreeDialog = 0;
}

Evas_Object * ZLTizenApplicationWindow::createDrawerPanel(Evas_Object *parent)
{
	Evas_Object *panel;

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
	ZLTizenApplicationWindow *app_win = (ZLTizenApplicationWindow*)data;

	if (app_win->showDrawerPanel())
			app_win->showToolBar();
	else
			app_win->hideToolBar();

}

bool ZLTizenApplicationWindow::showDrawerPanel(){
	if (!elm_object_disabled_get(drawer_panel))
	{
		elm_panel_toggle(drawer_panel);
		return true;
	}
	else
		return false;
}
void ZLTizenApplicationWindow::hideToolBar(){
	elm_layout_signal_emit(main_layout, "toolbar,hide", "app");
	ToolBarVisible = false;
}

void ZLTizenApplicationWindow::showToolBar(){
	elm_layout_signal_emit(main_layout, "toolbar,show", "app");
	ToolBarVisible = true;
}

void ZLTizenApplicationWindow::showTitle(){
	if (elm_naviframe_item_title_enabled_get(myTizenViewWidget->naviframe_item) == EINA_TRUE)
		elm_naviframe_item_title_enabled_set(myTizenViewWidget->naviframe_item, EINA_FALSE,	EINA_FALSE);
	else {
		elm_naviframe_item_title_enabled_set(myTizenViewWidget->naviframe_item, EINA_TRUE,	EINA_FALSE);
	//	elm_scroller_region_bring_in(myTizenViewWidget->scroller, 0, 50, 500,100);

	}

}
bool ZLTizenApplicationWindow::lastPageOfBook(){
	FBReader &fbreader = FBReader::Instance();
	const ZLTextArea &textArea  = fbreader.bookTextView().textArea();
	if ((!textArea.myEndCursor.paragraphCursor().isLast() || !textArea.myEndCursor.isEndOfParagraph()))
		return false;
	else
		return true;
}

bool ZLTizenApplicationWindow::firstPageOfBook(){
	FBReader &fbreader = FBReader::Instance();
	const ZLTextArea &textArea  = fbreader.bookTextView().textArea();
	if (!textArea.myStartCursor.paragraphCursor().isFirst() || !textArea.myStartCursor.isStartOfParagraph())
		return false;
	else
		return true;
}

void ZLTizenApplicationWindow::gotoPrevPage(){
	 doAppAction(ActionCode::PAGE_SCROLL_BACKWARD);
}

void ZLTizenApplicationWindow::refreshPage(){
	doAppAction(ActionCode::PAGE_REFRESH);
}

void ZLTizenApplicationWindow::gotoNextPage(){
	 doAppAction(ActionCode::PAGE_SCROLL_FORWARD);
}

void ZLTizenApplicationWindow::startDragPagePrevPage(){
	Evas_Object *img;
	img = myTizenViewWidget->image;
	myTizenViewWidget->image = myTizenViewWidget->image3;
	myTizenViewWidget->image3 = img;
	myTizenViewWidget->necessaryBoundsChecking = false;
	doAppAction(ActionCode::PAGE_SCROLL_BACKWARD);
}
void ZLTizenApplicationWindow::afterMovePrevPage(){
	Evas_Object *img;
	img = myTizenViewWidget->image;
	myTizenViewWidget->image = myTizenViewWidget->image3;
	myTizenViewWidget->image3 = img;

	elm_layout_signal_emit(main_layout, "prev_page_goto_default", "app");
	myTizenViewWidget->necessaryBoundsChecking = true;
	doAppAction(ActionCode::PAGE_REFRESH);
}

void ZLTizenApplicationWindow::startDragPage(){
	Evas_Object *img;
	img = myTizenViewWidget->image;
	myTizenViewWidget->image = myTizenViewWidget->image2;
	myTizenViewWidget->image2 = img;
	myTizenViewWidget->necessaryBoundsChecking = false;
	doAppAction(ActionCode::PAGE_SCROLL_FORWARD);

}

void ZLTizenApplicationWindow::afterMoveMainPage(){
	Evas_Object *img;
	img = myTizenViewWidget->image;
	myTizenViewWidget->image = myTizenViewWidget->image2;
	myTizenViewWidget->image2 = img;

	elm_layout_signal_emit(main_layout, "main_page_goto_default", "app");
	myTizenViewWidget->necessaryBoundsChecking = true;
	doAppAction(ActionCode::PAGE_REFRESH);
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

void ZLTizenApplicationWindow::setOrientation(int Angle){

	DBG("orientation %d", Angle);
	// -1 any orientation
	elm_win_wm_rotation_preferred_rotation_set(win, Angle);

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

	evas_object_smart_callback_add(win, "delete,request", win_delete_request_cb, NULL);
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
	/* Push a previous button to naviframe item automatically */
	elm_naviframe_prev_btn_auto_pushed_set(naviframe, EINA_TRUE);

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
//	tizenOptionsDialog->createOptionsDialogObject(naviframe);
	return  myOptionsDialog;
}

shared_ptr<ZLTreeDialog> ZLTizenApplicationWindow::createTizenTreeDialog(const ZLResource &resource){
	DBG("createTizenTreeDialog");
	ZLTizenTreeDialog* myTizenTreeDialog = new ZLTizenTreeDialog(this, resource);
	myTreeDialog = (ZLTreeDialog*) myTizenTreeDialog;
	//tizenTreeDialog->myWindows = this;
	//tizenTreeDialog->createItemsList(naviframe);
	return  myTreeDialog;
}

shared_ptr<ZLProgressDialog> ZLTizenApplicationWindow::createTizenProgressDialog(const ZLResourceKey &key){
	DBG("create ZLTizenProgressDialog");
	ZLTizenProgressDialog* myTizenProgressDialog = new ZLTizenProgressDialog(this, key);
	myProgressDialog = (ZLProgressDialog*) myTizenProgressDialog;

	return  myProgressDialog;
}
void start_drag_prev_page(void *data, Evas_Object *obj, const char *emission, const char *source){
	DBG("start_drag_page");
	ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;

	app->startDragPagePrevPage();
}
void after_move_prev_page(void *data, Evas_Object *obj, const char *emission, const char *source){
	DBG("after_move_prev_page");
	ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;

	app->afterMovePrevPage();
}

void start_drag_page(void *data, Evas_Object *obj, const char *emission, const char *source){
	DBG("start_drag_page");
	ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;

	app->startDragPage();
}

void after_move_main_page(void *data, Evas_Object *obj, const char *emission, const char *source){
	DBG("start_drag_page");
	ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;

	app->afterMoveMainPage();
}

void left_tap_zone_clicked(void *data, Evas_Object *obj, const char *emission, const char *source){
	DBG("left_tap_zone_clicked");
	ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;
	if(app->ToolBarVisible)
			app->hideToolBar();
	app->gotoPrevPage();
}

void right_tap_zone_clicked(void *data, Evas_Object *obj, const char *emission, const char *source){
	DBG("right_tap_zone_clicked");
	ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;
	if(app->ToolBarVisible)
			app->hideToolBar();
	app->gotoNextPage();
}

void center_tap_zone_clicked(void *data, Evas_Object *obj, const char *emission, const char *source){
	DBG("center_tap_zone_clicked");
	ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;
	if(app->ToolBarVisible)
		app->hideToolBar();
	else
		app->showToolBar();

}

void menu_icon_clicked(void *data, Evas_Object *obj, const char *emission, const char *source){
	DBG("menu_icon_clicked");
	ZLTizenApplicationWindow *app = (ZLTizenApplicationWindow *)data;
	app->showDrawerPanel();
}

void ZLTizenApplicationWindow::setCaption(const std::string &caption){
	DBG("setCaption %s", caption.c_str());
	if (toolBar_layout !=NULL) {
		elm_object_part_text_set(toolBar_layout, "caption", caption.c_str());
	}
}

ZLViewWidget *ZLTizenApplicationWindow::createViewWidget() {

	Evas_Object *layout;

	myTizenViewWidget = new ZLTizenViewWidget(&application(), ZLView::DEGREES0);
	myTizenViewWidget->myWindow = this;
	//layout = create_drawer_layout(naviframe);
	main_layout = ZLTizenUtil::create_layout(naviframe, "fbr.main");
	myTizenViewWidget->main_layout = main_layout;

	myTizenViewWidget->naviframe_item = elm_naviframe_item_push(naviframe, "FBReader", NULL, NULL, main_layout, NULL);
	elm_naviframe_item_title_enabled_set(myTizenViewWidget->naviframe_item, EINA_FALSE,	EINA_FALSE);

	elm_naviframe_item_pop_cb_set(myTizenViewWidget->naviframe_item, naviframe_pop_cb, win);

	//sub_layout = ZLTizenUtil::create_layout(layout, "fbr.main");
	toolBar_layout = ZLTizenUtil::create_layout(main_layout, "fbr.toolbar");
	//hideToolBar();

	layout = create_drawer_layout(main_layout);

	Evas* canvas = evas_object_evas_get(main_layout);

	Evas_Object *img = evas_object_image_add(canvas);

	evas_object_image_colorspace_set(img, EVAS_COLORSPACE_ARGB8888);
	evas_object_event_callback_add(img, EVAS_CALLBACK_RESIZE, image_resize_cb, myTizenViewWidget);
	evas_object_size_hint_weight_set(img, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_align_set(img, EVAS_HINT_FILL, EVAS_HINT_FILL);

	//Evas* canvas2 = evas_object_evas_get(main_layout);

	Evas_Object *img2 = evas_object_image_add(canvas);
	evas_object_image_colorspace_set(img2, EVAS_COLORSPACE_ARGB8888);
	//evas_object_event_callback_add(img2, EVAS_CALLBACK_RESIZE, image_resize_cb, myTizenViewWidget);
	evas_object_size_hint_weight_set(img2, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_align_set(img2, EVAS_HINT_FILL, EVAS_HINT_FILL);

	Evas_Object *img3 = evas_object_image_add(canvas);
	evas_object_image_colorspace_set(img3, EVAS_COLORSPACE_ARGB8888);
	//evas_object_event_callback_add(img3, EVAS_CALLBACK_RESIZE, image_resize_cb, myTizenViewWidget);
	evas_object_size_hint_weight_set(img3, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_align_set(img3, EVAS_HINT_FILL, EVAS_HINT_FILL);


	elm_object_signal_callback_add(main_layout, "click", "right_tap_zone",  right_tap_zone_clicked, this);
	elm_object_signal_callback_add(main_layout, "click", "center_tap_zone", center_tap_zone_clicked, this);
	elm_object_signal_callback_add(main_layout, "click", "left_tap_zone",   left_tap_zone_clicked, this);

	elm_object_signal_callback_add(main_layout, "start_drag", "tap_rect",   start_drag_page, this);
	elm_object_signal_callback_add(main_layout, "start_drag_prev_page", "tap_rect",   start_drag_prev_page, this);
	elm_object_signal_callback_add(main_layout, "after_move_prev_page", "tap_rect",   after_move_prev_page, this);
	elm_object_signal_callback_add(main_layout, "after_move_page", "tap_rect",   after_move_main_page, this);

	elm_object_signal_callback_add(toolBar_layout, "click", "menu_icon",   menu_icon_clicked, this);

	evas_object_show(toolBar_layout);

	//Evas_Object *panel = createTopPanel(sub_layout);

	elm_object_part_content_set(main_layout,  "toolbar", toolBar_layout);

	elm_object_part_content_set(main_layout,  "fbr.main.content", img);
	elm_object_part_content_set(main_layout,  "fbr.main.next_page", img2);
	elm_object_part_content_set(main_layout,  "fbr.main.prev_page", img3);
	//elm_object_part_content_set(layout, "elm.swallow.content", sub_layout);
	elm_object_part_content_set(main_layout, "fbr.main.drawer", layout);
	evas_object_show(img);							// Make the given Evas object visible
	evas_object_show(img2);
	evas_object_show(img3);

	myTizenViewWidget->image = img;
	myTizenViewWidget->image2 = img2;
	myTizenViewWidget->image3 = img3;
	/* Drawer bg */
	Evas_Object *bg = create_bg(layout);
	elm_object_part_content_set(layout, "elm.swallow.bg", bg);

	/* create_panel */
	drawer_panel = createDrawerPanel(layout);
	//eext_object_event_callback_add(drawer, EEXT_CALLBACK_BACK, drawer_back_cb, ad);
//	eext_object_event_callback_add(drawer_panel, EEXT_CALLBACK_BACK, drawer_back_cb, this);
	evas_object_smart_callback_add(drawer_panel, "scroll", panel_scroll_cb, bg);
	elm_object_part_content_set(layout, "elm.swallow.left", drawer_panel);


	/* Show window after base gui is set up */
	evas_object_show(win);
	//evas_object_image_filled_set(img, EINA_FALSE);
	return myTizenViewWidget;

}
