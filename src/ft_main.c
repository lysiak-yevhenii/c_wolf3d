#include  "../include/wolf3d.h"

int     ft_showmenu(t_win *main)
{

    main->main.lables[0] = "Start";
    main->main.lables[1] = "Exit";
    main->main.color[0].r = 255;
    main->main.color[0].g = 255;
    main->main.color[0].b = 255;
    main->main.color[1].r = 255;
    main->main.color[1].g = 0;
    main->main.color[1].b = 0;
    main->main.selected[0] = 1;
    main->main.selected[1] = 0;
    return (1);
}

void    ft_main(t_win *main) {
    int i;

    i = 0;
    main->main.ptr_texture = ft_get_img(main->main.names_with_path[main->main.lotary]);
    (main->main.selected[0] == 0 && main->main.menus[0] == NULL) ? \
	 main->main.menus[0] = TTF_RenderText_Solid(main->main.font, main->main.lables[0], main->main.color[0]) : \
   	 (main->main.menus[0] = TTF_RenderText_Solid(main->main.font, main->main.lables[0], main->main.color[1]));
    (main->main.selected[1] == 0 && main->main.menus[1] == NULL) ? \
	main->main.menus[1] = TTF_RenderText_Solid(main->main.font, main->main.lables[1], main->main.color[0]) : \
   	(main->main.menus[1] = TTF_RenderText_Solid(main->main.font, main->main.lables[1], main->main.color[1]));
    main->main.pos[0].x = main->main.ptr_texture->clip_rect.w - 200 - main->main.menus[0]->clip_rect.w;
    main->main.pos[0].y =main->main.ptr_texture->clip_rect.h - 200 - main->main.menus[0]->clip_rect.h;
    main->main.pos[1].x = main->main.ptr_texture->clip_rect.w - 200 - main->main.menus[1]->clip_rect.w;
    main->main.pos[1].y = main->main.ptr_texture->clip_rect.h - 50 - main->main.menus[1]->clip_rect.h;
    while (i < 2){
        (main->main.menus[i] != NULL) ? SDL_BlitSurface(main->main.menus[i], NULL, main->main.ptr_texture, &main->main.pos[i]) : 0;
        SDL_FreeSurface(main->main.menus[i]);
        main->main.menus[i] = NULL;
        i++;
    }
 	main->gTexture = SDL_CreateTextureFromSurface(main->gRenderer, main->main.ptr_texture);
    SDL_FreeSurface(main->main.ptr_texture);
    if (!main->gTexture)
    {
        printf("Error: %s", SDL_GetError());
    }
}
