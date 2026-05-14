#lang sicp
(define (square x)
  (* x x))

(define (square_of_sum x y)
  (square (+ x y)))