#!/bin/bash

CURRENT_CENTURY=21
SLEEP_TIME=30

for ((;;));
do
    echo "Setting date and time"
    sudo ./set_date $CURRENT_CENTURY $(gpspipe -R -n10 | sed -n "/GPRMC/,/*/p")
    sleep $SLEEP_TIME
done
