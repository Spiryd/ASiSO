#!/bin/sh
touch  -- ' ABC DEF' '-AbC aBc' '--ABC DEF'
find . -type f -print0 | xargs --null -Ix sh -c 'mv "$1" "$(echo "$1" | tr '[:upper:]' '[:lower:]')"' - x