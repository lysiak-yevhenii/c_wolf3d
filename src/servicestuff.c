#include "../include/wolf3d.h"

void        free_darray(char **src, int size)
{
    int i = 0;

    while (i < size)
        free(src[i++]);
    free(src);
}

char        **ft_doublerelloc_and_path(char **src, char *word, int size, char *path) {
    int     i;
    char    *tmp;
    char	**newptr;
    char    **begin;

    i = 0;
    if (src == NULL) {
        if (!(newptr = (char **)malloc(sizeof(char *) * 1)))
            return (NULL);
        ft_bzero(newptr, sizeof(newptr));
        tmp = ft_strjoin(path, word);
        *newptr = (char *)malloc(sizeof(char) * ft_strlen(tmp));
        ft_strcpy(*newptr, tmp);
        free(tmp);
        return (newptr);
    }
    else
    {
        newptr = (char **)malloc(sizeof(char *) * size + 1);
        begin = newptr;
        while (i < size)
        {
            *newptr = (char *)malloc(sizeof(char) * ft_strlen(*src));
            ft_strcpy(*newptr, *src);
            newptr++;
            src++;
            i++;
        }
        free_darray(src - i, size);
        tmp = ft_strjoin(path, word);
        *newptr = (char *)malloc(sizeof(char) * ft_strlen(tmp));
        ft_strcpy(*newptr, tmp);
        free(tmp);
    }
    return (begin);
}

char        **ft_doublerelloc(char **src, char *word, int size) {
    int     i;
    char	**newptr;
    char    **begin;
    (void)size;
    i = 0;

    if (src == NULL) {
        if (!(newptr = (char **)malloc(sizeof(char *) * 1)))
            return (NULL);
        newptr[0] = (char *)malloc(sizeof(char) * ft_strlen(word));
        ft_strcpy(*newptr, word);
        return (newptr);
    }
    else
    {
        newptr = (char **)malloc(sizeof(char *) * size + 1);
        begin = newptr;
        while (i < size)
        {
            *newptr = (char *)malloc(sizeof(char) * ft_strlen(*src));
            ft_strcpy(*newptr, *src);
            newptr++;
            src++;
            i++;
        }
        free_darray(src - i, size);
        *newptr = (char *)malloc(sizeof(char) * ft_strlen(word));
        ft_strcpy(*newptr, word);
    }
    return (begin);
}

void        ft_review_needed_folders(char *path, t_win *c_cl)
{
    c_cl->ofpresent = c_cl->nfpresent;
    (!ft_strcmp(path, "./imgs/ceiling/")) ? c_cl->nfpresent++ : 0;
    (!ft_strcmp(path, "./music/tracks/")) ? c_cl->nfpresent++ : 0;
    (!ft_strcmp(path, "./imgs/menu_elements/")) ? c_cl->nfpresent++ : 0;
    (!ft_strcmp(path, "./imgs/main_elements/"))  ? c_cl->nfpresent++ : 0;
    (!ft_strcmp(path, "./imgs/walls/"))  ? c_cl->nfpresent++ : 0;
    (!ft_strcmp(path, "./imgs/flats/")) ? c_cl->nfpresent++ : 0;
    (!ft_strcmp(path, "./fonts/")) ? c_cl->nfpresent++ : 0;
    (c_cl->ofpresent == c_cl->nfpresent) ? ft_error_folder() : 0;
}

int         ft_count_files(char *path, t_win *c_cl)
{
    int file_count;
    DIR *dirp;
    struct dirent *entry;

    file_count = 0;
    dirp = opendir(path);
	if (!dirp)
        ft_error_folder();
	ft_review_needed_folders(path, c_cl);
    while ((entry = readdir(dirp)) != NULL)
    {
        if (entry->d_type == DT_REG && ft_strcmp(entry->d_name, ".DS_Store")) {
            (!ft_strcmp(path, "./imgs/ceiling/")) ? (c_cl->ceiling.names = ft_doublerelloc(c_cl->ceiling.names, entry->d_name, file_count)) && \
            (c_cl->ceiling.names_with_path = ft_doublerelloc_and_path(c_cl->ceiling.names_with_path, entry->d_name, file_count, "./imgs/ceiling/")) : 0;
            (!ft_strcmp(path, "./music/tracks/")) ? (c_cl->music.track_names = ft_doublerelloc(c_cl->music.track_names, entry->d_name, file_count)) && \
            (c_cl->music.track_name_and_path = ft_doublerelloc_and_path(c_cl->music.track_name_and_path, entry->d_name, file_count, "./music/tracks/")) : 0;
            (!ft_strcmp(path, "./imgs/menu_elements/")) ? (c_cl->menu.names = ft_doublerelloc(c_cl->menu.names, entry->d_name, file_count)) && \
            (c_cl->menu.names_with_path = ft_doublerelloc_and_path(c_cl->menu.names_with_path, entry->d_name, file_count, "./imgs/menu_elements/")) : 0;
            (!ft_strcmp(path, "./imgs/main_elements/")) ? (c_cl->main.names = ft_doublerelloc(c_cl->main.names, entry->d_name, file_count)) && \
            (c_cl->main.names_with_path = ft_doublerelloc_and_path(c_cl->main.names_with_path, entry->d_name, file_count, "./imgs/main_elements/")) : 0;
            (!ft_strcmp(path, "./imgs/walls/")) ? (c_cl->walls.names = ft_doublerelloc(c_cl->walls.names, entry->d_name, file_count)) && \
            (c_cl->walls.names_with_path = ft_doublerelloc_and_path(c_cl->walls.names_with_path, entry->d_name, file_count, "./imgs/walls/")) : 0;
            (!ft_strcmp(path, "./imgs/flats/")) ? (c_cl->flats.names = ft_doublerelloc(c_cl->flats.names, entry->d_name, file_count)) && \
            (c_cl->flats.names_with_path = ft_doublerelloc_and_path(c_cl->flats.names_with_path, entry->d_name, file_count, "./imgs/flats/")) : 0;
            (!ft_strcmp(path, "./imgs/skybox/")) ? (c_cl->skybox.names = ft_doublerelloc(c_cl->flats.names, entry->d_name, file_count)) && \
            (c_cl->skybox.names_with_path = ft_doublerelloc_and_path(c_cl->skybox.names_with_path, entry->d_name, file_count, "./imgs/skybox/")) : 0;
			(!ft_strcmp(path, "./fonts/") && !ft_strcmp("wolfenstein.ttf", entry->d_name)) ? (c_cl->main.font = TTF_OpenFont("./fonts/wolfenstein.ttf", 140)) : 0;
              file_count++;
        }
    }
    closedir(dirp);
    return (file_count);
}


void        ft_init_rander(t_win *c_cl)
{
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    c_cl->gRenderer = SDL_CreateRenderer(c_cl->window, -1, render_flags);
    (c_cl->gRenderer == NULL) ? ft_truble_win("Render could not be created! SDL Error: ", c_cl) : 0;
}

void       ft_init_window(t_win *c_cl)  //The window we'll be rendering to
{
	printf("HERE 1");
    (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) ? printf("Initialize SDL_Error: %s\n", SDL_GetError()) && (c_cl->statement = FT_FALSE) : 0;
   printf("HERE 2");
   	if (!(c_cl->statement & FT_FALSE))
    {
		(TTF_Init() == -1) ? ft_error_ttf_init() : 0;
        (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) ? \
		ft_putstr("Warning: Linear texture filtering not enabled!\n") : 0;
        c_cl->window = SDL_CreateWindow( "Wolf3D", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		(c_cl->window == NULL) ? ft_truble_win("Window could not be created! SDL_Error: ", c_cl) : 0;
        (!(c_cl->statement & FT_FALSE)) ? ft_init_audios(c_cl) : 0;
		(!(c_cl->statement & FT_FALSE)) ? ft_init_rander(c_cl) : 0;
		(!(c_cl->statement & FT_FALSE)) ? ft_init_images(c_cl) : 0;
	}
}

void sdl_quatity_audiowasopen(void)
{
    int numtimesopened, frequency, channels;
    Uint16 format;
    numtimesopened=Mix_QuerySpec(&frequency, &format, &channels);
    if(!numtimesopened) {
        printf("Mix_QuerySpec: %s\n",Mix_GetError());
    }
    else {
        char *format_str="Unknown";
        switch(format) {
            case AUDIO_U8: format_str="U8"; break;
            case AUDIO_S8: format_str="S8"; break;
            case AUDIO_U16LSB: format_str="U16LSB"; break;
            case AUDIO_S16LSB: format_str="S16LSB"; break;
            case AUDIO_U16MSB: format_str="U16MSB"; break;
            case AUDIO_S16MSB: format_str="S16MSB"; break;
        }
        printf("opened=%d times  frequency=%dHz  format=%s  channels=%d",
               numtimesopened, frequency, format_str, channels);
    }
}

void sdl_close(t_win *c_sc)
{
    sdl_quatity_audiowasopen();
    (c_sc->music.track != NULL) ? Mix_FreeMusic(c_sc->music.track) : 0;
    SDL_DestroyTexture(c_sc->gTexture);
    SDL_DestroyRenderer(c_sc->gRenderer);
    SDL_DestroyWindow(c_sc->window);
    c_sc->gTexture = NULL;
    c_sc->window = NULL;
    c_sc->gRenderer = NULL;
    c_sc->music.track = NULL;
    Mix_CloseAudio();
	TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

