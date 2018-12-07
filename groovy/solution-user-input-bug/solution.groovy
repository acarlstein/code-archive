import groovy.swing.SwingBuilder;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
  
def sb = new SwingBuilder()
sb.frame(title: 'Action',
         location: [300, 55],
         pack: true,
         show: true,
         defaultCloseOperation: JFrame.EXIT_ON_CLOSE) {
 
    gridLayout(columns: 2, rows: 4)
    label('Continue [ Y/N ]:')
    textField(id: 'input')       
     
    button(text: 'Execute', actionPerformed: {
       execute(input.text, sb)
    })            
}
 
def execute(input, sb){    
    // Your code
    output("User andwer: ${input}", sb) 
    // More of your code
}
 
def output(output, sb){
    def out = (output) ? output : ""
    sb.optionPane().showMessageDialog(null, 
                                      "$output", 
                                      "Executing",
                                      JOptionPane.INFORMATION_MESSAGE)
}