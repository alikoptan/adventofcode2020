#!/usr/bin/env bash
cd src
if [ "$#" = 1 ]
then
  if [ -d "$1" ]
  then
    echo "compiling $1..."
    cd $1
    g++ -w -o solution *.cpp
    echo "running $1..."
    ./solution
    rm solution
  else
    echo "invalid day!"
  fi
else
  echo "invalid arguments."
fi
