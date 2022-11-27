#!/bin/bash
URL="$(curl -s https://api.thecatapi.com/v1/images/search | jq -r '.[0].url')"
curl -s "$URL" >  cat.jpg
catimg cat.jpg
rm cat.jpg
curl -s https://api.chucknorris.io/jokes/random | jq -r '.value'

