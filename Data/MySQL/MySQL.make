#
# MySQL.make
#
# Makefile fragment for finding MySQL library
#

ifdef POCO_MYSQL_INCLUDE
INCLUDE += -I$(POCO_MYSQL_INCLUDE)
else
INCLUDE += -I./../include
INCLUDE += -I/usr/local/include/mysql
INCLUDE += -I/usr/include/mysql
INCLUDE += -I/usr/mysql/include/mysql
INCLUDE += -I/usr/local/mysql/include
INCLUDE += -I/usr/local/opt/mysql-client/include
INCLUDE += -I/usr/local/opt/mysql-client/include/mysql 
INCLUDE += -I/opt/homebrew/opt/mysql-client/include
INCLUDE += -I/opt/homebrew/opt/mysql-client/include/mysql
endif

ifdef POCO_MYSQL_LIB
SYSLIBS += -L$(POCO_MYSQL_LIB)
else
SYSLIBS += -L/usr/local/lib
SYSLIBS += -L/usr/local/lib$(LIB64SUFFIX)/mysql
SYSLIBS += -L/usr/lib$(LIB64SUFFIX)/mysql
SYSLIBS += -L/usr/mysql/lib$(LIB64SUFFIX)
SYSLIBS += -L/usr/mysql/lib$(LIB64SUFFIX)/mysql
SYSLIBS += -L/usr/local/mysql/lib$(LIB64SUFFIX)
SYSLIBS += -L/usr/local/opt/mysql-client/lib
SYSLIBS += -L/opt/homebrew/opt/mysql-client/lib
endif

# Note: linking order is important, do not change it.
SYSLIBS += -lmysqlclient -lz -lpthread -ldl
