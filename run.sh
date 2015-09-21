#!/bin/bash

nice echo $1 | ./planar >$1.out 2>$1.err
