let rec gcd a b = 
	if b = 0 then a (* base case if b is 0, otherwise infite loop *)
	else if a = 0 then b (* similar to above clause *)
	else if a = b then a
	else if a > b then gcd b (a - b)
		else gcd a (b - a)

let () =
	print_endline "Enter first number:";
	let a = read_int () in
	print_endline "Enter second number:";
	let b = read_int () in
	Printf.printf "The GCD of %d and %d is %d\n" a b (gcd a b)

(* Added a let statement to allow users to input two numbers and execute the program *)
