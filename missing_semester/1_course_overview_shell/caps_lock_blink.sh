# Author: Abhinav Thakur
# Email : compilepeace@gmail.com
# 
# script makes caps lock led blink by writing sysfs (man 5 sysfs)
# '/sys/class/leds/input2::capslock/brightness'

#!/bin/bash

for i in {1..10000}; do
	
	# turn on the led if the counter is an even number
	if [ $((i % 2)) -eq 0 ]; then
		echo 1 | sudo tee '/sys/class/leds/input2::capslock/brightness'
	else
		echo 0 | sudo tee '/sys/class/leds/input2::capslock/brightness'
	fi	
done	

