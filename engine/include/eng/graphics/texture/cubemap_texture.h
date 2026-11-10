#ifndef CUBEMAP_TEXTURE_H
#define CUBEMAP_TEXTURE_H
#include <vector>
#include <string>
#include <glad/glad.h>
namespace eng
{
class CubemapTexture
{
public:
	// right, left, top, bottom, front, back
	explicit CubemapTexture(const std::vector<std::string>& faces);
	~CubemapTexture();

	CubemapTexture(const CubemapTexture&) = delete;
	CubemapTexture& operator=(const CubemapTexture&) = delete;

	void Bind(GLuint textureUnit) const;

	GLuint GetID() const
	{
		return m_id;
	}
private:
	GLuint m_id{0};
};

}
#endif // !CUBEMAP_TEXTURE_H
