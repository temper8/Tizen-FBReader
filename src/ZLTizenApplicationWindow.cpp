/*
 * ZLTizenApplicationWindow.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: Alex
 */

#include "ZLTizenApplicationWindow.h"
#include "ZLTizenViewWidget.h"
#include "ZLView.h"

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

	/* Conformant */
	conform = elm_conformant_add(win);
	elm_win_indicator_mode_set(win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	evas_object_show(conform);

	/* Label*/
	label = elm_label_add(conform);
	elm_object_text_set(label, "Hello EFL and FBReader!");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(conform, label);
	evas_object_show(label);

	/* Show window after base gui is set up */
	evas_object_show(win);

}

ZLTizenApplicationWindow::~ZLTizenApplicationWindow() {
	// TODO Auto-generated destructor stub
}

ZLViewWidget *ZLTizenApplicationWindow::createViewWidget() {

	ZLTizenViewWidget *viewWidget = new ZLTizenViewWidget(&application(), ZLView::DEGREES0);
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
