/*
 * FileName:
 * Author:         luny  Version: 1.0  Date: 2014-5-5
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

#ifndef _ISAPI_XMLUTIL_H_
#define _ISAPI_XMLUTIL_H_

#include "mxml.h"
#include "goahead.h"
#include "isapi_local.h"

mxml_node_t * xml_create(char * name);
mxml_node_t * add_element(mxml_node_t * root, char * name, bool has_ns);
void add_node_attr(mxml_node_t * node, char * attr, char * value);
mxml_node_t * add_node_str(mxml_node_t * f_node, char * name, char * value);
mxml_node_t * add_node_num(mxml_node_t * f_node, char * name, int value);
mxml_node_t * xml_parse_Get_Group(mxml_node_t * node, char * name, char * attr, char * attr_value);
int xml_parse_Get_Integer(mxml_node_t * node, char * name, int * integer);
char * xml_parse_GetString(mxml_node_t * node, const char * name, char * str);
char * xml_parse_GetOpaque(mxml_node_t * node, const char * name, char * str);
int GenHtml(Webs * wp, char * html_buf, int code);
int GenXmlResponseStatus(char * xml_buf, int bufsize, char  *requestURL, int statuscode, int substatuscode);
int GetWebsInputData(Webs * wp, char *cmdbuf, int size);

#endif
