# polymer-c

---

## Repository Organization

* `polymer-c/`

  - `Analysis/` contains (primarily MATLAB) files that generate figures/ do calculations using the output of driveMetropolis.c as input.

  - `docs/` contains documentation files, including the PolymerCode flowchart and outputControl format .txt file.

  - `drivers/` contains scripts for submitting jobs to HPC and looping through variables

  - `Gillespie/` contains C scripts for running the reversible and irreversible Gilespie simulations

  - `src/PolymerCode/` contains C scripts for running metropolis algorithm, as well as .txt files for parameters

---

## Quickstart

To run on UCI hpc3:

* go to `polymer-c/src/PolymerCode`
* `make`
* In `drivers/testslurm.sub`, make sure the account name and e-mail address are correct.
* In `drivers/Submitbash_single_slurm.sh`, make sure that `output_dir` is correct.
* Run `sh Submitbash_single.sh`
* Check your job with `squeue -u [yourusername]`.



