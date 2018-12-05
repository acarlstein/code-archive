// enum go outside the class
enum Enum_Colors {
	blue;
	red;
	yellow;
}

class Example_1 {

	static function main(){
			
		// Integers
		var variable_integer : Int;
		variable_integer = 0; 
		trace("1) variable_integer = " + variable_integer);
		variable_integer = -134; 
		trace("2) variable_integer = " + variable_integer);		
  	variable_integer = 0xFF00; 
		trace("3) variable_integer = " + variable_integer);
		
		// Float
		var variable_float : Float;
	  variable_float = 123.0; 
		trace("4) variable_float = " + variable_float);
	  variable_float = .14179; 
		trace("5) variable_float = " + variable_float);
	  variable_float = 13e50; 
		trace("6) variable_float = " + variable_float);
	  variable_float = -1e-99;
		trace("7) variable_float = " + variable_float);
		
		// String
		var variable_string : String;
	  variable_string = "hello"; 
		trace("8) variable_string = " + variable_string);
    variable_string = "hello \"world\" !";
    trace("9) variable_string = " + variable_string);
	  variable_string = 'hello "world" !'; 
	  trace("10) variable_string = " + variable_string);

		// Boolean
		var variable_bool : Bool;
	  variable_bool = true; 
	  trace("11) variable_bool = " + variable_bool);
  	variable_bool = false;
		trace("12) variable_bool = " + variable_bool);
	  
	  // Dynamic
	  var variable_dynamic : Dynamic;
	  variable_dynamic = 7; 
	  trace("13) variable_dynamic = " + variable_dynamic);
	  variable_dynamic = "Now, variable_dynamic holds a string";
	  trace("14) variable_dynamic = " + variable_dynamic);
	  
	  // Assigning null
	  var variable;
	  variable = null; 
	  trace("15) variable = " + variable);

		// Using enum constants
		var variable_colors : Enum_Colors;
		variable_colors = blue;
		if (variable_colors == blue){
			trace("16) variable_colors = blue");
		}else{
			trace("16) variable_colors is not blue");
		}

		variable_colors = yellow;
		if (variable_colors == blue){
			trace("17) variable_colors = blue");
		}else{
			trace("17) variable_colors is not blue");
		}

		// Using Arrays (in haxe, arrays are iterable)
		var integer_array : Array<Int> = [1,2,3,4];
		
		// You can loop through integer_array's members directly with a for..in loop
		var count : Int = 0;
		for (i in integer_array){
			trace("18) integer_array[" + count++ + "]: " + i);
		}
		
		var num : Int = 4;
		for (i in 0...num)
			trace("19) integer_array[" + i + "]: " + integer_array[i]);
			
		for (i in 0...4)	
			trace("20) integer_array[" + i + "]: " + integer_array[i]);

		// This would not work: for (i in 3...0)
		var i : Int = 3;
		while (i >= 0){
			trace("21) integer_array[" + i + "]: " + integer_array[i]);
			--i;
		}

  }
  
}
