#!/bin/bash

DIR_PREFIX="/usr/local"
PROJ_NAME="ddmgr"
DIR_BIN="${DIR_PREFIX}/bin"
DIR_CONF="${DIR_PREFIX}/etc/${PROJ_NAME}"
FILE_EXEC="${DIR_BIN}/${PROJ_NAME}"

. ${DIR_CONF}/main.conf

function call_gen {
	${FILE_EXEC} ${HOSTS} ${FIREWALL} ${v4_PREFIX} ${v4_EXTERNAL} ${v6_PREFIX} ${DOMAIN} $1
}


function dns {
	echo "generating dns"
	
	serial=$(date +"%y%m%d%H%M")
	cat ${BASE_DNS} | sed "s/SERIAL/${serial}/g" > ${OUT_DNS}.ext
	call_gen dnsext >> ${OUT_DNS}.ext

	cat ${BASE_DNS} | sed "s/SERIAL/${serial}/g" > ${OUT_DNS}.int	
	call_gen dnsint >> ${OUT_DNS}.int
}

function dhcp {
	echo "generating dhcp"
	
	cp ${BASE_DHCP} ${OUT_DHCP}
	call_gen dhcp >> ${OUT_DHCP}
}

function dhcpv6 {
	echo "generating dhcpv6"
	
	cp ${BASE_DHCPv6} ${OUT_DHCPv6}
	call_gen dhcpv6 >> ${OUT_DHCPv6}
}

function nftables {
	echo "generating nftables"
	
	call_gen nftables > ${OUT_NFTABLES}
}

function rev6 {
	echo "generating rev6"

	cp ${BASE_DNS_REV6} ${OUT_DNS_REV6}
	call_gen rev6 >> ${OUT_DNS_REV6}
}

dns
dhcp
dhcpv6
nftables
rev6
