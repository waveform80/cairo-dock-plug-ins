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

#ifndef __APPLET_ICON_FINDER__
#define  __APPLET_ICON_FINDER__

#include <cairo-dock.h>
#include "applet-struct.h"


Icon *cd_do_search_icon_by_command (const gchar *cCommandPrefix, Icon *pAfterIcon, CairoDock **pDock);


void cd_do_change_current_icon (Icon *pIcon, CairoDock *pDock);


void cd_do_search_current_icon (gboolean bLoopSearch);


gboolean cairo_dock_emit_motion_signal (CairoDock *pDock, int iMouseX, int iMouseY);


void cd_do_search_matching_icons (void);

void cd_do_select_previous_next_matching_icon (gboolean bNext);


#endif
