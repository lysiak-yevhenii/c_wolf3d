#ifndef WOLF3D_H
#define WOLF3D_H
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_timer.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"
# include <stdbool.h> //contained bool type;
# include <dirent.h>  //count files in folder
# include <stdio.h>
# include <libft.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>

#define SCREEN_WIDTH	1200 
#define SCREEN_HEIGHT	700
#define SCREEN_HHALPH	SCREEN_HEIGHT/2
#define FRAMES_PER_SECOND 60
#define PITWO       (M_PI * 2)
#define FT_FALSE    (1 << 2)
#define FT_MAIN     (1 << 0)
#define FT_MENU     (1 << 1)
#define FT_GAME     (1 << 2)

typedef struct s_ft_rect
{
    int     x;
    int     y;
    int     width;
    int     hight;
    int     color;
	int		startx;
	int		starty;
	int		endx;
	int		endy;
	int		tmp;
}              t_ft_rect;

typedef struct s_vector2d
{
    double     x0;
    double     y0;
    double     x1;
    double     y1;
    int     color;
}              t_vector2d;

typedef struct s_map
{
    int     fd;
    int     size;
    int     chkord;
    int     chk;
    int    **ceilingmap;
    int    **map;
    int     miniwidth;
    int     miniheight;
    char    *line;
}              t_map;

typedef struct  s_payer
{
    int         numbrays;

    double      rayscreenpos;
    double      rayviewdist;
    double      rayangle;
    double      stripwidth;
    double      viewdist;
    double      fov;

    double      rot;
    double      dir;
    int         walkr;
    int         walkl;
    int         walku;
    int         walkd;
    int         x;       //mouse X coordinate
    int         y;       //mouse Y coordinate
    double      speed;   // is the playing moving forward (speed = 1) or backwards (speed = -1).
    double      moviespeed; // how far (in map units) does the player move each step/update
    double      rotspeed; // how much does the player rotate each step/update (in degrees)

    double      posx;    //start postition X
    double      posy;    //start postiton Y

    double      camerax; //x coordinate in camera space
    double      dirx;    //direction vector x
    double      diry;    //direction vector y
    double      raydirx;
    double      raydiry;
    double      posz;    //distance from you to object like a wall
    double      planex;  //paycast camera plane
    double      planey;  //paycast camera plane
    double      sdistx;
    double      sdisty;
    double      ddistx;
    double      ddisty;
    double      perpwalldist;
    //what direction to step in x or y-direction (either +1 or -1)
    int         stepx;
    int         stepy;
    int         side; //was a NS or a EW wall hit?
    int         mapx;
    int         mapy;
    double      olddirx;
    double      olddiry;
    double      oldplanex;
    double      oldplaney;
    int         hit; //was there a wall hit?

}               t_player;


typedef struct  s_mp3
{
    int          play;
    int          next_song;
    int          previou_song;
    int          pause;
    int          stop;
    int          current_track;
    int          quant_tracks;
    char         **track_names;
    char         **track_name_and_path;
    Mix_Music    *track;            //full MP3
    int          quant_technicals;
    Mix_Music    *technical;        //full MP3
    int          quant_sounds;
    Mix_Chunk    **sounds;           //short
}               t_mp3;


typedef struct      s_main
{
	int          ttf_quantity;
    SDL_Rect   pos[2];
    int           x, y;
    const char   *lables[2];
    int          selected[2];
    TTF_Font     *font;
    SDL_Color    color[2];
    SDL_Surface  *menus[2];
    SDL_Surface  *ptr_texture;
    int          status;
    int          lotary;
    int          quantity;
    char         **names;
    char         **names_with_path;
}                   t_main;


typedef struct      s_menu
{
    SDL_Surface  *ptr_texture;
    int          status;
    int          lotary;
    int          quantity;
    char         **names;
    char         **names_with_path;
}                   t_menu;


typedef struct      s_textures
{
    SDL_Surface  **ptr_texture;
    int          status;
    int          lotary;
    int          quantity;
    char         **names;
    char         **names_with_path;
}                   t_textures;

typedef struct      s_win
{
    double distWall;
    double distPlayer;
    int floorTexX;
    int floorTexY;
     double floorxwall;
     double floorywall; 
	int			nfpresent;
	int			ofpresent;
    /*------FPS-----*/
    Uint32     time;
    /*-------------*/
    t_map    map;
    int      coff;
    double      zoom;
    uint32_t color_ptr;
    uint32_t *pixel_ptr;
    uint32_t *pixel_ptr_two;
    int     drawstart;
    int     drawend;
    int     texy;
    int     texx;
    /*-------- Draw mini map ---------*/
    int     color;
    double  x0;
    double  y0;
    double  sx;
    double  sy;
    int     tmpc;
    int     tmpk;
    double  mapw;
    double  maph;
    int     minimapscale;
    int     minimapcx;
    int     minimapcy;
    double  width;
    double  height;
    /*-------- Rest functionality ----*/
    t_mp3           music;
    /*-------- Textures size ---------*/
    int              x;
    int              y;
    int              x1;
    int              y1;
    int              x2;
    int              y2;
    t_main           main;
    t_menu           menu;
    t_textures       walls;
    t_textures       flats;
    t_textures       skybox;
    t_textures       ceiling;
    /*--------------------------------*/
    SDL_Window      *window;
    SDL_Surface     *screensurface;
    SDL_Surface     *minimapsurface;
    SDL_Surface     *screentmp;
    SDL_Renderer    *gRenderer;
    SDL_Texture     *gTexture;
    SDL_Event       event;
    SDL_Event       mpthree;
    const Uint8*    currentKeyStates;
    t_player        *player;
    int             statement;       // is Running
    int             flag_menu_game;  // MENU 1 GAME 2
    const uint8_t   *key;
    uint32_t        *image;
    uint32_t        *miniimage;
}                   t_win;

//Inicializers
void            ft_init_window(t_win *c_cl);                      //Starts up SDL and creates window
int             ft_init_images(t_win *c_cl);                      //Initialize imgs
int             ft_init_audios(t_win *c_cl);
int             ft_initialize_main_screen(t_win *sc_controller);
void			ft_initialize_player(t_win *sc_controller);
void            ft_initialize_stract(t_win *sc_controller);
char            **ft_doublerelloc(char **src, char *word, int size);

//Errors
int             ft_truble_win(char *truble, t_win *c_cl);
int             ft_truble_img(char *truble, t_win *c_cl);
int             ft_truble_mix(char *truble, t_win *c_cl);
void			ft_error_main_sound(void);
void			ft_error_textures(char *str, char *strtow);
void			ft_error_minus(void);
void			ft_error_gen(char *av);
void			ft_error_hex(void);
void			ft_error_notdigit(void);
void			ft_error_gnl(t_win *params);
void			ft_error_alloc(void);
void			ft_error_len(void);
void			ft_error_buzz(void);
void			ft_error_dir(void);
void	        ft_error_play_space(void);
void	        ft_error_not_empty(void);
void			ft_error_ttf_init(void);
void			ft_error_folder(void);

//Main
void			ft_event_main(t_win *main);
void			ft_main_keyevent_down(t_win *c_ct);

//Menu
void			ft_event_manu(t_win *c_ct);
void			ft_menu_execute(t_win *c_ct);
//Menu handlekey
void 			ft_menu_keyevent_up(t_win *c_ct);
void   		 	ft_menu_keyevent_down(t_win *c_ct);

//Game
void    		ft_new_event_player(t_win *c_ct);
void			ft_game_execute(t_win *c_ct);
//Motion
void			ft_turnleft(t_win *game);
void			ft_turnright(t_win *game);
void			ft_move_forward(t_win *game);
void			ft_move_backward(t_win *game);
void			ft_move(t_win *game);
//Minimap
void			ft_putplayer_sdl(t_win *game);
void			ft_drawminimap(t_win *game);
void			ft_additonal_engine(t_win *game);

//Text
void			ft_set_text_position(t_win *main);

//Music Player
void			ft_malmix(t_win *c_cl);
void			ft_fill_playlist(t_win *c_cl, int quantity);
void			ft_bzero_music_params(t_win *c_cl);
void			ft_music_player_keyevent_down(t_win *c_ct);
void    		ft_music_execute(t_win *c_ct);
//Loads media
int             ft_music_play(t_win *c_cl);
int             ft_music_previous(t_win *c_ct);
int             ft_music_next(t_win *c_ct);
int             ft_hold_music(t_win *c_cl);

//Drawing
void			ft_draw_wall(t_win *game, int wall_side, int x, int y);
void			ft_line_direct(t_win *game);
void			ft_fill_rect(t_ft_rect *rect, t_win *game);
int				ft_rgb(int r, int g, int b, int	transp);
//Vizualization 
void			ft_visualization(t_win *c_ct);

//Parsing
void            ft_map_parsing(char *av, t_win *c_cl);
//Screens
void            ft_main(t_win *main);
int             ft_showmenu(t_win *main);
void            ft_menu(t_win *menu);
void            ft_game_core(t_win *game);
//Libs help function
int             ft_count_files(char *path, t_win *c_cl);



//Frees media and shuts down SDL
void            ft_bzero_move_params(t_win *game);

//Keyboard handler
void            ft_keyboard_handle(t_win *c_ct);

//Mouse handler
void            ft_mouse_handle(t_win *c_ct);
void            ft_core(t_win *c_ct);

//Loads individual image as texture
SDL_Surface*    ft_get_img(char *path);

//EXIT
void            sdl_close(t_win *sc_control);

void            ft_draw_c_f(t_win *game, int x, int y, double currentdist);

void		    ft_line_sdl(t_vector2d *vector, t_win *game);

#endif
