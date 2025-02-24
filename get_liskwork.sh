#!/bin/bash

targz=liskvork-0.4.3-src.tar.gz

if [ ! -d liskvork && ! -f $targz ]; then
    echo "liskvork not found"
    exit 1
fi

if [ ! -d liskvork ]; then
    mkdir liskvork
    cp $targz liskvork
    cd liskvork
    tar -xvf $targz
fi

cd liskvork
docker build . --build-arg BUILD_VERSION=0.0.0-dev -t liskvork
docker create --name mon_conteneur_temp liskvork
docker cp mon_conteneur_temp:/liskvork .

mv liskvork gomocup
mv gomocup ..
docker rm mon_conteneur_temp

cd ..
