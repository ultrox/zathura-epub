/* See LICENSE file for license and copyright information */

#include <stdlib.h>
#include <signal.h>
#include <glib.h>

#include "epub.h"

static void
randomize_string(char* dest, size_t length)
{
  char charset[] = "0123456789";

  for (int i = 0; i < length; i++) {
    size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
    dest[i] = charset[index];
  }
}

static char*
create_tmp_filename() {
  char* tmp_filename = g_strdup("/tmp/tmp-XXXXXX.pdf");
  randomize_string(tmp_filename + 9, 6);

  return tmp_filename;
}

void
register_functions(zathura_plugin_functions_t* functions)
{
  functions->document_open = epub_document_open;
}

ZATHURA_PLUGIN_REGISTER(
  "epub",
  0, 1, 0,
  register_functions,
  ZATHURA_PLUGIN_MIMETYPES({
    "application/epub+zip"
  })
)

zathura_error_t
epub_document_open(zathura_document_t* document)
{
  if (document == NULL) {
    return ZATHURA_ERROR_UNKNOWN;
  }

  const char* path = zathura_document_get_path(document);

  if (path == NULL) {
    return ZATHURA_ERROR_UNKNOWN;
  }

  /* create temporary file */
  char* tmp_filename = create_tmp_filename();

  /* convert epub to pdf */
  char* argv_convert[] = {
    "ebook-convert",
    (char*) path,
    tmp_filename,
    "--enable-heuristics",
    NULL
  };

  gint exit_status = 0;

  g_spawn_sync(
      NULL,
      argv_convert,
      NULL,
      G_SPAWN_SEARCH_PATH,
      NULL,
      NULL,
      NULL,
      NULL,
      &exit_status,
      NULL);

  if (exit_status != 0) {
    g_free(tmp_filename);
    return ZATHURA_ERROR_UNKNOWN;
  }

  /* create new instance of zathura */
  char* argv_zathura[] = {
    "zathura",
    tmp_filename,
    NULL
  };

  g_spawn_async(NULL, argv_zathura, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);

  /* cleanup */
  g_free(tmp_filename);

  /* kill calling process */
  raise(SIGKILL);

  return ZATHURA_ERROR_UNKNOWN;
}
