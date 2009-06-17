#!/bin/sh
CONF=$1
if [ ! -f "$CONF" ]; 
then
    echo "configuration file not exist";
    echo "Usage: $0 configuration_file_name"
    exit -1; 
fi;
URL=$(grep '^ebanka_url' $CONF | cut -c12- | tr -d '"')
if [ -z "$URL" ]; then exit; fi
# run e-banka list and make invoice
wget -q -O /tmp/.ebanka.csv --no-check-certificate $URL
# transfer to UTF8
iconv --from-code=WINDOWS-1250 --to-code=UTF8 < /tmp/.ebanka.csv > /tmp/.e.csv
# log to syslog
/home/jara/enum/fred/build/root/sbin/fred-banking -C $CONF --ebanka-csv /tmp/.e.csv