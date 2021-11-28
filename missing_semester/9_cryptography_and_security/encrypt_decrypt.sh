#!/usr/bin/env bash

# Author: Abhinav Thakur
# Email : compilepeace@gmail.com
# Description:	This script encrypts/decrypts a file using symmetric cryptography via 
#		openssl utility.
#
# To hash long strings, use 'shasum -a 256 <filename>' to get sha256 hashes

if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <filename>"
	exit 7
fi

read -p "Provide encrypt or decrypt: " do_what

encrypt () {
	echo "[+] encrypting..."
	openssl aes-256-cbc -salt -in "$1" -out "$1".encrypt
	echo "[+] Done. created $1.encrypted"
}

decrypt () {
	echo "[+] decrypting..."
	openssl aes-256-cbc -d -in "$1" -out "$1".decrypt
	echo "[+] Done. created $1.decrypted"
}


if [[ "$do_what" == "encrypt" ]]; then
	encrypt "$1"
elif [[ "$do_what" == "decrypt" ]]; then
	decrypt "$1"
else
	echo "Usage: $0 <filename> "
	echo "enter a valid option [encrypt] or [decrypt]"
	exit 8
fi
