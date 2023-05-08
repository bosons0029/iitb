#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <wx/wx.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/animate.h>
#include <wx/math.h>
#include <wx/gdicmn.h>
using namespace std;
using namespace cv;

class VideoCaptureApp:public wxApp {
    public:
        bool OnInit();
        void OnStart(wxCommandEvent& event);
//        wxDECLARE_EVENT_TABLE();
};

wxIMPLEMENT_APP(VideoCaptureApp);

void VideoCaptureApp::OnStart(wxCommandEvent& event) {
    //Video Capture begins
    Mat stream;
    namedWindow("Video Stream");
    VideoCapture win1(0);
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    win1.open(deviceID, apiID);
    if (!win1.isOpened()) {
         cout << "No video stream detected\n";
         system("pause");
         return;
    }
    while (1) {
         win1 >> stream;
         if (stream.empty()) {
              break;
         }
         imshow("Video Stream", stream);
         char c = (char)waitKey(35);
         if (c == 27) { //Esc
              break;
         }
     }
     win1.release();
     return;
}

bool VideoCaptureApp::OnInit() {
    wxSize window_size(900, 600);
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Video Capture App", wxDefaultPosition, window_size, wxDEFAULT_FRAME_STYLE, "Video Capture App");
    frame->Show(true);
    wxPoint* pos = new wxPoint(15, 55);
    wxStaticText* input_source_label = new wxStaticText(frame, wxID_ANY, "Select Video Source", *pos, wxDefaultSize, 0, "Select Video Source"); 
    delete pos;
    pos = new wxPoint(15,80);
    wxChoice* video_input_source = new wxChoice(frame, wxID_ANY, *pos, wxSize(300, 25), 0, NULL, 0, wxDefaultValidator, "Select Video Source");
    delete pos;
    pos = new wxPoint(15,105);
    wxSize size(90, 25);
    wxButton* start_button = new wxButton(frame, wxID_ANY, "Start", *pos, size, 0, wxDefaultValidator, "Start");
    start_button->Bind(wxEVT_BUTTON, &VideoCaptureApp::OnStart, this);
    delete pos;
    pos = new wxPoint(165, 105);
    wxButton* stop_button = new wxButton(frame, wxID_ANY, "Stop", *pos, size, 0, wxDefaultValidator, "Stop");
    delete pos;
    pos = new wxPoint(15, 185);
    wxStaticText* brightness_label = new wxStaticText(frame, wxID_ANY, "Brightness", *pos, wxDefaultSize, 0, "Brightness"); 
    delete pos;
    pos = new wxPoint(15, 205);
    wxSlider* brightness_slider = new wxSlider(frame, wxID_ANY, 0, 0, 50, *pos, wxSize(300, 10), wxSL_HORIZONTAL, wxDefaultValidator, "Brightness");
    delete pos;
    pos = new wxPoint(15, 355);
    wxStaticText* contrast_label = new wxStaticText(frame, wxID_ANY, "Contrast", *pos, wxDefaultSize, 0, "Contrast"); 
    delete pos;
    pos = new wxPoint(15,375);
    wxSlider* contrast_slider = new wxSlider(frame, wxID_ANY, 0, 0, 50, *pos, wxSize(300, 10), wxSL_HORIZONTAL, wxDefaultValidator, "Contrast");
    delete pos;
    size = wxSize(500, 500);
    pos = new wxPoint(350,55);
    wxAnimationCtrl* video_stream = new wxAnimationCtrl(frame, wxID_ANY, wxNullAnimation, *pos, size, wxAC_DEFAULT_STYLE, "Video Stream");
     return true;
}

