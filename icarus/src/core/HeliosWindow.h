#pragma once
#include <SFML/Graphics.hpp>

class HeliosWindow
{
public:
	/// <summary>
	/// Helios Window Constructor
	/// </summary>
	/// <param name="windowSize">Size of the window</param>
	/// <param name="framerate">Framerate of the window</param>
	/// <param name="asRenderTexture">Should this window be rendered to a render texture (for editor purposes) or a typical window?</param>
	HeliosWindow(sf::Vector2<unsigned int> windowSize, int framerate, bool asRenderTexture = false);
	sf::RenderWindow* p_SFWindow;
private:
	

	sf::Vector2<unsigned int> m_WindowSize;
	int m_Framerate;
	bool m_IsRenderTexture;

	sf::RenderTexture m_RenderTexture;
public:
	void InitializeWindow();
	void StartDraw();
	void EndDraw();

	sf::RenderTexture& GetRenderTexture();
	const sf::Texture* GetSceneTexture() const;

	sf::RenderWindow& GetSFWindow();
	sf::Vector2<unsigned int> GetWindowSize();
	int GetFramerate();

	void SetWindowSize(sf::Vector2<unsigned int> size);
	void SetFramerate(int framerate);
};