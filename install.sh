#!/bin/bash

INSTALL_DIR="/opt/dhcp_dns_manager"

if [[ -d ${INSTALL_DIR} ]]; then
	echo "${INSTALL_DIR} exists, updating main only"
	cp main ${INSTALL_DIR}
	echo "done"
else
	echo "${INSTALL_DIR} doesn't exists, copying program and examples"
	mkdir ${INSTALL_DIR}
	cp main ${INSTALL_DIR}
	cp -r examples/* ${INSTALL_DIR}
	echo "done"
fi

