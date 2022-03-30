/*******************/
#include <stdio.h>
#include <string.h>
/*******************/
#define MODULE_TEST_ENABLED    false
#define MODULE_EXEC_ENABLED    false
#define MODULE_LOG_LEVEL       LOG_TRACE
/*******************/
#include "include/module.h"
/*******************/
#include "log/log.c"
/*******************/
#include "src/string_module.c"
/*******************/


void init(){
  log_set_level(MODULE_LOG_LEVEL);
}


void module_hook(){
  char *untrimmed_string = "       Wed Mar 30 08:54:15 PM UTC 2022          ";
  char *trimmed, *ltrimmed, *rtrimmed;


  void  do_trim(){
    trimmed = cm_string->trim(untrimmed_string);
    log_info("trimed %db string '%s' => %db string '%s'", strlen(untrimmed_string), untrimmed_string, strlen(trimmed), trimmed);
  }


  void  do_ltrim(){
    ltrimmed = cm_string->ltrim(untrimmed_string);
    log_info("left trimed %db string '%s' => %db string '%s'", strlen(untrimmed_string), untrimmed_string, strlen(ltrimmed), ltrimmed);
  }


  void do_rtrim(){
    rtrimmed = cm_string->rtrim(untrimmed_string);
    log_info("right trimed %db string '%s' => %db string '%s'", strlen(untrimmed_string), untrimmed_string, strlen(rtrimmed), rtrimmed);
  }

  do_trim();
  do_ltrim();
  do_rtrim();
}


/*******************/
void module_lifecycle(){
  pre();
  if (MODULE_TEST_ENABLED) {
    test();
  }
  if (MODULE_EXEC_ENABLED) {
    exec();
  }
  module_hook();
  post();
}


int main(void) {
  init();
  module_lifecycle();
  return(0);
}
/*******************/
