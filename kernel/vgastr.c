#include "vgastr.h"

void _strwrite (char *string)
{
  _strwrite_color (0, string);
}

void _strwrite_color (char color, char *string)
{
  char *p_strdst = (char *) (0xb8000);
  //指向显存的开始地址
  while (*string)
    {
      *p_strdst = *string++;
      p_strdst += 1;
      *p_strdst = color;
      p_strdst += 1;
    }
  return;
}

void printf (char *fmt, ...)
{
  _strwrite (fmt);
  return;
}

void printf_color (char color, char *fmt, ...)
{
  _strwrite_color (color, fmt);
  return;
}
