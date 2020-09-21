irace + SUMO: Reliable simulation-optimization of traffic lights in a real-world city
=======================================================================

Javier Ferrer, Manuel López-Ibáñez, and Enrique Alba. **Reliable
simulation-optimization of traffic lights in a real-world city**. 
_Applied Soft Computing_, 78:697–711, 2019. doi:10.1016/j.asoc.2019.03.016


Software versions used in the paper:

 * irace 3.0
 * SUMO 0.22.0


Installation
-------------

 1. Install irace (>=3.0): https://cran.r-project.org/package=irace

 2. Install SUMO (>= 0.22.0): https://www.eclipse.org/sumo/
 
     **IMPORTANT**: The `sumo` executable must be in the PATH, otherwise
     `sumo-wrapper` will not find it!
 
 3. Compile sumo-wrapper:

        make all -C src/sumo-wrapper/code
        
 4. The files `./irace/target-runner-rel` and `./irace/target-runner-abs`
    require Perl 5.


Execution
----------

Look at scenarios in `src/irace/`, choose one, for example
`scenario-abs-repjavier-first2new0confs10.txt`. Then run: 


        $ run.sh first2new0confs10 2
  
This will create a directory `./execdir-2` with the results of irace.


Overview
--------


 1. `run.sh` will call both `./irace/target-runner-rel` and
 `./irace/target-runner-abs` using the instance defined in `run.sh` to create
 `./irace/parameters-rel.txt` and `./irace/parameters-abs.txt`. 
 
 2. `run.sh` will call `irace` which calls either `./irace/target-runner-rel`
    or `./irace/target-runner-abs` (defined by the scenario
    `targetRunner`). Let's assume it is `./irace/target-runner-rel`.
    
 3. `./irace/target-runner-rel` will call
    `./src/sumo-wrapper/code/sumo-wrapper` which calls `sumo`
    
 4. `sumo` will use the files in `src/sumo-wrapper/instanceFiles/`
    `src/sumo-wrapper/instances/`
    
 
