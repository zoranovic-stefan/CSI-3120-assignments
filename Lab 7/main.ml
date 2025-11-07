class point x_init y_init = 
	object (self)
		val mutable x = x_init
		val mutable y = y_init

		method get_x = x
		method get_y = y

		method move dx dy =
			x <- x + dx;
			y <- y + dy

		method to_string = 
			"(" ^ (string_of_int x) ^ ", " ^ (string_of_int y) ^ ")"
	end
