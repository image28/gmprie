CONNECT="POST / HTTP/1.1\r\nHost:127.0.0.1:28332\r\nAuthorization: Basic **********\r\nAccept: */*\r\nContent-Length: 74\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n{\"method\": \"getblocktemplate\", \"params\": [{\"rules\":[\"segwit\"]}], \"id\": 0}\r\n"
SUBMIT=""

# Connect and get work
echo -ne "$CONNECT" | netcat -q10 127.0.0.1 28332
# Mine a block

# Submit the block

