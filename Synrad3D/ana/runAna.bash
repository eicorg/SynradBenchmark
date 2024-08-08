#!/bin/bash
python ana1.py
root -l -b -q ana2.C\(\"./output/synrad3d_converted.dat\",\"./output/synrad3d_converted.root\"\)
root -l -b -q ana3.C\(\"./output/synrad3d_converted.root\",\"./output/output_all.root\"\)

