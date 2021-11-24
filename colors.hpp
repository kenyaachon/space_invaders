#include <cstdint>
#include <cstdio>
#include <GL/glew.h>

struct Buffer
{
    std::size_t width, height;
    std::uint32_t *data;
};

struct Sprite
{
    size_t width, height;
    uint8_t *data;
};

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);

void buffer_clear(Buffer *buffer, uint32_t color);

void validate_shader(GLuint shader, const char *file);

bool validate_program(GLuint program);

void buffer_sprite_draw(Buffer *buffer, const Sprite &sprite, size_t x, size_t y, uint32_t color);

int opengl_shaders(Buffer *buffer);
