---
title: "Black-Scholes Finite Difference Solver"
author: "Mouhamed Nourou DIne Cisse and Mohammed-Yahya Dami"
output: html_document
---


## Project overview

This project implements the numerical pricing of European options using the Black-Scholes model in C++.

The Black-Scholes partial differential equation is

\[
\frac{\partial V}{\partial t}
+ \frac{1}{2}\sigma^2 S^2 \frac{\partial^2 V}{\partial S^2}
+ r S \frac{\partial V}{\partial S}
- r V = 0
\]

with terminal condition

\[
V(T,S) = \text{payoff}(S)
\]

---

## Features

- Call and Put option classes
- Black-Scholes PDE abstraction
- Finite difference framework
- Implicit and Crank-Nicholson schemes
- Tridiagonal solver using the Thomas algorithm
- Modular C++ design

---

## Numerical methods

- Implicit finite difference method
- Crank-Nicholson finite difference method

---

## Purpose

The project serves as a foundation for numerical option pricing and further extensions beyond analytical Black-Scholes solutions.
