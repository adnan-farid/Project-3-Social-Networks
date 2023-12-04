#include "MainFrame.h"
#include <wx/wx.h>

//Window contructor with title title and an arbitrary id wxID_ANY
MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	InitializeControls();
	EventHandlersBind();
}

//Define all controls
void MainFrame::InitializeControls()
{
	//Note: The following controls does not need to be manually deallocated as wxWidgets takes care of that
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 20)));

	//Initialize panel
	panel = new wxPanel(this);
	
	//Status bar to display time and distance
	wxStatusBar* statusBar = CreateStatusBar();
	statusBar->SetDoubleBuffered(true);

	//Set title text to be headlineFont and center allign it
	staticText = new wxStaticText(panel, wxID_ANY, "Project 3", wxPoint(0, 22), wxSize(800,-1), wxALIGN_CENTRE_HORIZONTAL);
	staticText->SetFont(headlineFont);

	//Create button to run BFS
	BFS_button = new wxButton(panel, wxID_ANY, "BFS", wxPoint(150, 500), wxSize(100, 35));

	//Create button to run Dijkstra
	Dij_button = new wxButton(panel, wxID_ANY, "Dijkstra", wxPoint(550, 500), wxSize(100, 35));

	//Create button to change data set
	Data_button = new wxButton(panel, wxID_ANY, "Change data", wxPoint(350, 500), wxSize(100, 35));

	//Text box to display the shortest path 
	textCtrl = new wxTextCtrl(panel, wxID_ANY, "Shortest Path - To be calculated", wxPoint(200, 145), wxSize(400, 200), wxTE_MULTILINE | wxTE_READONLY | wxTE_CENTER);
	textCtrl->SetFont(mainFont);

	wxArrayString choices;
	graph.readDataset("facebook_clean_data\\artist_edges.csv");
	for (int i = 1; i < graph.getGraphSize()+1; i++)
	{
		choices.Add(to_string(i));
	}

	wxArrayString data_choices;
	data_choices.Add("facebook_clean_data\\artist_edges.csv");
	data_choices.Add("facebook_clean_data\\athletes_edges.csv");
	data_choices.Add("facebook_clean_data\\company_edges.csv");
	data_choices.Add("facebook_clean_data\\government_edges.csv");
	data_choices.Add("facebook_clean_data\\new_sites_edges.csv");
	data_choices.Add("facebook_clean_data\\politician_edges.csv");
	data_choices.Add("facebook_clean_data\\public_figure_edges.csv");
	data_choices.Add("facebook_clean_data\\tvshow_edges.csv");

	//Drop down list for from node
	comboBoxFrom = new wxComboBox(panel, wxID_ANY, "Select Start Node", wxPoint(125, 450), wxSize(150, -1), choices);

	//Drop down list for to node
	comboBoxTo = new wxComboBox(panel, wxID_ANY, "Select End Node", wxPoint(525, 450), wxSize(150, -1), choices);

	//Drop down list for data list
	comboBoxData = new wxComboBox(panel, wxID_ANY, "Select Database", wxPoint(300, 450), wxSize(200, -1), data_choices);
	comboBoxData->SetValue("facebook_clean_data\\artist_edges.csv");
}

//Function to bind events 
void MainFrame::EventHandlersBind()
{
	BFS_button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClickBFS, this);

	Dij_button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClickDij, this);

	Data_button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClickData, this);

	comboBoxFrom->Bind(wxEVT_TEXT, &MainFrame::OnComboBoxText, this);
	comboBoxFrom->Bind(wxEVT_COMBOBOX, &MainFrame::OnComboBoxText, this);

	comboBoxTo->Bind(wxEVT_TEXT, &MainFrame::OnComboBoxText, this);
	comboBoxTo->Bind(wxEVT_COMBOBOX, &MainFrame::OnComboBoxText, this);

	comboBoxData->Bind(wxEVT_COMBOBOX, &MainFrame::OnComboBoxDataClick, this);
}

//Define event handler for button Dijkstra
void MainFrame::OnButtonClickDij(wxCommandEvent& evt)
{
	//Calculate time and path
	int to_node = wxAtoi(comboBoxTo->GetValue());
	int from_node = wxAtoi(comboBoxFrom->GetValue());
	double executionTime;
	auto result = graph.dijkstra(from_node, to_node, executionTime);
	wxString message = wxString::Format(wxT("Time: %lf, Distance: %d"), executionTime, result.first);
	string shortestPath = "";
	for (int i = 0; i < result.second.size(); i++) {
		if (i != result.second.size() - 1) {
			shortestPath.append(to_string(result.second.at(i)));
			shortestPath.append("->");
		}
		else
			shortestPath.append(to_string(result.second.at(i)));
	}
	wxString wxshortestPath(shortestPath);

	//Displaying the time, distance, and shortest path
	textCtrl->ChangeValue(wxshortestPath);
	wxLogStatus(message);
}

//Define event handler for button BFS
void MainFrame::OnButtonClickBFS(wxCommandEvent& evt)
{
	//Calculate time and path
	int to_node = wxAtoi(comboBoxTo->GetValue());
	int from_node = wxAtoi(comboBoxFrom->GetValue());
	double executionTime;
	auto result = graph.BFS(from_node, to_node, executionTime);
	wxString message = wxString::Format(wxT("Time: %lf, Distance: %d"), executionTime, result.first);
	string shortestPath = "";
	for (int i = 0; i < result.second.size(); i++) {
		if (i != result.second.size() - 1) {
			shortestPath.append(to_string(result.second.at(i)));
			shortestPath.append("->");
		}
		else
			shortestPath.append(to_string(result.second.at(i)));
	}
	wxString wxshortestPath(shortestPath);

	//Displaying the time, distance, and shortest path
	textCtrl->ChangeValue(wxshortestPath);
	wxLogStatus(message);
}

//Define event handler for changing database
void MainFrame::OnButtonClickData(wxCommandEvent& evt)
{
	graph.readDataset(std::string(comboBoxData->GetValue().mb_str()));

	comboBoxFrom->Clear();
	comboBoxTo->Clear();
	for (int i = 1; i < graph.getGraphSize() + 1; i++)
	{
		comboBoxFrom->Append(to_string(i));
		comboBoxTo->Append(to_string(i));
	}
}

//Define event handler for choosing option from dropdown
void MainFrame::OnComboClick(wxCommandEvent& evt)	
{
	wxLogStatus(wxString::Format(wxT("%i"), evt.GetString()));
}

//Define even handler for entering text in dropdown
void MainFrame::OnComboBoxText(wxCommandEvent& evt)
{
	wxLogStatus(evt.GetString());
}

//Define event handler for selecting dataset
void MainFrame::OnComboBoxDataClick(wxCommandEvent& evt)
{
	wxLogStatus(evt.GetString());
}
