#!/bin/sh
stty -F /dev/ttyACM0 38400 raw -echo -echoe -echok -crtscts clocal
