#pragma once
#include <SFML/Graphics.hpp>

class HeliosWindow
{
public:
	HeliosWindow(sf::Vector2<unsigned int> windowSize, int framerate);
	sf::RenderWindow* p_SFWindow;
private:
	

	sf::Vector2<unsigned int> m_WindowSize;
	int m_Framerate;
public:
	void InitializeWindow();
	void StartDraw();
	void EndDraw();

	sf::RenderWindow& GetSFWindow();
	sf::Vector2<unsigned int> GetWindowSize();
	int GetFramerate();

	void SetWindowSize(sf::Vector2<unsigned int> size);
	void SetFramerate(int framerate);
};