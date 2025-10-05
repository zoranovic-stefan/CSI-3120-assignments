% Added four lines of code;
% Two for handling the case where either of the numbers is 0
% Two for handling the case where either of the numbers is negative

cd(0,B,B) :- B >= 0.
gcd(A,0,A) :- A >= 0.
gcd(A,B,G) :- A < 0, A1 is -A, gcd(A1,B,G).
gcd(A,B,G) :- B < 0, B1 is -B, gcd(A,B1,G).

gcd(A,B,G) :- A = B, G = A.
gcd(A,B,G) :- A > B, C is A-B, gcd(C, B, G).
gcd(A,B,G) :- B > A, C is B-A, gcd(C, A, G).