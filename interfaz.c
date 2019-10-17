#include "interfaz.h"
#include "Controller.h"
gboolean update_model (gpointer user_data)
{
  GtkListStore *store = (GtkListStore*) user_data;
  GtkTreeIter iter;
  GtkTreePath *path;
  // double progress = 50.5;
  // float PI_value = 3.145926;
  //printf("hola\n" );
  path = gtk_tree_path_new_from_string (update_progress_var.path);
       gtk_tree_model_get_iter (GTK_TREE_MODEL (user_data),
                                &iter,
                                path);
  //      gtk_tree_path_free (path);
  //gtk_tree_model_get_iter_first (GTK_TREE_MODEL (user_data), &iter);
  gtk_list_store_set (store, &iter,
              COL_PROGRESS, update_progress_var.progress ,
              COL_PROCESS_ACTIVE, update_progress_var.status,
              COL_PI_VALUE, update_progress_var.PI_value,
              -1);

  return TRUE;
}


double arcsin(unsigned int terminos) {
    double ans = 4;
    float percentage;
    //
    for (uint i = 1; i <= terminos; i++) {
      ans += (4*pow(-1,i))/(2*i+1);
      percentage = 100*((double)i/(double)terminos);
    //  printf("i = %d, porcentaje: %lf, PI = %lf\n",i, percentage, ans );
    }
    return ans;
}
gpointer scheduler_thread(gpointer user_data) {
	Start_Scheduler();
}


GtkTreeModel *
create_and_fill_model (int num_process)
{
  GtkListStore  *store;
  GtkTreeIter    iter;

  store = gtk_list_store_new (NUM_COLS, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_STRING,G_TYPE_DOUBLE);


  for (uint i = 0; i < num_process; i++) {
    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter,
                        COL_PROCESS_ID, i,
                        COL_PROGRESS, 10.53,
                        COL_PROCESS_ACTIVE, "Inactive",
                        COL_PI_VALUE, 0.0,
                        -1);
  }



  return GTK_TREE_MODEL (store);
}

GtkWidget *
create_view_and_model (int num_process)
{
  GtkCellRenderer     *renderer;
  GtkTreeModel        *model;
  GtkWidget           *view;

  view = gtk_tree_view_new ();

  /* --- Column #1 --- */

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                               -1,
                                               "Process ID",
                                               renderer,
                                               "text", COL_PROCESS_ID,
                                               NULL);

  /* --- Column #2 --- */

  renderer = gtk_cell_renderer_progress_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1, "Progress",
                                               renderer, "value", COL_PROGRESS,NULL);

  //gtk_tree_view_insert_column (GTK_TREE_VIEW (view), COL_PROGRESS,-1);

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                             -1,
                                             "Status",
                                             renderer,
                                             "text", COL_PROCESS_ACTIVE,
                                             NULL);


  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                              -1,
                                              "PI Value",
                                              renderer,
                                              "text", COL_PI_VALUE,
                                              NULL);


  model = create_and_fill_model (num_process);

  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  /* The tree view has acquired its own reference to the
   *  model, so we can drop ours. That way the model will
   *  be freed automatically when the tree view is destroyed */

  g_object_unref (model);

  return view;
}
