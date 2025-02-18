#include "HeliosWindow.h"
#include <SFML/Graphics.hpp>

//Constructor
HeliosWindow::HeliosWindow(sf::Vector2<unsigned int> windowSize, int framerate)
{
	this->SetWindowSize(windowSize);
	this->SetFramerate(framerate);
}

void HeliosWindow::InitializeWindow()
{
	this->p_SFWindow = new sf::RenderWindow(sf::VideoMode({ this->m_WindowSize.x, this->m_WindowSize.y }), "Icarus");
	this->p_SFWindow->setFramerateLimit(this->m_Framerate);
}

void HeliosWindow::StartDraw()
{
	this->GetSFWindow().clear(sf::Color(0xFF3AF2E9));
}

void HeliosWindow::EndDraw()
{
	this->GetSFWindow().display();
}

sf::RenderWindow& HeliosWindow::GetSFWindow()
{
	return *this->p_SFWindow;
}

sf::Vector2<unsigned int> HeliosWindow::GetWindowSize()
{
	return sf::Vector2<unsigned int>();
}

int HeliosWindow::GetFramerate()
{
	return this->m_Framerate;
}

void HeliosWindow::SetWindowSize(sf::Vector2<unsigned int> size)
{
	this->m_WindowSize = size;
}

void HeliosWindow::SetFramerate(int framerate)
{
	this->m_Framerate = framerate;
}


