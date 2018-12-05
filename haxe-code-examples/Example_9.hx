/**
 * @author: Alejandro G. Carlstein R. M.
 * @description:
 */
 
import flash.display.MovieClip;
import flash.text.TextField;
import flash.text.TextFormat;
import flash.text.TextFormatAlign;
import flash.text.TextFormatDisplay;
 
class MyTextField extends flash.display.MovieClip{

	private var text_field : TextField;
	private var text_format : TextFormat;
	private var text_font : String;
	private var text_size : Int;
	private var text_color : Int;
	private var text : String;

	
	private function initTextFormat(){
		text_format = new TextFormat();
		text_format.font = text_font;
    text_format.size = text_size;
    text_format.color = text_color;
	}
	
	private function initTextField(){
		var text_field = new TextField();
		text_field.defaultTextFormat = text_format;
		text_field.text = text;
		text_field.x = x;
		text_field.y = y;
		flash.Lib.current.addChild(text_field);
	}
	
	public function new(){
		super();
		text_font = "Helvetica";
		text_size = 12;
		text_color = 0x000000;
		initTextFormat();
		text = "Default";
		initTextField();	
	}
}

class MyTextField2D extends TextField{

	private var text_format : TextFormat;			
	
	public static var LEFT : TextFormatAlign = TextFormatAlign.LEFT;
	public static var RIGHT : TextFormatAlign = TextFormatAlign.RIGHT;
	public static var CENTER : TextFormatAlign = TextFormatAlign.CENTER;
	public static var JUSTIFY : TextFormatAlign = TextFormatAlign.JUSTIFY;	

	public function new(?text : String, ?font : String, ?size : Int, ?color : Int){
		super();
		text_format = new TextFormat();
		text_format.font = (font == null) ? "Helvetica" : font;
		text_format.size = (size == null) ? 16 : size;		
		text_format.color = (color == null) ? 0x000000 : color;	
 		this.defaultTextFormat = text_format;
		this.text = "Default 2D";
	}
	
	public function setFont(font : String) : Void{
		text_format.font = font;
		this.setTextFormat(text_format);
	}
	
	public function getFont() : String{
		return text_format.font;
	}
	
	public function setSize(size : Float) : Void{
		text_format.size = size;
		this.setTextFormat(text_format);
	}
	
	public function getSize() : Float {
		return text_format.size;
	}
	
	public function setColor(color : Int) : Void{
		text_format.color = color;
		this.setTextFormat(text_format);
	}
	
	public function getColor() : Int {
		return text_format.color;
	}
	
	public function setBold(boolean : Bool) : Void {
		text_format.bold = boolean;
		this.setTextFormat(text_format);
	}
	
	public function isBold() : Bool{
		return text_format.bold;
	}
	
	public function setItalic (boolean : Bool) : Void{
		text_format.italic = boolean;
		this.setTextFormat(text_format);
	}
	
	public function isItalic() : Bool{
		return text_format.italic;
	}
	
	public function setUnderline(boolean : Bool) : Void{
		text_format.underline = boolean;
	}

	public function isUnderline() : Bool{
		return text_format.underline;
	}

	public function setAlign(align : TextFormatAlign) : Void {
		text_format.align = align;
		this.setTextFormat(text_format);
	}
	
	public function getAlign() : TextFormatAlign{
		return text_format.align;
	}
	
	public function setIndent(indentation : Float) : Void{
		text_format.indent = indentation;
		this.setTextFormat(text_format);
	}
	
	public function getIndent() : Float {
		return text_format.indent;
	}
	
	public function setURL(url : String) : Void{
		text_format.url = url;
		this.setTextFormat(text_format);
	}
	
	public function getURL() : String{
		return text_format.url;
	}
	
	public function setLeftMargin(margin : Float) : Void{
		text_format.leftMargin;
		this.setTextFormat(text_format);
	}
	
	public function getLeftMargin() : Float{
		return text_format.leftMargin;
	}
	
	public function setRightMargin(margin : Float) : Void{
		text_format.rightMargin;
		this.setTextFormat(text_format);
	}
	
	public function getRightMargin() : Float{
		return text_format.rightMargin;
	}
	
	public function setLetterSpacing(spacing : Float) : Void{
		text_format.letterSpacing = spacing;
		this.setTextFormat(text_format);
	}

	public function getLetterSpacing() : Float{
		return text_format.letterSpacing;
	}
	
	public function setLeading(leading : Float) : Void{
		text_format.leading = leading;
		this.setTextFormat(text_format);	
	}
	
	public function getLeading() : Float{
		return text_format.leading;
	}
	
	public function setKerning(boolean : Bool) : Void{
		text_format.kerning = boolean;
		this.setTextFormat(text_format);
	}
	
	public function isKerning() : Bool{
		return text_format.kerning;
	}
	
	public function setBullet(boolean : Bool) : Void{
		text_format.bullet = boolean;
		this.setTextFormat(text_format);
	}
	
	public function isBullet() : Bool{
		return text_format.bullet;
	}
	
	public function setBlockIndent(blockIndent : Float) : Void{
		text_format.blockIndent = blockIndent;
		this.setTextFormat(text_format);
	}

	public function getBlockIndex() : Float{
		return text_format.blockIndent;
	}
	
	public function setDisplay(display : TextFormatDisplay) : Void{
		text_format.display = display;
		this.setTextFormat(text_format);
	}
		
	public function getDisplay() : TextFormatDisplay{
		return text_format.display;
	}	
	
	public function setTarget(target : String) : Void{
		text_format.target = target;
		this.setTextFormat(text_format);
	}	
		
	public function getTartet() : String{
		return text_format.target;
	}
	
	public function setTabStops(tabStops : Array<UInt>) : Void{
		text_format.tabStops = tabStops;
		this.setTextFormat(text_format);
	}
	
	public function getTabStops() : Array<UInt>{
		return text_format.tabStops;
	}
	
	public function addAsChild() : Void {
		flash.Lib.current.addChild(this);
	}
} 

class Example_9 {
	
	static function main(){
		var myTextField : MyTextField = new MyTextField();
		
		var myTextField2D : MyTextField2D = new MyTextField2D();
		myTextField2D.x = 20.0;
		myTextField2D.y = 20.0;	
		flash.Lib.current.addChild(myTextField2D);
		haxe.Timer.delay(function(){myTextField2D.setColor(0xAAFF22);}, 2000);
		
	}

 }
