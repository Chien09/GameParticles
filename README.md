# GameParticles

Project aimed at optimizing rendering of particles. Code optimization log located in "Logs.pdf". 

**Optimizations**

-Change Double to Floats for Vect4D and Matrix functions/methods, operators, and constructor

-Convert Vect4D and Matrix into SIMD instructions (which allows faster computational times) instead of using math operators 

-Using RVO (Return Value Optimization) for the Vect4D to produce faster runtimes

-Updating variables to use CONST 

-Refactor for-loops and while loops 

-Change compiler settings 