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

class Example_4 {
	
	static function main(){

		var data : Array<Int> = [3, 7, 5, -1, 6, 1];
		printData(data);

		trace("heapsort:");
		var heapsort = new HeapSort(data);
		trace("sorting...");
		heapsort.sort();		
		data = heapsort.getData();
		printData(data);		

		data = [3, 7, 5, -1, 6, 1];
		printData(data);		
		
		trace("heapsort_2:");
		var heapsort_2 = new HeapSort();		
		trace("sorting without data...");
		heapsort_2.sort();
		trace("sorting with data...");
		heapsort_2.setData(data);
 		heapsort_2.sort();
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
