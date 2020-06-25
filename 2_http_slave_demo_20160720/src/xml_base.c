/****************************************************************
 * FileName:user_xml.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:xml process
 * *************************************************************/
#include "common.h"
#include "xml_common.h"
#if 1 //使用Mini-xml库解析xml文件，私库
mxml_node_t * xml_create(char * name)
{
    mxml_node_t * root, *node;

    root = mxmlNewXML("1.0");
    node = mxmlNewElement(root, name);
    mxmlElementSetAttr(node, "version", "1.0");
    mxmlElementSetAttr(node, "xmlns", "http://www.isapi.org/ver20/XMLSchema");
    return node;
}

/*
 * 函数功能描述：在root(父节点) 后面添加一个子节点
 * 输入参数 root：父节点
 * 输入参数 name：子节点名称
 * 输入参数has_ns：？
 * 函数返回值：新创建的节点
 * */
mxml_node_t * add_element(mxml_node_t * root, char * name, bool has_ns)
{
    mxml_node_t * node;

    node = mxmlNewElement(root, name);
    //mxmlElementSetAttr(node, name, NULL);
    //mxmlElementSetAttr(node, name, "1.0");
    //has_ns ? mxmlElementSetAttr(node, "version", "1.0"), mxmlElementSetAttr(node, "xmlns", "NULL") : 0;
    has_ns ? mxmlElementSetAttr(node, "version", "1.0"), mxmlElementSetAttr(node, "xmlns", "http://www.isapi.org/ver20/XMLSchema") : 0;
    return node;
}

void add_node_attr(mxml_node_t * node, char * attr, char * value)
{
    mxmlElementSetAttr(node, attr, value);
}

/*
 * 函数功能描述：在父节点后添加一个文本子节点
 * 输入参数：父节点
 * 输入参数：子节点名称
 * 输入参数：子节点的内容
 * 函数返回值：子节点
 * */
mxml_node_t * add_node_str(mxml_node_t * f_node, char * name, char * value)
{
    mxml_node_t * c_node;
    c_node = mxmlNewElement(f_node, name);
    mxmlNewText(c_node, 0, value);

    return c_node;
}

/*
 * 函数功能描述：在父节点后添加一个整数子节点
 * 输入参数：父节点
 * 输入参数：子节点名称
 * 输入参数：子节点的内容，一个整型数
 * 函数返回值：子节点
 * */
mxml_node_t * add_node_num(mxml_node_t * f_node, char * name, int value)
{
    mxml_node_t * c_node;

    c_node = mxmlNewElement(f_node, name);
    mxmlNewInteger(c_node, value);
    return c_node;
}

/*
 * 函数功能描述：
 * */
int mxmlCmpIgnoreNamespace(char * ElementName, const char * Name)
{
    char * ns = strchr(ElementName, ':');

    if( ns)
    {
        if( strcmp(ns+1, Name) == 0)
        {
            return 0;
        }
    }
    
    return strcmp(ElementName, Name);
}

mxml_node_t *				/* O - Element node or NULL */
mxmlFindElementIns(mxml_node_t * node,	/* I - Current node */
                   mxml_node_t * top,	/* I - Top node */
                   const char * name,	/* I - Element name(ignore namespace) or NULL for any */
                   const char * attr,	/* I - Attribute name, or NULL for none */
                   const char * value,	/* I - Attribute value, or NULL for any */
                   int         descend)	/* I - Descend into tree - MXML_DESCEND, MXML_NO_DESCEND, or MXML_DESCEND_FIRST */
{
    const char  * temp;         /* Current attribute value */


    /*
     * Range check input...
     */

    if (!node || !top || (!attr && value))
        return (NULL);

    /*
     * Start with the next node...
     */

    node = mxmlWalkNext(node, top, descend);

    /*
     * Loop until we find a matching element...
     */

    while (node != NULL)
    {
        /*
         * See if this node matches...
         */

        if (node->type == MXML_ELEMENT &&
                node->value.element.name &&
                (!name || !mxmlCmpIgnoreNamespace(node->value.element.name, name)))
        {
            /*
             * See if we need to check for an attribute...
             */

            if (!attr)
                return (node);          /* No attribute search, return it... */

            /*
             * Check for the attribute...
             */

            if ((temp = mxmlElementGetAttr(node, attr)) != NULL)
            {
                /*
                 * OK, we have the attribute, does it match?
                */

                if (!value || !strcmp(value, temp))
                    return (node);      /* Yes, return it... */
            }
        }

        /*
         * No match, move on to the next node...
         */

        if (descend == MXML_DESCEND)
            node = mxmlWalkNext(node, top, MXML_DESCEND);
        else
            node = node->next;
    }

    return (NULL);
}

/*
 * 函数功能描述：获取某个子节点的信息
 * 输入参数 node：父节点
 * 输入参数 name：子节点名称
 * 输入参数 attr：
 * 输出参数 attr_value：
 * 函数返回值：子节点
 * */
mxml_node_t * xml_parse_Get_Group(mxml_node_t * node, char * name, char * attr, char * attr_value)
{
    mxml_node_t * child = NULL;
    
    child = mxmlFindElementIns(node, node, (const char *)name, (const char *)attr, (const char *)attr_value, MXML_DESCEND);
    if (child == NULL)
    {
        return NULL;
    }
    return child;
}

int xml_parse_Get_Integer(mxml_node_t * node, char * name, int * integer)
{
    char str[1024] = {0};
    mxml_node_t * element = NULL;

    element = mxmlFindElementIns(node, node, name, NULL, NULL, MXML_DESCEND);
    if (element)
    {
        if (NULL == mxmlGetText(element, 0))
        {
            return -1;
        }
        strcpy(str, mxmlGetText(element, 0));

        *integer = atoi(str);
        return *integer;
    }
    return -1;
}

/*
 * 函数功能描述：从某个节点中获取某个字段(此字段是字符型的)的数据
 * 输入参数：节点名称
 * 输入参数：字段名称
 * 输出参数：字段对应的值
 * 函数返回值：NULL-失败 str-成功
 * */
char * xml_parse_GetString(mxml_node_t * node, const char * name, char * str)
{
    mxml_node_t * element = NULL;

    if (str == NULL)
    {
        return NULL;
    }

    element = mxmlFindElementIns(node, node, name, NULL, NULL, MXML_DESCEND);
    if (element)
    {
        if (NULL == mxmlGetText(element, 0))
        {
            return NULL;
        }
        strcpy(str, mxmlGetText(element, 0));
        //printf("<%s>%s</%s>\n", name, str, name);

        return str;
    }
    return NULL;
}
#endif
/*此函数需要重写*/
int web2master_log_querytype_switch(char * query_xml, int * pri_type, int * sec_type)
{
	printf("[%s]:Invalid function!!!! line:%d\n", __func__, __LINE__);
	return 0;
#if 0
    int i = 0, flag = -1;
    char oper[128] = {0}, oper_pri[32] = {0}, oper_sec[32] = {0};

    sscanf(query_xml, "%*[^/]%s", oper);
    sscanf(oper, "/%[^/]", oper_pri);
    sscanf(oper, "/%*[^/]/%s", oper_sec);

    //printf("[web2master_log_querytype_switch]oper:%s, oper_pri:%s, oper_sec:%s \n", oper, oper_pri, oper_sec);

    if (0 == strcmp(oper_pri, "Alarm"))
    {
        * pri_type = PRI_ALARM;
    }
    else if (0 == strcmp(oper_pri, "Operation"))
    {
        * pri_type = PRI_OPERATE;
    }
    else if (0 == strcmp(oper_pri, "Exception"))
    {
        * pri_type = PRI_ERROR;
    }
    else
    {
        * pri_type = -1;
    }

    if (PRI_ALARM == * pri_type)
    {
        if ((0 == strcmp(oper_sec, "All"))||(0 == strlen(oper_sec)))
        {
            * sec_type = -1;
        }
        else
        {
            for (i = 0; i < ALM_TYPE_MAX; i++)
            {
                if (0 == strcmp(oper_sec, log_type_alarm[i].weblogstr))
                {
                    * sec_type = log_type_alarm[i].hostlogindex;
                    flag = 1;
                    break;
                }
            }
            if (flag != 1)
            {
                * sec_type = -1;
            }
        }
    }
    else if (PRI_ERROR == * pri_type)
    {
        if ((0 == strcmp(oper_sec, "All"))||(0 == strlen(oper_sec)))
        {
            * sec_type = -1;
        }
        else
        {
            for (i = 0; i < ERR_TYPE_MAX; i++)
            {
                if (0 == strcmp(oper_sec, log_type_exception[i].weblogstr))
                {
                    * sec_type = log_type_exception[i].hostlogindex;
                    flag = 1;
                    break;
                }
            }
            if (flag != 1)
            {
                * sec_type = -1;
            }
        }
    }
    else if (PRI_OPERATE== * pri_type)
    {
        if ((0 == strcmp(oper_sec, "All"))||(0 == strlen(oper_sec)))
        {
            * sec_type = -1;
        }
        else
        {
            for (i = 0; i < OP_TYPE_MAX; i++)
            {
                if (0 == strcmp(oper_sec, log_type_operation[i].weblogstr))
                {
                    * sec_type = log_type_operation[i].hostlogindex;
                    flag = 1;
                    break;
                }
            }
            if (flag != 1)
            {
                * sec_type = -1;
            }
        }
    }
    else
    {
        * sec_type = -1;
    }

    return 0;
#endif
}

int ISDecodeCmd(char * buf, char isapi_cmd[][ISAPI_CMD_MAX_LEN])
{
    char * cp;
    int i = 0, j = 0;

    cp = buf;
    cp = cp + sizeof("\\ISAPI");

    while (*cp != '\0')
    {
        if (*cp == '/')
        {
            isapi_cmd[i][j] = '\0';
            i++, j = 0;
            cp++;
        }
        isapi_cmd[i][j] = *cp;
        cp++, j++;
    }
    isapi_cmd[i][j] = '\0';

    return i;
}

const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
#if 0
static char find_pos(char ch); 
char * base64_encode(const char * data, int data_len)
{
    //int data_len = strlen(data);
    int prepare = 0;
    int ret_len;
    int temp = 0;
    char * ret = NULL;
    char * f = NULL;
    int tmp = 0;
    char changed[4];
    int i = 0;

    ret_len = data_len / 3;
    temp = data_len % 3;
    if (temp > 0)
    {
        ret_len += 1;
    }
    ret_len = ret_len * 4 + 1;
    ret = (char *)malloc(ret_len);
    if (ret == NULL)
    {
        printf("No enough memory.\n");
        return NULL;
    }
    memset(ret, 0, ret_len);
    f = ret;
    while (tmp < data_len)
    {
        temp = 0;
        prepare = 0;
        memset(changed, '\0', 4);
        while (temp < 3)
        {
            //printf("tmp = %d\n", tmp);
            if (tmp >= data_len)
            {
                break;
            }
            prepare = ((prepare << 8) | (data[tmp] & 0xFF));
            tmp++;
            temp++;
        }
        prepare = (prepare << ((3 - temp) * 8));
        //printf("before for : temp = %d, prepare = %d\n", temp, prepare);
        for (i = 0; i < 4 ; i++)
        {
            if (temp < i)
            {
                changed[i] = 0x40;
            }
            else
            {
                changed[i] = (prepare >> ((3 - i) * 6)) & 0x3F;
            }             
            *f = base[changed[i]]; //MWARNING
            //printf("%.2X", changed[i]);
            f++;
        }
    }     
    *f = '\0';
    return ret;
}
#endif

static char find_pos(char ch)
{
    char * ptr = (char *)strrchr(base, ch); //the last position (the only) in base[]
    return (ptr - base);
}

char * base64_decode(const char * data, int data_len)
{
    int ret_len = (data_len / 4) * 3;
    int equal_count = 0;
    char * ret = NULL;
    char * f = NULL;
    int tmp = 0;
    int temp = 0;
    char need[3];
    int prepare = 0;
    int i = 0;
    if (*(data + data_len - 1) == '=')
    {
        equal_count += 1;
    }
    if (*(data + data_len - 2) == '=')
    {
        equal_count += 1;
    }
    if (*(data + data_len - 3) == '=')
    {
        equal_count += 1;
    }
    switch (equal_count)
    {
        case 0:
            ret_len += 4;//3
            break;
        case 1:
            ret_len += 4;//Ceil((6*3)/8)+1
            break;
        case 2:
            ret_len += 3;//Ceil((6*2)/8)+1
            break;
        case 3:
            ret_len += 2;//Ceil((6*1)/8)+1
            break;
    }
    ret = (char *)malloc(ret_len);
    if (ret == NULL)
    {
        printf("No enough memory.\n");
        return NULL;
    }
    memset(ret, 0, ret_len);
    f = ret;
    while (tmp < (data_len - equal_count))
    {
        temp = 0;
        prepare = 0;
        memset(need, 0, 3);
        while (temp < 4)
        {
            if (tmp >= (data_len - equal_count))
            {
                break;
            }
            prepare = (prepare << 6) | (find_pos(data[tmp]));
            temp++;
            tmp++;
        }
        prepare = prepare << ((4 - temp) * 6);
        for (i = 0; i < 3 ; i++)
        {
            if (i == temp)
            {
                break;
            }             
            *f = (char)((prepare >> ((2 - i) * 8)) & 0xFF);
            f++;
        }
    }
    *f = '\0';

    return ret;
}

