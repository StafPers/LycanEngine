#pragma once

#include "Core.h"

namespace Lycan
{
	class LYCAN_API Application
	{
	public:

		Application          ( void );
		virtual ~Application ( void );

		void Run             ( void );
	};

	Application* CreateApplication( void );

}