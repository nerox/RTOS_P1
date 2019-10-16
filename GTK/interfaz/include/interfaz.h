#ifndef _INTERFAZ_H
#define _INTERFAZ_H

static gboolean update_model (gpointer user_data);
double arcsin(unsigned int terminos);
gpointer arcsin_thread(gpointer user_data);
static GtkTreeModel *create_and_fill_model (int num_process);
static GtkWidget *create_view_and_model (int num_process);



#endif
