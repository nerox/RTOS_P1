
#include <gtk/gtk.h>
#include <math.h>
#include <unistd.h>


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

};
 //double PI_value;
 //float progress;

 struct update_progress update_progress_var;

static gboolean update_model (gpointer user_data)
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

    for (uint i = 1; i <= terminos; i++) {
      ans += (4*pow(-1,i))/(2*i+1);
      percentage = 100*((double)i/(double)terminos);
    //  printf("i = %d, porcentaje: %lf, PI = %lf\n",i, percentage, ans );
    }
    return ans;
}

gpointer arcsin_thread(gpointer user_data) {
    // double ans = 4;
    // float percentage;
    update_progress_var.path = "9";
    update_progress_var.status = "Active";//g_string_new (test);
    update_progress_var.PI_value = 4.0;
    uint terminos = update_progress_var.terminos;
    printf("%0.3f\n",update_progress_var.PI_value );

    for (uint i = 1; i <= terminos; i++) {
      update_progress_var.PI_value += (4*pow(-1,i))/(2*i+1);
      update_progress_var.progress = 100*((double)i/(double)terminos);
      printf("i = %d, porcentaje: %lf, PI = %lf\n",i, update_progress_var.progress, update_progress_var.PI_value);
    }
    return NULL;
}

static void
print_hello (GtkWidget *widget,
             gpointer   user_data)
{
  // GtkListStore *store = (GtkListStore*) user_data;
  // GtkTreeIter iter;
  // GtkTreePath *path;
  // path = gtk_tree_path_new_from_string ("4");
  //      gtk_tree_model_get_iter (GTK_TREE_MODEL (user_data),
  //                               &iter,
  //                               path);
  //      gtk_tree_path_free (path);
  // //gtk_tree_model_get_iter_first (GTK_TREE_MODEL (user_data), &iter);
  // gtk_list_store_set (store, &iter,
  //             COL_PROGRESS, 50.0,
  //             COL_PROCESS_ACTIVE, "Active",
  //             COL_PI_VALUE, 3.145926,
  //             -1);
  //struct update_progress *update_progress_var;
  double ans = 4;
  double percentage;
  uint terminos = 500000;
  gchar process_id = '1';
  //update_progress_var->user_data = user_data;

  for (uint i = 1; i <= terminos; i++) {
    ans += (4*pow(-1,i))/(2*i+1);
    percentage = 100*((double)i/(double)terminos);
    printf("i = %d, porcentaje: %lf, PI = %lf\n",i, percentage, ans );
    // update_progress_var->progress = percentage;
    // update_progress_var->PI_value = ans;
    //sleep(1);
    //update_model (user_data, ans, percentage);
    //g_thread_new ("",(GThreadFunc)update_model, (gpointer)update_progress_var);
  }
  //update_model (user_data);
}




static GtkTreeModel *
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

static GtkWidget *
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



int
main (int argc, char **argv)
{
  GtkWidget *window;
  GtkWidget *view;
  GtkWidget *scrolled_window;

  GtkWidget *okBtn;
 GtkWidget *clsBtn;

  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *halign;
  GtkWidget *valign;

  int num_process = 50;

  gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Project1 RTOS: The Scheduler");
    gtk_window_set_default_size (GTK_WINDOW (window), 270, 300);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect (window, "delete_event", gtk_main_quit, NULL); /* dirty */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    //gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 100);
    view = create_view_and_model (num_process);

    gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (scrolled_window),300);
    gtk_scrolled_window_set_min_content_width (GTK_SCROLLED_WINDOW (scrolled_window),350);

    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);

    //g_signal_connect (view,"changed",)

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  // valign = gtk_alignment_new(0, 1, 0, 0);
  // gtk_container_add(GTK_CONTAINER(vbox), valign);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);


  GtkTreeModel *ListModel;
  //GtkListStore *store;

  ListModel = gtk_tree_view_get_model (GTK_TREE_VIEW(view));

  // okBtn = gtk_button_new_with_label("Start");
  // gtk_widget_set_size_request(okBtn, 70, 30);
  // gtk_container_add(GTK_CONTAINER(hbox), okBtn);
  // g_signal_connect (okBtn, "clicked", G_CALLBACK (print_hello), ListModel);
  clsBtn = gtk_button_new_with_label("Exit");
  g_signal_connect_swapped (clsBtn, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add(GTK_CONTAINER(hbox), clsBtn);

  //halign = gtk_alignment_new(1, 0, 0, 0);
  //gtk_container_add(GTK_CONTAINER(halign), hbox);


  gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), G_OBJECT(window));


    gtk_container_add (GTK_CONTAINER (scrolled_window), view);

  //  gtk_container_add (GTK_CONTAINER (window), scrolled_window);

    gtk_widget_show_all (window);




//printf("%0.6f\n", update_progress_var.PI_value);

unsigned int n = 100;
update_progress_var.terminos = 1000000000;
float result = 0;


  result = arcsin(n);

  printf("terminos = %u, aproximacion = %lf\n", n, result );
  //update_progress_var.PI_value = result;
  g_thread_new ("thread", (GThreadFunc) arcsin_thread, NULL);
  g_timeout_add (1, update_model, ListModel);

  gtk_main ();


  return 0;
}
