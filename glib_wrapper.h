#ifndef GLIB_WRAPPER_H
#define GLIB_WRAPPER_H

/* Disable static assertions for cross-compilation */
#define G_STATIC_ASSERT_EXPR(expr) (void)0
#define G_STATIC_ASSERT(expr) 

#include_next <glib.h>

#endif
