#B6,B7 	: ESS and Ad-Hoc

set ns [new Simulator]
set tf [open lab.tr w]
$ns trace-all $tf
set topo [new Topography]
$topo load_flatgrid 1000 1000
set nf [open lab.nam w]
$ns namtrace-all-wireless $nf 1000 1000

$ns node-config -adhocRouting DSDV \
-llType LL \
-macType Mac/802_11 \
-ifqType Queue/DropTail \
-ifqLen 50 \
-phyType Phy/WirelessPhy \
-channelType Channel/WirelessChannel \
-propType Propagation/TwoRayGround \
-antType Antenna/OmniAntenna \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON

#GOD or General Operations Director is a ns-2 simulator object, which is used to store global information about the state of the environment,
# network, or nodes 

create-god 3
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
$n0 label "tcp0"
$n1 label "sink1/tcp1"
$n2 label "sink2"
#The below code is used to give the initial node positions.
$n0 set X_ 50
$n0 set Y_ 50
$n0 set Z_ 0
$n1 set X_ 100
$n1 set Y_ 100
$n1 set Z_ 0
$n2 set X_ 600
$n2 set Y_ 600
$n2 set Z_ 0


# the simulation  time = 0.1 seconds 
# coordinate =  50,50 at a speed of 15 meters per second
# the node n0 will move in this speed towards the coordinate specified


$ns at 0.1 "$n0 setdest 50 50 15"
$ns at 0.1 "$n1 setdest 100 100 25"
$ns at 0.1 "$n2 setdest 600 600 25"
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp0 $sink1
set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
set sink2 [new Agent/TCPSink]
$ns attach-agent $n2 $sink2
$ns connect $tcp1 $sink2
$ns at 5 "$ftp0 start"
$ns at 5 "$ftp1 start"
#The below code is used to provide the node movements.

#node n1 will start moving to 550,550 at speed = 15m/s at simulation time = 100

$ns at 20 "$n1 setdest 550 550 150"
$ns at 30 "$n1 setdest 70 70 150"
proc finish {} {
	exec nam lab.nam &
	set ctr1 0
	set ctr2 0
	set thr1 0
	set thr2 0
	set fid [open lab.tr r]

	# 0   1      2 3  4 
	# r 0.101003 0 2 tcp 40 ------- 1 0.0 3.0 0 0
	# c 1.592044 2 5 tcp 1054 ------- 0 0.0 2.0 87 1642
	# r 5.026987007 _1_ AGT  --- 7 tcp 1060 [13a 1 0 800] ------- [0:0 1:0 32 1] [2 0] 1 0
	# s 5.000000000 _0_ AGT  --- 3 tcp 40 [0 0 0 0] ------- [0:0 1:0 32 0] [0 0] 0 0

	while {[gets $fid line] != -1} { 
	     if { [string match "*s*" $line] && [string match "*AGT*" $line]  } {
		  set ctr1 [expr $ctr1 + 1 ]
	     }
	     set thr1 [expr $ctr1 / 5 ] 
	  
	puts "No of  packets transmitted  =   $ctr1" 
	puts "Throuput  =   $thr1 packets/sec "     
	exit 0
}

$ns at 0.1 "$ns set-animation-rate 1000.0ms"
$ns at 50 "finish"
$ns run
