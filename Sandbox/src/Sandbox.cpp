#include <Core/DynamicArray.h>
#include <Core/String.h>
#include <Core/Clock.h>
#include <Core/LoopTimer.h>
#include <Core/Log.h>
#include "Sandbox.h"
#include <Memory/UniquePtr.h>
#include <Math/Math.h>

using namespace Lycan::Core;
using namespace Lycan::Memory;
using namespace Lycan;

Sandbox::Sandbox()
{
}

Sandbox::~Sandbox()
{
}

void Sandbox::Initialize()
{
}

struct data
{
	int i = 0;
};

void Sandbox::Update()
{
	String str( "hej" );


	LogMessage( str.Reversed() );

}

void Sandbox::Render()
{
}
