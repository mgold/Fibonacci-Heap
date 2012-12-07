#!/bin/bash

for iter in {1..7}
do
    ./run >/dev/null
done
time ./run >/dev/null
