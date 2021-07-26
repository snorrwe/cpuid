#include "cq.h"

#include <assert.h>
#include <stdio.h>

union ax {
  unsigned e;
  /**
   * From table 3-17
   */
  struct {
    unsigned type : 5;
    unsigned lvl : 3;
  } b;
};

union bx {
  unsigned e;
  /**
   * From table 3-17
   */
  struct {
    unsigned linesz_ml : 12;
    unsigned parts_ml : 10;
    unsigned ways_ml : 10;
  } b;
};

void cq_print_cache_info(FILE *out, struct cq_cache_info const *info) {
  assert(info != NULL);
  const char *const units[] = {"  B", "KiB", "MiB", "GiB", NULL};
  const char *const *unit_str = &units[0];

  unsigned cache_sz = info->cache_size;
  while (cache_sz >= 1024) {
    if (*(unit_str + 1) == NULL) {
      break;
    }
    cache_sz /= 1024;
    ++unit_str;
  }
  fprintf(out, "(index %d) %3d%s L%d %s [Line Size: %dB]\n", info->cache_idx,
          cache_sz, *unit_str, info->lvl, cq_cache_type_str(info->type),
          info->linesz_ml + 1);
}

struct cq_cache_info cq_cache(int cache_idx) {
  union ax ax;
  union bx bx;
  unsigned cx, dx, cache_sz;

  ax.e = 0x4;
  cx = cache_idx;
  cq_cpuid(&ax.e, &bx.e, &cx, &dx);

  if (ax.b.type == CQ_TYPE_NULL) {
    return (struct cq_cache_info){.cache_idx = -1};
  }

  cache_sz = (bx.b.ways_ml + 1) * (bx.b.parts_ml + 1) * (bx.b.linesz_ml + 1) *
             (cx + 1);

  return (struct cq_cache_info){
      .cache_idx = cache_idx,
      .cache_size = cache_sz,
      .type = ax.b.type,
      .lvl = ax.b.lvl,
      .linesz_ml = bx.b.linesz_ml,
      .parts_ml = bx.b.parts_ml,
      .ways_ml = bx.b.ways_ml,
  };
}

const char *cq_cache_type_str(enum cq_cache_type ty) {
  static const char *const str[CQ_TYPE_MAX] = {
      [CQ_TYPE_NULL] = "NULL",
      [CQ_TYPE_DATA] = "DATA",
      [CQ_TYPE_INST] = "INST",
      [CQ_TYPE_UNIF] = "UNIF",
  };

  return str[ty];
}
