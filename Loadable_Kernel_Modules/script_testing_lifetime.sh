#!/bin/bash

MY_TIME=9

# This script tests the lifetime of a LKM in kernel space
sudo insmod 04_lifetime_in_kernel_space_lkm.ko
sleep $MY_TIME
sudo rmmod 04_lifetime_in_kernel_space_lkm
