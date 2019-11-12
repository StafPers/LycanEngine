#pragma once

#include "Core.h"

namespace Lycan
{
	class Application
	{
	public:

		Application             ( void ) {}
		virtual ~Application    ( void ) {}

		virtual void Initialize ( void ) = 0;
		virtual void Update     ( void ) = 0;
		virtual void Render     ( void ) = 0;
	};

	extern Application* CreateApplication( void );
}