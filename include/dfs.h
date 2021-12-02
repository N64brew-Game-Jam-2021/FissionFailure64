#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__
#include <stdarg.h>

#include <libdragon.h>

typedef struct sprites
{
    sprite_t *sprites[34];
    int slices;

    int height;
    int width;
} sprites_t;

void dfs_free_sprites(sprites_t *sprites);
sprite_t *dfs_load_sprite(const char *const path);
sprite_t *dfs_load_spritef(const char *const format, ...);
sprites_t *dfs_load_sprites(const char *const path);
sprites_t *dfs_load_sprites_int(const char *const path, const int i);
sprites_t *dfs_load_sprites_string(const char *const path, const char *c);
sprites_t *dfs_load_sprites_rod(const char *const path, const char *color, char letter, char number);
int dfs_openf(const char *const format, ...);

#endif //__FILESYSTEM_H__