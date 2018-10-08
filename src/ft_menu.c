#include "../include/wolf3d.h"

void    ft_menu(t_win *c_cl)
{
    (c_cl->gTexture != NULL) ? SDL_DestroyTexture(c_cl->gTexture) : 0;
    c_cl->gTexture = SDL_CreateTextureFromSurface(c_cl->gRenderer, (c_cl->menu.ptr_texture = ft_get_img(c_cl->menu.names_with_path[c_cl->menu.lotary])));
    SDL_FreeSurface(c_cl->menu.ptr_texture);
    if (!c_cl->gTexture)
        printf("Error: %s", SDL_GetError());
    printf("%d", c_cl->menu.lotary);
}