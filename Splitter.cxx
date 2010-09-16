#include <gtk/gtk.h>

#include "Splitter.h"
/*
void PageSwitched (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, gpointer user_data)
{
  CPageControl *pc=(CPageControl*)user_data;
  pc->OnPageSwitch(page_num);
  //g_print("Page switched to Page #%d\n",page_num);
}
*/
/*
void RowActivated (GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn  *col, gpointer user_data)
{
  CListView *lv=(CListView*)user_data;
  lv->OnRowActivated(path,col);
}
*/
CSplitter::CSplitter(GtkWidget *parent,bool vertical)
{
  if (vertical)
    Paned=gtk_vpaned_new(); 
  else
    Paned=gtk_hpaned_new ();
  
  //g_object_set(Paned,"min-position",10, NULL); //not writable
  //g_signal_connect(ListView, "row-activated", (GCallback) RowActivated, this);
  gtk_widget_show(Paned);
  if (GTK_IS_BOX(parent))
  {
    //g_print("box-parent (%x)\n",int(parent));
    gtk_box_pack_start(GTK_BOX(parent),Paned, TRUE, TRUE, 0);
  }else if (GTK_IS_CONTAINER(parent))
  {
    //g_print("container-parent (%x)\n",int(parent));
    gtk_container_add(GTK_CONTAINER(parent),Paned);
  }else g_print("unknown parent (Paned)");
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  g_object_set_data(G_OBJECT(Paned),"ClassPointer",this);
}

CSplitter::~CSplitter()
{
  if (GTK_IS_WIDGET(Paned)) //if control is not freed before (window destroyed)
    gtk_widget_destroy(Paned);
}

void CSplitter::SetClients(GtkWidget *Child1,GtkWidget *Child2)
{
  gtk_paned_add1(GTK_PANED(Paned),Child1);
  gtk_paned_add2(GTK_PANED(Paned),Child2);
}

const char* BoolToChar(bool b)
{
  if (b) return "true";else return "false";
}

void CSplitter::setPanedProperties(GtkWidget *child,bool resize,bool shrink)
{
  GValue gvalue_resize = {0};
  g_value_init(&gvalue_resize, G_TYPE_BOOLEAN);
  g_value_set_boolean(&gvalue_resize, resize);
  
  GValue gvalue_shrink = {0};
  g_value_init(&gvalue_shrink, G_TYPE_BOOLEAN);
  g_value_set_boolean(&gvalue_shrink, shrink);

  gtk_container_child_set_property(GTK_CONTAINER(Paned),child,"resize",&gvalue_resize);
  gtk_container_child_set_property(GTK_CONTAINER(Paned),child,"shrink",&gvalue_shrink);
}

void CSplitter::SetStaticChild(int c)
{
  GtkWidget *c1=gtk_paned_get_child1(GTK_PANED(Paned));
  GtkWidget *c2=gtk_paned_get_child2(GTK_PANED(Paned));

  switch (c)
  {
    case 0:
    {
      setPanedProperties(c1,true,true);
      setPanedProperties(c2,true,true);
    }; break;
    case 1:
    {
      setPanedProperties(c1,false,false);
      setPanedProperties(c2,true,true);
    }; break;
    case 2:
    {
      setPanedProperties(c1,true,true);
      setPanedProperties(c2,false,false);  
    }; break;
  }
}

void CSplitter::SetSplitterPosition(int p,bool SecondChild)
{
  if (!SecondChild)
    gtk_paned_set_position(GTK_PANED(Paned),p);
//  else
//    gtk_paned_set_position(Paned,Width-Splitterwidth-p);
}

//now the Events
/*
void CPageControl::OnPageSwitch(int page_num)
{
  g_print("Page switched to Page #%d\n",page_num);
}

*/
/*
void CListView::OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col)
{
  //GtkTreeModel *model; // => store
  GtkTreeIter   iter;
  //g_print ("A row has been double-clicked!\n");
  //model = gtk_tree_view_get_model(treeview);
  if (gtk_tree_model_get_iter(GTK_TREE_MODEL(store), &iter, path))
  {
     gchar *caption;
     gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &caption, -1);
     g_print ("Double-clicked row contains caption %s\n", caption);

     g_free(caption);
  }
}
*/
