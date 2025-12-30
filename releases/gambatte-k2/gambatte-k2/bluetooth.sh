#!/bin/bash

if [ "$1" = "enable" ]; then
  lipc-set-prop -s com.lab126.btfd BTenable 0:1 && \
  sleep 2 && \
  lipc-set-prop -s com.lab126.btfd BTenable 1:1 && \
  lipc-set-prop com.lab126.pillow customDialog '{"name":"bt_wizard_dialog", "clientParams": {"show":true, "winmgrModal":true, "replySrc":""}}'
fi

if [ "$1" = "disable" ]; then
  lipc-set-prop -s com.lab126.btfd BTenable 0:1
fi