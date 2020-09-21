#!/bin/bash

irace="~/bin/irace"
if [ ! -x $irace ]; then
    echo "error: cannot execute $irace is it installed?"
    exit 1
fi

#SCENARIO is a irace's scenario file
SCENARIO="$1"
# RUN is the run number to distinguish replications of irace
RUN="$2"
shift 2
INSTANCE=malagaChica
let SEED=1234567+RUN
IRACE_PARAMS="--scenario scenario-${SCENARIO}.txt --debug-level 3 --parallel 8  --seed ${SEED}"

test -r src/irace/scenario-${SCENARIO}.txt || exit 1
pushd ./src

# Generate parameter files.
./irace/target-runner-rel ./sumo-wrapper/instanceFiles/${INSTANCE}.txt > ./irace/parameters-rel.txt || exit 1
./irace/target-runner-abs ./sumo-wrapper/instanceFiles/${INSTANCE}.txt > ./irace/parameters-abs.txt || exit 1

EXECDIR="../execdir-$RUN"
# Run irace
cd irace && mkdir -p $EXECDIR && $irace --exec-dir=$EXECDIR ${IRACE_PARAMS}
popd
echo "All done!"

