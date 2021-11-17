#!/usr/bin/env sh

# Say you don’t want to start a process until another completes, how you would go about it? In this exercise our limiting process will always be sleep 60 &. One way to achieve this is to use the wait command. Try launching the sleep command and having an ls wait until the background process finishes.
sleep 300 &
ps
pgrep sleep
pkill sleep
ps
