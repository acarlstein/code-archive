/**
 * @author: Alejandro G. Carlstein R. M.
 * @description:
 */

import flash.display.MovieClip;


class Rectangle2D{
	private static var DEFAULT_BORDER_COLOR = 0x000000;
	private static var DEFAULT_BORDER_THICKNESS = 1.0;
	private var x : Int;
	private var y : Int;
	private var width : Int;
	private var height : Int;
	private var background_color : Null<Int>;
	private var border_color : Null<Int>;
	private var border_thickness : Null<Float>;
	private var movie_clip : flash.display.MovieClip;
	
	public function new(x : Int, 
											y : Int, 
											width : Int, 
											height : Int, 
											?background_color : Null<Int>,
											?border_color : Null<Int>,
											?border_thickness : Null<Float>){
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
		this.background_color = (background_color == null) ? null : background_color;	
		this.border_color = (border_color == null) ? DEFAULT_BORDER_COLOR : border_color;
		this.border_thickness = (border_thickness == null) ? DEFAULT_BORDER_THICKNESS : border_thickness;
	}
	
	public function draw(){
		movie_clip = flash.Lib.current;
		moveTo(x, y);			
	}
		
	public function moveTo(x : Int, y : Int){
		this.x = x;
		this.y = y;
		resize(width, height);
	}

	public function resize(width : Int, height : Int){
		movie_clip.graphics.clear();

    if (background_color != null)
    	movie_clip.graphics.beginFill(background_color);

		if (border_thickness != null)
	    movie_clip.graphics.lineStyle(border_thickness, border_color);

		movie_clip.graphics.moveTo(x, y);
    movie_clip.graphics.lineTo(width,y);
    movie_clip.graphics.lineTo(width, height);		
    movie_clip.graphics.lineTo(x, height);

    movie_clip.graphics.lineTo(x, y);

    if (background_color > -1)
    	movie_clip.graphics.endFill();

	}

}


class Shape2D extends MovieClip{
	private static var DEFAULT_BORDER_COLOR = 0x000000;
	private static var DEFAULT_BORDER_THICKNESS = 1.0;
	private var radius : Float;
	private var background_color : Null<Int>;
	private var border_color : Null<Int>;
	private var border_thickness : Null<Float>;

	public function new(x : Int, 
											y : Int,
											?background_color : Null<Int>,
											?border_color : Null<Int>,
											?border_thickness : Null<Float>){
		super();
		this.x = x;
		this.y = y;
		this.background_color = (background_color == null) ? null : background_color;	
		this.border_color = (border_color == null) ? DEFAULT_BORDER_COLOR : border_color;
		this.border_thickness = (border_thickness == null) ? DEFAULT_BORDER_THICKNESS : border_thickness;
	}

	public function drawCircle(radius : Float, ?x : Int, ?y : Int){
		if (x != null) this.x = x;
		if (x != null) this.y = y;
		this.radius = radius;
		beginDraw();
		graphics.drawCircle(x, y, radius);
		endDraw();
	}
	
	public function drawRectangle(width : Int, height : Int, ?x : Int, ?y : Int){
		if (x != null) this.x = x;
		if (x != null) this.y = y;
		this.width = width;
		this.height = height;
		beginDraw();
		graphics.drawRect(x, y, width, height);
		endDraw();
	}
	
	
	
	private function beginDraw(){
		graphics.clear();
		graphics.moveTo(x, y);

    if (background_color != null)
    	graphics.beginFill(background_color);

		if (border_thickness != null)
	    graphics.lineStyle(border_thickness, border_color);
	
	}
	
	private function endDraw(){
		 if (background_color > -1)
    	graphics.endFill();
	}

}
 
 
class Example_8{
 
 	static function main(){
		
		var rectangle : Rectangle2D = new Rectangle2D(100,100,100, 100, 0x334433, 0x44444);
		rectangle.draw();
		rectangle.resize(200, 200);
		haxe.Timer.delay(function(){rectangle.moveTo(0, 0);}, 2000);
		
		var shape2D : Shape2D = new Shape2D(100,100, null, 0x000000, 3.0);
		flash.Lib.current.addChild(shape2D);
		shape2D.drawCircle(45.0);
		
		haxe.Timer.delay(function(){shape2D.drawRectangle(100, 100);}, 2000);
		
 	}
}
