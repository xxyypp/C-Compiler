#!/bin/bash

SRCFILE=$1  # Program to optimise

CHANGED=1;
while [[ "$CHANGED" -ne 0 ]]; do
  CHANGED=0;

  cat $SRCFILE | bin/constant_fold > $SRCFILE.tmp
  if [[ "$?" -eq "0" ]]; then
    CHANGED=1;
  fi
  cp $SRCFILE.tmp $SRCFILE

  cat $SRCFILE | bin/dead_branch_removal > $SRCFILE.tmp
  if [[ "$?" -eq "0" ]]; then
    CHANGED=1;
  fi
  cp $SRCFILE.tmp $SRCFILE

  cat $SRCFILE | bin/constant_propagation > $SRCFILE.tmp
  if [[ "$?" -eq "0" ]]; then
    CHANGED=1;
  fi
  cp $SRCFILE.tmp $SRCFILE
fi

