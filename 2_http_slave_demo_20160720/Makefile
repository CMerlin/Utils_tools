#********************************************************************
# * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
# * File Name:Makefile
# * Author:merlin
# * Version:v1
# * Data:20160613
# * Description:此makefile会将工程中的文件编译成一个isapi测试程序
# * History:
#********************************************************************

#编译器和归档
#CC = arm-hisiv200-linux-gcc 
CC = gcc
AR = ar rc

#头文件和编译选项
CFLAGS += -I./include -I./lib/mxml_2.9/include
CFLAGS += -Wall 

#编译库需要用到的源文件
#SRC_OBJECT = ./src/http_client.c ./src/common.c ./src/print.c ./src/user_sock.c
#OBJECT = ./src/http_client.o ./src/common.o ./src/print.o ./src/user_sock.o
SRC_OBJECT = ./src/http_client.c ./src/common.c ./src/print.c ./src/user_sock.c ./src/print.c
OBJECT = ./src/http_client.o ./src/common.o ./src/print.o ./src/user_sock.o ./src/print.o

#编译可执行程序需要用到的源文件
#BIN_SRC = ./src/test_demo.c ./src/isapi_api_client.c ./src/xml_base.c ./src/xml_parse_contentmgmt.c ./src/xml_parse_event.c ./src/xml_parse_security.c ./src/xml_parse_sundry.c ./src/xml_parse_system.c ./src/common.c ./src/print.c
#BIN_OBJECT = ./src/test_demo.o ./src/isapi_api_client.o ./src/xml_parse_contentmgmt.c ./src/xml_parse_event.o ./src/xml_parse_security.o ./src/xml_parse_sundry.o ./src/xml_parse_system.o ./src/xml_base.o ./src/common.o ./src/print.o
BIN_SRC = ./src/test_demo.c ./src/isapi_api_client.c ./src/xml_base.c ./src/xml_parse_contentmgmt.c ./src/xml_parse_event.c ./src/xml_parse_security.c ./src/xml_parse_sundry.c ./src/xml_parse_system.c ./src/common.c
BIN_OBJECT = ./src/test_demo.o ./src/isapi_api_client.o ./src/xml_parse_contentmgmt.c ./src/xml_parse_event.o ./src/xml_parse_security.o ./src/xml_parse_sundry.o ./src/xml_parse_system.o ./src/xml_base.o ./src/common.o



#链接库文件并指定生成的库文件名和可执行程序文件名
ifeq "$(CC)" "gcc"
	LDFLAGS = -L./lib/mxml_2.9/x86 -lmxml -lpthread -L./lib -lhttp_client_x86
	LIB_OBJECT = ./lib/libhttp_client_x86.a
	BIN_OBJECT = ./bin/X86_HTTP_CLIENT_20160720
else
	LDFLAGS = -L ./lib/mxml_2.9/arm -lmxml -lpthread -L./lib -lhttp_client_arm
	LIB_OBJECT = ./lib/libhttp_client_arm.a
	BIN_OBJECT = ./bin/ARM_HTTP_CLIENT_20160720
endif

.PHONY:all

#生成两个目标文件，静态库文件，一个是测试程序的可执行程序
all:$(LIB_OBJECT) $(BIN_OBJECT)
	@echo "****** Build lib file:"$(LIB_OBJECT)" ******"
	@echo "****** Build bin file:"$(BIN_OBJECT)" ******"

#生成静态库的目标文件
$(LIB_OBJECT):$(OBJECT)
	$(AR) $(LIB_OBJECT) $(OBJECT) 

#生成可执行程序
$(BIN_OBJECT) : $(BIN_SRC)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)


#删编译产生的中间文件
clean:
	$(RM) ./lib/*.a ./bin/* ./src/*.o

