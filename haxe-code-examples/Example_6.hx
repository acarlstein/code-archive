/**
 * @author: Alejandro G. Carlstein R. M.
 */

enum PartitionType{
	DEFAULT;
	RANDOMIZED;
	HOARSE;
	RANDOMIZED_HOARSE;
}

class QuickSort{
	private var data : Array<Int>;
	private var partition_type : PartitionType;

	private function _sort(start_index : Int, end_index : Int) : Void{
		if (start_index < end_index){
			var partition_index : Int = getPartitionIndex(start_index, end_index);
			_sort(start_index, partition_index - 1);
			_sort(partition_index + 1, end_index);
		}
	}
	
	private function getPartitionIndex(start_index : Int, end_index : Int) : Int{
		switch(partition_type){
			case DEFAULT:
				return partition(start_index, end_index);
			case RANDOMIZED:
				return randomPartition(start_index, end_index);	
			case HOARSE:
				return hoarsePartition(start_index, end_index);
			case RANDOMIZED_HOARSE:		
				return randomizedHoarsePartition(start_index, end_index);
		}
		return -1;		
	}

	private function partition(start_index : Int, end_index : Int) : Int{
		var pivot_value : Int = data[end_index];
		var i : Int = start_index - 1;

		var index : Int = start_index;
		while (index < end_index){
			if (data[index] < pivot_value)
				exchange(++i, index);		
			++index;
		}				
		exchange(++i, end_index);
		return i;
	}

	private function randomPartition(start_index : Int, end_index : Int) : Int{
		exchange(getRandom(start_index, end_index), end_index);
		return partition(start_index, end_index); 
	}
	
	private function getRandom(maximum_value : Int, minimum_value : Int) : Int{
		return Math.floor(Math.random() % (maximum_value - minimum_value)) + minimum_value;
	}
	
	private function hoarsePartition(start_index : Int, end_index : Int) : Int{
		var pivot_value : Int = data[start_index];
		var left_index : Int = start_index;
		var right_index : Int = end_index;
		while (left_index < right_index){
			while (data[left_index] < pivot_value)
				--right_index;
			while (data[left_index] > pivot_value)
				++left_index;
			if (left_index < right_index)
				exchange(left_index, right_index);
			else
				break;
			if (data[right_index] == data[left_index]){
				--right_index;
				++left_index;
			}
		}
		return right_index;
	}

	private function randomizedHoarsePartition(start_index : Int, end_index : Int) : Int{
		exchange(getRandom(start_index, end_index), end_index);
		return hoarsePartition(start_index, end_index);
	}	

	private function exchange(index_a : Int, index_b : Int) : Void{
		var temp_value : Int = data[index_a];
		data[index_a] = data[index_b];
		data[index_b] = temp_value;
	}

	// Constructor ( ? means that items is optional)
	public function new(?data : Array<Int>, ?partition_type : PartitionType){
		this.data = (data == null) ? new Array() : data;	
		setPartitionType(partition_type);	
	}

	public function getData() : Array<Int> {
		return data;
	}
	
	public function setData(data : Array<Int>) : Void {
		this.data = data;
	}

	public function sort() : Void{
		if(data.iterator().hasNext())
			_sort(0, data.length - 1);
	}
	
	public function setPartitionType(parition_type : PartitionType) : Void{
		this.partition_type = (partition_type == null) ? DEFAULT : partition_type;	
	}
	
}
 
class Example_6 {
	
	static function main(){

		var data : Array<Int> = [3, 7, 1, -1];
		printData(data);

		trace("QuickSort using regular partition:");
		var quicksort = new QuickSort(data, DEFAULT);
		quicksort.sort();		
		data = quicksort.getData();
		printData(data);		

		data = [3, 7, 1, -1];
		trace("QuickSort using randomized partition:");
		var quicksort_1 = new QuickSort(data, RANDOMIZED);
		quicksort_1.sort();		
		data = quicksort_1.getData();
		printData(data);		

		data = [3, 7, 1, -1];
		trace("QuickSort using Hoarse partition:");
		var quicksort_2 = new QuickSort(data, HOARSE);
		quicksort_2.sort();		
		data = quicksort_2.getData();
		printData(data);		

		data = [3, 7, 1, -1];
		trace("QuickSort using randomized Hoarse partition:");
		var quicksort_3 = new QuickSort(data, RANDOMIZED_HOARSE);
		quicksort_3.sort();		
		data = quicksort_3.getData();
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
