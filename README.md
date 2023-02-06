# DHCP-DNS-other manager

## Program arguments
* `hosts file` -- path to file containing hosts defininitons (format below)
* `firewall file` -- path to file containing firewall exceptions (format below)
* `v4-prefix` -- private v4 prefix to be used on local network (classful, private, no host octets, ex. `192.168`)
* `v4-external` -- public v4 address
* `v6-prefix` -- public v6 prefix to be used on local network (no `:`, ex. `2000`)
* `config to output` -- config file suffix to generate, one of:
	* `dhcp` -- ISC-DHCP server, v4
	* `dhcpv6` -- ISC-DHCP server, v6
	* `dnsint` -- BIND9, internal view (private v4-prefix / v6-prefix)
	* `dntext` -- BIND9, external view (public v4 (same for all hosts) / v6-prefix)
	* `iptables` -- iptables rules for v4
	* `iptables6` -- iptables rules for v6

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
