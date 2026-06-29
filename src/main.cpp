#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/socket.h>
#include <sstream>

class Wordweb : public wxApp
{
	class GUI_Panel : public wxPanel
	{
		wxSocketClient* client{new wxSocketClient};

		void process_input_box(wxCommandEvent& event);

		public:
			GUI_Panel(wxWindow* parent);
	};

	class GUI_Frame : public wxFrame
	{
		public:
			GUI_Frame();
	};

	public:
		bool OnInit() override;
};

wxIMPLEMENT_APP(Wordweb);

bool Wordweb::OnInit()
{
	GUI_Frame* frame {new GUI_Frame};

	frame->Show();

	return true;
}

Wordweb::GUI_Frame::GUI_Frame() : wxFrame(nullptr, wxID_ANY, "Wordweb") // The actual wxwidgets window
{
	wxNotebook* notebook {new wxNotebook{this, wxID_ANY}};

	GUI_Panel* default_panel {new GUI_Panel{notebook}};

	notebook->AddPage(default_panel, "None");
}

Wordweb::GUI_Panel::GUI_Panel(wxWindow* parent) : wxPanel(parent, wxID_ANY) // The window containing chat/input/name list. It also contains the socket, and other information that is connected to the chat server.
{
	wxBoxSizer* sizer {new wxBoxSizer{wxHORIZONTAL}};

	wxTextCtrl* input_win{new wxTextCtrl{this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP | wxTE_MULTILINE | wxTE_PROCESS_ENTER}};
	wxTextCtrl* chat_win{new wxTextCtrl{this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP | wxTE_MULTILINE | wxTE_READONLY}};
	wxListBox* name_win{new wxListBox{this, wxID_ANY}};

	sizer->Add(input_win, 2, wxEXPAND);
	sizer->Add(chat_win, 5, wxEXPAND);
	sizer->Add(name_win, 1, wxEXPAND);

	input_win->Bind(wxEVT_TEXT_ENTER, &Wordweb::GUI_Panel::process_input_box, this);

	SetSizerAndFit(sizer);
}

void Wordweb::GUI_Panel::process_input_box(wxCommandEvent& event)
{
	wxTextCtrl* input_box{reinterpret_cast<wxTextCtrl*>(event.GetEventObject())};

	std::stringstream input_box_string_stream{input_box->GetValue().ToStdString()};
	std::vector<std::string> input_tokens{};

	do
	{
		std::string temp{};
		std::getline(input_box_string_stream, temp, ' ');
		input_tokens.push_back(temp);
	} while(!input_box_string_stream.eof() && !input_box_string_stream.fail());

	if(input_tokens[0][0] == '/') // A command (/join, /msg, etc)
	{

	}

	else // Treat as message
	{

	}
	
	input_box->SetValue("");
}
