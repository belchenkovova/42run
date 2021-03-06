#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

using namespace		engine;

					model::texture::texture()
{
	glGenTextures(1, &object);
}

					model::texture::texture(const path &source) :
						texture()
{
	int				number_of_components;

	stbi_set_flip_vertically_on_load(1);

	auto			*data = stbi_load(source.c_str(), &size.x, &size.y, &number_of_components, 0);

	if (not data)
		error::raise(error::id::texture_creation_error);

	GLenum			format = 0;

	switch (number_of_components)
	{
		case 1 :
			format = GL_RED;
			break ;
		case 3 :
			format = GL_RGB;
			break ;
		case 4 :
			format = GL_RGBA;
			break ;
		default :
			error::raise(error::id::texture_bad_format);

	}

	texture::use(true);

	glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture::use(false);

	stbi_image_free(data);
}

					model::texture::~texture()
{
	glDeleteTextures(1, &object);
}

void				model::texture::use(bool state)
{
	glBindTexture(GL_TEXTURE_2D, state ? object : 0);
}