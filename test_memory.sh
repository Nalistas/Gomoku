#!/bin/bash

# Vérifiez qu'un PID est fourni en argument
if [ -z "$1" ]; then
  echo "Usage: $0 <PID>"
  exit 1
fi

PID=$1

# Vérifiez que le processus existe
if ! ps -p "$PID" > /dev/null 2>&1; then
  echo "Le processus avec le PID $PID n'existe pas."
  exit 1
fi

# Boucle pour afficher uniquement la mémoire utilisée toutes les 0.3 secondes
while ps -p "$PID" > /dev/null 2>&1; do
  # Extraire la mémoire résidente (RSS) depuis /proc
  if [ -d "/proc/$PID" ]; then
    MEMORY=$(grep VmRSS /proc/$PID/status | awk '{print $2 " " $3}')
    echo "Mémoire résidente utilisée par le PID $PID : $MEMORY"
  else
    echo "Impossible d'accéder au processus (il peut être terminé)."
    break
  fi

  # Pause de 0.3 seconde
  sleep 0.3
done

echo "Le processus avec le PID $PID n'existe plus."
