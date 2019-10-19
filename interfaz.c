#include "interfaz.h"
#include "Controller.h"


gboolean update_model (gpointer user_data)
{
  GtkListStore *store = (GtkListStore*) user_data;
	GtkTreeIter iter;
	GtkTreePath *path_gtk;
	int index;
	for(index=0;index<PROCESSES_AVAILABLE;index++){
	sprintf(path, "%d", index);
	update_progress_var.path = path;
        update_progress_var.PI_value = calculated_pi_process[index];
        update_progress_var.progress = progress_by_process[index];
	switch (process_list[index].status)
		{
		case 0: // code to be executed if n = 0;
	      		update_progress_var.status = "Undeployed";
			break;
		case 1: // code to be executed if n = 1;
			update_progress_var.status = "Waiting";
			break;
		case 2: // code to be executed if n = 2;
			update_progress_var.status = "Finished";
			break;
		case 3: // code to be executed if n = 2;
			update_progress_var.status = "Active";
			break;
		default: // code to be executed if n doesn't match any cases
			break;

		}

	path_gtk = gtk_tree_path_new_from_string (update_progress_var.path);
	gtk_tree_model_get_iter (GTK_TREE_MODEL (user_data),
		                &iter,
		                path_gtk);

	gtk_list_store_set (store, &iter,
	      COL_PROGRESS, update_progress_var.progress ,
	      COL_PROCESS_ACTIVE, update_progress_var.status,
	      COL_PI_VALUE, update_progress_var.PI_value,
	      -1);
	}

  return TRUE;
}




gpointer scheduler_thread(gpointer user_data) {
	Start_Scheduler();
}


GtkTreeModel *create_and_fill_model (int num_process)
{
  GtkListStore  *store;
  GtkTreeIter    iter;

  store = gtk_list_store_new (NUM_COLS, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_STRING,G_TYPE_DOUBLE);


  for (uint i = 0; i < num_process; i++) {
    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter,
                        COL_PROCESS_ID, i,
                        COL_PROGRESS, 0.0,
                        COL_PROCESS_ACTIVE, "Inactive",
                        COL_PI_VALUE, 0.0,
                        -1);
  }



  return GTK_TREE_MODEL (store);
}

GtkWidget *create_view_and_model (int num_process)
{
  GtkCellRenderer     *renderer;
  GtkTreeModel        *model;
  GtkWidget           *view;

  view = gtk_tree_view_new ();


  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                               -1,
                                               "Process ID",
                                               renderer,
                                               "text", COL_PROCESS_ID,
                                               NULL);


  renderer = gtk_cell_renderer_progress_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1, "Progress",
                                               renderer, "value", COL_PROGRESS,NULL);



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


  g_object_unref (model);

  return view;
}

void setup_interfaz (int num_process)
{
  GtkWidget *view;
  GtkWidget *scrolled_window;
  GtkWidget *exit_bottom;
  GtkWidget *vbox;
  GtkWidget *hbox;

    update_progress_var.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (update_progress_var.window), "Project1 RTOS: The Scheduler");
    gtk_window_set_default_size (GTK_WINDOW (update_progress_var.window), 270, 300);
    gtk_container_set_border_width (GTK_CONTAINER (update_progress_var.window), 10);
    gtk_window_set_position(GTK_WINDOW(update_progress_var.window), GTK_WIN_POS_CENTER);
    g_signal_connect (update_progress_var.window, "delete_event", gtk_main_quit, NULL);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    update_progress_var.view = create_view_and_model (num_process);

    gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (scrolled_window),300);
    gtk_scrolled_window_set_min_content_width (GTK_SCROLLED_WINDOW (scrolled_window),350);

    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  gtk_container_add(GTK_CONTAINER(update_progress_var.window), vbox);

  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
  exit_bottom = gtk_button_new_with_label("Exit");
  g_signal_connect_swapped (exit_bottom, "clicked", G_CALLBACK (gtk_widget_destroy), update_progress_var.window);
  gtk_container_add(GTK_CONTAINER(hbox), exit_bottom);


  gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(update_progress_var.window), "destroy",G_CALLBACK(gtk_main_quit), G_OBJECT(update_progress_var.window));


    gtk_container_add (GTK_CONTAINER (scrolled_window), update_progress_var.view);

    gtk_widget_show_all (update_progress_var.window);

}
