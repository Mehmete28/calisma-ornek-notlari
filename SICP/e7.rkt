#lang sicp
(define (square x)
  (* x x))

(define (cube x)
  (* x x x))

(cube (square 2))