#!/bin/bash

# required duplication to get DIR_CONF
DIR_PREFIX="/usr/local"
PROJ_NAME="ddmgr"
DIR_BIN="${DIR_PREFIX}/bin"
DIR_CONF="${DIR_PREFIX}/etc/${PROJ_NAME}"

. ${DIR_CONF}/main.conf

function call_gen {
	${FILE_EXEC} ${HOSTS} ${FIREWALL} ${v4_PREFIX} ${v4_EXTERNAL} ${v6_PREFIX} ${DOMAIN} $1
}

function dns {
	echo -n "dns"
	
	call_gen dnsext >> ${OUT_DNS}.ext
	call_gen dnsint >> ${OUT_DNS}.int
}

function dhcp {
	echo -n "dhcp"
	
	call_gen dhcp >> ${OUT_DHCP}
}

function dhcpv6 {
	echo -n "dhcpv6"
	
	call_gen dhcpv6 >> ${OUT_DHCPv6}
}

function nftables {
	echo -n "nftables"
	
	call_gen nftables >> ${OUT_NFTABLES}
}

function rev6 {
	echo -n "rev6"

	call_gen rev6 >> ${OUT_DNS_REV6}
}


echo "preparing base files"

# dns
serial=$(date +"%y%m%d%H%M")
cat ${BASE_DNS} | sed "s/SERIAL/${serial}/g" > ${OUT_DNS}.ext
cat ${BASE_DNS} | sed "s/SERIAL/${serial}/g" > ${OUT_DNS}.int	

# dhcp
cp ${BASE_DHCP} ${OUT_DHCP}
cp ${BASE_DHCPv6} ${OUT_DHCPv6}

# nftables
: > ${OUT_NFTABLES}

# reverse v6 dns
cp ${BASE_DNS_REV6} ${OUT_DNS_REV6}

for dir in ${DIR_CONF_SUBNETS}/*; do
	echo "parsing $dir"
	
	. $dir/subnet.conf
	
	if [[ -z $v4_PREFIX ]]; then echo "v4_PREFIX not set in $dir"; exit 1; fi
	if [[ -z $v4_EXTERNAL ]]; then echo "v4_EXTERNAL not set in $dir"; exit 1; fi
	if [[ -z $v6_PREFIX ]]; then echo "v6_PREFIX not set in $dir"; exit 1; fi
	if [[ -z $DOMAIN ]]; then echo "DOMAIN not set in $dir"; exit 1; fi
	if [[ -z $HOSTS ]]; then echo "HOSTS not set in $dir"; exit 1; fi
	if [[ -z $FIREWALL ]]; then echo "FIREWALL not set in $dir"; exit 1; fi
	
	HOSTS=$dir/$HOSTS
	FIREWALL=$dir/$FIREWALL
	
	echo -ne "\tgenerating "
	
	dns			; echo -n ", "
	dhcp		; echo -n ", "
	dhcpv6		; echo -n ", "
	nftables	; echo -n ", "
	rev6		; echo ""
	
	unset v4_PREFIX
	unset v4_EXTERNAL
	unset v6_PREFIX
	unset DOMAIN
	unset HOSTS
	unset FIREWALL
done

