#!/bin/bash

INSTALL_DIR="/opt/dhcp_dns_manager"

OUT_DNS_INT="dns_int.txt"
OUT_DNS_EXT="dns_ext.txt"
OUT_DHCP="dhcp.txt"
OUT_DHCPv6="dhcpv6.txt"

BASE_DNS="${INSTALL_DIR}/base_dns.txt"
BASE_DHCP="${INSTALL_DIR}/base_dhcp.txt"
BASE_DHCPv6="${INSTALL_DIR}/base_dhcpv6.txt"


GENERATOR="${INSTALL_DIR}/main"
HOSTS="${INSTALL_DIR}/hosts.txt"
FIREWALL="${INSTALL_DIR}/firewall.txt"
v4_PREFIX="192.168"
v4_EXTERNAL="8.8.8.8"
v6_PREFIX="fd00"
function call_gen {
	${GENERATOR} ${HOSTS} ${FIREWALL} ${v4_PREFIX} ${v4_EXTERNAL} ${v6_PREFIX} $1
}

function dns {
	echo "generating dns"
	
	serial=$(date +"%y%m%d%H%M")
	cat ${BASE_DNS} | sed "s/SERIAL/${serial} ; serial/g" > ${OUT_DNS_INT}
	cat ${BASE_DNS} | sed "s/SERIAL/${serial} ; serial/g" > ${OUT_DNS_EXT}
	call_gen dnsint >> ${OUT_DNS_INT}
	call_gen dnsext >> ${OUT_DNS_EXT}
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

function iptables {
	# TODO
	echo "generating iptables"
	echo "unimplemented"
}

function iptables6 {
	# TODO
	echo "generating iptables6"
	echo "unimplemented"
}

dns
dhcp
dhcpv6
iptables
iptables6