#pragma once

#include <Lycan.h>

class Sandbox : public Lycan::Application
{
public:

	Sandbox();
	~Sandbox();

	void Initialize() override;
	void Update()     override;
	void Render()     override;

};

Lycan::Application* Lycan::CreateApplication( void )
{
	return new Sandbox();
}