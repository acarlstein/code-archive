class Example_2 {

	static function main(){
			
		//In haxe, arrays are iterable which mean that have methods and properties
		var integer_array : Array<Int> = [1,2,3,4];
		
		var num : Int = 4;
		for (i in 0...num)
			trace("1) integer_array[" + i + "]: " + integer_array[i]);
								
		integer_array.reverse();

		for (i in 0...num)
			trace("2) integer_array[" + i + "]: " + integer_array[i]);

		// While loop
		var count : Int = 0;
    while(count < 5){
			trace("3) While Count: " + count);			
    	++count;
    }
		
		count = 0;
		do{
			trace("4) Do While Count: " + count);			
    	count++;
    }while(count < 5);

		// continue - skip interation and go backi to while condition
		count = -1;
		while( count < 5 ) {
			++count;
			trace("5) While with continue Count: " + count);			
		  if( count == 3 ){
				trace("5) CONTINUE go to while");			
	      continue;
		  }			
		}
		trace("5) While with continue ends at count: " + count);			
		

		// break - Jump out of the "while" loop, and continue
		count = -1;
		while( count < 5 ) {
			++count;
			trace("6) While with break Count: " + count);			
		  if( count == 3 ){
				trace("6) Break!!!");			
	      break;
		  }			
		}
		trace("6) While with break ends at count: " + count);			


  }
  
}
