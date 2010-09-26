#include <gtk/gtk.h>

#include "PageControl.h"

void PageSwitched (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, gpointer user_data)
{
  CPageControl *pc=(CPageControl*)user_data;
  pc->OnPageSwitch(page_num);
  //g_print("Page switched to Page #%d\n",page_num);
}

CPageControl::CPageControl(GtkWidget *parent)
{
  GtkWidget *PageControl=gtk_notebook_new();
  gtk_notebook_set_scrollable (GTK_NOTEBOOK(PageControl),true);
  //gtk_widget_show(PageControl);
  g_signal_connect (PageControl, "switch-page",G_CALLBACK (PageSwitched), this);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(PageControl),"ClassPointer",this);
  
  //GtkWidget *page=AddPage("Test",-1);
  
  //g_print("Pages: %d\n",gtk_notebook_get_n_pages(GTK_NOTEBOOK(PageControl)));
  SetWidget(PageControl);
  SetParent(parent);
}

CPageControl::~CPageControl()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}

GtkWidget *CPageControl::AddPage(const char *caption,int position)
{
  //g_print("Adding Page (CPageControl)\n");
	GtkWidget *label=gtk_accel_label_new(caption);
  GtkWidget *vbox=gtk_vbox_new(2,false);
	gtk_widget_show(vbox);
	//g_print("now inserting (%x)\n",int(PageControl));
	
	gtk_notebook_insert_page(GTK_NOTEBOOK(GetWidget()),vbox,label,position);
	g_print("Page-Widget: %x\n",int(vbox));
  return vbox;
}

void CPageControl::RemovePage(int page_num)
{
  gtk_notebook_remove_page(GTK_NOTEBOOK(GetWidget()),page_num);
}

GtkWidget *CPageControl::GetPage(int page_num)
{
  return gtk_notebook_get_nth_page(GTK_NOTEBOOK(GetWidget()),page_num);
}

int CPageControl::GetPageCount()
{
  return gtk_notebook_get_n_pages(GTK_NOTEBOOK(GetWidget()));
}


//now the Events

void CPageControl::OnPageSwitch(int page_num)
{
  g_print("Page switched to Page #%d\n",page_num);
}

