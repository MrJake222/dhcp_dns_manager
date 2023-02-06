#!/bin/bash

DIR_PREFIX="/usr/local"
PROJ_NAME="ddmgr"
DIR_BIN="${DIR_PREFIX}/bin"
DIR_CONF="${DIR_PREFIX}/etc/${PROJ_NAME}"
FILE_EXEC="${DIR_BIN}/${PROJ_NAME}"
FILE_SCRIPT="${DIR_BIN}/${PROJ_NAME}_config"
FILE_SERVICE="/etc/systemd/system/ddmgr.service"

if [[ $# != 1 ]]; then
	echo "1 argument expected: [install/uninstall]"
	exit 1
fi

if [[ $1 == "install" ]]; then
	echo -n "installing exec in ${FILE_EXEC}... "
	cp main ${FILE_EXEC}
	echo "done"
	
	echo -n "installing config script in ${FILE_SCRIPT}... "
	cp install/gen_config.sh ${FILE_SCRIPT}
	echo "done"
	
	echo -n "installing service in ${FILE_SERVICE}... "
	cp install/ddmgr.service ${FILE_SERVICE}
	echo "done"

	if [[ ! -d ${DIR_CONF} ]]; then
		echo -n "conf dir ${DIR_CONF} doesn't exists, creating & copying examples... "
		mkdir ${DIR_CONF}
		cp -r examples/* ${DIR_CONF}
		echo "done"
	else
		echo "conf dir exists, pass."
	fi

elif [[ $1 == "uninstall" ]]; then
	echo -n "uninstalling... "
	rm ${FILE_EXEC}
	rm ${FILE_SCRIPT}
	rm ${FILE_SERVICE}
	rm -r ${DIR_CONF}
	echo "done"

else
	echo "invalid argument: $1"
fi

