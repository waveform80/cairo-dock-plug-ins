	/**
* This file is a part of the Cairo-Dock project
*
* Copyright : (C) see the 'copyright' file.
* E-mail    : see the 'copyright' file.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "applet-transitions.h"

///#define _cd_slider_erase_surface(myApplet) cairo_dock_erase_cairo_context (myDrawContext)

/**#define _cd_slider_add_background_to_slide(myApplet, fX, fY, alpha, slide) do { \
	if (myConfig.pBackgroundColor[3] != 0) {\
	cairo_set_source_rgba (myDrawContext, myConfig.pBackgroundColor[0], myConfig.pBackgroundColor[1], myConfig.pBackgroundColor[2], alpha * myConfig.pBackgroundColor[3]);\
	cairo_rectangle (myDrawContext, fX, fY, slide.fImgW, slide.fImgH);\
	cairo_fill (myDrawContext); } } while (0)
#define _cd_slider_add_background_to_slide_opengl(myApplet, fX, fY, alpha, slide) do { \
	glColor4f (myConfig.pBackgroundColor[0], myConfig.pBackgroundColor[1], myConfig.pBackgroundColor[2], alpha * myConfig.pBackgroundColor[3]);\
	glPolygonMode (GL_FRONT, GL_FILL);\
	glEnable (GL_BLEND);\
	glBlendFunc (GL_ONE, GL_ZERO);\
	if (myConfig.pBackgroundColor[3] != 0) {\
		glBegin(GL_QUADS);\
		glVertex3f(fX - slide.fImgW/2, fY - slide.fImgH/2, 0.);\
		glVertex3f(fX + slide.fImgW/2, fY - slide.fImgH/2, 0.);\
		glVertex3f(fX + slide.fImgW/2, fY + slide.fImgH/2, 0.);\
		glVertex3f(fX - slide.fImgW/2, fY + slide.fImgH/2, 0.);\
		glEnd(); } } while (0)*/

static void _cd_slider_add_background_to_slide (GldiModuleInstance *myApplet, double fX, double fY, double alpha, SliderImageArea *slide)
{
	if (myConfig.pBackgroundColor[3] != 0)
	{
		cairo_set_source_rgba (myDrawContext, myConfig.pBackgroundColor[0], myConfig.pBackgroundColor[1], myConfig.pBackgroundColor[2], alpha * myConfig.pBackgroundColor[3]);
		if (myConfig.iBackgroundType == 2)
		{
			int iLineWidth = _get_frame_linewidth (myApplet);
			double fRadius = MIN (5, .25*iLineWidth);
			cairo_save (myDrawContext);
			cairo_translate (myDrawContext, fX - .5*iLineWidth, fY);
			cairo_dock_draw_rounded_rectangle (myDrawContext, fRadius, iLineWidth, slide->fImgW - (2*fRadius), slide->fImgH - iLineWidth);
			cairo_set_line_width (myDrawContext, iLineWidth);
			cairo_stroke (myDrawContext);
			cairo_restore (myDrawContext);
		}
		else
		{
			cairo_rectangle (myDrawContext, fX, fY, slide->fImgW, slide->fImgH);
			cairo_fill (myDrawContext);
		}
	}
}
#define _cd_slider_add_background_to_current_slide(myApplet, fX, fY, alpha) _cd_slider_add_background_to_slide (myApplet, fX, fY, alpha, &myData.slideArea)
#define _cd_slider_add_background_to_prev_slide(myApplet, fX, fY, alpha) _cd_slider_add_background_to_slide (myApplet, fX, fY, alpha, &myData.prevSlideArea)

static void _cd_slider_add_background_to_slide_opengl(GldiModuleInstance *myApplet, double fX, double fY, double alpha, SliderImageArea *slide)
{
	if (myConfig.pBackgroundColor[3] != 0)
	{
		glDisable (GL_TEXTURE_2D);
		glColor4f (myConfig.pBackgroundColor[0], myConfig.pBackgroundColor[1], myConfig.pBackgroundColor[2], alpha * myConfig.pBackgroundColor[3]);
		if (myConfig.iBackgroundType == 2)
		{
			int iLineWidth = _get_frame_linewidth (myApplet);
			double fRadius = 1.33 * MIN (5, .25*iLineWidth);
			glPushMatrix ();
			glTranslatef (fX, fY, 0.);  // centre du rectangle.
			glBlendFunc (GL_ONE, GL_ZERO);
			cairo_dock_draw_rounded_rectangle_opengl (slide->fImgW - (2*fRadius) + iLineWidth, slide->fImgH + iLineWidth, fRadius, 0, NULL);  // we fill the rectangle, because the stroke function in opengl does not handle wide lines very well.
			glPopMatrix ();
			glPolygonMode (GL_FRONT, GL_FILL);
		}
		else
		{
			glPolygonMode (GL_FRONT, GL_FILL);
			glEnable (GL_BLEND);
			glBlendFunc (GL_ONE, GL_ZERO);
			if (myConfig.pBackgroundColor[3] != 0)
			{
				glBegin(GL_QUADS);
				glVertex3f(fX - slide->fImgW/2, fY - slide->fImgH/2, 0.);
				glVertex3f(fX + slide->fImgW/2, fY - slide->fImgH/2, 0.);
				glVertex3f(fX + slide->fImgW/2, fY + slide->fImgH/2, 0.);
				glVertex3f(fX - slide->fImgW/2, fY + slide->fImgH/2, 0.);
				glEnd();
			}
		}
	}
}
#define _cd_slider_add_background_to_current_slide_opengl(myApplet, fX, fY, alpha) _cd_slider_add_background_to_slide_opengl (myApplet, fX, fY, alpha, &myData.slideArea)
#define _cd_slider_add_background_to_prev_slide_opengl(myApplet, fX, fY, alpha) _cd_slider_add_background_to_slide_opengl (myApplet, fX, fY, alpha, &myData.prevSlideArea)

void cd_slider_draw_default (GldiModuleInstance *myApplet)
{
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN ();
		
		_cd_slider_add_background_to_current_slide_opengl (myApplet, 0., 0., 1.);
		
		_cairo_dock_set_blend_alpha ();
		glEnable (GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		_cairo_dock_apply_texture_at_size_with_alpha (myData.iTexture, myData.slideArea.fImgW, myData.slideArea.fImgH, 1.);
		
		_cairo_dock_disable_texture ();
		CD_APPLET_FINISH_DRAWING_MY_ICON;
	}
	else
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN_CAIRO ();
		//\______________________ On efface le fond
		///_cd_slider_erase_surface (myApplet);
		
		//\______________________ On empeche la transparence
		_cd_slider_add_background_to_current_slide (myApplet, myData.slideArea.fImgX, myData.slideArea.fImgY, 1.);
		
		//\______________________ On dessine la nouvelle surface.
		cairo_set_source_surface (myDrawContext, myData.pCairoSurface, myData.slideArea.fImgX, myData.slideArea.fImgY);
		cairo_paint (myDrawContext);
		CD_APPLET_FINISH_DRAWING_MY_ICON_CAIRO;
	}
}

gboolean cd_slider_fade (GldiModuleInstance *myApplet) {
	myData.iAnimCNT ++;
	myData.fAnimAlpha = 1.*myData.iAnimCNT / myConfig.iNbAnimationStep;
	if (myData.fAnimAlpha > 1)
		myData.fAnimAlpha = 1;
	
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN (FALSE);
		
		//Fond précédent.
		if (myData.iPrevTexture != 0)
			_cd_slider_add_background_to_prev_slide_opengl (myApplet, 0., 0., 1 - myData.fAnimAlpha);
		
		//On empeche la transparence.
		_cd_slider_add_background_to_current_slide_opengl (myApplet, 0., 0., myData.fAnimAlpha);
		
		_cairo_dock_set_blend_alpha ();
		glEnable (GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		//Image précédente
		if (myData.iPrevTexture != 0)
		{
			_cairo_dock_apply_texture_at_size_with_alpha (myData.iPrevTexture, myData.prevSlideArea.fImgW, myData.prevSlideArea.fImgH, 1 - myData.fAnimAlpha);
		}
		
		//Image courante.
		_cairo_dock_apply_texture_at_size_with_alpha (myData.iTexture, myData.slideArea.fImgW, myData.slideArea.fImgH, myData.fAnimAlpha);
		
		_cairo_dock_disable_texture ();
		CD_APPLET_FINISH_DRAWING_MY_ICON;
	}
	else
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN_CAIRO (FALSE);
		//On efface le fond
		///_cd_slider_erase_surface (myApplet);
		
		//Fond précédent.
		if (myData.pPrevCairoSurface != NULL)
			_cd_slider_add_background_to_prev_slide (myApplet, myData.prevSlideArea.fImgX, myData.prevSlideArea.fImgY, 1 - myData.fAnimAlpha);
		
		//On empeche la transparence.
		_cd_slider_add_background_to_current_slide (myApplet, myData.slideArea.fImgX, myData.slideArea.fImgY, myData.fAnimAlpha);
		
		//Image précédente
		if (myData.pPrevCairoSurface != NULL) {
			cairo_set_source_surface (myDrawContext, myData.pPrevCairoSurface, myData.prevSlideArea.fImgX, myData.prevSlideArea.fImgY);
			cairo_paint_with_alpha (myDrawContext, 1 - myData.fAnimAlpha);
		}
		
		cairo_set_source_surface (myDrawContext, myData.pCairoSurface, myData.slideArea.fImgX, myData.slideArea.fImgY);
		cairo_paint_with_alpha (myDrawContext, myData.fAnimAlpha);
		CD_APPLET_FINISH_DRAWING_MY_ICON_CAIRO;
	}
	
	return (myData.fAnimAlpha < .99);
}

gboolean cd_slider_blank_fade (GldiModuleInstance *myApplet) {
	myData.iAnimCNT ++;
	myData.fAnimAlpha = 1 - 1.*myData.iAnimCNT / myConfig.iNbAnimationStep;
	if (myData.fAnimAlpha < 0)
		myData.fAnimAlpha = 0;
	
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN (FALSE);
		
		//On empeche la transparence
		_cd_slider_add_background_to_current_slide_opengl (myApplet, 0., 0., 1.);
		
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable (GL_TEXTURE_2D);
		glEnable (GL_BLEND);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		//Image
		glColor4f (1., 1., 1., 1.);
		cairo_dock_apply_texture_at_size (myData.iTexture, myData.slideArea.fImgW, myData.slideArea.fImgH);
		
		//Masque
		glDisable (GL_TEXTURE_2D);
		glColor4f (1., 1., 1., myData.fAnimAlpha);
		glBegin(GL_QUADS);
		glVertex3f(-.5*myData.slideArea.fImgW,  .5*myData.slideArea.fImgH, 0.);
		glVertex3f( .5*myData.slideArea.fImgW,  .5*myData.slideArea.fImgH, 0.);
		glVertex3f( .5*myData.slideArea.fImgW, -.5*myData.slideArea.fImgH, 0.);
		glVertex3f(-.5*myData.slideArea.fImgW, -.5*myData.slideArea.fImgH, 0.);
		glEnd();
		
		glDisable (GL_BLEND);
		CD_APPLET_FINISH_DRAWING_MY_ICON;
	}
	else
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN_CAIRO (FALSE);
		//On efface le fond
		///_cd_slider_erase_surface (myApplet);
		
		//On empeche la transparence
		_cd_slider_add_background_to_current_slide (myApplet, myData.slideArea.fImgX, myData.slideArea.fImgY, 1.);
		
		//Image
		cairo_set_source_surface (myDrawContext, myData.pCairoSurface, myData.slideArea.fImgX, myData.slideArea.fImgY);
		cairo_paint (myDrawContext);
		
		//Masque
		cairo_set_source_rgba (myDrawContext, 1., 1., 1., myData.fAnimAlpha);
		cairo_rectangle(myDrawContext, 0., 0., myData.iSurfaceWidth, myData.iSurfaceHeight);
		cairo_fill(myDrawContext);
		CD_APPLET_FINISH_DRAWING_MY_ICON_CAIRO;
	}
	
	return (myData.fAnimAlpha > 0.01);
}

gboolean cd_slider_fade_in_out (GldiModuleInstance *myApplet) {
	myData.iAnimCNT ++;
	if (myData.iAnimCNT <= myConfig.iNbAnimationStep)  // courbe de alpha : \__/
		myData.fAnimAlpha = 1. * (myConfig.iNbAnimationStep - myData.iAnimCNT) / myConfig.iNbAnimationStep;
	else if (myData.iAnimCNT <= 1.5 * myConfig.iNbAnimationStep)
	{
		return TRUE;  // on ne fait rien, texture inchangee.
	}
	else
		myData.fAnimAlpha = 1. * (myData.iAnimCNT - 1.5 * myConfig.iNbAnimationStep) / myConfig.iNbAnimationStep;
	
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN (FALSE);
		
		if (myData.iAnimCNT < myConfig.iNbAnimationStep && myData.iPrevTexture != 0)  // image precedente en train de disparaitre
		{
			//On empeche la transparence
			_cd_slider_add_background_to_prev_slide_opengl (myApplet, 0., 0., myData.fAnimAlpha);
			
			//Image
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable (GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor4f (1., 1., 1., myData.fAnimAlpha);
			cairo_dock_apply_texture_at_size (myData.iPrevTexture, myData.prevSlideArea.fImgW, myData.prevSlideArea.fImgH);
		}
		else if (myData.iAnimCNT > myConfig.iNbAnimationStep) // image courante en train d'apparaitre.
		{
			//On empeche la transparence
			_cd_slider_add_background_to_current_slide_opengl (myApplet, 0., 0., myData.fAnimAlpha);
			
			//Image
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable (GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor4f (1., 1., 1., myData.fAnimAlpha);
			cairo_dock_apply_texture_at_size (myData.iTexture, myData.slideArea.fImgW, myData.slideArea.fImgH);
		}
		
		glDisable (GL_TEXTURE_2D);
		glDisable (GL_BLEND);
		CD_APPLET_FINISH_DRAWING_MY_ICON;
	}
	else
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN_CAIRO (FALSE);
		//On efface le fond
		///_cd_slider_erase_surface (myApplet);
		
		if (myData.iAnimCNT < myConfig.iNbAnimationStep)  // image precedente en train de disparaitre
		{
			//On empeche la transparence
			_cd_slider_add_background_to_prev_slide (myApplet, myData.prevSlideArea.fImgX, myData.prevSlideArea.fImgY, myData.fAnimAlpha);
			//Image
			cairo_set_source_surface (myDrawContext, myData.pPrevCairoSurface, myData.prevSlideArea.fImgX, myData.prevSlideArea.fImgY);
		}
		else if (myData.iAnimCNT > myConfig.iNbAnimationStep) // image courante en train d'apparaitre.
		{
			//On empeche la transparence
			_cd_slider_add_background_to_current_slide (myApplet, myData.slideArea.fImgX, myData.slideArea.fImgY, myData.fAnimAlpha);
			//Image
			cairo_set_source_surface (myDrawContext, myData.pCairoSurface, myData.slideArea.fImgX, myData.slideArea.fImgY);
		}
		cairo_paint_with_alpha (myDrawContext, myData.fAnimAlpha);
		CD_APPLET_FINISH_DRAWING_MY_ICON_CAIRO;
	}
	
	return (myData.fAnimAlpha < .99);
}

gboolean cd_slider_side_kick (GldiModuleInstance *myApplet) {
	myData.iAnimCNT += myData.sens;
	int xcumul = myData.iAnimCNT * (myData.iAnimCNT + 1) / 2;
	xcumul *= (10./myConfig.iNbAnimationStep);  /// au pif, a calculer ...
	if (xcumul > myData.iSurfaceWidth)  // en fait il faudrait regarder x > (iSurfaceWidth + fImgW)/2, mais comme ca on se prend pas la tete avec la difference de fImgW et fprevImgW, et ca laisse une petite tampo pendant laquelle l'icone est vide, c'est bien.
		myData.sens = -1;  // donc le coup d'apres on sera a nouveau en-dessous du seuil.
	
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN (FALSE);
		
		if (myData.sens == 1)  // image precedente qui part sur la gauche.
		{
			_cd_slider_add_background_to_prev_slide_opengl (myApplet, - xcumul, 0., 1.);
			
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable (GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor4f (1., 1., 1., 1.);
			
			glTranslatef (- xcumul, 0., 0.);
			cairo_dock_apply_texture_at_size (myData.iPrevTexture, myData.prevSlideArea.fImgW, myData.prevSlideArea.fImgH);
		}
		else  // image courante qui vient de la droite.
		{
			_cd_slider_add_background_to_current_slide_opengl (myApplet, xcumul, 0., 1.);
			
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable (GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor4f (1., 1., 1., 1.);
			
			glTranslatef (xcumul, 0., 0.);
			cairo_dock_apply_texture_at_size (myData.iTexture, myData.slideArea.fImgW, myData.slideArea.fImgH);
		}
		
		glDisable (GL_TEXTURE_2D);
		glDisable (GL_BLEND);
		CD_APPLET_FINISH_DRAWING_MY_ICON;
	}
	else
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN_CAIRO (FALSE);
		//On efface le fond
		///_cd_slider_erase_surface (myApplet);
		
		if (myData.sens == 1)  // image precedente qui part sur la gauche.
		{
			_cd_slider_add_background_to_prev_slide (myApplet, myData.prevSlideArea.fImgX - xcumul, myData.prevSlideArea.fImgY, 1.);
			
			cairo_set_source_surface (myDrawContext, myData.pPrevCairoSurface, myData.prevSlideArea.fImgX - xcumul, myData.prevSlideArea.fImgY);
		}
		else  // image courante qui vient de la droite.
		{
			_cd_slider_add_background_to_current_slide (myApplet, myData.slideArea.fImgX + xcumul, myData.slideArea.fImgY, 1.);
			
			cairo_set_source_surface (myDrawContext, myData.pCairoSurface, myData.slideArea.fImgX + xcumul, myData.slideArea.fImgY);
		}
		cairo_paint (myDrawContext);
		CD_APPLET_FINISH_DRAWING_MY_ICON_CAIRO;
	}
	
	return (myData.iAnimCNT > 0);
}

gboolean cd_slider_diaporama (GldiModuleInstance *myApplet) {
	static double a = .75;
	myData.iAnimCNT ++;
	myData.fAnimAlpha = 1.*myData.iAnimCNT / myConfig.iNbAnimationStep;
	if (myData.fAnimAlpha > 1)
		myData.fAnimAlpha = 1;
	
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN (FALSE);
		
		cairo_dock_set_perspective_view_for_icon (myIcon, myContainer);
		glScalef (1., -1., 1.);
		
		if (myData.iPrevTexture != 0 && myData.fAnimAlpha < a)
		{
			glPushMatrix ();
			
			glTranslatef (-myData.iSurfaceWidth/2, 0., 0.);
			glRotatef (120. * (myData.fAnimAlpha/a), 0., 1., 0.);
			glTranslatef (myData.iSurfaceWidth/2, 0., 0.);
			
			//On empeche la transparence
			_cd_slider_add_background_to_prev_slide_opengl (myApplet, 0., 0., 1.);
			
			//Image
			_cairo_dock_enable_texture ();
			_cairo_dock_set_blend_alpha ();
			_cairo_dock_set_alpha (1.);
			cairo_dock_apply_texture_at_size (myData.iPrevTexture, myData.prevSlideArea.fImgW, myData.prevSlideArea.fImgH);
			
			glPopMatrix ();
		}
		
		if (myData.fAnimAlpha > 1-a)
		{
			glTranslatef (myData.iSurfaceWidth/2, 0., 0.);
			glRotatef (-120. * (1-myData.fAnimAlpha)/a, 0., 1., 0.);
			glTranslatef (-myData.iSurfaceWidth/2, 0., 0.);
			
			//On empeche la transparence
			_cd_slider_add_background_to_current_slide_opengl (myApplet, 0., 0., 1.);
			
			//Image
			_cairo_dock_enable_texture ();
			_cairo_dock_set_blend_alpha ();
			_cairo_dock_set_alpha (1.);
			glColor4f (1., 1., 1., 1.);
			cairo_dock_apply_texture_at_size (myData.iTexture, myData.slideArea.fImgW, myData.slideArea.fImgH);
		}
		
		_cairo_dock_disable_texture ();
		
		CD_APPLET_FINISH_DRAWING_MY_ICON;
		
		if (myDock)
			cairo_dock_set_ortho_view (myContainer);
	}
	else
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN_CAIRO (FALSE);
		//On efface le fond
		///_cd_slider_erase_surface (myApplet);
		
		//Image précédante
		if (myData.pPrevCairoSurface != NULL)
		{
			_cd_slider_add_background_to_prev_slide (myApplet, myData.prevSlideArea.fImgX - myData.fAnimAlpha * myData.iSurfaceWidth, myData.prevSlideArea.fImgY, 1.);
			
			cairo_set_source_surface (myDrawContext, myData.pPrevCairoSurface, myData.prevSlideArea.fImgX - myData.fAnimAlpha * myData.iSurfaceWidth, myData.prevSlideArea.fImgY);
			cairo_paint(myDrawContext);
		}
		
		//Image courante.
		_cd_slider_add_background_to_current_slide (myApplet, myData.slideArea.fImgX + myData.iSurfaceWidth * (1 - myData.fAnimAlpha), myData.slideArea.fImgY, 1.);
		
		cairo_set_source_surface (myDrawContext, myData.pCairoSurface, myData.slideArea.fImgX + myData.iSurfaceWidth * (1 - myData.fAnimAlpha), myData.slideArea.fImgY);
		cairo_paint(myDrawContext);
		CD_APPLET_FINISH_DRAWING_MY_ICON_CAIRO;
	}
	
	return (myData.fAnimAlpha < .999);
}

gboolean cd_slider_grow_up (GldiModuleInstance *myApplet) {
	myData.iAnimCNT ++;
	myData.fAnimAlpha = 1.*myData.iAnimCNT / myConfig.iNbAnimationStep;
	if (myData.fAnimAlpha > 1)
		myData.fAnimAlpha = 1;
	
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN (FALSE);
		
		glPushMatrix ();
		glScalef (myData.fAnimAlpha, myData.fAnimAlpha, 1.);
		_cd_slider_add_background_to_current_slide_opengl (myApplet, 0., 0., 1.);
		glPopMatrix ();
		
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable (GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		glColor4f (1., 1., 1., 1.);
		cairo_dock_apply_texture_at_size (myData.iTexture, myData.slideArea.fImgW * myData.fAnimAlpha, myData.slideArea.fImgH * myData.fAnimAlpha);
		
		glDisable (GL_TEXTURE_2D);
		glDisable (GL_BLEND);
		CD_APPLET_FINISH_DRAWING_MY_ICON;
	}
	else
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN_CAIRO (FALSE);
		//On efface le fond
		///_cd_slider_erase_surface (myApplet);
		
		//On met a l'échelle en recentrant.
		cairo_save(myDrawContext);
		cairo_translate (myDrawContext, (myData.iSurfaceWidth - myData.slideArea.fImgW * myData.fAnimAlpha) / 2, (myData.iSurfaceHeight - myData.slideArea.fImgH * myData.fAnimAlpha) / 2);
		cairo_scale(myDrawContext, myData.fAnimAlpha, myData.fAnimAlpha);
		
		//On empeche la transparence et on affiche l'image
		_cd_slider_add_background_to_current_slide (myApplet, 0., 0., 1.);
		cairo_set_source_surface (myDrawContext, myData.pCairoSurface, 0., 0.);
		
		cairo_paint_with_alpha (myDrawContext, myData.fAnimAlpha);
		cairo_restore(myDrawContext);
		CD_APPLET_FINISH_DRAWING_MY_ICON_CAIRO;
	}
	
	return (myData.fAnimAlpha < .99);
}

gboolean cd_slider_shrink_down (GldiModuleInstance *myApplet) {
	myData.iAnimCNT ++;
	myData.fAnimAlpha = 2 - 1.*myData.iAnimCNT / myConfig.iNbAnimationStep;
	if (myData.fAnimAlpha < 1)
		myData.fAnimAlpha = 1;
	
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN (FALSE);
		
		glPushMatrix ();
		glScalef (myData.fAnimAlpha, myData.fAnimAlpha, 1.);
		_cd_slider_add_background_to_current_slide_opengl (myApplet, 0., 0., 1.);
		glPopMatrix ();
		
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable (GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		glColor4f (1., 1., 1., 1.);
		cairo_dock_apply_texture_at_size (myData.iTexture, myData.slideArea.fImgW * myData.fAnimAlpha, myData.slideArea.fImgH * myData.fAnimAlpha);
		
		glDisable (GL_TEXTURE_2D);
		glDisable (GL_BLEND);
		CD_APPLET_FINISH_DRAWING_MY_ICON;
	}
	else
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN_CAIRO (FALSE);
		//On efface le fond
		///_cd_slider_erase_surface (myApplet);
		
		//On met a l'échelle en recentrant.
		cairo_save(myDrawContext);
		cairo_translate (myDrawContext, (myData.iSurfaceWidth - myData.slideArea.fImgW * myData.fAnimAlpha) / 2, (myData.iSurfaceHeight - myData.slideArea.fImgH * myData.fAnimAlpha) / 2);
		cairo_scale(myDrawContext, myData.fAnimAlpha, myData.fAnimAlpha);
		
		//On empeche la transparence et on affiche l'image
		_cd_slider_add_background_to_current_slide (myApplet, 0., 0., 1.);
		cairo_set_source_surface (myDrawContext, myData.pCairoSurface, 0., 0.);
		
		cairo_paint_with_alpha (myDrawContext, myData.fAnimAlpha);
		cairo_restore(myDrawContext);
		CD_APPLET_FINISH_DRAWING_MY_ICON_CAIRO;
	}
	
	return (myData.fAnimAlpha > 1.01);
}

gboolean cd_slider_cube (GldiModuleInstance *myApplet) {
	myData.iAnimCNT ++;
	myData.fAnimAlpha = 1.*myData.iAnimCNT / myConfig.iNbAnimationStep;
	if (myData.fAnimAlpha > 1)
		myData.fAnimAlpha = 1;
	
	if (CD_APPLET_MY_CONTAINER_IS_OPENGL)
	{
		CD_APPLET_START_DRAWING_MY_ICON_OR_RETURN (FALSE);
		
		cairo_dock_set_perspective_view_for_icon (myIcon, myContainer);
		glScalef (1., -1., 1.);
		
		double fTheta = - 45. + myData.fAnimAlpha * 90.;  // -45 -> 45
		glTranslatef (0., 0., - myData.iSurfaceWidth * sqrt(2)/2 * cos (fTheta/180.*G_PI));  // pour faire tenir le cube dans la fenetre.
		glEnable (GL_DEPTH_TEST);
		
		// image precedente.
		if (fTheta < 25)  // inutile de dessiner si elle est derriere l'image courante, par l'effet de perspective (en fait 22.5, mais bizarrement ca a l'air un peu trop tot).
		{
			glPushMatrix ();
			glRotatef (45. + fTheta, 0., 1., 0.);  // 0 -> 90
			glTranslatef (0., 0., myData.slideArea.fImgW/2-1);
			
			_cd_slider_add_background_to_prev_slide_opengl (myApplet, 0., 0., 1.);
			
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable (GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			
			glTranslatef (0., 0., 1.);
			glColor4f (1., 1., 1., 1.);
			cairo_dock_apply_texture_at_size (myData.iPrevTexture, myData.prevSlideArea.fImgW, myData.prevSlideArea.fImgH);
			glDisable (GL_TEXTURE_2D);
			glPopMatrix ();
		}
		// image courante a 90deg.
		glRotatef (45. + fTheta, 0., 1., 0.);  // 0 -> 90
		if (myData.prevSlideArea.fImgW != 0)
			glTranslatef (- myData.prevSlideArea.fImgW/2+1, 0., 0.);
		else
			glTranslatef (- myData.iSurfaceWidth/2+1, 0., 0.);
		
		glPushMatrix ();
		glRotatef (-90., 0., 1., 0.);
		_cd_slider_add_background_to_current_slide_opengl (myApplet, 0., 0., 1.);
		glPopMatrix ();
		
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable (GL_TEXTURE_2D);
		
		glTranslatef (-1., 0., 0.);
		glRotatef (-90., 0., 1., 0.);
		glColor4f (1., 1., 1., 1.);
		cairo_dock_apply_texture_at_size (myData.iTexture, myData.slideArea.fImgW, myData.slideArea.fImgH);
		
		glDisable (GL_DEPTH_TEST);
		glDisable (GL_TEXTURE_2D);
		glDisable (GL_BLEND);
		CD_APPLET_FINISH_DRAWING_MY_ICON;
		
		if (myDock)
			cairo_dock_set_ortho_view (myContainer);
	}
	else
	{
		cd_slider_draw_default (myApplet);
		return FALSE;
	}
	return (myData.fAnimAlpha < .99);
}
