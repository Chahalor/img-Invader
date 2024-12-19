#!/bin/bash

IMG_PATH="tkt.png"
FILE=$(ls -r)

for i in $FILE do
	cp $IMG_PATH $i
done