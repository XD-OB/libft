/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 03:31:40 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/19 07:34:23 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <inttypes.h>
# include "libft.h"

# define ABS(x) (x < 0) ? -x : x

# define D_BIAS 1023
# define LD_BIAS 16383
# define MAX_D 	2047
# define MAX_LD 32767

# define GREEN  "\x1b[0;32m"
# define RED    "\x1b[0;31m"
# define YELLOW "\x1b[0;33m"
# define BLUE   "\x1b[0;34m"
# define PURPLE "\x1b[0;35m"
# define CYAN   "\x1b[0;36m"
# define B_GREEN  "\x1b[1;32m"
# define B_RED    "\x1b[1;31m"
# define B_YELLOW "\x1b[1;33m"
# define B_BLUE   "\x1b[1;34m"
# define B_PURPLE "\x1b[1;35m"
# define B_CYAN   "\x1b[1;36m"
# define EOC    "\x1b[0m"

typedef struct		s_64
{
	size_t			mantissa:52;
	long			exponent:11;
	long			sign:1;
}					t_64;

typedef struct		s_80
{
	size_t			mantissa:63;
	long			int_b:1;
	long			exponent:15;
	long			sign:1;
}					t_80;

typedef union		u_double
{
	t_64			zone;
	double			d;
}					t_double;

typedef union		u_ldouble
{
	t_80			zone;
	long double		ld;
}					t_ldouble;

typedef struct		s_fmt
{
	char			convers;
	int				zero:1;
	int				dash:1;
	int				dollar:1;
	int				space:1;
	int				minus:1;
	int				plus:1;
	int				quote:1;
	int				star:1;
	int				cap_l:1;
	int				l:1;
	int				h:1;
	int				ll:1;
	int				hh:1;
	int				r:1;
	int				j:1;
	int				z:1;
	char			*color;
	long			precis;
	long			width;
	int				pos;
	int				argn;
	va_list			*arglist;
	struct s_fmt	*next;
}					t_fmt;

int					is_format(char c);
int					is_postflag(char c);
int					is_preflag(char c);
int					fmtlen(t_fmt *fmt);
void				sumstr(char **s1, char *s2, int base);
void				multstr(char **s1, char *s2, int base);
void				foisdix(char **str, int *len);
int					check_fill(va_list tmp, char *str, int pos, t_fmt *curr);
int					put_spstr(char *str);
int					put_spstrn(char *str, size_t n);
void				print_fmt(t_fmt *fmt);
void				free_fmt(t_fmt **fmt);
t_fmt				*parse_format(va_list ap, char *str, int *pflag);
t_fmt				*add_node(t_fmt *head, t_fmt *node);
unsigned long long	cast_xxoub(va_list ap, t_fmt *format);
long long int		cast_di(va_list ap, t_fmt *format);
char				*add_sign(char *str, int sign);
int					fill_tab(t_icase **icase, long *new_exp, long exp);
void				conv_k(t_chr **mychr, va_list ap);
void				conv_color(t_fmt *fmt, t_chr **mychr);
void				conv_c(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_s(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_p(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_o(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_b(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_di(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_xx(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_lfh(t_fmt *fmt, t_chr **mychr, t_double db, int is_g);
void				conv_ee(t_fmt *fmt, t_chr **mychr, t_double db, int is_g);
void				conv_d_efgh(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_llf(t_fmt *fmt, t_chr **mychr, va_list ap, int is_g);
void				conv_lee(t_fmt *fmt, t_chr **mychr, va_list ap, int is_g);
void				conv_percent(t_chr **mychr, t_fmt *fmt, va_list ap);
void				conv_di(t_fmt *fmt, t_chr **mychr, va_list ap);
void				conv_u(t_fmt *fmt, t_chr **mychr, va_list ap);
char				*xx_zero(t_fmt *fmt);
void				eprecis(char **str, long precis, long *carry, long *len_s);
void				precis_u(char **str, t_fmt *fmt, int nbr_len);
char				*all_zero_u(char *nbr, int precis);
void				conv_invalid(t_chr **mychr, t_fmt *format, va_list ap);
char				*ejoin(t_fmt *fmt, char *entier, char *fract, long *len);
char				*eprefix(t_fmt *fmt, long *len);
char				*o_n(t_fmt *fmt, char *num, int len_num);
char				*flag_r(char c);
void				flag_star(t_fmt *format, va_list ap);
void				flag_dash(char **nbr, int base);
void				flag_apostrophe(char **str, t_fmt *fmt);
int					flag_dollar(t_fmt *fmt);
char				*ft_dollar_cs(t_fmt *fmt);
int					ft_countnp(char *s);
char				*cut_str(char *str, int p1, int p2);
t_chr				*load_chr(char *format, t_fmt *fmt);
void				fill_chr(t_fmt *fmt, t_chr *chr, va_list ap);
int					put_chr(t_fmt *fmt, t_chr *chr);
int					put_chr_fd(int fd, t_fmt *fmt, t_chr *chr);
int					put_chr_nfd(int fd, size_t n, t_chr *chr);
char				*ft_strcolor(char *str);
int					adv_freeflag(char **str);
int					pre_d_calc(t_double db, t_chr **mychr, t_fmt *fmt, int g);
int					pre_ld_calc(t_ldouble db, t_chr **mychr, t_fmt *fmt, int g);
long				int_exp(long bin_exp, int bias);
long long			int_mants(long bin_mants, int bias);
char				*get_entierld(long exp, t_ldouble db, t_fmt *format);
char				*get_entier(long exp, long bin_mantis,
							int bias, t_fmt *format);
char				*get_fractld(long exp, t_ldouble db, t_fmt *format);
char				*get_fract(long exp, long bin_mantis,
							int bias, t_fmt *format);
void				int_add(char **tab, unsigned int *oldsize, int data);
char				*ft_pointjoin(t_fmt *fmt, char *s1, char *s2, long *len);
void				customize_f(t_fmt *fmt, char **str, long *len, int sign);
void				add_sign_f(t_fmt *fmt, char **str, long *len, int sign);
void				fprecis(char **str, long precis, long *carry, long base);
char				*width_di(t_fmt *fmt, char *nbr, int len_nbr, int sign);
void				calcul_entier(char **tab, int size, t_fmt *format);
void				calcul_fract(char **tab, int size, t_fmt *format);
void				custom_nanf(t_fmt *fmt, char **str, long *len);
void				custom_inff(t_fmt *fmt, char **str, long *len, int sign);
int					ft_printf(const char *format, ...);
int					ft_sprintf(char **str, const char *format, ...);
int					ft_vprintf(const char *format, va_list ap);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_dnprintf(int fd, size_t n, const char *format, ...);
int					ft_snprintf(char **str, size_t n, const char *format, ...);

#endif
