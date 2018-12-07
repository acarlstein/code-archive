/**
 * @author: Alejandro G. Carlstein R. M.
 * @description: In order to use Tweener you have to install the feffects
 * 							 Install: neko-dev (Ubuntu: sudo apt-get neko-dev)
 *               Execute: haxelib install feffects
 *							 Compile with flag: -lib feffects
 *							 Tweens available: feffects.easing.
 *								 Quint.easeIn, Quint.easeOut, Quint.easeInOut
 *								 Sine.easeIn, Sine.easeOut, Sine.easeInOut
 * 								 Back.easeIn, Back.easeOut, Back.easeInOut
 * 								 Bounce.easeIn, Bounce.easeOut, Bounce.easeInOut
 *								 Circ.easeIn, Circ.easeOut, Circ.easeInOut
 *								 Cubic.easeIn, Cubic.easeOut, Cubic.easeInOut
 *								 Elastic.easeIn, Elastic.easeOut, Elastic.easeInOut
 *								 Expo.easeIn, Expo.easeOut, Expo.easeInOut
 * 								 Linear.easeIn, Linear.easeOut, Linear.easeInOut, Linear.easeNone
 * 								 Quad.easeIn, Quad.easeOut, Quad.easeInOut
 * 								 Quart.easeIn, Quart.easeOut, Quad.easeInOut
 *
 */

import feffects.Tween;
import feffects.easing.Bounce;
import feffects.easing.Circ;
import feffects.easing.Elastic;
import flash.text.TextField;
import flash.display.Sprite;

class NumericBall2D extends Sprite{
	private var text_field : TextField;
	private static var LINE_SIZE : Float = 1.0;
	private static var LINE_COLOR : Int = 0x000000;
	private static var FILL_COLOR : Int = 0x11FF33;
	private static var CIRCLE_X : Int = 0;
	private static var CIRCLE_Y : Int = 0;
	public function new(size : Float = 25){
		super();
		graphics.lineStyle(LINE_SIZE, LINE_COLOR);
    graphics.beginFill(FILL_COLOR);
	  graphics.drawCircle(CIRCLE_X, CIRCLE_Y, size);
    graphics.endFill();
    
	  text_field = new TextField();
		flash.Lib.current.addChild(text_field);
	}
	
	public function setText(text : String){
		text_field.text = text;
	  text_field.x = this.x - 12;
	  text_field.y = this.y - 40;
	}
}

class Example_10_Sprite2D{

    private var numericBall2D : NumericBall2D;
    private var tween : Tween;
		private static var MIN_Y : Int = 100;
		private static var MAX_Y : Int = 300;
		private static var EFFECT_DURATION : Int = 5000;

    public function new(?x : Float){
        numericBall2D = new NumericBall2D();
        numericBall2D.x = x;
        flash.Lib.current.addChild(numericBall2D);
        
        tween = new Tween(MIN_Y, MAX_Y, EFFECT_DURATION, Elastic.easeOut );
        tween.setTweenHandlers(moveY, msgFinished );
        trace ( "tween staring at position: " + MIN_Y);
        tween.start();
    }
    
    function moveY( position : Float ){
        numericBall2D.setText(Std.string(Math.round(position)));
        numericBall2D.y = position;
    }

    function msgFinished( position : Float ){
        trace ( "tween finished at position: " + position );
    }

}




