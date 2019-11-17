#B5 	: Ping

set ns [new Simulator]
set nf [open lab.tr w]
set tf [open lab.nam w]
$ns trace-all $nf
$ns namtrace-all $tf

#   [s0][ping]      [ping]      [ping]
#      [n0]          [n1]        [n3]
#         '.          |          .'	
#           '.        |        .'
#             '.      |      .'
#               '.    |    .'
#                 '.  |  .'
#                    [n2]
#                  .' | '.
#                .'   |   '.
#              .'     |     '.
#            .'       |       '.
#          .'         |         '.
#        .'           |           '.
#      [n4]          [n5]         [n6]
#    [ping][d0]   [s1][ping]   [ping][d1]

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

$ns duplex-link $n0 $n2 100Mb 300ms DropTail
$ns duplex-link $n5 $n2 100Mb 300ms DropTail
$ns duplex-link $n1 $n2 1Mb 300ms DropTail
$ns duplex-link $n3 $n2 1Mb 300ms DropTail
$ns duplex-link $n2 $n4 1Mb 300ms DropTail
$ns duplex-link $n2 $n6 1Mb 300ms DropTail


set ping0 [new Agent/Ping]
set ping4 [new Agent/Ping]
set ping5 [new Agent/Ping]
set ping6 [new Agent/Ping]

$ns attach-agent $n0 $ping0
$ns attach-agent $n4 $ping4
$ns attach-agent $n5 $ping5
$ns attach-agent $n6 $ping6

$ns connect $ping0 $ping4
$ns connect $ping5 $ping6

#Procedure for pinging
Agent/Ping instproc recv {from rtt} {
	$self instvar node_
	puts "The node [$node_ id] received a reply from $from with an RTT of $rtt"
}

#Procedure for packets dropped
proc finish {} {
	exec nam lab.nam &
	set ctr0 9
	set ctr1 0
	set fid [open lab.tr r]
	while {[gets $fid line] !=-1 } {
		puts "The node [$node_ id] received a reply from $from with an RTT of $rtt"
		if { [string match "c*" $line] } {
			set ctr1 [expr $ctr1 + 1]
		}
	}	
	puts "No. of packets dropped: $ctr0"
	exit 0
}

$ns run
