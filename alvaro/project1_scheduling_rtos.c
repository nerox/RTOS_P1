#include "interfaz.h"
#include "Controller.h"



// void setup_interfaz (int num_process)
// {
//   GtkWidget *view;
//   GtkWidget *scrolled_window;
//
//   GtkWidget *okBtn;
//  GtkWidget *clsBtn;
//
//   GtkWidget *vbox;
//   GtkWidget *hbox;
//   GtkWidget *halign;
//   GtkWidget *valign;
//
//     update_progress_var.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_title (GTK_WINDOW (update_progress_var.window), "Project1 RTOS: The Scheduler");
//     gtk_window_set_default_size (GTK_WINDOW (update_progress_var.window), 270, 300);
//     gtk_container_set_border_width (GTK_CONTAINER (update_progress_var.window), 10);
//     gtk_window_set_position(GTK_WINDOW(update_progress_var.window), GTK_WIN_POS_CENTER);
//     g_signal_connect (update_progress_var.window, "delete_event", gtk_main_quit, NULL);
//     scrolled_window = gtk_scrolled_window_new (NULL, NULL);
//     update_progress_var.view = create_view_and_model (num_process);
//
//     gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (scrolled_window),300);
//     gtk_scrolled_window_set_min_content_width (GTK_SCROLLED_WINDOW (scrolled_window),350);
//
//     gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
//                                   GTK_POLICY_AUTOMATIC,
//                                   GTK_POLICY_AUTOMATIC);
//
//     vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
//
//   gtk_container_add(GTK_CONTAINER(update_progress_var.window), vbox);
//
//   hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
//
//
//   // GtkTreeModel *ListModel;
//   //
//   // ListModel = gtk_tree_view_get_model (GTK_TREE_VIEW(view));
//   clsBtn = gtk_button_new_with_label("Exit");
//   g_signal_connect_swapped (clsBtn, "clicked", G_CALLBACK (gtk_widget_destroy), update_progress_var.window);
//   gtk_container_add(GTK_CONTAINER(hbox), clsBtn);
//
//
//   gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, FALSE, FALSE, 0);
//   gtk_box_pack_end(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
//
//   g_signal_connect(G_OBJECT(update_progress_var.window), "destroy",G_CALLBACK(gtk_main_quit), G_OBJECT(update_progress_var.window));
//
//
//     gtk_container_add (GTK_CONTAINER (scrolled_window), update_progress_var.view);
//
//     gtk_widget_show_all (update_progress_var.window);
//
// }


int
main (int argc, char **argv)
{
  start_Structures();
 //  GtkWidget *window;
 //  GtkWidget *view;
 //  GtkWidget *scrolled_window;
 //
 //  GtkWidget *okBtn;
 // GtkWidget *clsBtn;
 //
 //  GtkWidget *vbox;
 //  GtkWidget *hbox;
 //  GtkWidget *halign;
 //  GtkWidget *valign;

  int num_process = PROCESSES_AVAILABLE;

  gtk_init (&argc, &argv);
  setup_interfaz(num_process);

  //   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  //   gtk_window_set_title (GTK_WINDOW (window), "Project1 RTOS: The Scheduler");
  //   gtk_window_set_default_size (GTK_WINDOW (window), 270, 300);
  //   gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  //   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  //   g_signal_connect (window, "delete_event", gtk_main_quit, NULL);
  //   scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  //   view = create_view_and_model (num_process);
  //
  //   gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (scrolled_window),300);
  //   gtk_scrolled_window_set_min_content_width (GTK_SCROLLED_WINDOW (scrolled_window),350);
  //
  //   gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
  //                                 GTK_POLICY_AUTOMATIC,
  //                                 GTK_POLICY_AUTOMATIC);
  //
  //   vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  //
  // gtk_container_add(GTK_CONTAINER(window), vbox);
  //
  // hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);


  GtkTreeModel *ListModel;

  ListModel = gtk_tree_view_get_model (GTK_TREE_VIEW(update_progress_var.view));
  // clsBtn = gtk_button_new_with_label("Exit");
  // g_signal_connect_swapped (clsBtn, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  // gtk_container_add(GTK_CONTAINER(hbox), clsBtn);
  //
  //
  // gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, FALSE, FALSE, 0);
  // gtk_box_pack_end(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
  //
  // g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), G_OBJECT(window));
  //
  //
  //   gtk_container_add (GTK_CONTAINER (scrolled_window), view);
  //
  //   gtk_widget_show_all (window);

  g_timeout_add (10, update_model, ListModel);
  g_thread_new ("scheduler", (GThreadFunc) scheduler_thread, (gpointer)update_progress_var.window);


  gtk_main ();


  return 0;
}
