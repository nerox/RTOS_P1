#include "interfaz.h"
#include "Controller.h"


int
main (int argc, char **argv)
{
  start_Structures();
  GtkWidget *window;
  GtkWidget *view;
  GtkWidget *scrolled_window;

  GtkWidget *okBtn;
 GtkWidget *clsBtn;

  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *halign;
  GtkWidget *valign;

  int num_process = PROCESSES_AVAILABLE;

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


  //update_progress_var.PI_value = result;
  g_timeout_add (1, update_model, ListModel);
 // g_thread_new ("thread", (GThreadFunc) arcsin_thread, (gpointer)window);
  g_thread_new ("scheduler", (GThreadFunc) scheduler_thread, (gpointer)window);


  gtk_main ();


  return 0;
}
