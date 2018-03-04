#include <mruby.h>
#include <mruby/array.h>
#include <mruby/value.h>

#include <stdlib.h>

typedef struct {
  mrb_int z;
  mrb_int index;
  mrb_value v;
} _stable_sort_container_;

static int container_compare(const void *a, const void *b )
{
  _stable_sort_container_* x = (_stable_sort_container_*)a;
  _stable_sort_container_* y = (_stable_sort_container_*)b;
  return x->z != y->z ? x->z - y->z : x->index - y->index;
}

static mrb_value mrb_sort_ab_sort_ab(mrb_state *mrb, mrb_value ary)
{
  mrb_int i,len,z;
  mrb_value v, result, tmp;
  mrb_sym name;
  _stable_sort_container_ *que;

  mrb_get_args(mrb, "n", &name);
  len = RARRAY_LEN(ary);
  que = malloc(sizeof(_stable_sort_container_)*len);

  for (i = 0; i < len; i++) {
    v = RARRAY_PTR(ary)[i];

    tmp = mrb_funcall_argv(mrb,v,name,0,NULL);

    z = mrb_fixnum(tmp);
    que[i].z = z;
    que[i].index = i;
    que[i].v = v;
  }

  // sorting...
  qsort(que,len,sizeof(_stable_sort_container_),container_compare);

  result = mrb_ary_new_capa(mrb, len);
  for( int i=0; i<len; i++) {
    mrb_ary_push(mrb,result,que[i].v);
  }
  free(que);

  return result;
}

void mrb_mruby_stable_sort_gem_init(mrb_state *mrb)
{
  struct RClass * a = mrb->array_class;

  mrb_define_method(mrb, a, "stable_sort", mrb_sort_ab_sort_ab, MRB_ARGS_REQ(1));
}

void mrb_mruby_stable_sort_gem_final(mrb_state *mrb)
{
}
