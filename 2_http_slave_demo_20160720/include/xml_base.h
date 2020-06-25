#ifndef _XML_BASE_H
#define XML_BASE_H_
#include "common.h"
#include "xml_common.h"

extern mxml_node_t * xml_create(char * name);
extern mxml_node_t * add_element(mxml_node_t * root, char * name, bool has_ns);
extern mxml_node_t * add_node_str(mxml_node_t * f_node, char * name, char * value);
extern mxml_node_t * add_node_num(mxml_node_t * f_node, char * name, int value);
extern mxml_node_t * xml_parse_Get_Group(mxml_node_t * node, char * name, char * attr, char * attr_value);
extern int mxmlCmpIgnoreNamespace(char * ElementName, const char * Name);
extern mxml_node_t *mxmlFindElementIns(mxml_node_t * node,	/* I - Current node */
                   mxml_node_t * top,	/* I - Top node */
                   const char * name,	/* I - Element name(ignore namespace) or NULL for any */
                   const char * attr,	/* I - Attribute name, or NULL for none */
                   const char * value,	/* I - Attribute value, or NULL for any */
                   int         descend);	/* I - Descend into tree - MXML_DESCEND, MXML_NO_DESCEND, or MXML_DESCEND_FIRST */

extern void add_node_attr(mxml_node_t * node, char * attr, char * value);
extern int xml_parse_Get_Integer(mxml_node_t * node, char * name, int * integer);
extern char * xml_parse_GetString(mxml_node_t * node, const char * name, char * str);

extern sint32 uint_ip_to_string(char * str_ip, sint32 str_size, uint32 int_ip);
extern uint32 string_ip_to_uint(char * str_ip);
extern int ParseTimeSpan(char * tm_buf, SYSTIME * tm);
extern char * xml_parse_GetOpaque(mxml_node_t * node, const char * name, char * str);

#endif 
