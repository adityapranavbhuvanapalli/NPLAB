#Author : Aditya Pranav Bhuvanapalli
#B1 	: P2P Dropped packets

#Initialise new simulator
set ns [new Simulator]
#nf -> lab.tr in write mode 	
set nf [open lab.tr w] 	
#tf -> lab.nam in write mode
set tf [open lab.nam w]	

$ns trace-all $nf  
$ns namtrace-all $tf

#	(0)   (1)
#         \   /
#          (2) 
#	    |		
#          (3)
#Connection : 	(0) ----> (3)
#		(1) ----> (3)


#Create nodes
set n0 [$ns node] 
set n1 [$ns node] 
set n2 [$ns node] 
set n3 [$ns node]

#Initialise Application Layer Traffic (Constant Bit Rate) for senders
set cbr0 [new Application/Traffic/CBR] 
set cbr1 [new Application/Traffic/CBR] 

#Initialise Transport Layer Protocols (UDP) for senders
set udp0 [new Agent/UDP] 
set udp1 [new Agent/UDP]

#Initialise a Null agent for receiver
set null3 [new Agent/Null]

#Establish links between the nodes.
$ns duplex-link $n0 $n2 10Mb 300ms DropTail 
$ns duplex-link $n1 $n2 10Mb 300ms DropTail 
$ns duplex-link $n2 $n3 1Mb 300ms DropTail
#Attach Transport Layer Protocol to Network Layer
$ns attach-agent $n0 $udp0 
$ns attach-agent $n1 $udp1  
$ns attach-agent $n3 $null3

#Attach Application Layer Traffic to Transport Layer Protocol 
$cbr0 attach-agent $udp0 
$cbr1 attach-agent $udp1 

#Establish connections between senders and receivers
$ns connect $udp0 $null3 
$ns connect $udp1 $null3

#Starting process
$cbr0 set packetSize_ 500Mb 
$cbr0 set interval_ 0.005

proc finish { } { 
	exec nam lab.nam & 
	set ctr 0 
	set fid [open lab.tr r] 
	while { [gets $fid line] != -1 } { 
		if { [string match "*d*" $line] } { 
			set ctr [expr $ctr + 1] 
		} 
	} 
	puts "No of packets: $ctr"
	exit 0 
} 

$ns at 0.01 "$cbr0 start" 
$ns at 0.01 "$cbr1 start" 
$ns at 5.0 "finish" 
$ns run
