#ifndef _INTERFAZ_H
#define _INTERFAZ_H

#include <gtk/gtk.h>
#include <math.h>
#include <unistd.h>

struct update_progress update_progress_var;

enum
{
  COL_PROCESS_ID,
  COL_PROGRESS ,
  COL_PROCESS_ACTIVE,
  COL_PI_VALUE,
  NUM_COLS
} ;

struct update_progress {
  gpointer user_data;
 double PI_value;
 float progress;
 uint terminos;
 const gchar *status;
 const gchar *path;
 GtkWidget *window;
 GtkWidget *view;
};

gboolean update_model (gpointer user_data);
double arcsin(unsigned int terminos);
gpointer arcsin_thread(gpointer user_data);
GtkTreeModel *create_and_fill_model (int num_process);
GtkWidget *create_view_and_model (int num_process);
gpointer scheduler_thread(gpointer user_data);
void setup_interfaz (int num_process);

#endif
