#include <cstdio>
#include <cstdint>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GAME_MAX_BULLETS 128

typedef void (*GLFWerrorfun)(int, const char *);
typedef void (*GLFWkeyfun)(GLFWwindow *, int, int, int, int);
GLFWerrorfun glfwSetCharCallback(GLFWerrorfun cbfun);

bool game_running = false;
int move_dir = 0;
bool fire_pressed = 0;
struct Buffer
{
    size_t width, height;
    uint32_t *data;
};

struct Sprite
{
    size_t width, height;
    uint8_t *data;
};

struct Alien
{
    size_t x, y;
    uint8_t type;
};

struct Player
{
    size_t x, y;
    size_t life;
};
struct Bullet
{
    size_t x, y;
    int dir;
};

struct Game
{
    size_t width, height;
    size_t num_aliens;
    size_t num_bullets;
    Alien *aliens;
    Player player;
    Bullet bullets[GAME_MAX_BULLETS];
};

struct SpriteAnimation
{
    bool loop;
    size_t num_frames;
    size_t frame_duration;
    size_t time;
    Sprite **frames;
};

enum AlienType : uint8_t
{
    ALIEN_DEAD = 0,
    ALIEN_TYPE_A = 1,
    ALIEN_TYPE_B = 2,
    ALIEN_TYPE_C = 3
};

void create_all_alien_sprites(Sprite *alien_sprites)
{
    //Sprite alien_sprites[6];

    alien_sprites[0].width = 8;
    alien_sprites[0].height = 8;
    alien_sprites[0].data = new uint8_t[64]{
        0, 0, 0, 1, 1, 0, 0, 0, // ...@@...
        0, 0, 1, 1, 1, 1, 0, 0, // ..@@@@..
        0, 1, 1, 1, 1, 1, 1, 0, // .@@@@@@.
        1, 1, 0, 1, 1, 0, 1, 1, // @@.@@.@@
        1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@
        0, 1, 0, 1, 1, 0, 1, 0, // .@.@@.@.
        1, 0, 0, 0, 0, 0, 0, 1, // @......@
        0, 1, 0, 0, 0, 0, 1, 0  // .@....@.
    };

    alien_sprites[1].width = 8;
    alien_sprites[1].height = 8;
    alien_sprites[1].data = new uint8_t[64]{
        0, 0, 0, 1, 1, 0, 0, 0, // ...@@...
        0, 0, 1, 1, 1, 1, 0, 0, // ..@@@@..
        0, 1, 1, 1, 1, 1, 1, 0, // .@@@@@@.
        1, 1, 0, 1, 1, 0, 1, 1, // @@.@@.@@
        1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@
        0, 0, 1, 0, 0, 1, 0, 0, // ..@..@..
        0, 1, 0, 1, 1, 0, 1, 0, // .@.@@.@.
        1, 0, 1, 0, 0, 1, 0, 1  // @.@..@.@
    };

    alien_sprites[2].width = 11;
    alien_sprites[2].height = 8;
    alien_sprites[2].data = new uint8_t[88]{
        0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, // ..@.....@..
        0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, // ...@...@...
        0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, // ..@@@@@@@..
        0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, // .@@.@@@.@@.
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, // @.@@@@@@@.@
        1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, // @.@.....@.@
        0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0  // ...@@.@@...
    };

    alien_sprites[3].width = 11;
    alien_sprites[3].height = 8;
    alien_sprites[3].data = new uint8_t[88]{
        0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, // ..@.....@..
        1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, // @..@...@..@
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, // @.@@@@@@@.@
        1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, // @@@.@@@.@@@
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, // .@@@@@@@@@.
        0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, // ..@.....@..
        0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0  // .@.......@.
    };

    alien_sprites[4].width = 12;
    alien_sprites[4].height = 8;
    alien_sprites[4].data = new uint8_t[96]{
        0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, // ....@@@@....
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, // .@@@@@@@@@@.
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@@
        1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, // @@@..@@..@@@
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@@
        0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, // ...@@..@@...
        0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, // ..@@.@@.@@..
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1  // @@........@@
    };

    alien_sprites[5].width = 12;
    alien_sprites[5].height = 8;
    alien_sprites[5].data = new uint8_t[96]{
        0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, // ....@@@@....
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, // .@@@@@@@@@@.
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@@
        1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, // @@@..@@..@@@
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@@
        0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, // ..@@@..@@@..
        0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, // .@@..@@..@@.
        0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0  // ..@@....@@..
    };
    //return alien_sprites;
}

Sprite alien_death_sprite_Func()
{

    Sprite alien_death_sprite;
    alien_death_sprite.width = 13;
    alien_death_sprite.height = 7;
    alien_death_sprite.data = new uint8_t[91]{
        0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, // .@..@...@..@.
        0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, // ..@..@.@..@..
        0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, // ...@.....@...
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, // @@.........@@
        0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, // ...@.....@...
        0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, // ..@..@.@..@..
        0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0  // .@..@...@..@.
    };
    return alien_death_sprite;
}
uint32_t
rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b)
{
    return (r << 24) | (g << 16) | (b << 8) | 255;
}

Sprite player_sprite_func()
{
    Sprite player_sprite;
    player_sprite.width = 11;
    player_sprite.height = 7;
    player_sprite.data = new uint8_t[77]{
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, // .....@.....
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, // ....@@@....
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, // ....@@@....
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, // .@@@@@@@@@.
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@
    };
    return player_sprite;
}

Sprite alien_sprite_func()
{
    Sprite alien_sprite;
    alien_sprite.width = 11;
    alien_sprite.height = 8;
    alien_sprite.data = new uint8_t[88]{
        0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, // ..@.....@..
        0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, // ...@...@...
        0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, // ..@@@@@@@..
        0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, // .@@.@@@.@@.
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, // @.@@@@@@@.@
        1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, // @.@.....@.@
        0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0  // ...@@.@@...
    };

    return alien_sprite;
}

Sprite alien_sprite_inversFunc()
{
    Sprite alien_sprite1;
    alien_sprite1.width = 11;
    alien_sprite1.height = 8;
    alien_sprite1.data = new uint8_t[88]{
        0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, // ..@.....@..
        1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, // @..@...@..@
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, // @.@@@@@@@.@
        1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, // @@@.@@@.@@@
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // @@@@@@@@@@@
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, // .@@@@@@@@@.
        0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, // ..@.....@..
        0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0  // .@.......@.
    };
    return alien_sprite1;
}

Sprite bullet_sprite_Func()
{
    Sprite bullet_sprite;
    bullet_sprite.width = 1;
    bullet_sprite.height = 3;
    bullet_sprite.data = new uint8_t[3]{
        1, // @
        1, // @
        1, // @
    };
    return bullet_sprite;
}
void buffer_sprite_draw(
    Buffer *buffer, const Sprite &sprite,
    size_t x, size_t y, uint32_t color)
{
    for (size_t xi = 0; xi < sprite.width; ++xi)
    {
        for (size_t yi = 0; yi < sprite.height; ++yi)
        {
            size_t sy = sprite.height - 1 + y - yi;
            size_t sx = x + xi;
            if (sprite.data[yi * sprite.width + xi] &&
                sy < buffer->height && sx < buffer->width)
            {
                buffer->data[sy * buffer->width + sx] = color;
            }
        }
    }
}

void setupGameAnimation(SpriteAnimation *alien_animation, Sprite *alien_sprites)
{
    for (size_t i = 0; i < 3; i++)
    {
        alien_animation[i].loop = true;
        alien_animation[i].num_frames = 2;
        alien_animation[i].frame_duration = 10;
        alien_animation[i].time = 0;

        alien_animation[i].frames = new Sprite *[2];
        alien_animation[i].frames[0] = &alien_sprites[2 * i];
        alien_animation[i].frames[1] = &alien_sprites[2 * i + 1];
    }

    glfwSwapInterval(1);
}

void updateAnimatations(SpriteAnimation *alien_animation)
{
    /* ++alien_animation->time;
    if (alien_animation->time == alien_animation->num_frames * alien_animation->frame_duration)
    {
        if (alien_animation->loop)
            alien_animation->time = 0;
        else
        {
            delete alien_animation;
            alien_animation = nullptr;
        }
    } */

    for (size_t i = 0; i < 3; i++)
    {
        ++alien_animation[i].time;
        if (alien_animation[i].time == alien_animation[i].num_frames * alien_animation[i].frame_duration)
        {
            alien_animation[i].time = 0;
        }
    }
}

void updateAnimationFrame(Game game, SpriteAnimation *alien_animation, Buffer *buffer, uint8_t *death_counters)
{

    for (size_t ai = 0; ai < game.num_aliens; ai++)

    {

        if (!death_counters[ai])
            continue;
        const Alien &alien = game.aliens[ai];
        if (alien.type == ALIEN_DEAD)
        {
            Sprite alien_death_sprite = alien_death_sprite_Func();
            buffer_sprite_draw(buffer, alien_death_sprite, alien.x, alien.y, rgb_to_uint32(128, 0, 0));
        }
        else
        {
            const SpriteAnimation &animation = alien_animation[alien.type - 1];
            size_t current_frame = animation.time / animation.frame_duration;
            printf("current frame %zu", current_frame);
            const Sprite &sprite = *animation.frames[current_frame];
            //printf("Sprite width %zu", sprite.width);
            //printf("Sprite height %zu", sprite.height);

            buffer_sprite_draw(buffer, sprite, alien.x, alien.y, rgb_to_uint32(128, 0, 0));
        }
    }
}

void controlPLayerDirection(Game *game, int *player_move_dir, Sprite player_sprite)
{
    if (*player_move_dir != 0)
    {
        if (game->player.x + player_sprite.width + *player_move_dir >= game->width - 1)
        {
            game->player.x = game->width - player_sprite.width - *player_move_dir - 1;
            *player_move_dir *= -1;
        }
        else if ((int)game->player.x + *player_move_dir <= 0)
        {
            game->player.x = 0;
            *player_move_dir *= -1;
        }
        else
            game->player.x += *player_move_dir;
    }
}
void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void buffer_clear(Buffer *buffer, uint32_t color)
{
    for (size_t i = 0; i < buffer->width * buffer->height; ++i)
    {
        buffer->data[i] = color;
    }
}

void validate_shader(GLuint shader, const char *file = 0)
{
    static const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

    if (length > 0)
    {
        printf("Shader %d(%s) compile error: %s",
               shader, (file ? file : ""), buffer);
    }
}

bool validate_program(GLuint program)
{
    static const GLsizei BUFFER_SIZE = 512;
    GLchar buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

    if (length > 0)
    {
        printf("Program %d link error: %s \n", program, buffer);
        return false;
    }

    return true;
}

int opengl_shaders(Buffer *buffer)
{

    GLuint buffer_texture;
    glGenTextures(1, &buffer_texture);
    glBindTexture(GL_TEXTURE_2D, buffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, buffer->width, buffer->height, 0,
                 GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buffer->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Create vao for generating fullscreen triangle
    GLuint fullscreen_triangle_vao;
    glGenVertexArrays(1, &fullscreen_triangle_vao);

    // Create shader for displaying buffer
    static const char *fragment_shader =
        "\n"
        "#version 330\n"
        "\n"
        "uniform sampler2D buffer;\n"
        "noperspective in vec2 TexCoord;\n"
        "\n"
        "out vec3 outColor;\n"
        "\n"
        "void main(void){\n"
        "    outColor = texture(buffer, TexCoord).rgb;\n"
        "}\n";

    static const char *vertex_shader =
        "\n"
        "#version 330\n"
        "\n"
        "noperspective out vec2 TexCoord;\n"
        "\n"
        "void main(void){\n"
        "\n"
        "    TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0;\n"
        "    TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0;\n"
        "    \n"
        "    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);\n"
        "}\n";

    GLuint shader_id = glCreateProgram();

    {
        //Create vertex shader
        GLuint shader_vp = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(shader_vp, 1, &vertex_shader, 0);
        glCompileShader(shader_vp);
        validate_shader(shader_vp, vertex_shader);
        glAttachShader(shader_id, shader_vp);

        glDeleteShader(shader_vp);
    }

    {
        //Create fragment shader
        GLuint shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(shader_fp, 1, &fragment_shader, 0);
        glCompileShader(shader_fp);
        validate_shader(shader_fp, fragment_shader);
        glAttachShader(shader_id, shader_fp);

        glDeleteShader(shader_fp);
    }

    glLinkProgram(shader_id);

    if (!validate_program(shader_id))
    {
        fprintf(stderr, "Error while validating shader.\n");
        glfwTerminate();
        glDeleteVertexArrays(1, &fullscreen_triangle_vao);
        delete[] buffer->data;
        return -1;
    }

    glUseProgram(shader_id);

    GLint location = glGetUniformLocation(shader_id, "buffer");
    glUniform1i(location, 0);

    //OpenGL setup
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(fullscreen_triangle_vao);

    return 0;
}

Game createGame(const size_t buffer_width, const size_t buffer_height)
{
    Game game;
    game.width = buffer_width;
    game.height = buffer_height;
    game.num_aliens = 55;
    game.aliens = new Alien[game.num_aliens];

    game.num_bullets = 0;
    game.player.x = 112 - 5;
    game.player.y = 32;

    game.player.life = 3;
    return game;
}

void positionAliens(Game *game, Buffer *buffer, Sprite *alien_sprites)
{
    Sprite alien_death_sprite = alien_death_sprite_Func();
    for (size_t yi = 0; yi < 5; yi++)
    {
        for (size_t xi = 0; xi < 11; xi++)
        {
            Alien &alien = game->aliens[yi * 11 + xi];
            alien.type = (5 - yi) / 2 + 1;

            const Sprite &sprite = alien_sprites[2 * (alien.type - 1)];
            game->aliens[yi * 11 + xi].x = 16 * xi + 20 + (alien_death_sprite.width - sprite.width) / 2;
            game->aliens[yi * 11 + xi].y = 17 * yi + 128;
        }
    }

    /* for (size_t ai = 0; ai < game.num_aliens; ai++)
    {
        const Alien &alien = game.aliens[ai];
        buffer_sprite_draw(buffer, alien_sprite,
                           alien.x, alien.y, rgb_to_uint32(128, 0, 0));
    }
    buffer_sprite_draw(buffer, player_sprite, game.player.x, game.player.y, rgb_to_uint32(128, 0, 0)); */
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            game_running = false;
        break;
    case GLFW_KEY_RIGHT:
        if (action == GLFW_PRESS)
            move_dir += 1;
        else if (action == GLFW_RELEASE)
            move_dir -= 1;
        break;
    case GLFW_KEY_LEFT:
        if (action == GLFW_PRESS)
            move_dir -= 1;
        else if (action == GLFW_RELEASE)
            move_dir += 1;
        break;
    case GLFW_KEY_SPACE:
        if (action == GLFW_RELEASE)
            fire_pressed = true;
        break;
    default:
        break;
    }
}

void draw_projectiles(Buffer *buffer, Game game)
{
    for (size_t bi = 0; bi < game.num_bullets; ++bi)
    {
        const Bullet &bullet = game.bullets[bi];
        const Sprite &sprite = bullet_sprite_Func();
        buffer_sprite_draw(buffer, sprite, bullet.x, bullet.y, rgb_to_uint32(128, 0, 0));
    }
}

bool sprite_overlap_check(
    const Sprite &sp_a, size_t x_a, size_t y_a,
    const Sprite &sp_b, size_t x_b, size_t y_b)
{
    if (x_a < x_b + sp_b.width && x_a + sp_a.width > x_b &&
        y_a < y_b + sp_b.height && y_a + sp_a.height > y_b)
    {
        return true;
    }
    return false;
}
void update_projectiles(Game *game, SpriteAnimation *alien_animation)
{
    Sprite bullet_sprite = bullet_sprite_Func();
    for (size_t bi = 0; bi < game->num_bullets;)
    {

        game->bullets[bi].y += game->bullets[bi].dir;
        if (game->bullets[bi].y >= game->height ||
            game->bullets[bi].y < bullet_sprite.height)
        {
            game->bullets[bi] = game->bullets[game->num_bullets - 1];
            --game->num_bullets;
            continue;
        }

        for (size_t ai = 0; ai < game->num_aliens; ai++)
        {
            const Alien &alien = game->aliens[ai];
            if (alien.type == ALIEN_DEAD)
                continue;

            const SpriteAnimation &animation = alien_animation[alien.type - 1];
            size_t current_frame = animation.time / animation.frame_duration;
            const Sprite &alien_sprite = *animation.frames[current_frame];
            bool overlap = sprite_overlap_check(
                bullet_sprite, game->bullets[bi].x, game->bullets[bi].y,
                alien_sprite, alien.x, alien.y);

            if (overlap)
            {
                game->aliens[ai].type = ALIEN_DEAD;
                //NOTE: Hack to recenter death sprite
                Sprite alien_death_sprite = alien_death_sprite_Func();
                game->aliens[ai].x -= (alien_death_sprite.width - alien_sprite.width) / 2;
                game->bullets[bi] = game->bullets[game->num_bullets - 1];
                --game->num_bullets;
                continue;
            }
        }
        ++bi;
    }
}

void firing_projectiles(Game *game, Sprite player_sprite)
{
    if (fire_pressed && game->num_bullets < GAME_MAX_BULLETS)
    {
        game->bullets[game->num_bullets].x = game->player.x + player_sprite.width / 2;
        game->bullets[game->num_bullets].y = game->player.y + player_sprite.height;
        game->bullets[game->num_bullets].dir = 2;
        ++game->num_bullets;
    }
    fire_pressed = false;
}

void draw_specific_alien(Game game, uint8_t *death_counters)
{
    for (size_t ai = 0; ai < game.num_aliens; ai++)
    {
        const Alien &alien = game.aliens[ai];
        if (alien.type == ALIEN_DEAD && death_counters[ai])
        {
            --death_counters[ai];
        }
    }
}

int main(int argc, char *argv[])
{
    glfwSetErrorCallback(error_callback);
    const size_t buffer_width = 224;
    const size_t buffer_height = 256;

    //initializing the GLFW library
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window;
    window = glfwCreateWindow(640, 480, "Space Invaders Woho", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Error initializing GLEW.\n");
        glfwTerminate();
        return -1;
    }

    int glVersion[2] = {-1, 1};
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

    printf("Using OpenGL: %d.%d\n", glVersion[0], glVersion[1]);

    glClearColor(1.0, 0.0, 0.0, 1.0);

    //Create graphics buffer
    uint32_t clear_color = rgb_to_uint32(0, 128, 0);
    Buffer buffer;
    buffer.width = buffer_width;
    buffer.height = buffer_height;
    buffer.data = new uint32_t[buffer.width * buffer.height];
    buffer_clear(&buffer, 0);
    opengl_shaders(&buffer);

    //buffer_clear(&buffer, clear_color);

    // Create texture for presenting buffer to OpenGL
    // Prepare game

    Sprite player_sprite = player_sprite_func();
    //Sprite alien_sprite0 = alien_sprite_func();
    //Sprite alien_sprite1 = alien_sprite_inversFunc();
    Sprite alien_sprites[6];

    create_all_alien_sprites(alien_sprites);
    for (int i = 0; i < 6; i++)
    {
        printf("alien sprites %zu \n", alien_sprites[i].height);
    }

    SpriteAnimation alien_animation[3];
    setupGameAnimation(alien_animation, alien_sprites);

    Game game = createGame(buffer_width, buffer_height);
    positionAliens(&game, &buffer, alien_sprites);

    game_running = true;
    uint8_t *death_counters = new uint8_t[game.num_aliens];
    for (size_t i = 0; i < game.num_aliens; i++)
    {
        death_counters[i] = 10;
    }
    int player_move_dir = 1;

    while (!glfwWindowShouldClose(window) && game_running)
    {
        buffer_clear(&buffer, clear_color);

        glClear(GL_COLOR_BUFFER_BIT);

        updateAnimationFrame(game, alien_animation, &buffer, death_counters);

        draw_projectiles(&buffer, game);
        buffer_sprite_draw(&buffer, player_sprite, game.player.x, game.player.y, rgb_to_uint32(128, 0, 0));

        updateAnimatations(alien_animation);

        glTexSubImage2D(
            GL_TEXTURE_2D, 0, 0, 0,
            buffer.width, buffer.height,
            GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
            buffer.data);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glfwSwapBuffers(window);
        draw_specific_alien(game, death_counters);
        update_projectiles(&game, alien_animation);

        //Simulate player
        player_move_dir = 2 * move_dir;
        controlPLayerDirection(&game, &player_move_dir, player_sprite);

        //Process events
        firing_projectiles(&game, player_sprite);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
