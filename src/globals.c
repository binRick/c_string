#include <stdio.h>
#include <string.h>

/*******************/
module(string_module) * cm_string;


/*******************/


/*******************/
void pre(void) {
  log_set_level(MODULE_LOG_LEVEL);
  cm_string = require(string_module);
}


/*******************/
void test(void) {
}


/*******************/


/*******************/
void exec(void){
  log_info("string exec>");
}


/*******************/


/*******************/
void post(void) {
  log_debug("string unload>");
  clib_module_free(cm_string);
}


/*******************/


/*******************/
