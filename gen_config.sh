BASE_DNS="base_dns.txt"
OUT_DNS_INT="dns_int.txt"
OUT_DNS_EXT="dns_ext.txt"

BASE_DHCP="base_dhcp.txt"
OUT_DHCP="dhcp.txt"
OUT_DHCPv6="dhcpv6.txt"

GENERATOR="../main"
HOSTS="hosts.txt"
FIREWALL="firewall.txt"
v4_PREFIX="192.168"
v4_EXTERNAL="8.8.8.8"
v6_PREFIX="fd00"
function call_gen {
	./${GENERATOR} ${HOSTS} ${FIREWALL} ${v4_PREFIX} ${v4_EXTERNAL} ${v6_PREFIX} $1
}

serial=$(date +"%y%m%d%H%M")
cat ${BASE_DNS} | sed "s/SERIAL/${serial} ; serial/g" > ${OUT_DNS_INT}
cat ${BASE_DNS} | sed "s/SERIAL/${serial} ; serial/g" > ${OUT_DNS_EXT}
call_gen dnsint >> ${OUT_DNS_INT}
call_gen dnsext >> ${OUT_DNS_EXT}

cp ${BASE_DHCP} ${OUT_DHCP}
cp ${BASE_DHCP} ${OUT_DHCPv6}
call_gen dhcp >> ${OUT_DHCP}
call_gen dhcpv6 >> ${OUT_DHCPv6}

# do iptables(6)
