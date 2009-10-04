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

#include "applet-struct.h"
#include "applet-star.h"


CairoParticleSystem *cd_icon_effect_init_stars (Icon *pIcon, CairoDock *pDock, double dt)
{
	if (myData.iStarTexture == 0)
		myData.iStarTexture = cd_icon_effect_load_star_texture ();
	double fMaxScale = (!g_bEasterEggs && pDock->bAtBottom ? 1. : cairo_dock_get_max_scale (CAIRO_CONTAINER (pDock)));
	CairoParticleSystem *pStarParticleSystem = cairo_dock_create_particle_system (myConfig.iNbStarParticles, myData.iStarTexture, pIcon->fWidth * pIcon->fScale, pIcon->fHeight * fMaxScale);
	g_return_val_if_fail (pStarParticleSystem != NULL, NULL);
	pStarParticleSystem->dt = dt;
	pStarParticleSystem->bAddLuminance = TRUE;
	
	static double a = .4;
	static double epsilon = 0.1;
	double r = myConfig.iStarParticleSize;
	double fBlend;
	CairoParticle *p;
	int i;
	for (i = 0; i < myConfig.iNbStarParticles; i ++)
	{
		p = &pStarParticleSystem->pParticles[i];
		
		p->x = 2 * g_random_double () - 1;
		p->y = g_random_double ();
		p->z = 2 * g_random_double () - 1;
		p->fWidth = r*(p->z + 1)/2 * g_random_double ();
		p->fHeight = p->fWidth;
		
		p->vx = 0.;
		p->vy = 0.;
		
		p->iInitialLife = myConfig.iStarDuration / dt;
		p->iLife = p->iInitialLife * (g_random_double () + a) / (1 + a);
		
		if (myConfig.bMysticalStars)
		{
			p->color[0] = g_random_double ();
			p->color[1] = g_random_double ();
			p->color[2] = g_random_double ();
		}
		else
		{
			fBlend = g_random_double ();
			p->color[0] = fBlend * myConfig.pStarColor1[0] + (1 - fBlend) * myConfig.pStarColor2[0];
			p->color[1] = fBlend * myConfig.pStarColor1[1] + (1 - fBlend) * myConfig.pStarColor2[1];
			p->color[2] = fBlend * myConfig.pStarColor1[2] + (1 - fBlend) * myConfig.pStarColor2[2];
		}
		p->color[3] = 0.;  // on va gerer nous-mêmes la transparence.
		
		p->fOscillation = 0.;
		p->fOmega = 0.;
		
		p->fSizeFactor = 1.;
		p->fResizeSpeed = - 1. / myConfig.iStarDuration * dt;  // zoom 0 a la fin.
	}
	
	return pStarParticleSystem;
}

gboolean cd_icon_effect_update_star_system (CairoParticleSystem *pParticleSystem, CairoDockRewindParticleFunc pRewindParticle)
{
	static double a = .4;
	gboolean bAllParticlesEnded = TRUE;
	double x;
	CairoParticle *p;
	int i;
	for (i = 0; i < pParticleSystem->iNbParticles; i ++)
	{
		p = &(pParticleSystem->pParticles[i]);
		
		if (p->iLife > a * p->iInitialLife)
			p->color[3] = 0.;
		else
		{
			x = 1. * p->iLife / p->iInitialLife;
			p->color[3] = 1 - fabs (x - a/2) / (a/2);
		}
		
		p->fSizeFactor += p->fResizeSpeed;
		if (p->iLife > 0)
		{
			p->iLife --;
			if (pRewindParticle && p->iLife == 0)
			{
				pRewindParticle (p, pParticleSystem->dt);
			}
			if (bAllParticlesEnded && p->iLife != 0)
				bAllParticlesEnded = FALSE;
		}
	}
	return ! bAllParticlesEnded;
}

void cd_icon_effect_rewind_star_particle (CairoParticle *p, double dt)
{
	double a = .2;
	p->x = 2 * g_random_double () - 1;
	p->y = g_random_double ();
	p->fSizeFactor = 1.;
	p->iInitialLife = myConfig.iStarDuration / dt;
	p->iLife = p->iInitialLife * (g_random_double () + a) / (1 + a);
}
