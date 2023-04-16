#pragma once

#include "Renderer.h"

class Texture
{
public:
	Texture();
	~Texture();

private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture(const std::string& path);

	// windows 32 textures solts
	void Bind(unsigned int solt = 0) const;
	void Ubind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};