(* Create an object of the 'point' class *)
let p1 = new Main.point 0 0;;

(* Call methods on the object *)
let x_val = p1#get_x;;
let y_val = p1#get_y;;
print_endline ("Initial point: " ^ p1#to_string);; (* Output: Initial point: (0, 0) *)

p1#move 10 5;;
print_endline ("Moved point: " ^ p1#to_string);; (* Output: Moved point: (10, 5) *)

(* Create another object *)
let p2 = new Main.point 100 200;;
print_endline ("Another point: " ^ p2#to_string);; (* Output: Another point: (100, 200) *)
