# cellular-automata-snowflake-simulation
### Simulation studies of ice dendrite growth.

#### authors: Tereza Magerková, Tomáš Husár

#### usage:

configure parameters in Makefile: `[size]`, `[number_of_iterations]`, `[alpha]`, `[beta]`, `[gamma]` where:
- `[size]` - size of lattice (2d array)
- `[number_of_iterations]` - number of iterations
- `[alpha]` - alpha ∈ <0,1>, constant used for hexagonal field approximation
- `[beta]` - beta ∈ <0,1>, constant representating ambient supersaturation and temperature
- `[gamma]` - gamma ∈ <0,1>, additive constant representing freezing intensity

after configuration of parameters, start the code with:
`$ make run`

to portray the output in `out.txt` use:
`$ python3 plot.py`
