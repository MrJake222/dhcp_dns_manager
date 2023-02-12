# DHCP-DNS-other manager

## Program arguments
* `hosts file` -- path to file containing hosts defininitons (format below)
* `firewall file` -- path to file containing firewall exceptions (format below)
* `v4-prefix` -- private v4 prefix to be used on local network (classful, private, no host octets, ex. `192.168`)
* `v4-external` -- public v4 address
* `v6-prefix` -- public v6 prefix to be used on local network (no `:`, ex. `2000`)
* `domain` -- domain name (ex. `home.local`)
* `config to output` -- config file suffix to generate, one of:
	* `dhcp` -- ISC-DHCP server, v4
	* `dhcpv6` -- ISC-DHCP server, v6
	* `dnsint` -- BIND9, internal view (private v4-prefix / v6-prefix)
	* `dntext` -- BIND9, external view (public v4 (same for all hosts) / v6-prefix)
	* `nftables` -- nftables rules
	* `rev6` -- reverse DNS zone for v6 addresses (generates full 128 bit entries)

## Hosts file
Consists of hosts defined in single lines, whitespace character separated,
supports comments with `#`. Columns:
* `mac` -- MAC address (must be unique, treated as placeholder if `static` flag set)
* `ipv4` -- v4 suffix (host octets with leading dot, ex. `.1.2`)
* `ipv6` -- v6 suffix (host part, with leading `:` or `::`, ex. `::2`)
* `name` -- name (DNS compatible)
* `options` (optional) -- options (comma separated list). Possible values:
	* `nov6` -- host doesn't support v6 addresses (ESP for example). DHCPv6/DNS AAAA records not generated
	* `static` -- host has static address bound (no mac needed, no DHCP records generated, DNS records)

Example input:
```
# mac				ipv4	ipv6	name	options
# 1.1 BPi
4C:CC:xx:xx:xx:xx	.1.2	::2		npc				# nPC
e8:db:xx:xx:xx:xx	.1.64	::40	piec	nov6	# ESP-piec (v4 only)
```

Program checks for MAC address duplicates, name clashes.

## Firewall file
Simmilar to hosts file, each line is one rule, whitespace separated.
Columns:
* `name` -- Maps to name from hosts file
* `internal` -- internal port number (of machine)
* `external` -- external port number (used only for v4 NAT, `0` to disable v4 access)
* `protocol` -- protocol to forward (ex. tcp, udp, sctp. Provide single one)

Example input:
```
# name	internal	external
mpc		25565		25565		# minecraft (v6 25565 port open, NAT 25565 -> mpc:25565)
npc		22 			0			# ssh (v6 only)
```

Program checks for duplicate entries (identical rows values) and global NAT port clashes.

## Provided scripting infrastructure
Generates config files for basic services. Base files are copied to output files
and to each output file script adds result of parsing subnet files.
Subnets are located in (assuming `/usr/local` prefix): `/usr/local/etc/ddmgr/subnets.d`.
Each dir should contain `subnet.conf` file which must define:
* v4_PREFIX, v4_EXTERNAL, v6_PREFIX, DOMAIN -- passed to program (see 1st paragraph here)
* HOSTS -- hosts file name (in subnet directory)
* FIREWALL -- firewall rules file name (in subnet directory)

Example subnet.conf file:
```
# file /usr/local/etc/ddmgr/subnets.d/lan/subnet.conf

v4_PREFIX="172.16"
v4_EXTERNAL="8.8.8.9"
v6_PREFIX="fd00:1"
DOMAIN="int.home.local" 

HOSTS="hosts.txt"			# this points to /usr/local/etc/ddmgr/subnets.d/lan/hosts.txt
FIREWALL="firewall.txt"		# this points to /usr/local/etc/ddmgr/subnets.d/lan/firewall.txt
```
