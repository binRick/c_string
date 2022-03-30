/***********************************/
#ifndef MODULE_LOG_LEVEL
#define MODULE_LOG_LEVEL    LOG_TRACE
#endif
/***********************************/
#include <stdio.h>
/***********************************/
#include "../include/module.h"
/***********************************/
#include "../deps/trim/trim.h"
/***********************************/
/***********************************/
/***********************************/
/***********************************/

// `string_module` module definition
module(string_module) {
  defaults(string_module, CLIB_MODULE);
  void *private;

  ///////////////////////////////////
  /*         PARSE STRING          */
  ///////////////////////////////////
  bool (*isnumeric)(const char *num, size_t len);
  ///////////////////////////////////
  ///////////////////////////////////
  /*         TRIM STRING           */
  ///////////////////////////////////
  char * (*trim)(char *string);
  char * (*rtrim)(char *string);
  char * (*ltrim)(char *string);
  ///////////////////////////////////
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
  bool (*isnumeric)(const char *num, size_t len);
  char * (*trim)(char *string);
  char * (*rtrim)(char *string);
  char * (*ltrim)(char *string);
};


static bool string_module_private_string_isnumeric(char *string, size_t len){
  bool res;
  int  is;

  is = is_number(string, len);
  log_trace("isnumeric(%s)/%d:%d", string, len, is);
  res = (is == 1) ? true : false;
  return(res);
}


static char * string_module_private_string_rtrim(char *string){
  log_trace("right trim():%s/%d", string);
  char *ns;
  char os[1024];

  sprintf(&os, "%s", string);
  ns = trim_right(os);
  return(ns);
}


static char * string_module_private_string_ltrim(char *string){
  log_trace("left trim():%s/%d", string);
  char *ns;
  char os[1024];

  sprintf(&os, "%s", string);
  ns = trim_left(os);
  return(ns);
}


static char * string_module_private_string_trim(char *string){
  log_trace("string_module_private_string_trim():%s/%d", string);
  char *ns;
  char os[1024];

  sprintf(&os, "%s", string);
  ns = trim(os);
  return(ns);
}


// `private` module exports
exports(private) {
  defaults(private, CLIB_MODULE_DEFAULT),
  .trim      = string_module_private_string_trim,
  .ltrim     = string_module_private_string_ltrim,
  .rtrim     = string_module_private_string_rtrim,
  .isnumeric = string_module_private_string_isnumeric,
};


static bool string_module_isnumeric(char *string, size_t len){
  log_trace("string_module_isnumeric():%s/%d", string);
  return(require(private)->isnumeric(string, len));
}


static char * string_module_trim(char *string){
  log_trace("string_module_trim():%s/%d", string);
  return(require(private)->trim(string));
}


static char * string_module_ltrim(char *string){
  log_trace("string_module_ltrim():%s/%d", string);
  return(require(private)->ltrim(string));
}


static char * string_module_rtrim(char *string){
  log_trace("string_module_trim():%s/%d", string);
  return(require(private)->rtrim(string));
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
  exports->isnumeric = string_module_isnumeric;
  exports->trim      = string_module_trim;
  exports->ltrim     = string_module_ltrim;
  exports->rtrim     = string_module_rtrim;
  exports->private   = require(private);
  debug_private();

  return(0);
}


// `string_module` module deinitializer
static void string_module_deinit(module(string_module) *exports) {
  log_trace("string_module_deinit()");
  clib_module_free((module(private) *) exports->private);
}

