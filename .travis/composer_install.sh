#!/bin/bash

PHP_VERSION=$1
TEST_PATH=$2

COMPOSER_JSON=$TEST_PATH/composer.json
OLD_JOSN=$TEST_PATH/composer.json.5.4

function version_ge()
{
    python << EOF
import sys
from distutils.version import LooseVersion

sys.exit(not (LooseVersion('$1') > LooseVersion('$2')))
EOF
}

# change es version by php version
if version_ge $PHP_VERSION "5.6.0"; then
    # do nothing
    echo "skip"
else
    cp $OLD_JOSN  $COMPOSER_JSON
fi
