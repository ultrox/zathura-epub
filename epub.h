/* See LICENSE file for license and copyright information */

#ifndef EPUB_H
#define EPUB_H

#include <zathura/plugin-api.h>

/**
 * Opens a new document
 *
 * @param document The document
 * @return ZATHURA_ERROR_OK if no error occured
 */
zathura_error_t epub_document_open(zathura_document_t* document);

#endif // EPUB_H
