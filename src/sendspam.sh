#!/bin/bash

echo "Recipient: "
echo $1
sleep 2
read recipient

echo "Sender: "
sleep 2
read sender

echo "Message: "
sleep 2
read message

"open mail.cs.ucr.edu 25" >> cmd.sh
"helo whitehouse.gov" >> cmd.sh
"mail from: $sender" >> cmd.sh
"rcpt to: $recipient" >> cmd.sh
data
Subject: THIS IS SPAM!
message

