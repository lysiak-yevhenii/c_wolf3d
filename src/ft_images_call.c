#include "../include/wolf3d.h"

SDL_Surface*    ft_get_img(char *path)
{
    SDL_Surface *optimized;
    SDL_Surface *tmp;
    SDL_PixelFormat sdl_format;

    sdl_format.BitsPerPixel = 32;
    sdl_format.BytesPerPixel = 4;
    sdl_format.palette = NULL;
    sdl_format.Rmask = 0;
    sdl_format.Gmask = 0;
    sdl_format.Bmask = 0;
    sdl_format.Amask = 0;
    tmp = NULL;
    optimized = NULL;
    ((tmp = IMG_Load(path)) != NULL) ? (optimized = SDL_ConvertSurface(tmp, \
    &sdl_format, 0)) : 0;
    SDL_FreeSurface(tmp);
    return (optimized);
}

void            ft_fill_array_of_textures(t_textures *texture)
{
    int     itertmp;

    itertmp = texture->quantity;
    while (itertmp--) {
       texture->ptr_texture[itertmp] = ft_get_img(texture->names_with_path[itertmp]);
        printf("%s\n", texture->names_with_path[itertmp]);
    }
}

void        ft_malloc_surfaces(t_win *c_cl)
{
    c_cl->main.quantity = ft_count_files("./imgs/main_elements/", c_cl);
	c_cl->main.ttf_quantity = ft_count_files("./fonts/", c_cl);
    c_cl->menu.quantity = ft_count_files("./imgs/menu_elements/", c_cl);
    c_cl->walls.quantity = ft_count_files("./imgs/walls/",c_cl);
    c_cl->walls.ptr_texture = malloc(sizeof(SDL_Surface) * c_cl->walls.quantity);
    ft_fill_array_of_textures(&c_cl->walls);
    c_cl->flats.quantity = ft_count_files("./imgs/flats/",c_cl);
    c_cl->flats.ptr_texture = malloc(sizeof(SDL_Surface) * c_cl->flats.quantity);
    ft_fill_array_of_textures(&c_cl->flats);
    c_cl->ceiling.quantity = ft_count_files("./imgs/ceiling/",c_cl);
    c_cl->ceiling.ptr_texture = malloc(sizeof(SDL_Surface) * c_cl->ceiling.quantity);
    ft_fill_array_of_textures(&c_cl->ceiling);
}

int             ft_init_images(t_win *c_cl)
{
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    (!(IMG_Init(imgFlags)&imgFlags)) ? ft_truble_img("SDL_image could not initialize! SDL_image Error: " , c_cl) : 0;
    (!(c_cl->statement & FT_FALSE)) ? ft_malloc_surfaces(c_cl) : 0;
    return (1);
}
