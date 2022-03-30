/***********************************/
#ifndef MODULE_LOG_LEVEL
#define MODULE_LOG_LEVEL    LOG_DEBUG
#endif
/***********************************/
#include <stdio.h>
/***********************************/
#include "../include/module.h"
/***********************************/
#include "log/log.h"
/***********************************/
/***********************************/
#include "deps/trim/trim.h"
/***********************************/
/***********************************/

// `string_module` module definition
module(string_module) {
  defaults(string_module, CLIB_MODULE);
  void *private;

  char          * (*encode)(const unsigned char *string, size_t len);
  unsigned char * (*decode)(const char *encoded, size_t len);
};

// `string_module` module prototypes
static int  string_module_init(module(string_module) * exports);

static void string_module_deinit(module(string_module) * exports);

// `string_module` module exports
exports(string_module) {
  .init   = string_module_init,
  .deinit = string_module_deinit,
};

// `private` module definition
module(private) {
  define(private, CLIB_MODULE);
  char          * (*encode)(const unsigned char *string, size_t len);
  unsigned char * (*decode)(const char *encoded, size_t len);
};


// private `private` module string_decodesymbol
static char * string_module_private_string_decode(const unsigned char *string, size_t len) {
  log_trace("string_module_private_string_decode():%s/%d", string, len);
  return(trim(b64_decode(string, len)));
}


// private `private` module string_encode symbol
static char * string_module_private_string_encode(const unsigned char *string, size_t len) {
  log_trace("string_module_private_string_encode():%s/%d", string, len);
  return(trim(b64_encode(string, len)));
}


// `private` module exports
exports(private) {
  defaults(private, CLIB_MODULE_DEFAULT),
  .encode = string_module_private_string_encode,
  .decode = string_module_private_string_decode,
};


static char * string_module_decode(const unsigned char *string, size_t len) {
  log_trace("string_module_private_string_decode():%s/%d", string, len);
  return(require(private)->decode(string, len));
}


static char * string_module_encode(const unsigned char *string, size_t len) {
  log_trace("string_module_private_string_encode():%s/%d", string, len);
  return(require(private)->encode(string, len));
}


// `string_module` module initializer
static int string_module_init(module(string_module) *exports) {
  void debug_private(){
    if (0 != exports->private) {
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_YELLOW "init> NON PRIVATE MODE" AC_RESETALL);
    }else{
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_BLUE "init> PRIVATE MODE" AC_RESETALL);
    }
  }

  debug_private();
  exports->encode  = string_module_encode;
  exports->decode  = string_module_decode;
  exports->private = require(private);
  debug_private();

  return(0);
}


// `string_module` module deinitializer
static void string_module_deinit(module(string_module) *exports) {
  log_trace("string_module_deinit()");
  clib_module_free((module(private) *) exports->private);
}

