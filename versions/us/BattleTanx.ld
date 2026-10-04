OUTPUT_ARCH(mips)
SECTIONS
{
  .text : { *(.text) }
  /DISCARD/ : { *(*) }
}
INCLUDE versions/us/symbols.ld
