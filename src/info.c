#include "cq.h"

#include <stdio.h>

union ax {
  unsigned e;
  struct {
    unsigned stepping : 4;
    unsigned model : 4;
    unsigned family : 4;
    unsigned ty : 2;
    unsigned res1_ : 2;
    unsigned ext_model : 4;
    unsigned ext_family : 8;
    unsigned res0_ : 4;
  } b;
};

union bx {
    unsigned e;
    struct {
        unsigned brand_index: 7;
    } b;
};

void cq_cpuinfo(void) {

  union ax ax;
  union bx bx;
  unsigned cx, dx;

  ax.e = 1;
  cq_cpuid(&ax.e, &bx.e, &cx, &dx);

  const unsigned family_id =
      ax.b.family + ((ax.b.family == 0xf) * ax.b.ext_family);

  unsigned model_id = ax.b.model;
  if (ax.b.family == 6 || ax.b.family == 0xf) {
    model_id += ax.b.ext_model << 4;
  }

  printf("Family Id   : %d\n", family_id);
  printf("Model  Id   : %d\n", model_id);
  printf("Brand  Index: %d\n", bx.b.brand_index);

  const char *ty_str[4] = {
      "Original equipment manufacturer (OEM) Processor",
      "Intel Overdrive Processor",
      "Dual processor (not applicable to Intel486 processors)",
      "Reserved value "};
  printf("Processor type: %s\n", ty_str[ax.b.ty]);
}
