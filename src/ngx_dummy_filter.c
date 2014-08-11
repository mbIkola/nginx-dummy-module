/*
 * What i've felt, what i've known
 * never shined through in what i've shown.
 * never be, never see,
 * Won't see what mught have been. 
 *
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>



/** 
 * Postconfiguration callback called after parsing the http configuration. 
 */
static ngx_int_t postconfiguration(ngx_conf_t *cf);
/* 
 * And nothing else matters.  
 *
static ngx_int_t (*preconfiguration)(ngx_conf_t *cf)                                     = NULL;
static void *    (*create_main_configuration)(ngx_conf_t *cf)                            = NULL;
static char *    (*init_main_configuration)(ngx_conf_t *cf, void *conf)                  = NULL;
static void *    (*create_server_configuration)(ngx_conf_t *cf)                          = NULL;
static char *    (*merge_server_configuration)(ngx_conf_t *cf, void *prev, void *conf)   = NULL;
static void *    (*create_location_configuration)(ngx_conf_t *cf)                        = NULL;
static char *    (*merge_locaction_configuration)(ngx_conf_t *cf, void *prev, void *conf)= NULL;
*/




/** 
 * Standard module definitions. Struct called 'module context' with meaning "Set of callbacks 
 *  for module initialization. " 
 */
static ngx_http_module_t ngx_http_dummy_filter_ctx = {
         NULL, // preconfiguration, /* preconfiguration */
         postconfiguration, /* postconfiguration */
         NULL, // create_main_configuration, /* create main configuration */
         NULL, // init_main_configuration, /* init main configuration */
         NULL, // create_server_configuration, /* create server configuration */
         NULL, // merge_server_configuration, /* merge server configuration */
         NULL, // create_location_configuration, /* create location configuration */
         NULL, // merge_location_configuration /* merge location configuration */
};

/**
 * and exported module definitions 
 * Should not be declared with extern directive (all declarations without static assumed  as 'extern' 
 * and fucking nginx build scripts generates warnign on this
 * --add-module=[module-name] should match with name of ngx_module_t struct, otherwise 
 *  magic wont happen
 **/ 
ngx_module_t ngx_http_dummy_filter = {
    NGX_MODULE_V1,
    &ngx_http_dummy_filter_ctx, /* module context */
    NULL, /* module directives here */
    NGX_HTTP_MODULE, /* module type, like NGX_EVENT_MODULE, NGX_MAIL_MODULE, etc  */
    NULL, /* init master    im pulling your strings */
    NULL, /* init module    twisting your mind and smashing your dreams*/
    NULL, /* init process   blinded by me you cant see a strings */
    NULL, /* init thread    just call my name cause ill hear your scream */
    NULL, /* exit thread    come crawling faster  */
    NULL, /* exit process   your life burns faster  */
    NULL, /* exit master    obey your master  */
    NGX_MODULE_V1_PADDING
};





/** 
 *  local variables to store original header and body filters. 
 *  There are to many ways to implement requested. We'll just override 
 *  global pointers to next_body_filter/next_header_filter (it's looks like 
 *  we insert our own handler to nginx headers list) 
 **/ 
static ngx_http_output_header_filter_pt original_header_filter;
static ngx_http_output_body_filter_pt   original_body_filter;
static ngx_int_t dummy_header_filter(ngx_http_request_t *request ) 
{
    return original_header_filter(request); /* as described in docs never should  be null */
}
static ngx_int_t dummy_body_filter(ngx_http_request_t *request, ngx_chain_t *in)  
{
    return original_body_filter(request, in); 
}

/**
 * Postconfiguration callback called after parsing the http configuration. 
 */
ngx_int_t postconfiguration(ngx_conf_t *cf) 
{
    original_header_filter = ngx_http_top_header_filter; 
    original_body_filter   = ngx_http_top_body_filter; 


    ngx_http_top_header_filter = dummy_header_filter; 
    ngx_http_top_body_filter   = dummy_body_filter ; 

    return NGX_OK; 
}







