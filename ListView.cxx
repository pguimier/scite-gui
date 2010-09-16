#include <gtk/gtk.h>

#include "ListView.h"
/*
void PageSwitched (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, gpointer user_data)
{
  CPageControl *pc=(CPageControl*)user_data;
  pc->OnPageSwitch(page_num);
  //g_print("Page switched to Page #%d\n",page_num);
}
*/

void RowActivated (GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn  *col, gpointer user_data)
{
  /*
  GtkTreeModel *model;
  GtkTreeIter   iter;

  //g_print ("A row has been double-clicked!\n");

  model = gtk_tree_view_get_model(treeview);

  if (gtk_tree_model_get_iter(model, &iter, path))
  {
     gchar *name;

     gtk_tree_model_get(model, &iter, COL_NAME, &name, -1);

     g_print ("Double-clicked row contains name %s\n", name);

     g_free(name);
  }*/
  CListView *lv=(CListView*)user_data;
  lv->OnRowActivated(path,col);
}

CListView::CListView(GtkWidget *parent,int cols)
{
  fColCount=0;
  ListView = gtk_tree_view_new ();
  //store = gtk_list_store_new (cols, G_TYPE_STRING, G_TYPE_STRING);
  store = gtk_list_store_new (10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
  gtk_tree_view_set_model (GTK_TREE_VIEW (ListView), GTK_TREE_MODEL(store));
  /* The tree view has acquired its own reference to the
   *  model, so we can drop ours. That way the model will
   *  be freed automatically when the tree view is destroyed */
  g_object_unref (store);
  /*
  //add columns
  GtkCellRenderer     *renderer;
  for (int i=0;i<cols;i++)
  {
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (ListView),
                                                 -1,      
                                                 "Text",  
                                                 renderer,
                                                 "text", i,
                                                 NULL);
  }
  */
  g_signal_connect(ListView, "row-activated", (GCallback) RowActivated, this);
  
  gtk_widget_show(ListView);
  if (GTK_IS_BOX(parent))
  {
    //g_print("box-parent (%x)\n",int(parent));
    gtk_box_pack_start(GTK_BOX(parent),ListView, TRUE, TRUE, 0);
  }else if (GTK_IS_CONTAINER(parent))
  {
    //g_print("container-parent (%x)\n",int(parent));
    gtk_container_add(GTK_CONTAINER(parent),ListView);
  }else g_print("unknown parent (Listview)");
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  g_object_set_data(G_OBJECT(ListView),"ClassPointer",this);
}

CListView::~CListView()
{
  if (GTK_IS_WIDGET(ListView)) //if control is not freed before (window destroyed)
    gtk_widget_destroy(ListView);
}

bool CListView::SetValue(int row,int col,const char *value)
{
  GtkTreeIter iter;
  //store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
  
  if (gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(store), &iter, NULL, row))
  {
    gtk_list_store_set (store, &iter, col, value, -1);
    return true;
  }
  return false;
}

GtkTreeIter CListView::AddItem(const char *caption)
{
  g_print("Add Item (%s)",caption);
  GtkTreeIter iter;
  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter,0, caption,-1);
  return iter;
}

int CListView::AddColumn(const char *caption)
{
  GtkCellRenderer *renderer;
  renderer = gtk_cell_renderer_text_new ();
  fColCount=gtk_tree_view_insert_column_with_attributes (
    GTK_TREE_VIEW (ListView),
    -1,      
    caption,
    renderer,
    "text", fColCount,
    NULL);
  gtk_tree_view_column_set_resizable  (gtk_tree_view_get_column(GTK_TREE_VIEW (ListView),fColCount-1),true);
}

/*
int getsingleselect ( GtkTreeView * tv )
   {
   GtkTreeSelection * tsel = gtk_tree_view_get_selection (tv);
   GtkTreeIter iter ;
   GtkTreeModel * tm ;
   GtkTreePath * path ;
   int * i ;
   if ( gtk_tree_selection_get_selected ( tsel , &tm , &iter ) )
      {
      path = gtk_tree_model_get_path ( tm , &iter ) ;
      i = gtk_tree_path_get_indices ( path ) ;
      return i [ 0 ] ;
      }
   return -1;
   }
   
gint
ghb_selected_subtitle_row(signal_user_data_t *ud)
{
        GtkTreeView *treeview;
        GtkTreePath *treepath;
        GtkTreeSelection *selection;
        GtkTreeModel *store;
        GtkTreeIter iter;
        gint *indices;
        gint row = -1;
       
        g_debug("ghb_selected_subtitle_row ()");
        treeview = GTK_TREE_VIEW(GHB_WIDGET(ud->builder, "subtitle_list"));
        selection = gtk_tree_view_get_selection (treeview);
        if (gtk_tree_selection_get_selected(selection, &store, &iter))
        {
                // Get the row number
                treepath = gtk_tree_model_get_path (store, &iter);
                indices = gtk_tree_path_get_indices (treepath);
                row = indices[0];
                gtk_tree_path_free(treepath);
        }
        return row;
}
*/
/*
GtkWidget *CPageControl::AddPage(const char *caption,int position)
{
  g_print("Adding Page (CPageControl)\n");
	GtkWidget *label=gtk_accel_label_new(caption);
  GtkWidget *vbox=gtk_vbox_new(2,false);
	gtk_widget_show(vbox);
	g_print("now inserting (%x)\n",int(PageControl));
	
	gtk_notebook_insert_page(GTK_NOTEBOOK(PageControl),vbox,label,position);
	g_print("inserted\n");
  return vbox;
}

void CPageControl::RemovePage(int page_num)
{
  gtk_notebook_remove_page(GTK_NOTEBOOK(PageControl),page_num);
}

GtkWidget *CPageControl::GetPage(int page_num)
{
  return gtk_notebook_get_nth_page(GTK_NOTEBOOK(PageControl),page_num);
}

int CPageControl::GetPageCount()
{
  return gtk_notebook_get_n_pages(GTK_NOTEBOOK(PageControl));
}

*/
//now the Events
/*
void CPageControl::OnPageSwitch(int page_num)
{
  g_print("Page switched to Page #%d\n",page_num);
}

*/

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
