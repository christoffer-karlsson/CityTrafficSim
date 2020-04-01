#include "application.h"

application::application() : 
	Window(L"City Traffic Simulator and Planner | Mid Sweden University Thesis Project | Cristoffer Tanda", 1280, 720), 
	//Graphics(Window.GetHandle(), 1280, 720),
	//Timing(), 
	Running(true)
{
}

application::~application()
{
}

void application::Run()
{
	bool BlockWorldInput = 0;

	Window.ShowMouseCursor(1);
	Window.ClipMouseCursor(0);

	while(Running)
	{
		MSG Message;

		while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		// NOTE(Cristoffer): Run program here!!
	}
}