#lang sicp
(define (square x)
  (* x x))

(define (sum_of_squares x y)
  (+(square x)
    (square y)
    ))