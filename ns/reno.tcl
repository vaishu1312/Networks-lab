#Create a simulator object
set ns [new Simulator]
#Open the nam trace file
set nf [open outr.nam w]
$ns namtrace-all $nf
$ns color 1 Red
#Define a 'finish' procedure
proc finish {} {
global ns nf
$ns flush-trace
#Close the trace file
close $nf
#Execute nam on the trace file
exec nam outr.nam &
exit 0
}
# Creating Nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

#Setting Links
$ns duplex-link $n0 $n1 10Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail

#Setting Topology
$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right

#Setting Queue Limit
$ns queue-limit $n0 $n1 8
$ns queue-limit $n1 $n2 8
#Setup a TCP connection over 0 and 2 and its flow id, window size, packet size
set tcp [new Agent/TCP/Reno]
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink
$tcp set fid_ 1
$tcp set window_ 16
$tcp set packetSize_ 552
#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

#Start and stop  ftp
$ns at 0.1 "$ftp start"
$ns at 4.0 "$ftp stop"

#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"
#Run the simulation
$ns run
