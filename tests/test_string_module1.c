/*******************/
#define MODULE_TEST_ENABLED    false
#define MODULE_EXEC_ENABLED    false
#define MODULE_LOG_LEVEL       LOG_INFO
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
  char *decoded_string = "Wed Mar 30 08:54:15 PM UTC 2022";
  char *encoded, *decoded;

  encoded = cm_string->encode(decoded_string, strlen(decoded_string));
  log_info("encoded %db string '%s' => %db string '%s'", strlen(decoded_string), decoded_string, strlen(encoded), encoded);
  decoded = cm_string->decode(encoded, strlen(encoded));
  log_info("decoded %db string '%s' => %db string '%s'", strlen(encoded), encoded, strlen(decoded), decoded);

  log_info("decoded strings OK");
  if (strcmp(decoded, decoded_string) == 0) {
  }else{
    log_fatal("failed to decode strings");
  }
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
