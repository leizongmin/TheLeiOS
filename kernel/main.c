#include "vgastr.h"

void
main ()
{
  k_vgastr_reset (K_VGASTR_COLOR_DARK_GREY, 178);
  k_vgastr_write_string (
      "Like the Allman and Whitesmiths styles, GNU "
      "style puts braces on a line by themselves, indented by two "
      "spaces, except when opening a function definition, where "
      "they are not indented. In either case, the contained code "
      "is indented by two spaces from the braces.!\n");
  k_vgastr_set_color (K_VGASTR_COLOR_LIGHT_GREEN);
  k_vgastr_write_string ("Welcome to the LeiOS! ^_^\n");
  k_vgastr_set_color (K_VGASTR_COLOR_CYAN);
  k_vgastr_write_string ("Going to done.\n");
  k_vgastr_set_color (K_VGASTR_COLOR_LIGHT_RED);
  k_vgastr_write_string (
      "I/O from the guest is cached on the host but written through to the "
      "physical medium. This mode is slower and prone to scaling problems. "
      "Best used for small number of guests with lower I/O requirements. "
      "Suggested for guests that do not support a writeback cache (such as "
      "Red Hat Enterprise Linux 5.5 and earlier), where migration is not "
      "needed.\n");
}
