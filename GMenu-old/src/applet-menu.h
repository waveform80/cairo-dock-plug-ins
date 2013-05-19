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


#ifndef __APPLET_MENU__
#define  __APPLET_MENU__

#include <cairo-dock.h>
#define GMENU_I_KNOW_THIS_IS_UNSTABLE
#include <gmenu-tree.h>

#define PANEL_ICON_FOLDER "folder"
// #define PANEL_DEFAULT_MENU_ICON_SIZE 24


GtkWidget * add_menu_separator (GtkWidget *menu);

GtkWidget * create_fake_menu (GMenuTreeDirectory *directory);

GdkPixbuf * panel_make_menu_icon (GtkIconTheme *icon_theme,
		      const char   *icon,
		      const char   *fallback,
		      int           size,
		      gboolean     *long_operation);

void setup_menuitem (GtkWidget   *menuitem,
		GtkIconSize  icon_size,
		///GtkWidget   *image,
		const char  *title);

GtkWidget * populate_menu_from_directory (GtkWidget          *menu,
			      GMenuTreeDirectory *directory);

void image_menu_destroy (GtkWidget *image, gpointer *data);

void reload_image_menu_items (void);

GtkWidget * create_empty_menu (void);

GtkWidget * create_applications_menu (const char *menu_file,
			  const char *menu_path, GtkWidget *parent_menu);

gchar ** cd_gmenu_get_xdg_menu_dirs (void);

GtkWidget * create_main_menu (GldiModuleInstance *myApplet);


#endif
