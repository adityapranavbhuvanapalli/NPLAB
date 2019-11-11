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

$ns queue-limit $n0 $n2 5
$ns queue-limit $n5 $n2 5
$ns queue-limit $n2 $n4 3
$ns queue-limit $n2 $n6 2

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
	set ctr0 0
	set fid [open lab.tr r]
	while {[gets $fid line] !=-1 } {
		if { [string match "*d*" $line] } {
			set ctr0 [expr $ctr0 + 1]
		}
	}
	puts "No. of packets dropped: $ctr0"
	exit 0
}

$ns rtmodel-at 0.9 down $n2 $n6
$ns rtmodel-at 1.5 up $n2 $n6
$ns at 0.1 "$ping0 send"
$ns at 0.2 "$ping0 send"
$ns at 0.3 "$ping0 send"
$ns at 0.4 "$ping0 send"
$ns at 0.5 "$ping0 send"
$ns at 0.6 "$ping0 send"
$ns at 0.7 "$ping0 send"
$ns at 0.8 "$ping0 send"
$ns at 0.9 "$ping0 send"
$ns at 1.0 "$ping0 send"
$ns at 1.1 "$ping0 send"
$ns at 1.2 "$ping0 send"
$ns at 1.3 "$ping0 send"
$ns at 1.4 "$ping0 send"
$ns at 1.5 "$ping0 send"
$ns at 1.6 "$ping0 send"
$ns at 1.7 "$ping0 send"
$ns at 1.8 "$ping0 send"
$ns at 1.9 "$ping0 send"
$ns at 0.1 "$ping5 send"
$ns at 0.2 "$ping5 send"
$ns at 0.3 "$ping5 send"
$ns at 0.4 "$ping5 send"
$ns at 0.5 "$ping5 send"
$ns at 0.6 "$ping5 send"
$ns at 0.7 "$ping5 send"
$ns at 0.8 "$ping5 send"
$ns at 0.9 "$ping5 send"
$ns at 1.0 "$ping5 send"
$ns at 1.1 "$ping5 send"
$ns at 1.2 "$ping5 send"
$ns at 1.3 "$ping5 send"
$ns at 1.4 "$ping5 send"
$ns at 1.5 "$ping5 send"
$ns at 1.6 "$ping5 send"
$ns at 1.7 "$ping5 send"
$ns at 1.8 "$ping5 send"
$ns at 1.9 "$ping5 send"
$ns at 5.0 "finish"
$ns run
