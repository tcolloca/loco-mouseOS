#include "../include/descriptors.h"
#include "../include/defs.h"

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access, byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}
