# mPFC-lookup-generator
A small suite of programs for analysing and verifying Bernd Porr's limbic system simulator: https://github.com/berndporr/limbic-system-simulator 

lookup.c :generates a lookup table of pre frontal cortex activity in relation to seratonin(5ht) activity and visual stimulus(x).
ls_prototype.c: generates a file which shows the number of steps an agent using Bernd's ls theory will take to reach a reward location, and once the reward has spawned, have its 5ht receptors exited and claim the reward. Used for deciding the scaling of a Prism model.

Compile with GCC as >gcc -w -Wall -o lookup lookup.c -lm
