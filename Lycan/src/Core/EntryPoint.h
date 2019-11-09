#pragma once

#ifdef LC_PLATFORM_WINDOWS

extern Lycan::Application* Lycan::CreateApplication();

int main( int argc, char** argv )
{
	auto app = Lycan::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif