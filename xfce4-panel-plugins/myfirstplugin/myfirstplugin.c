/* myfirstplugin.c

*/

#include <libxfce4panel/xfce-panel-plugin.h>

static void constructor(XfcePanelPlugn * plugin) {
    // Any gtk container can be used it will be packed into
    // the XfcePanelPlugn variable
    GtkWidget * scroll_win = gtk_scrolled_window(NULL, NULL);

    /* Write gtk application */

    // Pack gtk container into plugin's container
    gtk_container_add(GTK_CONTAINER(plugin), scroll_win);

    // Show the widget
    gtk_widget_show_all(scroll_win);
    xfce_panel_plugin_set_expand(XFCE_PANEL_PLUGIN(plugin), TRUE);
}
