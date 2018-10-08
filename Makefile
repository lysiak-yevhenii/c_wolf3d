# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/07 02:47:01 by ylisyak           #+#    #+#              #
#    Updated: 2018/10/07 06:26:00 by ylisyak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	wolf3d

FLAGS	=	-Wall -Werror -Wextra

DIR_H	=	./include/

DIR_S	=	./src/

DIR_O	=	./tmp/

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft 

# ft SDL2
SDL		= ./sdl/sdl2/2.0.8/lib/
SDL_LIB	= $(addprefix $(FT),libSDL2.a)
SDL_INC	= -I ./sdl/sdl2/2.0.8/include/SDL2/
SDL_LNK	= -L ./sdl/sdl2/2.0.8/lib/ -l SDL2

# ft SDL2_image
SDL_IMG	= ./sdl/sdl2_image/2.0.3/lib/
IMG_LIB	= $(addprefix $(FT),libSDL2_image.a)
IMG_INC	= -I ./sdl/sdl2_image/2.0.3/include/SDL2/
IMG_LNK	= -L ./sdl/sdl2_image/2.0.3/lib/ -l SDL2_image

# ft SDL2_mixer
SDL_MIX	= ./sdl/sdl2_mixer/2.0.2_3/lib/
MIX_LIB	= $(addprefix $(FT),libSDL2_mixer.a)
MIX_INC	= -I ./sdl/sdl2_mixer/2.0.2_3/include/SDL2/
MIX_LNK	= -L ./sdl/sdl2_mixer/2.0.2_3/lib/ -l SDL2_mixer

# ft SDL2_ttf
SDL_TTF	= ./sdl/sdl2_ttf/2.0.14/lib/
TTF_LIB	= $(addprefix $(FT),libSDL2_mixer.a)
TTF_INC	= -I ./sdl/sdl2_ttf/2.0.14/include/SDL2/
TTF_LNK	= -L ./sdl/sdl2_ttf/2.0.14/lib/ -l SDL2_ttf

SRC		=	main.c \
			ft_map_parsing.c \
			error.c \
			ft_inicialize_state.c \
			servicestuff.c \
			ft_images_call.c \
			ft_audio_call.c \
			ft_drawline.c \
			ft_game.c \
			ft_keyboard_controller.c \
			ft_main.c \
			ft_menu.c \

OBJ_P	=	$(addprefix $(DIR_O), $(SRC:.c=.o))

all:	tmp $(FT_LIB) $(NAME)

tmp:
	@mkdir -p $(DIR_O)

$(DIR_O)%.o:$(DIR_S)%.c
	@gcc $(FLAGS) $(FT_INC) $(SDL_INC) $(IMG_INC) $(MIX_INC) $(TTF_INC) -I $(DIR_H) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(NAME): $(OBJ_P)
	@gcc $(OBJ_P) $(SDL_LNK) $(IMG_LNK) $(MIX_LNK) $(TTF_LNK) $(FT_LNK) -lm  -o $(NAME)
	@say -v Karen "Compilation is finished."
	@echo "All is done!"

clean:
	@rm -rf $(DIR_O)
	@make -C $(FT) clean
	@say -v Karen "You deleted all object files."
	@echo "Objects files deleted"

fclean: clean
	@rm -fr .DS*
	@rm -rf $(NAME)
	@make -C $(FT) fclean
	@say -v Karen "You clean all files of the project. To use it again please recompile project."
	@echo "All is clear!"

re: fclean all
