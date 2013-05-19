/* CDApplet.h generated by valac 0.18.1, the Vala compiler, do not modify */


#ifndef ___HOME_FAB_CD2_CAIRO_DOCK_PLUG_INS_DBUS_INTERFACES_VALA_SRC_CDAPPLET_H__
#define ___HOME_FAB_CD2_CAIRO_DOCK_PLUG_INS_DBUS_INTERFACES_VALA_SRC_CDAPPLET_H__

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

G_BEGIN_DECLS


#define CAIRO_DOCK_APPLET_TYPE_IAPPLET (cairo_dock_applet_iapplet_get_type ())
#define CAIRO_DOCK_APPLET_IAPPLET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CAIRO_DOCK_APPLET_TYPE_IAPPLET, CairoDockAppletIApplet))
#define CAIRO_DOCK_APPLET_IS_IAPPLET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CAIRO_DOCK_APPLET_TYPE_IAPPLET))
#define CAIRO_DOCK_APPLET_IAPPLET_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), CAIRO_DOCK_APPLET_TYPE_IAPPLET, CairoDockAppletIAppletIface))

typedef struct _CairoDockAppletIApplet CairoDockAppletIApplet;
typedef struct _CairoDockAppletIAppletIface CairoDockAppletIAppletIface;

#define CAIRO_DOCK_APPLET_TYPE_IAPPLET_PROXY (cairo_dock_applet_iapplet_proxy_get_type ())

#define CAIRO_DOCK_APPLET_TYPE_ISUB_APPLET (cairo_dock_applet_isub_applet_get_type ())
#define CAIRO_DOCK_APPLET_ISUB_APPLET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CAIRO_DOCK_APPLET_TYPE_ISUB_APPLET, CairoDockAppletISubApplet))
#define CAIRO_DOCK_APPLET_IS_ISUB_APPLET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CAIRO_DOCK_APPLET_TYPE_ISUB_APPLET))
#define CAIRO_DOCK_APPLET_ISUB_APPLET_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), CAIRO_DOCK_APPLET_TYPE_ISUB_APPLET, CairoDockAppletISubAppletIface))

typedef struct _CairoDockAppletISubApplet CairoDockAppletISubApplet;
typedef struct _CairoDockAppletISubAppletIface CairoDockAppletISubAppletIface;

#define CAIRO_DOCK_APPLET_TYPE_ISUB_APPLET_PROXY (cairo_dock_applet_isub_applet_proxy_get_type ())

#define CAIRO_DOCK_APPLET_TYPE_CD_APPLET (cairo_dock_applet_cd_applet_get_type ())
#define CAIRO_DOCK_APPLET_CD_APPLET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CAIRO_DOCK_APPLET_TYPE_CD_APPLET, CairoDockAppletCDApplet))
#define CAIRO_DOCK_APPLET_CD_APPLET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CAIRO_DOCK_APPLET_TYPE_CD_APPLET, CairoDockAppletCDAppletClass))
#define CAIRO_DOCK_APPLET_IS_CD_APPLET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CAIRO_DOCK_APPLET_TYPE_CD_APPLET))
#define CAIRO_DOCK_APPLET_IS_CD_APPLET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CAIRO_DOCK_APPLET_TYPE_CD_APPLET))
#define CAIRO_DOCK_APPLET_CD_APPLET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CAIRO_DOCK_APPLET_TYPE_CD_APPLET, CairoDockAppletCDAppletClass))

typedef struct _CairoDockAppletCDApplet CairoDockAppletCDApplet;
typedef struct _CairoDockAppletCDAppletClass CairoDockAppletCDAppletClass;
typedef struct _CairoDockAppletCDAppletPrivate CairoDockAppletCDAppletPrivate;

#define CAIRO_DOCK_APPLET_CD_APPLET_TYPE_SCREEN_POSITION (cairo_dock_applet_cd_applet_screen_position_get_type ())

#define CAIRO_DOCK_APPLET_CD_APPLET_TYPE_CONTAINER_TYPE (cairo_dock_applet_cd_applet_container_type_get_type ())

#define CAIRO_DOCK_APPLET_CD_APPLET_TYPE_EMBLEM_POSITION (cairo_dock_applet_cd_applet_emblem_position_get_type ())

#define CAIRO_DOCK_APPLET_CD_APPLET_TYPE_EMBLEM_MODIFIER (cairo_dock_applet_cd_applet_emblem_modifier_get_type ())

#define CAIRO_DOCK_APPLET_CD_APPLET_TYPE_MENU_ITEM_TYPE (cairo_dock_applet_cd_applet_menu_item_type_get_type ())

#define CAIRO_DOCK_APPLET_CD_APPLET_TYPE_MENU_ITEM_ID (cairo_dock_applet_cd_applet_menu_item_id_get_type ())

#define CAIRO_DOCK_APPLET_CD_APPLET_TYPE_DIALOG_KEY (cairo_dock_applet_cd_applet_dialog_key_get_type ())

struct _CairoDockAppletIAppletIface {
	GTypeInterface parent_iface;
	GVariant* (*Get) (CairoDockAppletIApplet* self, const gchar* cProperty, GError** error);
	GHashTable* (*GetAll) (CairoDockAppletIApplet* self, GError** error);
	void (*SetQuickInfo) (CairoDockAppletIApplet* self, const gchar* cQuickInfo, GError** error);
	void (*SetLabel) (CairoDockAppletIApplet* self, const gchar* cLabel, GError** error);
	void (*SetIcon) (CairoDockAppletIApplet* self, const gchar* cImage, GError** error);
	void (*SetEmblem) (CairoDockAppletIApplet* self, const gchar* cImage, gint iPosition, GError** error);
	void (*Animate) (CairoDockAppletIApplet* self, const gchar* cAnimation, gint iRounds, GError** error);
	void (*DemandsAttention) (CairoDockAppletIApplet* self, gboolean bStart, const gchar* cAnimation, GError** error);
	void (*ShowDialog) (CairoDockAppletIApplet* self, const gchar* cMessage, gint iDuration, GError** error);
	void (*PopupDialog) (CairoDockAppletIApplet* self, GHashTable* hDialogAttributes, GHashTable* hWidgetAttributes, GError** error);
	void (*AddDataRenderer) (CairoDockAppletIApplet* self, const gchar* cType, gint iNbValues, const gchar* cTheme, GError** error);
	void (*RenderValues) (CairoDockAppletIApplet* self, gdouble* pValues, int pValues_length1, GError** error);
	void (*ControlAppli) (CairoDockAppletIApplet* self, const gchar* cApplicationClass, GError** error);
	void (*ShowAppli) (CairoDockAppletIApplet* self, gboolean bShow, GError** error);
	void (*AddMenuItems) (CairoDockAppletIApplet* self, GHashTable** pItems, int pItems_length1, GError** error);
	void (*BindShortkey) (CairoDockAppletIApplet* self, gchar** cShortkeys, int cShortkeys_length1, GError** error);
};

struct _CairoDockAppletISubAppletIface {
	GTypeInterface parent_iface;
	void (*SetQuickInfo) (CairoDockAppletISubApplet* self, const gchar* cQuickInfo, const gchar* cIconID, GError** error);
	void (*SetLabel) (CairoDockAppletISubApplet* self, const gchar* cLabel, const gchar* cIconID, GError** error);
	void (*SetIcon) (CairoDockAppletISubApplet* self, const gchar* cImage, const gchar* cIconID, GError** error);
	void (*SetEmblem) (CairoDockAppletISubApplet* self, const gchar* cImage, gint iPosition, const gchar* cIconID, GError** error);
	void (*Animate) (CairoDockAppletISubApplet* self, const gchar* cAnimation, gint iNbRounds, const gchar* cIconID, GError** error);
	void (*ShowDialog) (CairoDockAppletISubApplet* self, const gchar* message, gint iDuration, const gchar* cIconID, GError** error);
	void (*AddSubIcons) (CairoDockAppletISubApplet* self, gchar** pIconFields, int pIconFields_length1, GError** error);
	void (*RemoveSubIcon) (CairoDockAppletISubApplet* self, const gchar* cIconID, GError** error);
};

struct _CairoDockAppletCDApplet {
	GObject parent_instance;
	CairoDockAppletCDAppletPrivate * priv;
	CairoDockAppletIApplet* icon;
	CairoDockAppletISubApplet* sub_icons;
	gchar* cAppletName;
	gchar* cConfFile;
	gchar* cParentAppName;
	gchar* cBusPath;
	gchar* cShareDataDir;
	gchar* cRootDataDir;
};

struct _CairoDockAppletCDAppletClass {
	GObjectClass parent_class;
	void (*on_click) (CairoDockAppletCDApplet* self, gint iState);
	void (*on_middle_click) (CairoDockAppletCDApplet* self);
	void (*on_build_menu) (CairoDockAppletCDApplet* self);
	void (*on_menu_select) (CairoDockAppletCDApplet* self, gint iNumEntry);
	void (*on_scroll) (CairoDockAppletCDApplet* self, gboolean bScrollUp);
	void (*on_drop_data) (CairoDockAppletCDApplet* self, const gchar* cReceivedData);
	void (*on_answer) (CairoDockAppletCDApplet* self, GVariant* answer);
	void (*on_answer_dialog) (CairoDockAppletCDApplet* self, gint iButton, GVariant* answer);
	void (*on_shortkey) (CairoDockAppletCDApplet* self, const gchar* cKey);
	void (*on_change_focus) (CairoDockAppletCDApplet* self, gboolean bIsActive);
	void (*on_click_sub_icon) (CairoDockAppletCDApplet* self, gint iState, const gchar* cIconID);
	void (*on_middle_click_sub_icon) (CairoDockAppletCDApplet* self, const gchar* cIconID);
	void (*on_scroll_sub_icon) (CairoDockAppletCDApplet* self, gboolean bScrollUp, const gchar* cIconID);
	void (*on_drop_data_sub_icon) (CairoDockAppletCDApplet* self, const gchar* cReceivedData, const gchar* cIconID);
	void (*on_build_menu_sub_icon) (CairoDockAppletCDApplet* self, const gchar* cIconID);
	void (*on_menu_select_sub_icon) (CairoDockAppletCDApplet* self, gint iNumEntry, const gchar* cIconID);
	void (*begin) (CairoDockAppletCDApplet* self);
	void (*end) (CairoDockAppletCDApplet* self);
	void (*reload) (CairoDockAppletCDApplet* self);
	void (*get_config) (CairoDockAppletCDApplet* self, GKeyFile* keyfile);
};

typedef enum  {
	CAIRO_DOCK_APPLET_CD_APPLET_SCREEN_POSITION_BOTTOM = 0,
	CAIRO_DOCK_APPLET_CD_APPLET_SCREEN_POSITION_TOP,
	CAIRO_DOCK_APPLET_CD_APPLET_SCREEN_POSITION_RIGHT,
	CAIRO_DOCK_APPLET_CD_APPLET_SCREEN_POSITION_LEFT
} CairoDockAppletCDAppletScreenPosition;

typedef enum  {
	CAIRO_DOCK_APPLET_CD_APPLET_CONTAINER_TYPE_DOCK = 0,
	CAIRO_DOCK_APPLET_CD_APPLET_CONTAINER_TYPE_DESKLET
} CairoDockAppletCDAppletContainerType;

typedef enum  {
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_TOP_LEFT = 0,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_BOTTOM_RIGHT,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_BOTTOM_LEFT,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_TOP_RIGHT,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_MIDDLE,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_BOTTOM,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_TOP,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_RIGHT,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_POSITION_EMBLEM_LEFT
} CairoDockAppletCDAppletEmblemPosition;

typedef enum  {
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_MODIFIER_EMBLEM_PERSISTENT = 0,
	CAIRO_DOCK_APPLET_CD_APPLET_EMBLEM_MODIFIER_EMBLEM_PRINT = 9
} CairoDockAppletCDAppletEmblemModifier;

typedef enum  {
	CAIRO_DOCK_APPLET_CD_APPLET_MENU_ITEM_TYPE_MENU_ENTRY = 0,
	CAIRO_DOCK_APPLET_CD_APPLET_MENU_ITEM_TYPE_MENU_SUB_MENU,
	CAIRO_DOCK_APPLET_CD_APPLET_MENU_ITEM_TYPE_MENU_SEPARATOR,
	CAIRO_DOCK_APPLET_CD_APPLET_MENU_ITEM_TYPE_MENU_CHECKBOX,
	CAIRO_DOCK_APPLET_CD_APPLET_MENU_ITEM_TYPE_MENU_RADIO_BUTTON
} CairoDockAppletCDAppletMenuItemType;

typedef enum  {
	CAIRO_DOCK_APPLET_CD_APPLET_MENU_ITEM_ID_MAIN_MENU_ID = 0
} CairoDockAppletCDAppletMenuItemId;

typedef enum  {
	CAIRO_DOCK_APPLET_CD_APPLET_DIALOG_KEY_DIALOG_KEY_ENTER = -1,
	CAIRO_DOCK_APPLET_CD_APPLET_DIALOG_KEY_DIALOG_KEY_ESCAPE = -2
} CairoDockAppletCDAppletDialogKey;


GType cairo_dock_applet_iapplet_proxy_get_type (void) G_GNUC_CONST;
guint cairo_dock_applet_iapplet_register_object (void* object, GDBusConnection* connection, const gchar* path, GError** error);
GType cairo_dock_applet_iapplet_get_type (void) G_GNUC_CONST;
GVariant* cairo_dock_applet_iapplet_Get (CairoDockAppletIApplet* self, const gchar* cProperty, GError** error);
GHashTable* cairo_dock_applet_iapplet_GetAll (CairoDockAppletIApplet* self, GError** error);
void cairo_dock_applet_iapplet_SetQuickInfo (CairoDockAppletIApplet* self, const gchar* cQuickInfo, GError** error);
void cairo_dock_applet_iapplet_SetLabel (CairoDockAppletIApplet* self, const gchar* cLabel, GError** error);
void cairo_dock_applet_iapplet_SetIcon (CairoDockAppletIApplet* self, const gchar* cImage, GError** error);
void cairo_dock_applet_iapplet_SetEmblem (CairoDockAppletIApplet* self, const gchar* cImage, gint iPosition, GError** error);
void cairo_dock_applet_iapplet_Animate (CairoDockAppletIApplet* self, const gchar* cAnimation, gint iRounds, GError** error);
void cairo_dock_applet_iapplet_DemandsAttention (CairoDockAppletIApplet* self, gboolean bStart, const gchar* cAnimation, GError** error);
void cairo_dock_applet_iapplet_ShowDialog (CairoDockAppletIApplet* self, const gchar* cMessage, gint iDuration, GError** error);
void cairo_dock_applet_iapplet_PopupDialog (CairoDockAppletIApplet* self, GHashTable* hDialogAttributes, GHashTable* hWidgetAttributes, GError** error);
void cairo_dock_applet_iapplet_AddDataRenderer (CairoDockAppletIApplet* self, const gchar* cType, gint iNbValues, const gchar* cTheme, GError** error);
void cairo_dock_applet_iapplet_RenderValues (CairoDockAppletIApplet* self, gdouble* pValues, int pValues_length1, GError** error);
void cairo_dock_applet_iapplet_ControlAppli (CairoDockAppletIApplet* self, const gchar* cApplicationClass, GError** error);
void cairo_dock_applet_iapplet_ShowAppli (CairoDockAppletIApplet* self, gboolean bShow, GError** error);
void cairo_dock_applet_iapplet_AddMenuItems (CairoDockAppletIApplet* self, GHashTable** pItems, int pItems_length1, GError** error);
void cairo_dock_applet_iapplet_BindShortkey (CairoDockAppletIApplet* self, gchar** cShortkeys, int cShortkeys_length1, GError** error);
GType cairo_dock_applet_isub_applet_proxy_get_type (void) G_GNUC_CONST;
guint cairo_dock_applet_isub_applet_register_object (void* object, GDBusConnection* connection, const gchar* path, GError** error);
GType cairo_dock_applet_isub_applet_get_type (void) G_GNUC_CONST;
void cairo_dock_applet_isub_applet_SetQuickInfo (CairoDockAppletISubApplet* self, const gchar* cQuickInfo, const gchar* cIconID, GError** error);
void cairo_dock_applet_isub_applet_SetLabel (CairoDockAppletISubApplet* self, const gchar* cLabel, const gchar* cIconID, GError** error);
void cairo_dock_applet_isub_applet_SetIcon (CairoDockAppletISubApplet* self, const gchar* cImage, const gchar* cIconID, GError** error);
void cairo_dock_applet_isub_applet_SetEmblem (CairoDockAppletISubApplet* self, const gchar* cImage, gint iPosition, const gchar* cIconID, GError** error);
void cairo_dock_applet_isub_applet_Animate (CairoDockAppletISubApplet* self, const gchar* cAnimation, gint iNbRounds, const gchar* cIconID, GError** error);
void cairo_dock_applet_isub_applet_ShowDialog (CairoDockAppletISubApplet* self, const gchar* message, gint iDuration, const gchar* cIconID, GError** error);
void cairo_dock_applet_isub_applet_AddSubIcons (CairoDockAppletISubApplet* self, gchar** pIconFields, int pIconFields_length1, GError** error);
void cairo_dock_applet_isub_applet_RemoveSubIcon (CairoDockAppletISubApplet* self, const gchar* cIconID, GError** error);
GType cairo_dock_applet_cd_applet_get_type (void) G_GNUC_CONST;
GType cairo_dock_applet_cd_applet_screen_position_get_type (void) G_GNUC_CONST;
GType cairo_dock_applet_cd_applet_container_type_get_type (void) G_GNUC_CONST;
GType cairo_dock_applet_cd_applet_emblem_position_get_type (void) G_GNUC_CONST;
GType cairo_dock_applet_cd_applet_emblem_modifier_get_type (void) G_GNUC_CONST;
GType cairo_dock_applet_cd_applet_menu_item_type_get_type (void) G_GNUC_CONST;
GType cairo_dock_applet_cd_applet_menu_item_id_get_type (void) G_GNUC_CONST;
GType cairo_dock_applet_cd_applet_dialog_key_get_type (void) G_GNUC_CONST;
CairoDockAppletCDApplet* cairo_dock_applet_cd_applet_new (gchar** argv, int argv_length1);
CairoDockAppletCDApplet* cairo_dock_applet_cd_applet_construct (GType object_type, gchar** argv, int argv_length1);
void cairo_dock_applet_cd_applet_run (CairoDockAppletCDApplet* self);
void cairo_dock_applet_cd_applet_on_click (CairoDockAppletCDApplet* self, gint iState);
void cairo_dock_applet_cd_applet_on_middle_click (CairoDockAppletCDApplet* self);
void cairo_dock_applet_cd_applet_on_build_menu (CairoDockAppletCDApplet* self);
void cairo_dock_applet_cd_applet_on_menu_select (CairoDockAppletCDApplet* self, gint iNumEntry);
void cairo_dock_applet_cd_applet_on_scroll (CairoDockAppletCDApplet* self, gboolean bScrollUp);
void cairo_dock_applet_cd_applet_on_drop_data (CairoDockAppletCDApplet* self, const gchar* cReceivedData);
void cairo_dock_applet_cd_applet_on_answer (CairoDockAppletCDApplet* self, GVariant* answer);
void cairo_dock_applet_cd_applet_on_answer_dialog (CairoDockAppletCDApplet* self, gint iButton, GVariant* answer);
void cairo_dock_applet_cd_applet_on_shortkey (CairoDockAppletCDApplet* self, const gchar* cKey);
void cairo_dock_applet_cd_applet_on_change_focus (CairoDockAppletCDApplet* self, gboolean bIsActive);
void cairo_dock_applet_cd_applet_on_click_sub_icon (CairoDockAppletCDApplet* self, gint iState, const gchar* cIconID);
void cairo_dock_applet_cd_applet_on_middle_click_sub_icon (CairoDockAppletCDApplet* self, const gchar* cIconID);
void cairo_dock_applet_cd_applet_on_scroll_sub_icon (CairoDockAppletCDApplet* self, gboolean bScrollUp, const gchar* cIconID);
void cairo_dock_applet_cd_applet_on_drop_data_sub_icon (CairoDockAppletCDApplet* self, const gchar* cReceivedData, const gchar* cIconID);
void cairo_dock_applet_cd_applet_on_build_menu_sub_icon (CairoDockAppletCDApplet* self, const gchar* cIconID);
void cairo_dock_applet_cd_applet_on_menu_select_sub_icon (CairoDockAppletCDApplet* self, gint iNumEntry, const gchar* cIconID);
void cairo_dock_applet_cd_applet_begin (CairoDockAppletCDApplet* self);
void cairo_dock_applet_cd_applet_end (CairoDockAppletCDApplet* self);
void cairo_dock_applet_cd_applet_reload (CairoDockAppletCDApplet* self);
void cairo_dock_applet_cd_applet_get_config (CairoDockAppletCDApplet* self, GKeyFile* keyfile);


G_END_DECLS

#endif
