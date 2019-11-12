#include <Core/DynamicArray.h>
#include <Core/String.h>
#include <Core/Clock.h>
#include <Core/LoopTimer.h>
#include <Core/Log.h>
#include "Sandbox.h"

using namespace Lycan::Core;

Sandbox::Sandbox()
{
}

Sandbox::~Sandbox()
{
}

void Sandbox::Initialize()
{
}

void Sandbox::Update()
{
	LogError( String( "Hej error\n" ) );
	LogWarning( String( "Hej varning\n" ) );
	LogMessage( String( "Delta tid %f\n", Clock::Instance().DeltaTime() ) );
}

void Sandbox::Render()
{
}
