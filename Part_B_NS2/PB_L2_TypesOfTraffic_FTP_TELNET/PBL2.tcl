#New Simulator
set ns [new Simulator]	
#tf -> lab.tr in write mode
set tf [open lab.tr w]	
#nf -> lab.nam in write mode
set nf [open lab.nam w]	

$ns trace-all $tf
$ns namtrace-all $nf

#Create Nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#Initialise Transport Layer Protocols
set tcp0 [new Agent/TCP]
set udp1 [new Agent/UDP]
set tcps3 [new Agent/TCPSink]
set null3 [new Agent/Null]

#Initialise Application Layer Protocols
set ftp0 [new Application/FTP]
set cbr1 [new Application/Traffic/CBR]

#Establish links between the nodes
$ns duplex-link $n0 $n2 100Mb 1ms DropTail
$ns duplex-link $n1 $n2 100Mb 1ms DropTail
$ns duplex-link $n2 $n3 100Mb 1ms DropTail

#Things get crazy from here
#Attach transport layer protocols to network layer

#n1,n2 are senders
$ns attach-agent $n0 $tcp0  
$ns attach-agent $n1 $udp1

#n3 is receiver
$ns attach-agent $n3 $tcps3 
$ns attach-agent $n3 $null3

#Attach application layer protocols to transport layer
$ftp0 attach-agent $tcp0
$cbr1 attach-agent $udp1

#Connection between nodes (through transport layer)
$ns connect $udp1 $null3
$ns connect $tcp0 $tcps3

#Process
proc finish {} {
	global ns nf tf
	$ns flush-trace
	exec nam lab.nam &
	close $nf
	close $tf
	set ctr0 0
	set ctr1 0
	set fid [open lab.nam r]
	while {[gets $fid line] !=-1} {
		if { [string match "*tcp*" $line] } {
			set ctr0 [expr $ctr0 + 1]
		}
		if { [string match "*cbr*" $line] } {
			set ctr1 [expr $ctr1 + 1]
		}
	}
	puts "No of tcp : $ctr0"
	puts "No of udp : $ctr1"
	exit 0
}

$ns at 0.01 "$ftp0 start"
$ns at 0.01 "$cbr1 start"
$ns at 5.0 "finish"
$ns run
