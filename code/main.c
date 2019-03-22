#include "graphics.h"
#include "all.h"

int main(int argc, char *argv[])
{
  //Constants
  FONT_SIZE = 12;
  LOOP_WAIT = 50;
  WINDOW_SIZE = 1600;
  CIRCLE_HEIGHT = 15;
  LINE_WIDTH = 3;
  BRANCH_WIDTH = 7;
  FONT = "Purisa";
  HEIGHT_CONSTANT = 6.0;
  TEXT_DISTANCE = 0.5;

  MODE = 2;
  MAX_VTIME = 0;
  MEAN_ALLOT = 0.3;
  STD_ALLOT = 0.3;

  MEAN_RUNTIME = 5.0;
  STD_RUNTIME = 1.5;
  //Start variables
  read_file();
  GtkWidget *window;
  GtkWidget *darea;
  RED[0] = 0.69;
  RED[1] = 0.19;
  RED[2] = 0.0;
  BLACK[0] = BLACK[1] = BLACK[2] = 0.0;
  WHITE[0] = WHITE[1] = WHITE[2] = 1.0;
  ROOT = build_tree();
  glob.count = 0;

  //Set up gtk
  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);
  g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_SIZE, WINDOW_SIZE);
  gtk_window_set_title(GTK_WINDOW(window), "RB Tree Demonstration");
  g_timeout_add(LOOP_WAIT, (GSourceFunc) time_handler, (gpointer) window);
  gtk_widget_show_all(window);


  //Helpful stuff for timing
  srand(time(0));
  time_t end, start;
  time_t seconds = 10; // end loop after this time has elapsed
  struct timespec tim;
  tim.tv_sec = 0;
  tim.tv_nsec = 100000000L;
  end = start + seconds;
  printf("processing activated at %s", ctime(&start));


  //Helpful stuff for red black trees
  NUM_OF_TASKS = 0;
  struct node *root = NULL;
  // struct node *min = NULL;
  struct node* n;
  int starting_tasks = 60;
  GENERATE_NEW_TASKS = 0;


  //-----------Generate tasks------------
  for(int i = 0; i < starting_tasks; i++){
    n = generate_task(NUM_OF_TASKS, 0);
    if(MODE == 1){
      n->priority = PRIORITIES[i];
      set_task_color_1(n);
    }
    insert(&root, &MIN, n);
    NUM_OF_TASKS++;
  }

  //Reassign to global pointer
  ROOT = root;

  //Start the "real work" in graphics.c
  gtk_main();

  printf("end time is %s", ctime(&end));

  return 0;
}
