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

  char * (*trim)(char *string);
  char * (*trim_right)(char *string);
  char * (*trim_left)(char *string);
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
  char * (*trim)(char *string);
  char * (*trim_right)(char *string);
  char * (*trim_left)(char *string);
};


static char * string_module_private_string_trim_right(char *string){
  log_trace("right trim():%s/%d", string);
  char *ns;
  char os[1024];

  sprintf(&os, "%s", string);
  ns = trim_right(os);
  return(ns);
}


static char * string_module_private_string_trim_left(char *string){
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
  .trim = string_module_private_string_trim,
};


static char * string_module_trim(char *string){
  log_trace("string_module_trim():%s/%d", string);
  return(require(private)->trim(string));
}


static char * string_module_trim_left(char *string){
  log_trace("string_module_trim_left():%s/%d", string);
  return(require(private)->trim_left(string));
}


static char * string_module_trim_right(char *string){
  log_trace("string_module_trim_right():%s/%d", string);
  return(require(private)->trim_right(string));
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
  exports->trim       = string_module_trim;
  exports->trim_left  = string_module_trim_left;
  exports->trim_right = string_module_trim_right;
  exports->private    = require(private);
  debug_private();

  return(0);
}


// `string_module` module deinitializer
static void string_module_deinit(module(string_module) *exports) {
  log_trace("string_module_deinit()");
  clib_module_free((module(private) *) exports->private);
}

