
#include "mlx.h"

#include "font.c"


#define TEXTURE_MAX_CHAR 32
#define ATLAS_NB_CHAR 95

#define FONT_WIDTH	(font_atlas.width/ATLAS_NB_CHAR-2)


int mlx_put_image_to_window_scale(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y, int w, int h);

void mlx_int_copy_glyph(int c, unsigned char *data, int sl, int posx, int color)
{
  int j;
  int i;

  j = 0;
  while (j < font_atlas.height)
    {
      i = 0;
      while (i < FONT_WIDTH)
	{
	  data[j*sl + 4*(posx+i)] = color&0xFF;
	  data[j*sl + 4*(posx+i)+1] = (color>>8)&0xFF;
	  data[j*sl + 4*(posx+i)+2] = (color>>16)&0xFF;
	  data[j*sl + 4*(posx+i)+3] = 0xFF - font_atlas.pixel_data[j*font_atlas.width*4+c*font_atlas.width/ATLAS_NB_CHAR*4+i*4+3];
	  i ++;
	}
      j ++;
    }
}


void mlx_int_clean(unsigned char *data, int size_line)
{
  int i;

  i = 0;
  while (i < size_line*font_atlas.height)
    data[i++] = 0xFF;
}


int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string)
{
  static void *font = (void *)0;
  static unsigned char *data = (void *)0;
  static int size_line = 0;
  int bpp;
  int endian;
  int pos;
  int val;
  int dest_w;
  int dest_h;

  if (font == (void *)0)
    {
      font = mlx_new_image(mlx_ptr, TEXTURE_MAX_CHAR*FONT_WIDTH, font_atlas.height);
      data = (unsigned char *)mlx_get_data_addr(font, &bpp, &size_line, &endian);
    }

  dest_w = (TEXTURE_MAX_CHAR*FONT_WIDTH*5)/7;   /// ratio with X11 standard mlx_string_put
  dest_h = (font_atlas.height*5)/7;
  y = y - (dest_h*2)/3;

  mlx_int_clean(data, size_line);

  pos = 0;
  while (*string)
    {
      if (*string >= 32 && *string <= 127)
	val = *string - 32;
      else
	val = 31;
      mlx_int_copy_glyph(val, data, size_line, (pos%TEXTURE_MAX_CHAR)*(FONT_WIDTH), color);
      if (pos%TEXTURE_MAX_CHAR == TEXTURE_MAX_CHAR-1)
	{
	  mlx_put_image_to_window_scale(mlx_ptr, win_ptr, font, x+(pos/TEXTURE_MAX_CHAR)*dest_w, y, dest_w, dest_h);
	  mlx_do_sync(mlx_ptr);
	  mlx_int_clean(data, size_line);
	}
      pos ++;
      string ++;
    }
  if ((pos-1)%TEXTURE_MAX_CHAR != TEXTURE_MAX_CHAR-1)
    mlx_put_image_to_window_scale(mlx_ptr, win_ptr, font, x+(pos/TEXTURE_MAX_CHAR)*dest_w, y, dest_w, dest_h);
  mlx_do_sync(mlx_ptr);
  return (0);
}
