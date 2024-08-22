# minitalk
Minitalk is a project that implements a server and client in C for inter-process communication using SIGUSR1 and SIGUSR2 signals. The server receives and prints messages, while the client sends them.

## Overview
    Server: Listens for messages from the client and prints them to the console.
    Client: Sends messages to the server using SIGUSR1 and SIGUSR2 signals to encode the data.

## Features
    Signal Handling: Utilizes Unix signals (SIGUSR1, SIGUSR2) for communication.
    Message Encoding: Encodes messages into bits for transmission.
    Process Communication: Demonstrates inter-process communication techniques.

## Requirements
    C compiler (e.g., gcc)
    Unix-like operating system
