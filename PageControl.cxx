#include <gtk/gtk.h>

#include "PageControl.h"

void PageSwitched (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, gpointer user_data)
{
  CPageControl *pc=(CPageControl*)user_data;
  pc->OnPageSwitch(page_num);
}

CPageControl::CPageControl(GtkWidget *parent)
{
  GtkWidget *PageControl=gtk_notebook_new();
  gtk_notebook_set_scrollable (GTK_NOTEBOOK(PageControl),true);
  g_signal_connect (PageControl, "switch-page",G_CALLBACK (PageSwitched), this);
  SetWidget(PageControl);
  SetParent(parent);
}

CPageControl::~CPageControl()
{
}

GtkWidget *CPageControl::AddPage(const char *caption,int position)
{
	GtkWidget *label=gtk_accel_label_new(caption);
  GtkWidget *vbox=gtk_vbox_new(2,false);
	gtk_widget_show(vbox);
	
	gtk_notebook_insert_page(GTK_NOTEBOOK(GetWidget()),vbox,label,position);
//	g_print("Page-Widget: %x\n",int(vbox));
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

