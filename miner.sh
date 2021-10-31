CONNECT="POST / HTTP/1.1\r\nHost:127.0.0.1:28332\r\nAuthorization: Basic **********\r\nAccept: */*\r\nContent-Length: 74\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n{\"method\": \"getblocktemplate\", \"params\": [{\"rules\":[\"segwit\"]}], \"id\": 0}\r\n"
SUBMIT="POST / HTTP/1.1\r\nHost:127.0.0.1:28332\r\nAuthorization: Basic **********\r\nAccept: */*\r\nContent-Length: BLOCKLENGTH\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n{\"method\": \"submitblock\", \"params\": [{\"OUTPUT\"}], \"id\": BLOCKID}\r\n"
#THREADS=2
INTERVAL=100000000000
DATE=`date +%j.%Y`

# Connect and get work
echo -ne "$CONNECT" | netcat -q10 127.0.0.1 28332 > .worklog-$DATE
# Calculate difficulty
DIFF=`cat .worklog-$DATE` # unfinished
BLOCKID=`cat .worklog-$DATE`
LIMIT=$((DIFF+INTERVAL))
# Mine a block
OUTPUT=`./gmp_prime $DIFF $LIMIT`

# Submit the block
echo -ne "$SUBMIT" | \
    sed -e s/"BLOCKID"/"$BLOCKID"/ | \
    sed -e s/"BLOCKLENGTH"/"$BLOCKLENGTH"/ | \
    sed -e s/"OUTPUT"/"$OUTPUT"/ | \
    netcat -q10 127.0.0.1 28332
