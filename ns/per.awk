BEGIN {
recvdSize = 0
txsize=0
drpSize=0
startTime = 0
stopTime = 0
thru=0
}
{
event = $1
time = $2
node_id = $3
pkt_size = $6
level = $5
# Store start time
if (level == "cbr" && (event == "+" || event == "s") )
{
if (time < startTime)
{
startTime = time
}
txsize++;}
# Update total received packetsâ€TM size and store packets arrival time
if (level == "cbr" && event == "r" )
{
if (time > stopTime)
{
stopTime = time
}
recvdSize++
}
if (level == "cbr" && event == "d" )
{
drpSize++
}
}
END {
printf("Average Throughput[kbps] = %.2f\ns=%.2f\nd=%.2f\nr=%.2f\nStartTime=%.2f\nStopTime=%.2f\n",(recvdSize/(stopTime-startTime)),txsize,drpSize,recvdSize,startTime,stopTime)
}
