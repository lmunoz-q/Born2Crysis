# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/30 23:36:53 by mfischer          #+#    #+#              #
#    Updated: 2019/09/04 15:11:06 by mfischer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	mflib.a

#

INC_PATH	=	include/ .
SRCS		=	src/math/mat_scale.c src/math/mat_translate.c src/math/vec_equal.c\
				src/math/matmat_multiply.c src/math/matrix_clear.c src/math/matrix_init.c \
				src/math/matvec_multiply.c src/math/vec_add.c src/math/vec_conversions.c \
				src/math/vec_crossproduct.c src/math/vec_dot.c src/math/vec_magnitude.c \
				src/math/vec_normalize.c src/math/vec_substract.c src/math/vector_clear.c \
				src/math/vector_init.c src/math/mat4_rotate.c \
				src/math/vecscalar_multiply.c src/math/vecscalar_add.c src/math/vecscalar_divide.c \
				src/math/vec_divide.c src/math/dist_pointplane.c \
				src/math/vec_get_normal.c src/math/vec_dist.c \
				src/math/vec_divide.c src/math/vec_multiply.c src/math/dist_pointplane.c \
				src/math/vec_get_normal.c src/math/vec_angle.c \
				src/string/mf_itoa.c src/string/mf_itoa_s.c src/string/mf_strnew.c \
				src/string/mf_strchr.c src/string/mf_strcpy.c src/string/mf_strclr.c \
				src/string/mf_strdup.c src/string/mf_strlen.c src/string/mf_strjoin.c \
				src/string/mf_atoi.c src/string/mf_isspace.c src/string/mf_strsub.c \
				src/string/mf_atof.c src/string/mf_isdigit.c src/string/mf_strnchr.c \
				src/string/mf_strcmp.c src/string/mf_strstr.c src/string/mf_strncpy.c \
				src/string/mf_uitoa.c src/string/mf_toupper.c src/string/mf_strtoupper.c \
				src/string/mf_strrchr.c \
				src/files/get_next_line.c \
				src/list/mf_lstadd.c src/list/mf_lstcount.c src/list/mf_lstdel.c \
				src/list/mf_lstdelone.c src/list/mf_lstiter.c src/list/mf_lstmap.c \
				src/list/mf_lstnew.c \
				src/list2/list2_at.c src/list2/list2_create.c src/list2/list2_destroy.c \
				src/list2/list2_pop.c src/list2/list2_popback.c src/list2/list2_push.c \
				src/list2/list2_pushback.c src/list2/list2_toarray.c src/list2/list2_delete.c \
				src/list2/list2_insert.c \
				src/memory/mf_memset.c src/memory/mf_bzero.c src/memory/mf_memalloc.c \
				src/memory/mf_memcpy.c \
				src/stack/stack_create.c src/stack/stack_destroy.c src/stack/stack_pop.c \
				src/stack/stack_push.c src/stack/stack_state.c src/stack/stack_top.c \
				src/stack/stack_reset.c src/stack/stack_next_to_top.c \
				src/var/mf_swap.c src/var/mf_min.c src/var/mf_clamp.c \
				src/var/mf_wrap_around.c \
				src/sort/mf_quicksort.c src/sort/mf_quicksort_c.c \
				src/math/quaternions.c \
				src/printf/mf_printf.c src/printf/mf_parse.c src/printf/mf_s.c src/printf/mf_dispatch.c src/printf/mf_f.c \
				src/printf/mf_dui.c src/printf/mf_p.c src/printf/mf_s.c src/printf/mf_o.c src/printf/mf_c.c src/printf/mf_x.c \
				src/printf/mf_na.c src/printf/mf_get.c src/printf/mf_percent_func.c src/printf/mf_subparse.c \
				src/printf/mf_float_utils.c src/printf/mf_subprint.c \
				src/rand/mf_rand.c src/rand/mf_seed.c

#

CC			=	gcc
CL			=	ar rc
RAN			=	ranlib
CFLAGS		+=	-Wall -Werror -Wextra -g -flto -O3
CFLAGS		+=	$(foreach d, $(INC_PATH), -I $d)
OBJS		=	$(patsubst src/%.c,obj/%.o,$(SRCS))
RM			=	rm -rf

#

all			:	$(OBJS) $(NAME)

$(OBJS)		:	| obj

obj			:	
		@mkdir	-p $@
		@mkdir	-p $@/math/vec3d
		@mkdir	-p $@/string
		@mkdir	-p $@/files
		@mkdir	-p $@/list
		@mkdir	-p $@/list2
		@mkdir	-p $@/memory
		@mkdir	-p $@/stack
		@mkdir	-p $@/var
		@mkdir	-p $@/threadpool
		@mkdir	-p $@/sort
		@mkdir	-p $@/printf
		@mkdir	-p $@/rand

obj/%.o		:	src/%.c
		@echo	"\033[31m--| Creation du $@ |--\033[0m"
		$(CC)	$(CFLAGS) -c $< -o $@
		@echo	"\033[32m[DONE]\033[0m"

$(NAME)		:	$(OBJS)
		@echo	"\033[31m--| Creation de mylib.a : $@ |--\033[0m"
		$(CL)	$(NAME) $^
		$(RAN)	$(NAME)
		@echo	"\033[32m[DONE]\033[0m\n"

clean		:
		@echo	"\033[31m--| Suppression des .0 |--\033[0m"
		$(RM) $(OBJS)
		@echo	"\033[32m[DONE]\033[0m\n"

fclean		:	clean
		@echo	"\033[31m--| Suppression de mylib.a : $(NAME) |--\033[0m"
		$(RM)	$(NAME)
		$(RM)	obj

re			:	fclean all

.PHONY		:	clean fclean re all

