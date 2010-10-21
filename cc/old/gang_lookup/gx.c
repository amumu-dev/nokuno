/* gang look up */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 4096

struct gx_key {
  char *key_str;
  void *ptr;
};

struct gx {
  int nr_keys;
  int key_array_len;
  struct gx_key *keys;
};

struct gx *
gx_new()
{
  struct gx *g = malloc(sizeof(*g));
  g->nr_keys = 0;
  g->key_array_len = 0;
  g->keys = NULL;
  return g;
}

void
gx_free(struct gx *g)
{
  int i;
  for (i = 0; i < g->nr_keys; i++) {
    free(g->keys[i].key_str);
  }
  free(g->keys);
  free(g);
}

void
gx_add_item(struct gx *g, const char *key, void *ptr)
{
  if (g->nr_keys >= g->key_array_len) {
    g->key_array_len ++;
    g->key_array_len *= 5;
    g->key_array_len /= 4;
    g->keys = realloc(g->keys, sizeof(struct gx_key) * g->key_array_len);
  }
  g->keys[g->nr_keys].key_str = strdup(key);
  g->keys[g->nr_keys].ptr = ptr;
  g->nr_keys ++;
}

static int
compare_gx_key(const void *p, const void *q)
{
  const struct gx_key const *k1 = p;
  const struct gx_key const *k2 = q;
  return strcmp(k1->key_str, k2->key_str);
}

static void
sort_keys(struct gx *g)
{
  qsort(g->keys, g->nr_keys, sizeof(struct gx_key),
	compare_gx_key);
}

void
gx_scan(struct gx *g,
	int (*cb)(struct gx *, int ln, const char *key,
		  const char *line, void *ptr),
	const char *fn)
{
  FILE *fp = fopen(fn, "r");
  char buf[MAX_LINE_LEN];
  int key_idx, key_len;
  int ln;
  /**/
  if (!fp) {
    return ;
  }
  sort_keys(g);
  ln = 0;
  key_idx = 0;
  key_len = strlen(g->keys[key_idx].key_str);
  /**/
  while (fgets(buf, MAX_LINE_LEN, fp)) {
    int c, r;
    ln ++;
  again:
    r = strncmp(g->keys[key_idx].key_str, buf, key_len);
    if (r == 0) {
      if (buf[key_len] == ' ') {
	c = cb(g, ln, g->keys[key_idx].key_str,
	       &buf[key_len+1], g->keys[key_idx].ptr);
      } else if (buf[key_len] == '\n') {
	c = cb(g, ln, g->keys[key_idx].key_str,
	       NULL, g->keys[key_idx].ptr);
      } else {
	r = -1;
	c = 0;
      }
      if (c) {
	break;
      }
    }
    /*printf("line=(%s) key=(%s) key_len=(%d) r=(%d)\n\n",
      buf, g->keys[key_idx].key_str, key_len, r);*/
    if (r < 0) {
      key_idx ++;
      if (key_idx >= g->nr_keys) {
	break;
      }
      key_len = strlen(g->keys[key_idx].key_str);
      goto again;
    }
  }
  fclose(fp);
}
/* API functions */
struct gx *gx_new();
void gx_free(struct gx *g);
void gx_add_item(struct gx *g, const char *key, void *ptr);
void gx_scan(struct gx *g,
	     int (*cb)(struct gx *, int ln,
		       const char *key, const char *line,
		       void *ptr),
	     const char *fn);
/* test */
int
find_cb(struct gx *g, int ln, const char *key,
	const char *line, void *ptr)
{
  printf("line=(%d) key=(%s) found\n", ln, key);
  return 0;
}

int
main(int argc, char **argv)
{
  struct gx *g = gx_new();
  gx_add_item(g, "a", NULL);
  gx_add_item(g, "hello", NULL);
  gx_add_item(g, "\xff", NULL);
  gx_add_item(g, "abc", NULL);
  if (argc > 1) {
    gx_scan(g, find_cb, argv[1]);
  } else {
    gx_scan(g, find_cb, "input");
  }
  gx_free(g);
  return 0;
}
