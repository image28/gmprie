CONNECT="POST / HTTP/1.1\r\nHost:127.0.0.1:28332\r\nAuthorization: Basic **********\r\nAccept: */*\r\nContent-Length: 74\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n{\"method\": \"getblocktemplate\", \"params\": [{\"rules\":[\"segwit\"]}], \"id\": 0}\r\n"
SUBMIT="POST / HTTP/1.1\r\nHost:127.0.0.1:28332\r\nAuthorization: Basic **********\r\nAccept: */*\r\nContent-Length: BLOCKLENGTH\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n{\"method\": \"submitblock\", \"params\": [{\"OUTPUT\"}], \"id\": BLOCKID}\r\n"
DATE=`date +%j.%Y`

# Connect and get work
echo -ne "$CONNECT" | netcat -q10 127.0.0.1 28332 > .worklog-$DATE
# Calculate difficulty
HEIGHT=`cat .worklog-$DATE | grep -iEo "height\":[0-9]*" | awk -F':' '{print $2}'`
BLOCKID=`cat .worklog-$DATE | grep -iEo "ID\":[0-9]*" | awk -F':' '{print $2}'`
BITS=`cat .worklog-$DATE | grep -iEo "bits\":[0-9]*" | awk -F':' '{print $2}'`
CURTIME=`cat .worklog-$DATE | grep -iEo "curtime\":[0-9]*" | awk -F':' '{print $2}'`
#  2^(Difficulty - 80)(2^80 + 2^64*L + 2^32*Height + Requests)
#DIFF=
# Mine a block
#OUTPUT=`./gmp_prime $DIFF $LIMIT`

# Submit the block
#echo -ne "$SUBMIT" | \
#    sed -e s/"BLOCKID"/"$BLOCKID"/ | \
#   sed -e s/"BLOCKLENGTH"/"$BLOCKLENGTH"/ | \
#    sed -e s/"OUTPUT"/"$OUTPUT"/ | \
#   netcat -q10 127.0.0.1 28332
