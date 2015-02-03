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


static void win_delete_request_cb(void *data , Evas_Object *obj , void *event_info)
{
	ui_app_exit();
}

void ZLTizenApplicationWindow::win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	ZLTizenApplicationWindow *tw = (ZLTizenApplicationWindow*)data;
	/* Let window go to hide state. */
	elm_win_lower(tw->win);
}

static Evas_Object* create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	elm_object_style_set(scroller, "dialogue");
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_AUTO);
	//evas_object_show(scroller);

	return scroller;
}

static Eina_Bool naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	Evas_Object *win = (Evas_Object *)data;

	elm_win_lower(win);

	return EINA_FALSE;
}

static void nf_more_cb(void *data, Evas_Object *obj, void *event_info)
{
 DBG("nf_more_cb");
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

ZLTizenApplicationWindow::ZLTizenApplicationWindow(ZLApplication *application): ZLApplicationWindow(application),
																				win(NULL), conform(NULL), label(NULL)
{
	// TODO Auto-generated constructor stub
	win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(win, EEXT_CALLBACK_BACK, ZLTizenApplicationWindow::win_back_cb, this);
	eext_object_event_callback_add(win, EEXT_CALLBACK_MORE, nf_more_cb, this);

	/* Conformant */
	conform = elm_conformant_add(win);
	elm_win_indicator_mode_set(win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	evas_object_show(conform);


	/* Naviframe */
	naviframe = elm_naviframe_add(conform);
	//eext_object_event_callback_add(naviframe, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, this);
	//eext_object_event_callback_add(naviframe, EEXT_CALLBACK_MORE, nf_more_cb, this);
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
_render_flush_cb(void *data, // evas event EVAS_CALLBACK_RENDER_FLUSH_PRE callback function.
                     Evas *e,
                     void *event_info)
{
   dlog_print(DLOG_DEBUG, LOG_TAG, "Canvas is about to flush its rendering pipeline!");
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


ZLViewWidget *ZLTizenApplicationWindow::createViewWidget() {

	ZLTizenViewWidget *viewWidget = new ZLTizenViewWidget(&application(), ZLView::DEGREES0);


	viewWidget->scroller = create_scroller(naviframe);

	/* Label*/
	label = elm_label_add(viewWidget->scroller);
	elm_object_text_set(label, "Hello EFL and FBReader!");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(viewWidget->scroller, label);
	evas_object_show(label);


	// Adds a callback function to a given canvas event.
//	evas_event_callback_add(viewWidget->scroller, EVAS_CALLBACK_RENDER_FLUSH_PRE, _render_flush_cb, NULL);


	Evas* canvas = evas_object_evas_get(viewWidget->scroller);

	Evas_Object *img = evas_object_image_add(canvas);
	evas_object_image_colorspace_set(img, EVAS_COLORSPACE_ARGB8888);
	evas_object_event_callback_add(img, EVAS_CALLBACK_RESIZE, image_resize_cb, viewWidget);
	evas_object_size_hint_weight_set(img, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_align_set(img, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_content_set(viewWidget->scroller, img);
	evas_object_show(img);							// Make the given Evas object visible

	viewWidget->image = img;

	// Add a callback function to a given Evas object event.
	evas_object_event_callback_add(img, EVAS_CALLBACK_MOUSE_DOWN, _on_mousedown, NULL);


	Elm_Object_Item *nf_it =elm_naviframe_item_push(naviframe, "main navi", NULL, NULL, viewWidget->scroller, NULL);
	//nf_it = elm_naviframe_item_push(ad->nf, "Layout Samples", NULL, NULL, main_list, NULL);
	elm_naviframe_item_pop_cb_set(nf_it, naviframe_pop_cb, win);


	return viewWidget;

/*	ZLGtkViewWidget *viewWidget = new ZLGtkViewWidget(&application(), (ZLViewWidget::Angle)application().AngleStateOption.value());
	gtk_container_add(GTK_CONTAINER(myVBox), viewWidget->area());
	ZLGtkSignalUtil::connectSignal(GTK_OBJECT(viewWidget->area()), "expose_event", GTK_SIGNAL_FUNC(repaint), this);
	ZLGtkSignalUtil::connectSignal(GTK_OBJECT(viewWidget->area()), "button_press_event", GTK_SIGNAL_FUNC(mousePressed), viewWidget);
	ZLGtkSignalUtil::connectSignal(GTK_OBJECT(viewWidget->area()), "button_release_event", GTK_SIGNAL_FUNC(mouseReleased), viewWidget);
	ZLGtkSignalUtil::connectSignal(GTK_OBJECT(viewWidget->area()), "motion_notify_event", GTK_SIGNAL_FUNC(mouseMoved), viewWidget);
	gtk_widget_show_all(myVBox);
	*/

}
