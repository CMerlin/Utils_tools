#ifndef _XML_PARSE_SECURITY_H_
#define _XML_PARSE_SECURITY_H_
#include "common.h"
#include "xml_common.h"

extern int GenXmlAdminAccesses(char * xml_buf, SECURITY_PORTINFO_S *portinfo);

extern int ParseXmlSecurityUsers(char * xml_buf, SECURITY_USER_S * user, int type); //type:0-put,1-post
extern int ParseXmlAdminAccesses(char * xml_buf, SECURITY_PORTINFO_S *portinfo);
#endif
