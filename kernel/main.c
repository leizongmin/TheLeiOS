#include "vgastr.h"

void
main ()
{
  k_vgastr_write ("GNU style. Like the Allman and Whitesmiths styles, GNU "
                  "style puts braces on a line by themselves, indented by two "
                  "spaces, except when opening a function definition, where "
                  "they are not indented. In either case, the contained code "
                  "is indented by two spaces from the braces.!\n");
  k_vgastr_set_color (0xb);
  k_vgastr_write ("Welcome to the LeiOS!\n");
  //  k_vgastr_set_color (0xf);
  //  k_vgastr_write ("Going to done.\n");
}
