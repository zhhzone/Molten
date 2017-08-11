#!/bin/bash
function logit() {
    echo "[ext_build] $@" 1>&2
}

function build()
{
    php_path=`cd $1; pwd`
    add_build_flag=$2

    php="$php_path/bin/php"
    phpize="$php_path/bin/phpize"
    phpcfg="$php_path/bin/php-config"
    if [ ! -f $phpcfg ]; then
        logit "invalid PHP path $php_path"
        return 1
    fi

    # clean
    make clean      >/dev/null 2>&1
    $phpize --clean >/dev/null 2>&1

    # configure, make
    $phpize &&
    if [ -z "$add_build_flag" ]; then
        ./configure --with-php-config=$phpcfg && \
        make install
    else
        ./configure --with-php-config=$phpcfg --enable-level-id && \
        make install
    fi

    ret=$?

    if [ $ret -eq 0 ]; then
        logit "done"
    else
        logit "fail"
    fi

    return $ret
}

# main
if [ $# -lt 1 ]; then
    echo "usage: `basename $0` <php-path>"
    exit 1
fi

# argument
php_path="$1"
if [ ! -d "$php_path" ]; then
    logit "error: invalid PHP path \"$php_path\""
    exit 1
fi
logit "php_path: $php_path"

# build
build $php_path $2
