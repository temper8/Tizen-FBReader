/*
 * ZLTizenViewWidget.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: Alex
 */

#include "logger.h"

#include "ZLTizenViewWidget.h"
#include <cairo.h>

struct _cairo_context
{
    Evas_Object *image;
    int width;
    int height;

    cairo_t *cairo;
    cairo_surface_t *surface;
    //data_chart_draw_cb draw_cb;
};

ZLTizenViewWidget::ZLTizenViewWidget(ZLApplication *application, ZLView::Angle initialAngle) : ZLViewWidget(initialAngle), myApplication(application) {
	// TODO Auto-generated constructor stub

}

ZLTizenViewWidget::~ZLTizenViewWidget() {
	// TODO Auto-generated destructor stub
}


void ZLTizenViewWidget::repaint(){

}


static void draw_text( cairo_t *cr){
	cairo_text_extents_t extents;

	const char *utf8 = "FBReader for Tizen 2.3";
	double x,y;

	cairo_select_font_face (cr, "Sans",
	    CAIRO_FONT_SLANT_NORMAL,
	    CAIRO_FONT_WEIGHT_NORMAL);

	cairo_set_font_size (cr, 40.0);
	cairo_text_extents (cr, utf8, &extents);

	x=20.0;
	y=150.0;
	cairo_set_source_rgb (cr, 0, 0, 0);

	cairo_move_to (cr, x,y);
	cairo_show_text (cr, utf8);


	/* draw helping lines */
	cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
	cairo_set_line_width (cr, 6.0);
	cairo_arc (cr, x, y, 10.0, 0, 2*M_PI);
	cairo_fill (cr);
	cairo_move_to (cr, x,y);
	cairo_rel_line_to (cr, 0, -extents.height);
	cairo_rel_line_to (cr, extents.width, 0);
	cairo_rel_line_to (cr, extents.x_bearing, -extents.y_bearing);
	cairo_stroke (cr);

}

void ZLTizenViewWidget::test_draw_on_cairo(Evas_Object *image){

	ZLTizenPaintContext &tizenContext = (ZLTizenPaintContext&)view()->context();

	 //char img_path[PATH_MAX] = { 0, };
	 //app_get_resource("tizen_logo.png", img_path, PATH_MAX);



	 int width,height;
	 evas_object_geometry_get(image, NULL, NULL, &width, &height);
	 evas_object_image_size_set(image, width, height);
	 evas_object_image_fill_set(image, 0, 0, width, height);


	 tizenContext.width = width;
	 tizenContext.height = height;

	 cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

	 tizenContext.surface = surface;
	 //DBG("wwidth = %d", width);
	 //DBG("height = %d", height);

	// RETM_IF(0 == width, "width is 0");
	// RETM_IF(0 == height, "height is 0");


	 cairo_t *cairo = cairo_create(surface);
	 tizenContext.cairo = cairo;

	 cairo_set_source_rgb(cairo, 0.5, 0.5, 1.0);
	 cairo_paint(cairo);

	 //cairo_surface_t *png_image = cairo_image_surface_create_from_png (img_path);
	 //cairo_set_source_surface (cairo, png_image, 150, 10);
	 //cairo_paint (cairo);

	 draw_text(cairo);

	 cairo_set_line_width (cairo, 0.1);
	 cairo_set_source_rgb (cairo, 0, 0, 0);
	 cairo_rectangle (cairo, 50,50, 100, 100);
	 cairo_stroke (cairo);

	 cairo_set_source_rgb (cairo, 0, 0, 0);
	 cairo_rectangle (cairo, 25, 25, 50, 50);
	 cairo_fill (cairo);

	 cairo_set_source_rgb(cairo, 1.0,0.0,0.5);
	 cairo_set_line_width(cairo, 1.5);
	 cairo_move_to(cairo, 10.0, 10.0);
	 cairo_line_to(cairo, 210.0, 210.0);
	 cairo_stroke(cairo);
	 // flush


}
void ZLTizenViewWidget::updateImage(){
	ZLTizenPaintContext &tizenContext = (ZLTizenPaintContext&)view()->context();
	 evas_object_image_data_set(image, cairo_image_surface_get_data(tizenContext.surface));
	 evas_object_image_data_update_add(image, 0, 0, tizenContext.width, tizenContext.height);
}

void ZLTizenViewWidget::draw(){
	DBG(" ZLTizenViewWidget::draw()");
	if(view().isNull()) {
		DBG(" view is Null");
		return;
	}
	ZLTizenPaintContext &tizenContext = (ZLTizenPaintContext&)view()->context();
	//tizenContext = (ZLTizenPaintContext)view()->context();

	test_draw_on_cairo(image);
	updateImage();

}
