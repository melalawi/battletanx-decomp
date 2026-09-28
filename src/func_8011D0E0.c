/* Calls func_8011D0D0 with a literal 0x400 and nothing else; the frame exists only to
 * hold the return address across that call.
 * There is no load or store of data, so no field types are involved: the single
 * argument is an immediate word. */

extern void func_8011D0D0(int size);

void func_8011D0E0(void) {
    func_8011D0D0(0x400);
}
