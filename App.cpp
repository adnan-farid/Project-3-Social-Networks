#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

//Specify which class represents app for wxWidgets
wxIMPLEMENT_APP(App);

//Create an instance of the window mainFrame
bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("Project 3 - Social Networks");
	
	//Center mainFrame and resize
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();

	//Display the window
	mainFrame->Show();

    return true;
}
