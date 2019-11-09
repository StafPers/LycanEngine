#include <Lycan.h>

class Sandbox : public Lycan::Application
{
public:

	Sandbox( void )
	{

	}

	~Sandbox( void )
	{

	}
};

Lycan::Application* Lycan::CreateApplication( void )
{
	return new Sandbox();
}