#!/bin/bash
predictor="gshare" 
mkdir -p simout 
mkdir -p simout/$predictor
./run-sniper -c nehalem-lite -sprogresstrace -s stop-by-icount:1000000000 --pinballs=pinballs/mcf/pinball
cat sim.out  > simout/$predictor/mcfout.txt 
./run-sniper -c nehalem-lite -sprogresstrace -s stop-by-icount:1000000000 --pinballs=pinballs/bzip2/pinball
cat sim.out  > simout/$predictor/bzip2out.txt 
./run-sniper -c nehalem-lite -sprogresstrace -s stop-by-icount:100000000 --pinballs=pinballs/gobmk/pinball
cat sim.out  > simout/$predictor/gobmk.txt 
./run-sniper -c nehalem-lite -sprogresstrace -s stop-by-icount:100000000 --pinballs=pinballs/sjeng/pinball
cat sim.out  > simout/$predictor/sjeng.txt 
./run-sniper -c nehalem-lite -sprogresstrace -s stop-by-icount:100000000 --pinballs=pinballs/astar/pinball
cat sim.out  > simout/$predictor/astar.txt 
