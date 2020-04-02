#include "application.h"

application::application() : 
	Window("City Traffic Simulator and Planner | Mid Sweden University Thesis Project | Cristoffer Tanda", 1280, 720), 
	// TODO(Cristoffer): What should d3d buffer size be based on?
	Direct3D(Window.GetHandle(), 1280, 720),
	Timing(), 
	Running(true),
	TimeCheck(0.0)
{
}

application::~application()
{
}

void application::Run()
{
	Window.ShowMouseCursor(1);
	Window.ClipMouseCursor(0);

	while(Running)
	{
		Timing.StartFrameTimer();

		MSG Message;

		while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		if(KeyReleased(KEY_ESCAPE))
		{
			Running = FALSE;
		}



		real64 CurrentTime = Timing.GetWallclockSeconds();

		// NOTE(Cristoffer): Run program here!!
		if((CurrentTime - TimeCheck) > 1.0)
		{
			TimeCheck = CurrentTime;

			std::string StringValue = std::to_string(Timing.GetFramesPerSecond());

			std::wstring stemp = std::wstring(StringValue.begin(), StringValue.end());
			LPCWSTR sw = stemp.c_str();

			OutputDebugStringW(sw);
			OutputDebugStringW(L"\n");
		}

		Direct3D.EndFrame();


		Timing.EndFrameTimer();
	}
}