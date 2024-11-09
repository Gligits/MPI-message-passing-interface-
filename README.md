# Installing mpi on your linux machine : 
sudo apt-get update

sudo apt install mpich 

# Once installed, you can check if MPICH is available by running:
mpicc --version

# Why Use MPICH?
MPICH is an implementation of the Message Passing Interface (MPI), which is a standardized and portable library for parallel programming. 
It’s designed for distributed computing, where you want multiple processors (often across multiple machines) to work together to solve a problem. 
Here’s why you might want to install and use MPICH:

- Parallel Processing: MPI allows you to divide tasks across multiple processors, enabling faster computations, particularly useful in high-performance computing, simulations, and data processing.
- Scalability: MPICH is built to handle tasks across many processors, making it scalable from small clusters to supercomputers.
- Cross-Platform: MPICH is highly portable and can run on many platforms, from personal computers to large clusters.
- Standardized Communication: MPI is the standard for process communication in distributed computing, offering features for point-to-point and collective communication, synchronization, and data exchange.
