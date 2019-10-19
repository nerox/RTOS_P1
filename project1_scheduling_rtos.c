#include "interfaz.h"
#include "Controller.h"


int main (int argc, char **argv)
{
  GtkTreeModel *ListModel;


  gtk_init (&argc, &argv);
  start_Structures();
  int num_process = PROCESSES_AVAILABLE;

  setup_interfaz(num_process);

  ListModel = gtk_tree_view_get_model (GTK_TREE_VIEW(update_progress_var.view));
  

  g_timeout_add (100, update_model, ListModel);
  g_thread_new ("scheduler", (GThreadFunc) scheduler_thread, (gpointer)update_progress_var.window);


  gtk_main ();


  return 0;
}
