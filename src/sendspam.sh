#!/bin/bash

echo Subject: 
sleep 1
read subject

echo Message:
sleep 1

body=$(cat)
(
echo open mail.cs.ucr.edu 25
sleep 1
echo helo mail.cs.ucr.edu
sleep 1
echo mail from: $1
sleep 1
echo rcpt to: $2
sleep 1
echo data
sleep 1
echo Subject: "$subject"
sleep 1
echo "$body"
sleep 1
echo .
sleep 1
) | telnet
