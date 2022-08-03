
# Gate Level Information Flow Tracking (GLIFT)

# Project discription

This project is on implementation of Gate level inform ation flow tracking (GLIFT), a Hardware based information flow Technique in code using Cpp language.

# Table of contents

   * Introduction
   * About GLIFT
   * Methodology for implementation
   * Reference 
   
## Introduction
As Information flow tracking is an effective tool in computer security for detecting unintended information flows.software based information flow tracking 
implementations have drawbacks in preciseness and performance . So we go to hardware based information flow tracking, GLIFT (Gate level information flow tracking).GLIFT tracks information flow at the granularity of indivisual bits.
This project is to do fundamental analysis of GLIFT and its properties and to implement the theories via code and verify the same using test cases.

## About GLIFT
GLIFT,gate level information flow tracking is used to track information at granularity of indivisual bits more precisely. Few features of GLIFT are mentioned 
below:
* Propagate information at fine granularity.
* Targets secure system.
* Detect integrity violations where untrusted inputs flow to trusted outputs.
* Labeling of data bits to track propagation.

## Methodogy for Implementation.
* Identify of the input gates and output gates.
* Levelizing complete circuit
* Classify each gate by its level and start evaluating levelwise.
* Tracking the input bit value and tainted bit value.
* Evaluate the values using the shadow logic functions corresponding to that particular gate.

## Reference
* https://cseweb.ucsd.edu/~weh140/resource/TCAD_11.pdf
* https://users.ece.utexas.edu/~tiwari/pubs/DAC-10-glift.pdf







