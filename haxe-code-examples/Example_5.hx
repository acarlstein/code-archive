/**
 * @author: Alejandro G. Carlstein R. M.
 */

class HeapSort{
	
	private var data : Array<Int>;
	private var heap_size : Int;
	private inline function leftChild(index : Int) : Int{ return (index << 1) + 1;	}
	private inline function rightChild(index : Int) : Int{ return (index << 1) + 2; }
		
	// Constructor ( ? means that items is optional)
	public function new(?data : Array<Int>){
		this.data = (data == null) ? new Array() : data;	
	}

	public function getData() : Array<Int> {
		return data;
	}
	
	public function setData(data : Array<Int>) : Void {
		this.data = data;
	}
	
	public function sort() : Void{
		if(data.iterator().hasNext()){
			heap_size = data.length;
			buildMaxHeap();
			var index : Int = data.length - 1;
			while (index > -1){
				exchange(0, index);
				maxHeapify(0, --heap_size);
				--index;
			}
		}else{
			trace("There is no data to sort");
		}
	}

	private function buildMaxHeap() : Void{
		var index : Int = data.length >> 1;	
		while (index > -1){
			maxHeapify(index, heap_size);
			--index;
		}
	}

	private function maxHeapify(index : Int, heapSize : Int) : Void{
		var largest : Int = index; 		
		var left : Int = leftChild(index);	
		var right : Int = rightChild(index);	

		if (left < heapSize && data[left] > data[index])
			largest = left;
			
		if (right < heapSize && data[right] > data[largest]) 
			largest = right;

		if (largest != index){
			exchange(index, largest);
			maxHeapify(largest, heapSize);	
		}
	}
	
	private function exchange(index_a : Int, index_b : Int) : Void{
		var temp_value : Int = data[index_a];
		data[index_a] = data[index_b];
		data[index_b] = temp_value;
	}
		
}

class BinarySearch{
	private var heapsort : HeapSort;
	private var data : Array<Int>;
	private function search(value : Int, start_index : Int, end_index : Int){
		var middle_index : Int = (start_index + end_index) >> 1;
		var was_found : Bool = false;
		if(start_index < end_index){
			if(data[middle_index] == value){
				return true;
			}else{
				if(data[middle_index] > value){
					was_found = search(value, start_index, middle_index);
				}else{
					was_found = search(value, middle_index + 1, end_index);
				}
			}
		}
		return was_found;
	}
		
	// Constructor ( ? means that items is optional)
	public function new(?data : Array<Int>){
		this.data = (data == null) ? new Array() : data;	
		if (data != null) setData(data);
	}

	public function getData() : Array<Int> {
		return data;
	}
	
	public function setData(data : Array<Int>) : Void {
		if (data != null){
			heapsort = new HeapSort();
			heapsort.setData(data);
			heapsort.sort();
			data = heapsort.getData();
		}
	}
	
	public function doExist(value : Int) : Bool{
		return search(value, 0, data.length);
	}
	

}

class Example_5 {
	
	static function main(){

		var data : Array<Int> = [3, 7, 5, -1, 6, 1, -3];
		printData(data);

		trace("Binary Search:");
		var binarySearch = new BinarySearch(data);
		trace ("Do 3 exist? " + binarySearch.doExist(3));
		trace ("Do 4 exist? " + binarySearch.doExist(4));
		trace ("Do 7 exist? " + binarySearch.doExist(7));
			
		data = binarySearch.getData();
		printData(data);		
	
	}
	
	private static function printData(data : Array<Int>){
		var iter = data.iterator();
		var index : Int = 0;
		trace("[DATA]");
		while (iter.hasNext()){
			trace("data[" + index++ + "]: " + iter.next());
		}
	}

}
