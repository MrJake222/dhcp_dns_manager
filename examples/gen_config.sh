#!/bin/bash

INSTALL_DIR="/opt/dhcp_dns_manager"

OUT_DNS="dns.txt"
OUT_DHCP="dhcp.txt"
OUT_DHCPv6="dhcpv6.txt"
OUT_NFTABLES="nftables.txt"

BASE_DNS_INT="${INSTALL_DIR}/base_dns_int.txt"
BASE_DNS_EXT="${INSTALL_DIR}/base_dns_ext.txt"
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
	cat ${BASE_DNS_EXT} | sed "s/SERIAL/${serial} ; serial/g" > ${OUT_DNS}
	call_gen dnsext		>> ${OUT_DNS}
	cat ${BASE_DNS_INT} >> ${OUT_DNS}
	call_gen dnsint		>> ${OUT_DNS}
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
	echo "generating iptables"
	
	call_gen nftables >> ${OUT_NFTABLES}
}

dns
dhcp
dhcpv6
nftables
