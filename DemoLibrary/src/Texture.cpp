#include "Texture.h"
#include "stb_image/stb_image.h"


Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	// opengl is bottom left(0,0), png is top left(0,0), so need flip it on load
	stbi_set_flip_vertically_on_load(1);
	// 4 is RGBA
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);


	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	// delete from gpu
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int solt /*= 0*/) const
{
	// specify a texture slot
	GLCall(glActiveTexture(GL_TEXTURE0 + solt));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Ubind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}