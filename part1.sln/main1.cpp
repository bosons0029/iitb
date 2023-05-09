#include <wx/wx.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/animate.h>
#include <wx/math.h>
#include <wx/gdicmn.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class VideoCaptureApp:public wxApp {
	public:
                //This variable is manipluated 
                //when stopping a video capture stream
		bool running;
                //these variables are used to store
                //brightness and contrast levels on the
                //fly
		double brightness;
		double contrast;
                wxSlider* brightness_slider;
                wxSlider* contrast_slider;
		bool OnInit();
		void drawFrame();
		void OnStart(wxCommandEvent& event);
		void OnStop(wxCommandEvent& event);
		void brightness_changed(wxScrollEvent& event);
		void contrast_changed(wxScrollEvent& event);
};

wxIMPLEMENT_APP(VideoCaptureApp);

//Event binding when brightness slider is changed
void VideoCaptureApp::brightness_changed(wxScrollEvent& event) {
      this->brightness = this->brightness_slider->GetValue();
}

//Event binding when contrast slider is changed
void VideoCaptureApp::contrast_changed(wxScrollEvent& event) {
      this->contrast = this->contrast_slider->GetValue();
}

//Event binding when stop button is pressed
void VideoCaptureApp::OnStop(wxCommandEvent& event) {
	this->running = false;
	destroyWindow("Video Stream");
}

//Event binding when start button is pressed
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
	this->running = true;
        Mat stream1;
        Mat stream2;
        //Loop to render multiple video frames
        //giving a feel of streaming
        //while also manipulating
        //the brightness and contrast
        //until killed by the stop button
	while (this->running) {
		win1 >> stream;
		if (stream.empty()) {
			break;
		}
                stream.convertTo(stream1, -1, 1, this->brightness);
                stream1.convertTo(stream2, -1, this->contrast/100.0, 0);
		imshow("Video Stream", stream2);
		char c = (char)waitKey(35);
		if (c == 27) { //Esc
			break;
		}
	}
	win1.release();
	return;
}

bool VideoCaptureApp::OnInit() {
        //The frontend or UI aspects of the Application
        //implemented in wxWidgets - Cross Platform
	wxSize window_size(350, 600);
	wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Video Capture App", wxDefaultPosition, window_size, wxDEFAULT_FRAME_STYLE, "Video Capture App");
	frame->Show(true);
	VideoCapture win1(0);
	int deviceID = 0;
	int apiID = cv::CAP_ANY;
	win1.open(deviceID, apiID);
	if (!win1.isOpened()) {
		cout << "No video stream detected\n";
		wxPoint* pos = new wxPoint(15, 55);
		wxStaticText* input_source_label = new wxStaticText(frame, wxID_ANY, "No Video Stream Detected", *pos, wxDefaultSize, 0, "No Video Stream Detected"); 
	} else {
		wxPoint* pos = new wxPoint(15, 55);
		wxStaticText* input_source_label = new wxStaticText(frame, wxID_ANY, "Select Video Source", *pos, wxDefaultSize, 0, "Select Video Source"); 
		wxArrayString str;
		str.Add("Default Camera");
		delete pos;
		pos = new wxPoint(15,80);
		wxChoice* video_input_source = new wxChoice(frame, wxID_ANY, *pos, wxSize(300, 25), 0, new wxString("Default Camera"), 0, wxDefaultValidator, wxString("Select Video Source"));
		video_input_source->Set(str);
		delete pos;
		pos = new wxPoint(15,105);
		wxSize size(90, 25);
		wxButton* start_button = new wxButton(frame, wxID_ANY, "Start", *pos, size, 0, wxDefaultValidator, "Start");
		start_button->Bind(wxEVT_BUTTON, &VideoCaptureApp::OnStart, this);
		delete pos;
		pos = new wxPoint(165, 105);
		wxButton* stop_button = new wxButton(frame, wxID_ANY, "Stop", *pos, size, 0, wxDefaultValidator, "Stop");
		stop_button->Bind(wxEVT_BUTTON, &VideoCaptureApp::OnStop, this);
		delete pos;
		pos = new wxPoint(15, 185);
		wxStaticText* brightness_label = new wxStaticText(frame, wxID_ANY, "Brightness", *pos, wxDefaultSize, 0, "Brightness"); 
		delete pos;
		pos = new wxPoint(15, 215);
		wxSlider* brightness_slider = new wxSlider(frame, wxID_ANY, 50, 0, 100, *pos, wxSize(300, 20), wxSL_HORIZONTAL, wxDefaultValidator, "Brightness");
                this->brightness_slider = brightness_slider;
                brightness_slider->Bind(wxEVT_SCROLL_THUMBRELEASE, &VideoCaptureApp::brightness_changed, this);
		this->brightness = brightness_slider->GetValue();
		delete pos;
		pos = new wxPoint(15, 355);
		wxStaticText* contrast_label = new wxStaticText(frame, wxID_ANY, "Contrast", *pos, wxDefaultSize, 0, "Contrast"); 
		delete pos;
		pos = new wxPoint(15,385);
		wxSlider* contrast_slider = new wxSlider(frame, wxID_ANY, 50, 0, 100, *pos, wxSize(300, 20), wxSL_HORIZONTAL, wxDefaultValidator, "Contrast");
                contrast_slider->Bind(wxEVT_SCROLL_THUMBRELEASE, &VideoCaptureApp::contrast_changed, this);
		this->contrast = contrast_slider->GetValue();
                this->contrast_slider = contrast_slider;
		delete pos;
	}
	return true;
}
