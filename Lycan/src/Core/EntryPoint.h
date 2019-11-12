#pragma once

#include "Clock.h"

#ifdef LC_PLATFORM_WINDOWS

extern Lycan::Application* Lycan::CreateApplication();

int main( int argc, char** argv )
{
	auto app = Lycan::CreateApplication();
	app->Initialize();
	
	while( true )
	{
		Lycan::Core::Clock::Instance().Update();
		app->Update();
		app->Render();
	}

	delete app;

	return 0;
}

#endif