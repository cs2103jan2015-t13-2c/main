//@author A0114084N
#include "TaskkyGUI.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThread]

void main(array<String^>^ args){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TaskkyUI::TaskkyGUI mainWindow;
	Application::Run(%mainWindow);
}