#include "vgastr.h"

void
welcome ()
{
  k_vgastr_reset (K_VGASTR_COLOR_DARK_GREY, 178);

  k_vgastr_set_color (K_VGASTR_COLOR_LIGHT_BROWN);
  for (int i = 0; i < 400; i++)
    {
      k_vgastr_write ('+');
    }

  k_vgastr_set_color (K_VGASTR_COLOR_LIGHT_GREEN);
  k_vgastr_write_string ("    Welcome to the LeiOS!\n\n");
  k_vgastr_set_color (K_VGASTR_COLOR_LIGHT_CYAN);
  k_vgastr_write_string (
      "    Homepage: https://github.com/leizongmin/TheLeiOS\n\n");

  k_vgastr_set_color (K_VGASTR_COLOR_LIGHT_BROWN);
  for (int i = 0; i < 400; i++)
    {
      k_vgastr_write ('+');
    }
}

void
main ()
{
  welcome ();
}
