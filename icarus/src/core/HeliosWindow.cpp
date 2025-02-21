#include "HeliosWindow.h"
#include <SFML/Graphics.hpp>

//Constructor
HeliosWindow::HeliosWindow(sf::Vector2<unsigned int> windowSize, int framerate, bool asRenderTexture)
{
	this->SetWindowSize(windowSize);
	this->SetFramerate(framerate);
	this->m_IsRenderTexture = asRenderTexture;
}

void HeliosWindow::InitializeWindow()
{
	this->p_SFWindow = new sf::RenderWindow(sf::VideoMode({ this->m_WindowSize.x, this->m_WindowSize.y }), "Icarus");
	this->p_SFWindow->setFramerateLimit(this->m_Framerate);

	if (m_IsRenderTexture)
	{
		m_RenderTexture = sf::RenderTexture({ m_WindowSize.x, m_WindowSize.y });
	}
}

void HeliosWindow::StartDraw()
{
	if (m_IsRenderTexture)
	{
		this->GetRenderTexture().clear(sf::Color(0x87ceebFF));
	}
	else 
	{
		this->GetSFWindow().clear(sf::Color(0x87ceebFF));
	}
	
}

void HeliosWindow::EndDraw()
{
	if (m_IsRenderTexture)
	{
		this->GetRenderTexture().display();
	}

	this->GetSFWindow().display();

}

sf::RenderTexture& HeliosWindow::GetRenderTexture()
{
	return this->m_RenderTexture;
}

const sf::Texture* HeliosWindow::GetSceneTexture() const
{
	if (m_IsRenderTexture)
	{
		return &(m_RenderTexture.getTexture());
	}

	return nullptr;
}

sf::RenderWindow& HeliosWindow::GetSFWindow()
{
	return *this->p_SFWindow;
}

sf::Vector2<unsigned int> HeliosWindow::GetWindowSize()
{
	return this->m_WindowSize;
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


