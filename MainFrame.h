#pragma once
#include <wx/wx.h>
#include "graph.cpp"

//Define class to represent the window
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void InitializeControls();
	void EventHandlersBind();

	void OnButtonClickDij(wxCommandEvent& evt);
	void OnButtonClickBFS(wxCommandEvent& evt);
	void OnButtonClickData(wxCommandEvent& evt);
	void OnComboClick(wxCommandEvent& evt);
	void OnComboBoxText(wxCommandEvent& evt);
	void OnComboBoxDataClick(wxCommandEvent& evt);
	
	Graph graph;
	wxPanel* panel;
	wxStatusBar* statusBar;
	wxButton* BFS_button;
	wxButton* Dij_button;
	wxButton* Data_button;
	wxStaticText* staticText;
	wxTextCtrl* textCtrl;
	wxComboBox* comboBoxFrom;
	wxComboBox* comboBoxTo;
	wxComboBox* comboBoxData;

};

